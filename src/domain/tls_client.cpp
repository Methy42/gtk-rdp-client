#include "tls_client.h"

TLSClient::TLSClient(
    std::string host,
    std::string port,
    std::string cert_file,
    std::string key_file,
    std::string cert_password) : m_host(std::move(host)),
                            m_port(std::move(port)),
                            m_cert_file(std::move(cert_file)),
                            m_key_file(std::move(key_file))
{
    TLSClient::m_cert_password = cert_password;
}

std::string TLSClient::m_cert_password = "";

bool TLSClient::connect()
{
    // 初始化 OpenSSL 库
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();

    // 创建 SSL 上下文对象，并配置相关参数
    m_ctx = SSL_CTX_new(TLS_client_method());
    if (!m_ctx)
    {
        std::cerr << "Error creating SSL context\n";
        ERR_print_errors_fp(stderr);
        return false;
    }

    
    SSL_CTX_set_default_passwd_cb(m_ctx, TLSClient::password_callback);

    // 加载证书和私钥
    if (SSL_CTX_use_certificate_file(m_ctx, m_cert_file.c_str(), SSL_FILETYPE_PEM) <= 0)
    {
        std::cerr << "Error loading client certificate file\n";
        ERR_print_errors_fp(stderr);
        return false;
    }
    if (SSL_CTX_use_PrivateKey_file(m_ctx, m_key_file.c_str(), SSL_FILETYPE_PEM) <= 0)
    {
        std::cerr << "Error loading client private key file\n";
        ERR_print_errors_fp(stderr);
        return false;
    }

    // 创建 BIO 对象，用于连接服务器
    m_bio = BIO_new_connect((m_host + ":" + m_port).c_str());
    if (!m_bio)
    {
        std::cerr << "Error creating connection BIO\n";
        ERR_print_errors_fp(stderr);
        return false;
    }

    // 创建 SSL 对象，并将其绑定到 BIO 上
    m_ssl = SSL_new(m_ctx);
    if (!m_ssl)
    {
        std::cerr << "Error creating SSL object\n";
        ERR_print_errors_fp(stderr);
        return false;
    }
    SSL_set_bio(m_ssl, m_bio, m_bio);

    // 发起 TLS 握手流程，建立安全连接
    int ret = SSL_connect(m_ssl);
    if (ret != 1)
    {
        std::cerr << "Error performing TLS handshake\n";
        ERR_print_errors_fp(stderr);
        return false;
    }

    return true;
}

void TLSClient::disconnect()
{
    // 断开连接，释放资源
    SSL_shutdown(m_ssl);
    SSL_free(m_ssl);
    BIO_free_all(m_bio);
    SSL_CTX_free(m_ctx);

    // 清理 OpenSSL 库的状态
    EVP_cleanup();
    ERR_free_strings();
}

bool TLSClient::send_request(const char *request, size_t len)
{
    int ret = SSL_write(m_ssl, request, len);
    if (ret <= 0)
    {
        std::cerr << "Error sending data\n";
        ERR_print_errors_fp(stderr);
        return false;
    }
    return true;
}

bool TLSClient::receive_response()
{
    char response[1024] = {0};
    int nread = 0;
    while ((nread = SSL_read(m_ssl, response, sizeof(response) - 1)) > 0)
    {
        response[nread] = '\0';
        std::cout << response;
    }
    if (nread < 0)
    {
        std::cerr << "Error receiving data\n";
        ERR_print_errors_fp(stderr);
        return false;
    }
    return true;
}

int TLSClient::password_callback(char *buf, int size, int rwflag, void *userdata)
{
    std::cout << "Enter password: " << TLSClient::m_cert_password << std::endl;
    const char *password = TLSClient::m_cert_password.c_str();  // 替换成您的证书密码
    int len = strlen(password);
    if (len > size) len = size;
    memcpy(buf, password, len);
    return len;
}
