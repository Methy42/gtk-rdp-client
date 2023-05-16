#include "rdp_service.h"

void print_buf(uv_buf_t buf)
{
  printf("buf length: %ld\n", buf.len);
  printf("buf content: ");
  for (size_t i = 0; i < buf.len; ++i)
  {
    printf("%02X ", buf.base[i]);
  }
  printf("\n");
}

RDPService::RDPService(){};

int RDPService::status = RDP_SERVICE_INIT_STATUS;

void RDPService::on_connect(uv_connect_t *req, int status)
{
  if (status < 0)
  {
    std::cerr << "Error: Failed to connect: " << uv_strerror(status) << std::endl;
    uv_close(reinterpret_cast<uv_handle_t *>(req->handle), nullptr);
    return;
  }

  std::cout << "Connected to server!" << status << std::endl;

  // 发送RDP连接请求
  uv_buf_t x224_buffer = uv_buf_init((char *)malloc(15), 15);
  X224::create_connect_buffer(&x224_buffer);
  uv_buf_t req_buffer = uv_buf_init((char *)malloc(19), 19);
  TPKT::pack(&req_buffer, &x224_buffer);
  free(x224_buffer.base);
  print_buf(req_buffer);
  uv_write_t *write_req = (uv_write_t *)malloc(sizeof(uv_write_t));
  uv_write(write_req, reinterpret_cast<uv_stream_t *>(req->handle), &req_buffer, 1, [](uv_write_t *req, int status)
           {
        if (status < 0) {
            std::cerr << "Error: Failed to write data: " << uv_strerror(status) << std::endl;
        } else {
            std::cout << "Sent RDP connection request!" << status << std::endl;
        } 
        free(req);
        free(req->write_buffer.base); });

  // 启动流模式的读取操作
  uv_read_start((uv_stream_t *)req->handle, on_alloc, on_read);
}

void RDPService::on_alloc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf)
{
  std::cout << "Allocating buffer..." << std::endl;
  std::cout << "Allocating buffer suggested size: " << suggested_size << std::endl;
  buf->base = new char[suggested_size];
  buf->len = suggested_size;
}

void RDPService::on_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
  std::cout << "Reading data..." << status << std::endl;
  if (nread < 0)
  {
    std::cerr << "Error: Failed to read data: " << uv_strerror(nread) << std::endl;
    uv_close(reinterpret_cast<uv_handle_t *>(stream), nullptr);
    delete[] buf->base;
    return;
  }

  if (nread == 0)
  {
    // 没有数据可读
    std::cerr << "Error: No data can be read: " << uv_strerror(nread) << std::endl;
    delete[] buf->base;
    return;
  }

  if (status == RDP_SERVICE_CONNECT_REQUEST_STATUS)
  {
    std::cout << "Received RDP connection response!" << std::endl;

    uv_buf_t connect_buffer = uv_buf_init((char *)malloc(32), 32);
    connect_buffer.len = 32;
    std::memset(connect_buffer.base, 0, connect_buffer.len);
    std::memcpy(connect_buffer.base, buf->base + 4, connect_buffer.len);

    X224_Connect_Result connwct_result = X224_Connect_Result(&connect_buffer);
    printf("X224_Connect_Result: length=%02X, code=%02X\n", connwct_result.get_length(), connwct_result.get_code());
    printf("X224_Negotiation: type=%02X, flags=%02X, length=%02X, result=%02X\n", connwct_result.get_negotiation()->get_type(), connwct_result.get_negotiation()->get_flags(), connwct_result.get_negotiation()->get_length(), connwct_result.get_negotiation()->get_result());
    free(connect_buffer.base);

    if (connwct_result.get_negotiation()->get_type() == TYPE_RDP_NEG_FAILURE)
    {
      std::cerr << "Failed to connect RDP server. " << std::endl;
      std::cerr << "Error code: " << connwct_result.get_negotiation()->get_result() << std::endl;
      return;
    }

    if (connwct_result.get_negotiation()->get_type() == TYPE_RDP_NEG_RSP)
    {
      printf("%02X == %02X\n", connwct_result.get_negotiation()->get_result(), PROTOCOL_SSL);
      if (connwct_result.get_negotiation()->get_result() == PROTOCOL_SSL)
      {
        std::cout << "Success to connect RDP server. " << std::endl;
        RDPService::getInstance().createTLSConnection();
      }
    }
  }

  delete[] buf->base;
}

int RDPService::createRDPConnection()
{
  status = RDP_SERVICE_INIT_STATUS;

  uv_loop_t *loop = uv_default_loop();

  ConnectionData *conn_data = new ConnectionData();
  uv_tcp_init(loop, &conn_data->socket);

  sockaddr_in dest;
  uv_ip4_addr("10.52.18.252", 3389, &dest);

  uv_tcp_connect(&conn_data->connect_req, &conn_data->socket, reinterpret_cast<const sockaddr *>(&dest), on_connect);

  status = RDP_SERVICE_CONNECT_REQUEST_STATUS;

  uv_run(loop, UV_RUN_DEFAULT);

  std::cout << "Delete connection data" << std::endl;

  delete conn_data;

  return 0;
}

int RDPService::createTLSConnection()
{
  status = RDP_SERVICE_TLS_CONNECT_STATUS;
  tls_client = new TLSClient("10.52.18.252", "3389", "./client.csr", "./client.key", "123456");

  if (!tls_client->connect())
  {
    std::cerr << "Error connecting to server\n";
    return 1;
  }

  const char *request = "GET / HTTP/1.1\r\nHost: www.example.com\r\n\r\n";
  size_t len = strlen(request);
  if (!tls_client->send_request(request, len))
  {
    std::cerr << "Error sending request\n";
    tls_client->disconnect();
    return 1;
  }

  if (!tls_client->receive_response())
  {
    std::cerr << "Error receiving response\n";
    tls_client->disconnect();
    return 1;
  }

  tls_client->disconnect();

  return 0;
}

RDPService &RDPService::getInstance()
{
  return instance;
}

RDPService RDPService::instance;
