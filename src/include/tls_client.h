#ifndef TLS_CLIENT_H
#define TLS_CLIENT_H

#include <iostream>
#include <string>
#include <functional>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

class TLSClient
{
public:
	TLSClient(std::string host, std::string port,
			  std::string cert_file, std::string key_file, std::string cert_password);
	
	static std::string m_cert_password; // 客户端证书密码
	bool connect();
	void disconnect();
	bool send_request(const char *request, size_t len);
	bool receive_response();

	static int password_callback(char *buf, int size, int rwflag, void *userdata);

private:
	std::string m_host;			 // 服务器主机名
	std::string m_port;			 // 服务器端口号
	std::string m_cert_file;	 // 客户端证书文件路径
	std::string m_key_file;		 // 客户端私钥文件路径
	SSL_CTX *m_ctx = nullptr;	 // SSL 上下文对象
	BIO *m_bio = nullptr;		 // BIO 对象
	SSL *m_ssl = nullptr;		 // SSL 对象
};

#endif // TLS_CLIENT_H