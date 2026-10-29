#include <fstream>
#include "ConsoleColor.h"
#include "EmployeeManager.h"
#include "TemplateUtils.h"
#include "Employee.h"
#include "FileManager.h"

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cctype>

using namespace std;


static string chuanHoaHoTen(const string& hoTen)
{
    string ketQua;
    bool dauTu = true;

    for (size_t i = 0; i < hoTen.length(); i++)
    {
        unsigned char ch =
            static_cast<unsigned char>(hoTen[i]);

        if (isspace(ch))
        {
            if (!ketQua.empty() && ketQua.back() != ' ')
                ketQua += ' ';

            dauTu = true;
        }
        else
        {
            ketQua += static_cast<char>(
                dauTu ? toupper(ch) : tolower(ch)
                );
            dauTu = false;
        }
    }

    if (!ketQua.empty() && ketQua.back() == ' ')
        ketQua.pop_back();

    return ketQua;
}

static bool soDienThoaiHopLe(const string& sdt)
{
    if (sdt.length() != 10)
        return false;

    for (size_t i = 0; i < sdt.length(); i++)
    {
        if (!isdigit(static_cast<unsigned char>(sdt[i])))
            return false;
    }

    return true;
}

static bool emailHopLe(const string& email)
{
    size_t at = email.find('@');

    if (at == string::npos || at == 0 ||
        at == email.length() - 1)
        return false;

    if (email.find('@', at + 1) != string::npos)
        return false;

    size_t cham = email.find('.', at + 1);

    if (cham == string::npos ||
        cham == at + 1 ||
        cham == email.length() - 1)
        return false;

    for (size_t i = 0; i < email.length(); i++)
    {
        if (isspace(static_cast<unsigned char>(email[i])))
            return false;
    }

    return true;
}


// Username khong duoc co khoang trang hoac ky tu duong dan.
static bool usernameHopLe(const string& username)
{
    if (username.empty())
        return false;

    for (size_t i = 0; i < username.length(); i++)
    {
        unsigned char ch =
            static_cast<unsigned char>(username[i]);

        if (isspace(ch) ||
            username[i] == '/' ||
            username[i] == '\\' ||
            username[i] == '|' ||
            username[i] == ':' ||
            username[i] == '*' ||
            username[i] == '?' ||
            username[i] == '"' ||
            username[i] == '<' ||
            username[i] == '>' ||
            username[i] == '.')
        {
            return false;
        }
    }

    return true;
}


void EmployeeManager::themNhanVien()
{
    vector<Employee> ds;

    if (!FileManager::docDanhSachNhanVien(ds))
    {
        cout << "Loi doc danh sach! Da huy thao tac them.\n";
        return;
    }

    string username;

    setColor(14);
    cout << "\n===== THEM NHAN VIEN =====\n";
    setColor(7);
    cout << "Nhap username: ";
    getline(cin, username);

    if (!usernameHopLe(username))
    {
        cout << "Username khong hop le!\n";
        return;
    }

    if (FileManager::kiemTraUsername(username))
    {
        cout << "Username da ton tai!\n";
        return;
    }

    Employee nv(username, "111111", "", "", "", "", 1);

    cout << "\nNhap thong tin nhan vien:\n";

    string hoTen, diaChi, sdt, email;

    cout << "Nhap ho ten: ";
    getline(cin, hoTen);
    hoTen = chuanHoaHoTen(hoTen);

    while (hoTen.empty())
    {
        cout << "Ho ten khong duoc de trong! Nhap lai: ";
        getline(cin, hoTen);
        hoTen = chuanHoaHoTen(hoTen);
    }

    cout << "Nhap dia chi: ";
    getline(cin, diaChi);
    diaChi = chuanHoaHoTen(diaChi);

    cout << "Nhap so dien thoai: ";
    getline(cin, sdt);

    while (!soDienThoaiHopLe(sdt))
    {
        cout << "So dien thoai phai gom dung 10 chu so! Nhap lai: ";
        getline(cin, sdt);
    }

    cout << "Nhap email: ";
    getline(cin, email);

    while (!emailHopLe(email))
    {
        cout << "Email khong hop le! Nhap lai: ";
        getline(cin, email);
    }

    nv.setFullName(hoTen);
    nv.setAddress(diaChi);
    nv.setPhone(sdt);
    nv.setEmail(email);

    // Kiem tra file ho so da ton tai chua
    ifstream fileHoSo(username + ".txt");
    if (fileHoSo.is_open())
    {
        fileHoSo.close();
        cout << "File ho so da ton tai! Khong the them nhan vien.\n";
        return;
    }

    if (!FileManager::ghiHoSoNhanVien(nv))
    {
        cout << "Khong tao duoc file ho so!\n";
        return;
    }

    ds.push_back(nv);

    if (!FileManager::ghiDanhSachNhanVien(ds))
    {
        FileManager::xoaHoSoNhanVien(username);
        cout << "Khong ghi duoc Employees.txt!\n";
        return;
    }

    cout << "Them nhan vien thanh cong!\n";
    cout << "Mat khau mac dinh: 111111\n";
}


void EmployeeManager::xoaNhanVien()
{
    vector<Employee> ds;

    if (!FileManager::docDanhSachNhanVien(ds))
    {
        cout << "Loi doc danh sach! Da huy thao tac.\n";
        return;
    }
    if (ds.empty())
    {
        cout << "Danh sach rong hoac co loi doc file!\n";
        return;
    }
    string username;

    setColor(14);
    cout << "\n===== XOA NHAN VIEN =====\n";
    setColor(7);
    cout << "Nhap username can xoa: ";
    getline(cin, username);

    int index = -1;

    for (size_t i = 0; i < ds.size(); i++)
    {
        if (ds[i].getUsername() == username)
        {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1)
    {
        cout << "Khong tim thay nhan vien!\n";
        return;
    }

    cout << "\nThong tin nhan vien:\n";
    ds[index].hienThiThongTin();

    char choice;
    cout << "Ban co chac chan muon xoa? (Y/N): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice != 'Y' && choice != 'y')
    {
        cout << "Da huy thao tac xoa.\n";
        return;
    }

    // Luu danh sach cu de khoi phuc neu xoa ho so that bai.
    vector<Employee> dsCu = ds;

    ds.erase(ds.begin() + index);

    if (!FileManager::ghiDanhSachNhanVien(ds))
    {
        cout << "Khong cap nhat duoc Employees.txt!\n";
        return;
    }


    if (!FileManager::xoaHoSoNhanVien(username))
    {
        if (FileManager::ghiDanhSachNhanVien(dsCu))
        {
            cout << "Khong xoa duoc file ho so.\n";
            cout << "Danh sach nhan vien da duoc khoi phuc.\n";
        }
        else
        {
            cout << "Khong xoa duoc file ho so.\n";
            cout << "Canh bao: Khong khoi phuc duoc danh sach!\n";
        }

        return;
    }


    cout << "Xoa nhan vien thanh cong!\n";
}

void EmployeeManager::timNhanVien()
{
    vector<Employee> ds;

    if (!FileManager::docDanhSachNhanVien(ds))
    {
        cout << "Loi doc danh sach! Da huy thao tac.\n";
        return;
    }

    string username;

    setColor(14);
    cout << "\n===== TIM NHAN VIEN =====\n";
    setColor(7);
    cout << "Nhap username can tim: ";
    getline(cin, username);

    for (size_t i = 0; i < ds.size(); i++)
    {
        if (ds[i].getUsername() == username)
        {
            ds[i].hienThiThongTin();
            return;
        }
    }

    cout << "Khong tim thay nhan vien!\n";
}

void EmployeeManager::capNhatNhanVien()
{
    vector<Employee> ds;

    if (!FileManager::docDanhSachNhanVien(ds))
    {
        cout << "Loi doc danh sach! Da huy thao tac.\n";
        return;
    }
    if (ds.empty())
    {
        cout << "Danh sach rong hoac co loi doc file!\n";
        return;
    }
    string username;

    setColor(14);
    cout << "\n===== CAP NHAT NHAN VIEN =====\n";
    setColor(7);
    cout << "Nhap username can cap nhat: ";
    getline(cin, username);

    int index = -1;

    for (size_t i = 0; i < ds.size(); i++)
    {
        if (ds[i].getUsername() == username)
        {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1)
    {
        cout << "Khong tim thay nhan vien!\n";
        return;
    }

    Employee nv = ds[index];
    int choice = -1;

    do
    {
        setColor(14);
        cout << "\n===== CHON THONG TIN CAN CAP NHAT =====\n";
        cout << "1. Ho va ten\n";
        cout << "2. Dia chi\n";
        cout << "3. So dien thoai\n";
        cout << "4. Email\n";
        cout << "0. Luu va quay lai\n";

        setColor(7);
        cout << "Lua chon: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n');
            cout << "Vui long nhap so!\n";
            choice = -1;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string value;


        switch (choice)
        {
        case 1:
            cout << "Nhap ho ten moi: ";
            getline(cin, value);
            value = chuanHoaHoTen(value);

            while (value.empty())
            {
                cout << "Ho ten khong duoc de trong! Nhap lai: ";
                getline(cin, value);
                value = chuanHoaHoTen(value);
            }

            nv.setFullName(value);
            break;

        case 2:
            cout << "Nhap dia chi moi: ";
            getline(cin, value);
            value = chuanHoaHoTen(value);

            while (value.empty())
            {
                cout << "Dia chi khong duoc de trong! Nhap lai: ";
                getline(cin, value);
                value = chuanHoaHoTen(value);
            }

            nv.setAddress(value);
            break;

        case 3:
            cout << "Nhap so dien thoai moi: ";
            getline(cin, value);

            while (!soDienThoaiHopLe(value))
            {
                cout << "So dien thoai phai gom dung 10 chu so! Nhap lai: ";
                getline(cin, value);
            }

            nv.setPhone(value);
            break;

        case 4:
            cout << "Nhap email moi: ";
            getline(cin, value);

            while (!emailHopLe(value))
            {
                cout << "Email khong hop le! Nhap lai: ";
                getline(cin, value);
            }

            nv.setEmail(value);
            break;

        case 0:
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }


    } while (choice != 0);

    if (FileManager::ghiHoSoNhanVien(nv))
        cout << "Cap nhat nhan vien thanh cong!\n";
    else
        cout << "Khong ghi duoc file ho so!\n";
}

void EmployeeManager::hienThiDanhSach()
{
    vector<Employee> ds;

    if (!FileManager::docDanhSachNhanVien(ds))
    {
        cout << "Loi doc danh sach! Da huy thao tac.\n";
        return;
    }

    sapXepTheoUsername(ds);

    setColor(14);
    cout << "\n===== DANH SACH NHAN VIEN =====\n";
    setColor(7);

    if (ds.empty())
    {
        cout << "Danh sach nhan vien rong.\n";
        return;
    }

    for (size_t i = 0; i < ds.size(); i++)
    {
        cout << "\nNhan vien thu " << i + 1 << ":\n";
        ds[i].hienThiThongTin();
        cout << "-----------------------------\n";
    }
}

void EmployeeManager::menuQuanLyNhanVien()
{
    int choice;

    do
    {
        setColor(14);
        cout << "\n*********************\n";
        cout << "* ";

        setColor(10);
        cout << "   MENU ADMIN   ";

        setColor(14);
        cout << "  *\n";
        cout << "*********************\n";
        cout << "1. Them Employee\n";
        cout << "2. Xoa Employee\n";
        cout << "3. Tim Employee\n";
        cout << "4. Cap nhat Employee\n";
        cout << "5. Hien thi thong tin Employee\n";
        cout << "6. Thoat!\n";

        setColor(7);
        cout << "Lua chon: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n');
            cout << "Vui long nhap so!\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            themNhanVien();
            break;

        case 2:
            xoaNhanVien();
            break;

        case 3:
            timNhanVien();
            break;

        case 4:
            capNhatNhanVien();
            break;

        case 5:
            hienThiDanhSach();
            break;

        case 6:
            cout << "Thoat menu quan ly nhan vien.\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 6);
}
