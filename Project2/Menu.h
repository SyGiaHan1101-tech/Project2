#ifndef MENU_H
#define MENU_H

#include <string>
#include "AccountManager.h"
#include "EmployeeManager.h"

class Menu {
public:
    void run();
    void showAdminMenu();
    void showEmployeeMenu(std::string username);

private:
    AccountManager accountManager;
    EmployeeManager employeeManager;
};

#endif
