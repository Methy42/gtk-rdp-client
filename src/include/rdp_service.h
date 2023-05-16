#ifndef RDP_SERVICE_H
#define RDP_SERVICE_H

#include <iostream>
#include <cstdint>
#include <cstring>
#include <uv.h>

#include "x224.h"
#include "tpkt.h"
#include "tls_client.h"

const int RDP_SERVICE_INIT_STATUS = 0;
const int RDP_SERVICE_CONNECT_REQUEST_STATUS = 1;
const int RDP_SERVICE_TLS_CONNECT_STATUS = 2;

struct ConnectionData
{
  uv_connect_t connect_req;
  uv_tcp_t socket;
};

class RDPService
{
public:
  RDPService();

  TLSClient *tls_client;

  static int status;

  int createRDPConnection();

  int createTLSConnection();

  static RDPService &getInstance();

private:
  static RDPService instance;

  static void on_connect(uv_connect_t *req, int status);

  static void on_alloc(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);

  static void on_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf);
};

#endif // RDP_SERVICE_H
