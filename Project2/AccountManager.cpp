#include <cstdio>
#include "AccountManager.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>

using namespace std;

// Nhap mat khau va hien dau *
string inputPassword() {
    string password;
    char ch;

    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password += ch;
            cout << '*';
        }
    }

    cout << '\n';
    return password;
}

bool AccountManager::adminLogin() {
    string username;

    cout << "Nhap username Admin: ";
    cin >> username;

    cout << "Nhap password: ";
    string password = inputPassword();

    ifstream file("Administrators.txt");
    if (!file.is_open()) {
        cout << "Khong mo duoc file Administrators.txt!\n";
        return false;
    }

    string savedUsername, savedPassword;

    while (file >> savedUsername >> savedPassword) {
        if (savedUsername == username && savedPassword == password) {
            cout << "Dang nhap Admin thanh cong!\n";
            return true;
        }
    }

    cout << "Sai username hoac password!\n";
    return false;
}

bool AccountManager::employeeLogin(string& username) {
    string password;
    int attempts = 0;

    while (attempts < 3) {
        cout << "Nhap username nhan vien: ";
        cin >> username;

        cout << "Nhap password: ";
        password = inputPassword();

        ifstream file("Employees.txt");
        if (!file.is_open()) {
            cout << "Khong mo duoc file Employees.txt!\n";
            return false;
        }

        string savedUsername, savedPassword;
        int mustChangePassword;
        bool found = false;

        while (file >> savedUsername >> savedPassword >> mustChangePassword) {
            if (savedUsername == username && savedPassword == password) {
                found = true;
                break;
            }
        }

        file.close();

        if (found) {
            cout << "Dang nhap nhan vien thanh cong!\n";

            if (mustChangePassword == 1) {
                cout << "Ban phai doi mat khau trong lan dang nhap dau tien!\n";
                if (!changePassword(username)) {
                    return false;
                }
            }

            return true;
        }

        attempts++;
        cout << "Sai thong tin dang nhap! Con "
            << 3 - attempts << " lan thu.\n";
    }

    cout << "Ban da nhap sai 3 lan. Thoat!\n";
    return false;
}

bool AccountManager::isUsernameExists(string username) {
    ifstream file("Employees.txt");
    if (!file.is_open()) {
        return false;
    }

    string savedUsername, savedPassword;
    int status;

    while (file >> savedUsername >> savedPassword >> status) {
        if (savedUsername == username) {
            return true;
        }
    }

    return false;
}

bool AccountManager::changePassword(string username) {
    string oldPassword, newPassword, confirmPassword;

    cout << "Nhap mat khau hien tai: ";
    oldPassword = inputPassword();

    ifstream inFile("Employees.txt");
    if (!inFile.is_open()) {
        cout << "Khong mo duoc file Employees.txt!\n";
        return false;
    }

    vector<Account> accounts;
    vector<int> statuses;

    string savedUsername, savedPassword;
    int status;
    bool found = false;

    while (inFile >> savedUsername >> savedPassword >> status) {
        if (savedUsername == username && savedPassword == oldPassword) {
            found = true;
        }

        accounts.push_back(Account(savedUsername, savedPassword));
        statuses.push_back(status);
    }

    inFile.close();

    if (!found) {
        cout << "Mat khau hien tai khong dung!\n";
        return false;
    }

    cout << "Nhap mat khau moi: ";
    newPassword = inputPassword();

    cout << "Nhap lai mat khau moi: ";
    confirmPassword = inputPassword();

    if (newPassword != confirmPassword) {
        cout << "Mat khau nhap lai khong khop!\n";
        return false;
    }

    ofstream outFile("Employees.tmp");

    if (!outFile.is_open())
    {
        cout << "Khong the tao file tam!\n";
        return false;
    }

    for (size_t i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getUsername() == username)
        {
            outFile << accounts[i].getUsername() << " "
                << newPassword << " 0\n";
        }
        else
        {
            outFile << accounts[i].getUsername() << " "
                << accounts[i].getPassword() << " "
                << statuses[i] << "\n";
        }
    }

    outFile.close();

    if (outFile.fail())
    {
        remove("Employees.tmp");
        cout << "Loi ghi file tam!\n";
        return false;
    }

    if (rename("Employees.txt", "Employees.bak") != 0)
    {
        remove("Employees.tmp");
        cout << "Khong the sao luu file cu!\n";
        return false;
    }

    if (rename("Employees.tmp", "Employees.txt") != 0)
    {
        rename("Employees.bak", "Employees.txt");
        remove("Employees.tmp");
        cout << "Khong the cap nhat file!\n";
        return false;
    }

    remove("Employees.bak");

    cout << "Doi mat khau thanh cong!\n";
    return true;

    for (size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].getUsername() == username) {
            outFile << accounts[i].getUsername() << " "
                << newPassword << " 0\n";
        }
        else {
            outFile << accounts[i].getUsername() << " "
                << accounts[i].getPassword() << " "
                << statuses[i] << "\n";
        }
    }

    outFile.close();

    if (outFile.fail())
    {
        cout << "Loi khi ghi file Employees.txt!\n";
        return false;
    }

    cout << "Doi mat khau thanh cong!\n";
    return true;
}


