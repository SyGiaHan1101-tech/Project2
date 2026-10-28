
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    std::string username;
    std::string password;

public:
    Account();
    Account(std::string username, std::string password);

    std::string getUsername() const;
    std::string getPassword() const;

    void setUsername(std::string username);
    void setPassword(std::string password);
};

#endif
