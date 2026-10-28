
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

bool FileManager::docDanhSachNhanVien(vector<Employee>& ds)
{
    ds.clear();

    ifstream file("Employees.txt");

    if (!file.is_open())
    {
        cerr << "Loi: Khong mo duoc Employees.txt!\n";
        return false;
    }

    string username, password;
    int status;

    while (file >> username >> password >> status)
    {
        if (status != 0 && status != 1)
        {
            cerr << "Loi: Trang thai nhan vien khong hop le!\n";
            return false;
        }

        Employee nv(username, password, "", "", "", "", status);

        if (!docHoSoNhanVien(nv))
        {
            cerr << "Loi: Khong doc duoc ho so: "
                << username << ".txt\n";
            cerr << "Da huy thao tac de tranh mat du lieu!\n";
            return false;
        }

        ds.push_back(nv);
    }

    if (!file.eof())
    {
        cerr << "Loi: Du lieu Employees.txt khong hop le!\n";
        return false;
    }

    return true;
}

bool FileManager::ghiDanhSachNhanVien(const vector<Employee>& ds)
{
    ofstream file("Employees.tmp");

    if (!file.is_open())
        return false;

    for (size_t i = 0; i < ds.size(); i++)
    {
        file << ds[i].getUsername() << " "
            << ds[i].getPassword() << " "
            << ds[i].getMustChangePassword() << '\n';
    }

    file.close();

    if (file.fail())
    {
        remove("Employees.tmp");
        return false;
    }

    if (rename("Employees.txt", "Employees.bak") != 0)
    {
        remove("Employees.tmp");
        return false;
    }

    if (rename("Employees.tmp", "Employees.txt") != 0)
    {
        rename("Employees.bak", "Employees.txt");
        remove("Employees.tmp");
        return false;
    }

    remove("Employees.bak");
    return true;
}

bool FileManager::docHoSoNhanVien(Employee& nv)
{
    string filename = nv.getUsername() + ".txt";
    ifstream file(filename);

    if (!file.is_open())
        return false;

    string fullName, address, phone, email;

    if (!getline(file, fullName) ||
        !getline(file, address) ||
        !getline(file, phone) ||
        !getline(file, email))
    {
        file.close();
        return false;
    }

    nv.setFullName(fullName);
    nv.setAddress(address);
    nv.setPhone(phone);
    nv.setEmail(email);

    file.close();
    return true;
}

bool FileManager::ghiHoSoNhanVien(const Employee& nv)
{
    string filename = nv.getUsername() + ".txt";
    ofstream file(filename);

    if (!file.is_open())
        return false;

    file << nv.getFullName() << '\n';
    file << nv.getAddress() << '\n';
    file << nv.getPhone() << '\n';
    file << nv.getEmail() << '\n';

    file.close();
    return !file.fail();
}

bool FileManager::xoaHoSoNhanVien(const string& username)
{
    string filename = username + ".txt";
    ifstream file(filename);

    if (!file.is_open())
        return false;

    file.close();
    return remove(filename.c_str()) == 0;
}

bool FileManager::kiemTraUsername(const string& username)
{
    ifstream file("Employees.txt");

    if (!file.is_open())
        return true;

    string savedUsername, savedPassword;
    int status;

    while (file >> savedUsername >> savedPassword >> status)
    {
        if (savedUsername == username)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
