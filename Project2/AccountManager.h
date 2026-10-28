
#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <string>
#include "Account.h"

class AccountManager {
public:
    bool adminLogin();
    bool employeeLogin(std::string& username);
    bool isUsernameExists(std::string username);
    bool changePassword(std::string username);
};

#endif
