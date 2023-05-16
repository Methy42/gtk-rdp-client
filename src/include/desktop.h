#ifndef DESKTOP_H
#define DESKTOP_H

#include <string>

class Desktop {
public:
    Desktop(const std::string& name, const std::string& ip,
            int port, const std::string& account, const std::string& password,
            const std::string& domain, bool auto_login);
            
    int getId() const;
    std::string getName() const;
    std::string getIP() const;
    int getPort() const;
    std::string getAccount() const;
    std::string getPassword() const;
    std::string getDomain() const;
    bool getAutoLogin() const;

    void setId(int id);
    void setName(const std::string& name);
    void setIP(const std::string& ip);
    void setPort(int port);
    void setAccount(const std::string& account);
    void setPassword(const std::string& password);
    void setDomain(const std::string& domain);
    void setAutoLogin(bool auto_login);

private:
    int id_;
    std::string name_;
    std::string ip_;
    int port_;
    std::string account_;
    std::string password_;
    std::string domain_;
    bool auto_login_;
};

#endif  // DESKTOP_H
