
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
private:
    std::string username;
    std::string password;
    std::string fullName;
    std::string address;
    std::string phone;
    std::string email;
    int mustChangePassword;

public:
    Employee();

    Employee(std::string username, std::string password,
        std::string fullName, std::string address,
        std::string phone, std::string email,
        int mustChangePassword = 1);

    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;
    std::string getAddress() const;
    std::string getPhone() const;
    std::string getEmail() const;
    int getMustChangePassword() const;

    void setUsername(std::string username);
    void setPassword(std::string password);
    void setFullName(std::string fullName);
    void setAddress(std::string address);
    void setPhone(std::string phone);
    void setEmail(std::string email);
    void setMustChangePassword(int status);

    void nhapThongTinCaNhan();
    void hienThiThongTin() const;
};

#endif
