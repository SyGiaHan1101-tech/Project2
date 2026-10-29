
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "Employee.h"

class FileManager {
public:
    static bool docDanhSachNhanVien(std::vector<Employee>& ds);
    static bool ghiDanhSachNhanVien(const std::vector<Employee>& ds);
    static bool docHoSoNhanVien(Employee& nv);
    static bool ghiHoSoNhanVien(const Employee& nv);
    static bool xoaHoSoNhanVien(const std::string& username);
    static bool kiemTraUsername(const std::string& username);
};

#endif
