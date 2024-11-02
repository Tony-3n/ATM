#ifndef USER_H // Nếu chưa được định nghĩa
#define USER_H // Định nghĩa USER_H

#include <iostream>//
#include <fstream>//
#include <string>
#include <set>

//T
using namespace std;

class User {
private:
    string id;           // Mã số tài khoản
    string name;         // Tên tài khoản
    double balance;      // Số dư tài khoản
    string currency;     // Loại tiền tệ
    bool isLocked;       // Trạng thái khóa tài khoản
    bool isFirstLogin;   // Trạng thái đăng nhập lần đầu
    string pin;          // Mã PIN của tài khoản

public:
    // Constructor
    User(string id, string name, double balance, string currency, const string& pin, bool locked = false, bool firstLogin = true)
        : id(id), name(name), balance(balance), currency(currency), pin(pin), isLocked(locked), isFirstLogin(firstLogin) {}

    User(const string& id) : id(id), balance(0.0), isLocked(false), isFirstLogin(true) {}

    // Hàm load dữ liệu tài khoản từ file
    bool loadFromFile() {
        string filename = id + ".txt";
        ifstream file(filename);
        if(!file) {
            cerr << "Khong the mo file: " << filename << endl;
            return false;
        }
        getline(file, name);
        file >> balance >> currency;
        file >> isLocked; // Đọc trạng thái khóa từ file
        file >> isFirstLogin; // Đọc trạng thái đăng nhập lần đầu từ file
        file >> pin; // Đọc mã PIN từ file
        file.close();
        return true;
    }

    // Hàm hiển thị thông tin tài khoản
    void displayAccountInfo() const {
        cout << "ID: " << id << endl;
        cout << "Ten tai khoan: " << name << endl;
        cout << "So tien: " << balance << " " << currency << endl;
        cout << "Trang thai: " << (isLocked ? "Khoa" : "Mo Khoa") << endl;
        cout << "Trang thai dang nhap lan dau: " << (isFirstLogin ? "Co" : "Khong") << endl;
    }

    // getter
    string getID() const { return id; }
    string getName() const { return name; }
    double getBalance() const { return balance; }
    string getCurrency() const { return currency; }
    string getPIN() const { return pin; } // Thêm hàm getPIN
    bool isAccountLocked() const { return isLocked; }
    bool isFirstLoginStatus() const { return isFirstLogin; }

    // setter
    void setName(const string& newName) { name = newName; }
    void setBalance(double newBalance) { balance = newBalance; }
    void setCurrency(const string& newCurrency) { currency = newCurrency; }
    void setPIN(const string& newPIN) { pin = newPIN; } 
    void lock() { isLocked = true; }
    void unlock() { isLocked = false; }
    void setFirstLoginStatus(bool status) { isFirstLogin = status; }
};

#endif // USER_H
