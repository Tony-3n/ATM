#pragma once
#include <string>
#include <conio.h>//
#include <fstream>//
#include <sstream>//
#include <iostream>//
#include <Windows.h>//
#include <vector>//
using namespace std;

//T
void setColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
}

//T
void clearScreen() {
#ifdef _WIN32
    system("cls"); // Dành cho Windows
#else
    system("clear"); // Dành cho Linux/Unix
#endif
}

class Admin {
private:
    string username;
    string password;
public:
    Admin(string user = "", string pass = "") : username(user), password(pass) {}
    //T
    bool login() {
        clearScreen();
        setColor(13);
        cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
        setColor(13);
        cout << "*          ";
        setColor(2);
        cout << "DANG NHAP ADMIN              ";
        setColor(13);
        cout << "*" << endl;
        setColor(13);
        cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
        string userInput, passInput;
        int attempts = 0;
        while(attempts < 3) {
            setColor(2);
            cout << "Ten tai khoan: ";
            cin >> userInput;
            cout << "Password: ";
            passInput = "";
            char ch;
            while ((ch = _getch()) != '\r') { // '\r' là ký tự Enter
                if (ch == '\b') { // Xử lý backspace
                    if (!passInput.empty()) {
                        passInput.pop_back();
                        cout << "\b \b";
                    }
                }
                else {
                    passInput += ch;
                    cout << '*';
                }
            }
            cout << endl;
            ifstream file("Admin.txt");
            if (!file) {
                cerr << "Khong the mo file Admin.txt" << endl;
                return false;
            }
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string fileUsername, filePassword;
                if (getline(ss, fileUsername, ',') && getline(ss, filePassword)) {
                    if (fileUsername == userInput && filePassword == passInput) {
                        cout << "Dang nhap thanh cong! Xin chao, " << fileUsername << "!" << endl;
                        username = fileUsername;
                        password = filePassword;
                        return true;
                    }
                }
            }
            attempts++;
            cout << "Nhap sai, vui long nhap lai. (" << attempts << "/3)" << endl;
        }
        cout << "Ban da nhap sai qua 3 lan. Thoat chuong trinh..." << endl;
        return false;
    }

    //N
    // hàm show các chức năng menu
    void showAdminMenu() {
        clearScreen();
        setColor(14); 
        cout << "* * * * * * * * * * * * * * MENU * * * * * * * * * * * * *" << endl;
        setColor(7); 
        cout << "* 1. Xem danh sach tai khoan                             *" << endl;
        cout << "* 2. Them tai khoan                                      *" << endl;
        cout << "* 3. Xoa tai khoan                                       *" << endl;
        cout << "* 4. Mo khoa tai khoan                                   *" << endl;
        cout << "* 5. Hien thi toan bo Admin                              *" << endl; 
        cout << "* 6. Quay lai man hinh Login                             *" << endl;
        setColor(14); 
        cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
        setColor(7); // Trở lại màu mặc định
    }

    //N
    // hàm hiện tat ca admin trong file Admin.txt
    void showAllAdmins() {
        ifstream file("Admin.txt");
        if (!file) {
            cerr << "Khong the mo file Admin.txt" << endl;
            return;
        }
        setColor(13);
        cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "*";
        setColor(2);
        cout << "DANH SACH ADMIN ";
        setColor(13);
        cout <<"*" << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string fileUsername, filePassword;
            if (getline(ss, fileUsername, ',') && getline(ss, filePassword)) {
                cout << "Ten tai khoan: " << fileUsername << ", Password: " << filePassword << endl;
            }
        }
        setColor(13);
        cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
        system("pause");
    }
    //T
    // hàm thêm 1 admin vao Admin.txt
    void addAdmin(const string& username, const string& password) {
        ofstream file("Admin.txt", ios::app);
        if (!file) {
            cerr << "Khong the mo file Admin.txt" << endl;
            return;
        }
        file << username << "," << password << endl;
        cout << "Them tai khoan admin thanh cong!" << endl;
    }
    //T
    // hàm xóa 1 admin trong Admin.txt
    void deleteAdmin(const string& username) {
        ifstream file("Admin.txt");
        ofstream tempFile("temp.txt");
        if(!file || !tempFile) {
            cerr << "Khong the mo file Admin.txt" << endl;
            return;
        }
        string line;
        bool found = false;
        while(getline(file, line)) {
            stringstream ss(line);
            string fileUsername;
            getline(ss, fileUsername, ',');
            if(fileUsername != username) {
                tempFile << line << endl;
            }
            else {
                found = true;
            }
        }
        file.close();
        tempFile.close();
        remove("Admin.txt");
        rename("temp.txt", "Admin.txt");
        if(found) {
            cout << "Xoa tai khoan " << username << " thanh cong!" << endl;
        }
        else {
            cout << "Khong tim thay tai khoan " << username << "!" << endl;
        }
    }

    // hàm mo khoa 1 tai khoan user
    void unlockAccount(const string& id) {
        string filename = id + ".txt"; // Tạo tên file tương ứng với ID
        ifstream file(filename); // Mở file người dùng
        if(!file.is_open()) {
            cerr << "Khong the mo file: " << filename << endl;
            return;
        }
        string line;
        bool found = false;
        vector<string> lines; // Để lưu các dòng trong file
        // Đọc từng dòng trong file
        while(getline(file, line)) {
            if(line.find("ID: ") == 0 && line.substr(4) == id) {
                found = true; // Đã tìm thấy người dùng
            }
            // Kiểm tra trạng thái khóa
            if(line.find("Trang thai: ") == 0) {
                string isLocked = line.substr(10);
                if(isLocked == "1") { // Nếu tài khoản bị khóa
                    line = "Trang thai: 0"; // Thay đổi trạng thái thành không khóa
                }
            }
            lines.push_back(line); // Lưu lại tất cả các dòng
        }
        file.close(); // Đóng file sau khi đọc
        if(found) {
            // Ghi lại thông tin mới vào file
            ofstream outFile(filename);
            if(!outFile.is_open()) {
                cerr << "Khong the mo file de ghi: " << filename << endl;
                return;
            }
            // Ghi lại tất cả thông tin vào file
            for(const auto& l : lines) {
                outFile << l << endl; // Ghi lại từng dòng
            }
            outFile.close(); // Đóng file sau khi ghi
            cout << "Mo khoa tai khoan " << id << " thanh cong!" << endl;
        }
        else {
            cout << "Khong tim thay tai khoan " << id << endl;
        }
    }
};
