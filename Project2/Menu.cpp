#include "Menu.h"
#include "ConsoleColor.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Menu::run() {
    int choice = -1;

    do {
        setColor(14);
        cout << "\n*********************\n";
        cout << "* ";

        setColor(10);
        cout << "QUAN LY NHAN VIEN";

        setColor(14);
        cout << " *\n";
        cout << "*********************\n";
        cout << "1. Dang nhap Admin\n";
        cout << "2. Dang nhap Nhan vien\n";
        cout << "0. Thoat\n";

        setColor(7);
        cout << "Lua chon: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Vui long nhap so!\n";
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            if (accountManager.adminLogin()) {
                showAdminMenu();
            }
            break;

        case 2: {
            string username;
            if (accountManager.employeeLogin(username)) {
                showEmployeeMenu(username);
            }
            break;
        }

        case 0:
            cout << "Tam biet!\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);
}

void Menu::showAdminMenu() {
    int choice = -1;

    do {
        setColor(14);
        cout << "\n* * * * * * * * MENU ADMIN * * * * * * * *\n";
        cout << "1. Quan ly nhan vien\n";
        cout << "0. Dang xuat\n";
        setColor(7);
        cout << "Lua chon: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Vui long nhap so!\n";
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            employeeManager.menuQuanLyNhanVien();
            break;
        case 0:
            cout << "Da dang xuat Admin.\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

void Menu::showEmployeeMenu(string username) {
    int choice = -1;

    do {
        setColor(14);
        cout << "\n* * * * * * MENU EMPLOYEE * * * * * *\n";
        cout << "Tai khoan: " << username << "\n";
        cout << "1. Xem thong tin ca nhan\n";
        cout << "2. Doi mat khau\n";
        cout << "0. Dang xuat\n";
        setColor(7);
        cout << "Lua chon: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Vui long nhap so!\n";
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1: {
            ifstream file(username + ".txt");

            if (!file.is_open()) {
                cout << "Khong mo duoc file thong tin!\n";
                break;
            }

            string hoTen, diaChi, soDienThoai, email;

            if (!getline(file, hoTen) ||
                !getline(file, diaChi) ||
                !getline(file, soDienThoai) ||
                !getline(file, email)) {
                cout << "File thong tin nhan vien bi thieu du lieu!\n";
                file.close();
                break;
            }

            string dongThua;
            if (getline(file, dongThua)) {
                cout << "File thong tin nhan vien co du lieu thua!\n";
                file.close();
                break;
            }

            if (file.bad()) {
                cout << "Loi khi doc file thong tin nhan vien!\n";
                file.close();
                break;
            }

            file.close();

            setColor(14);
            cout << "\n===== THONG TIN CA NHAN =====\n";
            setColor(7);
            cout << "Ho ten: " << hoTen << "\n";
            cout << "Dia chi: " << diaChi << "\n";
            cout << "So dien thoai: " << soDienThoai << "\n";
            cout << "Email: " << email << "\n";
            break;
        }
        case 2:
            accountManager.changePassword(username);
            break;
        case 0:
            cout << "Da dang xuat nhan vien.\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}
