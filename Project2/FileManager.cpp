#include <filesystem>
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
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

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        string username, password;
        int status;
        string duLieuThua;

        istringstream iss(line);

        if (!(iss >> username >> password >> status) ||
            (iss >> duLieuThua))
        {
            cerr << "Loi: Du lieu Employees.txt khong hop le!\n";
            ds.clear();
            return false;
        }

        if (status != 0 && status != 1)
        {
            cerr << "Loi: Trang thai nhan vien khong hop le!\n";
            ds.clear();
            return false;
        }

        Employee nv(username, password, "", "", "", "", status);

        if (!docHoSoNhanVien(nv))
        {
            cerr << "Loi: Khong doc duoc ho so: "
                << username << ".txt\n";
            cerr << "Da huy thao tac de tranh mat du lieu!\n";
            ds.clear();
            return false;
        }

        ds.push_back(nv);
    }

    if (file.bad())
    {
        cerr << "Loi: Khong doc duoc Employees.txt!\n";
        ds.clear();
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

    // Kiem tra file backup cu.
    std::error_code ec;
    bool backupTonTai = std::filesystem::exists("Employees.bak", ec);

    if (ec)
    {
        remove("Employees.tmp");
        cerr << "Loi: Khong the kiem tra Employees.bak!\n";
        return false;
    }

    if (backupTonTai)
    {
        remove("Employees.tmp");
        cerr << "Loi: Employees.bak da ton tai!\n";
        cerr << "Vui long kiem tra file backup truoc khi tiep tuc.\n";
        return false;
    }

    // Chuyen file cu sang file backup.
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
    string fileTam = filename + ".tmp";
    string fileBackup = filename + ".bak";

    // Ghi du lieu vao file tam.
    ofstream file(fileTam, ios::trunc);

    if (!file.is_open())
        return false;

    file << nv.getFullName() << '\n';
    file << nv.getAddress() << '\n';
    file << nv.getPhone() << '\n';
    file << nv.getEmail() << '\n';

    file.close();

    if (file.fail())
    {
        remove(fileTam.c_str());
        return false;
    }

    // Kiem tra file ho so cu co ton tai khong.
    ifstream fileCu(filename);

    if (!fileCu.is_open())
    {
        // Neu chua co file cu, tao file moi tu file tam.
        if (rename(fileTam.c_str(), filename.c_str()) != 0)
        {
            remove(fileTam.c_str());
            return false;
        }

        return true;
    }

    fileCu.close();

    // Kiem tra file backup da ton tai chua.
    ifstream fileKiemTra(fileBackup);

    if (fileKiemTra.is_open())
    {
        fileKiemTra.close();
        remove(fileTam.c_str());
        cerr << "File backup da ton tai!\n";
        return false;
    }

    // Sao luu file cu.
    if (rename(filename.c_str(), fileBackup.c_str()) != 0)
    {
        remove(fileTam.c_str());
        return false;
    }

    // Dua file moi vao vi tri file chinh.
    if (rename(fileTam.c_str(), filename.c_str()) != 0)
    {
        if (rename(fileBackup.c_str(), filename.c_str()) != 0)
            cerr << "CANH BAO: Khong khoi phuc duoc file ho so cu!\n";

        remove(fileTam.c_str());
        return false;
    }

    remove(fileBackup.c_str());

    return true;
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



int FileManager::kiemTraUsername(const string& username)
{
    ifstream file("Employees.txt");

    if (!file.is_open())
    {
        cerr << "Loi: Khong mo duoc Employees.txt!\n";
        return -1;
    }

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        string savedUsername, savedPassword;
        string duLieuThua;
        int status;

        istringstream iss(line);

        if (!(iss >> savedUsername >> savedPassword >> status) ||
            (iss >> duLieuThua))
        {
            cerr << "Loi: Du lieu Employees.txt khong hop le!\n";
            return -1;
        }

        if (status != 0 && status != 1)
        {
            cerr << "Loi: Trang thai nhan vien khong hop le!\n";
            return -1;
        }

        if (savedUsername == username)
            return 1;
    }

    if (file.bad())
    {
        cerr << "Loi: Khong doc duoc Employees.txt!\n";
        return -1;
    }

    return 0;
}

