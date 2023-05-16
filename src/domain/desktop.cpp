#include "desktop.h"

Desktop::Desktop(const std::string& name, const std::string& ip,
                 int port, const std::string& account, const std::string& password,
                 const std::string& domain, bool auto_login)
    : name_(name), ip_(ip), port_(port), account_(account),
      password_(password), domain_(domain), auto_login_(auto_login) {}

int Desktop::getId() const {
  return id_;
}

std::string Desktop::getName() const {
    return name_;
}

std::string Desktop::getIP() const {
    return ip_;
}

int Desktop::getPort() const {
    return port_;
}

std::string Desktop::getAccount() const {
    return account_;
}

std::string Desktop::getPassword() const {
    return password_;
}

std::string Desktop::getDomain() const {
    return domain_;
}

bool Desktop::getAutoLogin() const {
    return auto_login_;
}

void Desktop::setId(int id) {
  id_ = id;
}

void Desktop::setName(const std::string& name) {
    name_ = name;
}

void Desktop::setIP(const std::string& ip) {
    ip_ = ip;
}

void Desktop::setPort(int port) {
    port_ = port;
}

void Desktop::setAccount(const std::string& account) {
    account_ = account;
}

void Desktop::setPassword(const std::string& password) {
    password_ = password;
}

void Desktop::setDomain(const std::string& domain) {
    domain_ = domain;
}

void Desktop::setAutoLogin(bool auto_login) {
    auto_login_ = auto_login;
}
