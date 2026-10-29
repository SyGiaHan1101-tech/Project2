
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
    // Ghi danh sach moi vao file tam.
    ofstream file("Employees.tmp", ios::trunc);

    if (!file.is_open())
    {
        cerr << "Loi: Khong tao duoc Employees.tmp!\n";
        return false;
    }

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
        cerr << "Loi: Khong ghi duoc du lieu vao file tam!\n";
        return false;
    }

    // Khong ghi de file cu neu file chinh chua ton tai.
    ifstream fileCu("Employees.txt");

    if (!fileCu.is_open())
    {
        remove("Employees.tmp");
        cerr << "Loi: Khong mo duoc Employees.txt!\n";
        return false;
    }

    fileCu.close();

    // Chuyen file cu sang file backup.
    remove("Employees.bak");

    if (rename("Employees.txt", "Employees.bak") != 0)
    {
        remove("Employees.tmp");
        cerr << "Loi: Khong sao luu duoc Employees.txt!\n";
        return false;
    }

    // Dua file moi vao vi tri file chinh.
    if (rename("Employees.tmp", "Employees.txt") != 0)
    {
        if (rename("Employees.bak", "Employees.txt") != 0)
            cerr << "CANH BAO: Khong khoi phuc duoc file cu!\n";

        remove("Employees.tmp");
        cerr << "Loi: Khong cap nhat duoc Employees.txt!\n";
        return false;
    }

    // Chi xoa ban sao sau khi cap nhat thanh cong.
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
        return false;
    }

    // Kiem tra file co du lieu thua hay khong.
    string dongThua;
    if (getline(file, dongThua))
    {
        cerr << "Loi: File ho so co du lieu thua: "
            << filename << '\n';
        return false;
    }

    if (file.bad())
    {
        cerr << "Loi: Khong doc duoc file ho so: "
            << filename << '\n';
        return false;
    }

    nv.setFullName(fullName);
    nv.setAddress(address);
    nv.setPhone(phone);
    nv.setEmail(email);

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
    {
        cerr << "Loi: Khong mo duoc Employees.txt!\n";
        return true;
    }

    string savedUsername, savedPassword;
    int status;

    while (file >> savedUsername >> savedPassword >> status)
    {
        if (status != 0 && status != 1)
        {
            cerr << "Loi: Trang thai nhan vien khong hop le!\n";
            return true;
        }

        if (savedUsername == username)
            return true;
    }

    if (!file.eof())
    {
        cerr << "Loi: Du lieu Employees.txt khong hop le!\n";
        return true;
    }

    return false;
}

