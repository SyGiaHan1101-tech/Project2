#include <cstdio>
#include "AccountManager.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>

using namespace std;

// Nhap mat khau va hien dau *

string inputPassword()
{
    string password;
    int ch;

    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b')
        {
            if (!password.empty())
            {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else if (ch == 0 || ch == 224)
        {
            // Bo qua phim dieu khien nhu mui ten.
            _getch();
        }
        else if (ch >= 32 && ch <= 126)
        {
            password += static_cast<char>(ch);
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


bool AccountManager::employeeLogin(string& username)
{
    int attempts = 0;

    while (attempts < 3)
    {
        cout << "Nhap username nhan vien: ";
        cin >> username;

        ifstream file("Employees.txt");
        if (!file.is_open())
        {
            cout << "Khong mo duoc file Employees.txt!\n";
            return false;
        }

        string savedUsername, savedPassword;
        int status;
        bool usernameExists = false;
        bool dataError = false;
        vector<Account> accounts;
        vector<int> statuses;

        while (file >> savedUsername >> savedPassword >> status)
        {
            if (status != 0 && status != 1)
            {
                dataError = true;
                break;
            }

            accounts.push_back(Account(savedUsername, savedPassword));
            statuses.push_back(status);

            if (savedUsername == username)
            {
                usernameExists = true;
            }
        }

        if (!file.eof())
        {
            dataError = true;
        }

        file.close();

        if (dataError)
        {
            cout << "Du lieu Employees.txt khong hop le!\n";
            return false;
        }

        if (!usernameExists)
        {
            attempts++;
            cout << "Tai khoan khong ton tai!\n";
            cout << "Con " << 3 - attempts << " lan thu.\n";
            continue;
        }

        cout << "Nhap password: ";
        string password = inputPassword();

        bool found = false;
        int accountStatus = 0;

        for (size_t i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].getUsername() == username &&
                accounts[i].getPassword() == password)
            {
                found = true;
                accountStatus = statuses[i];
                break;
            }
        }

        if (found)
        {
            cout << "Dang nhap nhan vien thanh cong!\n";

            if (accountStatus == 1)
            {
                cout << "Ban phai doi mat khau trong lan dang nhap dau tien!\n";

                if (!changePassword(username))
                {
                    return false;
                }
            }

            return true;
        }

        attempts++;
        cout << "Sai mat khau!\n";
        cout << "Con " << 3 - attempts << " lan thu.\n";
    }

    cout << "Ban da nhap sai 3 lan. Thoat!\n";
    return false;
}



bool AccountManager::isUsernameExists(string username) {
    ifstream file("Employees.txt");

    if (!file.is_open()) {
        cout << "Khong mo duoc file Employees.txt!\n";
        return true;
    }

    string savedUsername, savedPassword;
    int status;

    while (file >> savedUsername >> savedPassword >> status) {
        if (savedUsername == username) {
            return true;
        }
    }

    if (!file.eof()) {
        cout << "Du lieu Employees.txt khong hop le!\n";
        return true;
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


    while (inFile >> savedUsername >> savedPassword >> status)
    {
        if (status != 0 && status != 1)
        {
            cout << "Trang thai tai khoan khong hop le!\n";
            inFile.close();
            return false;
        }

        if (savedUsername == username && savedPassword == oldPassword)
        {
            found = true;
        }

        accounts.push_back(Account(savedUsername, savedPassword));
        statuses.push_back(status);
    }

    if (!inFile.eof())
    {
        cout << "Du lieu Employees.txt khong hop le!\n";
        inFile.close();
        return false;
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
        if (accounts[i].getUsername() == username &&
            accounts[i].getPassword() == oldPassword)
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
}


