
#include "Employee.h"
#include <iostream>

using namespace std;

Employee::Employee()
{
    username = "";
    password = "";
    fullName = "";
    address = "";
    phone = "";
    email = "";
    mustChangePassword = 1;
}

Employee::Employee(string username, string password,
    string fullName, string address,
    string phone, string email,
    int mustChangePassword)
{
    this->username = username;
    this->password = password;
    this->fullName = fullName;
    this->address = address;
    this->phone = phone;
    this->email = email;
    this->mustChangePassword = mustChangePassword;
}

string Employee::getUsername() const
{
    return username;
}

string Employee::getPassword() const
{
    return password;
}

string Employee::getFullName() const
{
    return fullName;
}

string Employee::getAddress() const
{
    return address;
}

string Employee::getPhone() const
{
    return phone;
}

string Employee::getEmail() const
{
    return email;
}

int Employee::getMustChangePassword() const
{
    return mustChangePassword;
}

void Employee::setUsername(string username)
{
    this->username = username;
}

void Employee::setPassword(string password)
{
    this->password = password;
}

void Employee::setFullName(string fullName)
{
    this->fullName = fullName;
}

void Employee::setAddress(string address)
{
    this->address = address;
}

void Employee::setPhone(string phone)
{
    this->phone = phone;
}

void Employee::setEmail(string email)
{
    this->email = email;
}

void Employee::setMustChangePassword(int status)
{
    mustChangePassword = status;
}

void Employee::nhapThongTinCaNhan()
{
    cout << "Nhap ho va ten: ";
    getline(cin, fullName);

    cout << "Nhap dia chi: ";
    getline(cin, address);

    cout << "Nhap so dien thoai: ";
    getline(cin, phone);

    cout << "Nhap email: ";
    getline(cin, email);
}

void Employee::hienThiThongTin() const
{
    cout << "Username: " << username << '\n';
    cout << "Ho va ten: " << fullName << '\n';
    cout << "Dia chi: " << address << '\n';
    cout << "So dien thoai: " << phone << '\n';
    cout << "Email: " << email << '\n';
}
