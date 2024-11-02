#pragma once
#include <iostream>//
#include <set>
#include <fstream>//
#include <sstream>//
#include <vector>//
#include <string>
#include <iomanip>//
#include "User.h"
#include "TheTu.h"

using namespace std;

class QuanLyUser {
private:
    vector<User> danhSachUser;
    vector<TheTu> danhSachTheTu;
public:
    QuanLyUser() {
        docDuLieuTuFile();
        docDuLieuUser(); // Doc du lieu nguoi dung tu file
    }
    // N
    vector<User> getDanhSachUser() {
        return danhSachUser;
    }

    //T
    // Kiem tra ID da ton tai trong danh sach nguoi dung
    bool kiemTraIDTrung(const string& id) {
        for(const auto& user: danhSachUser) {
            if(user.getID() == id) return true;
        }
        return false;
    }

    // N
    // Doc du lieu tu file the tu
    void docDuLieuTuFile() {
        ifstream file("TheTu.txt");
        string line;
        while(getline(file, line)) {
            stringstream ss(line);
            string id, pin;
            if(getline(ss, id, ',') && getline(ss, pin)) {
                danhSachTheTu.emplace_back(id, pin);
            }
        }
    }
    //H
    // Đọc dữ liệu người dùng từ file
    void docDuLieuUser() {
        for(const auto& theTu: danhSachTheTu) {
            string id = theTu.getID();
            ifstream file(id + ".txt");
            if(file) {
                string ten;
                double soDu;
                string loaiTien;
                bool isLocked;
                string line;
                // Bỏ qua dòng ID
                getline(file, line); // ID
                getline(file, line); // Ten
                ten = line.substr(line.find(":") + 2); // Lấy tên
                getline(file, line); // So du
                soDu = stof(line.substr(line.find(":") + 2)); // Lấy số dư
                getline(file, line); // Loai tien
                loaiTien = line.substr(line.find(":") + 2); // Lấy loại tiền
                getline(file, line); // Trạng thái khóa
                isLocked = line.substr(line.find(":") + 2) == "1"; // Đọc trạng thái khóa
                // Lấy mã PIN từ danh sách thẻ
                string pin = theTu.getPIN(); // Sử dụng mã PIN từ danh sách thẻ
                // Tạo đối tượng User và thêm vào danh sách
                User user(id, ten, soDu, loaiTien, pin, isLocked);
                danhSachUser.push_back(user);
                // In ra thông tin đã đọc
                cout << "Đã tải người dùng: ID: " << id << ", Tên: " << ten
                    << ", Số dư: " << soDu << ", Loại tiền: " << loaiTien
                    << ", Trạng thái: " << (isLocked ? "Khóa" : "Mở Khóa") << endl;
            }
            else {
                cout << "Không thể mở file: " << id + ".txt" << endl;
            }
        }
    }

    // Hiển thị danh sách tài khoản
    void hienThiDanhSachUser() {
        if(danhSachTheTu.empty()) {
            cout << "Khong co tai khoan nao." << endl;
            return;
        }
        // Sử dụng một tập hợp để theo dõi ID đã hiển thị
        set<string> displayedIDs;
        for(const auto& theTu: danhSachTheTu) {
            string id = theTu.getID();
            // Kiểm tra xem ID đã được hiển thị hay chưa
            if(displayedIDs.find(id) != displayedIDs.end()) {
                continue; // Nếu đã hiển thị, bỏ qua
            }
            ifstream file(id + ".txt");
            if(file) {
                string ten;
                double soDu;
                string loaiTien;
                bool isLocked;
                string line;
                // Bỏ qua dòng ID
                getline(file, line); // ID
                getline(file, line); // Tên
                ten = line.substr(line.find(":") + 2); // Lấy tên
                getline(file, line); // Số dư
                soDu = stof(line.substr(line.find(":") + 2)); // Lấy số dư
                getline(file, line); // Loại tiền
                loaiTien = line.substr(line.find(":") + 2); // Lấy loại tiền
                getline(file, line); // Trạng thái khóa
                isLocked = line.substr(line.find(":") + 2) == "1"; // Đọc trạng thái khóa
                // Hiển thị thông tin đã cập nhật
                cout << "ID: " << id << ", Ten: " << ten
                    << ", So du: " << fixed << setprecision(2) << soDu
                    << ", Loai tien: " << loaiTien
                    << ", Trang thai: " << (isLocked ? "Khoa" : "Mo Khoa") << endl;
                // Thêm ID vào tập hợp đã hiển thị
                displayedIDs.insert(id);
            }
            else {
                cout << "Khong the mo file: " << id + ".txt" << endl;
            }
        }
        system("pause");
    }

    // Cap nhat PIN cho the tu
    void capNhatPIN(const string& id, const string& newPin) {
        for(auto& theTu: danhSachTheTu) {
            if(theTu.getID() == id) {
                theTu.setPIN(newPin);
                cout << "Cap nhat PIN thanh cong!" << endl;
                // Cap nhat lai file TheTu.txt
                ofstream fileTheTu("TheTu.txt");
                for(const auto& card: danhSachTheTu) {
                    card.saveToFile(fileTheTu);
                }
                return;
            }
        }
        cout << "Khong tim thay the tu voi ID: " << id << endl;
    }

    // Xoa tai khoan theo ID
    void xoaTaiKhoan(const string& id) {
        // Tìm và xóa trong danh sách người dùng
        auto itUser = std::remove_if(danhSachUser.begin(), danhSachUser.end(), [&](const User& user) {
            return user.getID() == id;
            });
        // Tìm và xóa trong danh sách thẻ từ
        auto itCard = std::remove_if(danhSachTheTu.begin(), danhSachTheTu.end(), [&](const TheTu& card) {
            return card.getID() == id;
            });
        // Kiểm tra xem có tìm thấy tài khoản và thẻ từ không
        if(itUser != danhSachUser.end() || itCard != danhSachTheTu.end()) {
            // Xóa tài khoản và thẻ từ ra khỏi vector
            danhSachUser.erase(itUser, danhSachUser.end());
            danhSachTheTu.erase(itCard, danhSachTheTu.end());
            cout << "Xóa tài khoản thành công!" << endl;
            Sleep(2000);
            // Xóa file liên quan
            if(remove((id + ".txt").c_str()) != 0) {
                perror("Không thể xóa file");
            }
            else {
                cout << "Đã xóa file: " << id + ".txt" << endl;
            }
            if(remove(("LichSu" + id + ".txt").c_str()) != 0) {
                perror("Không thể xóa file");
            }
            else {
                cout << "Đã xóa file: " << "LichSu" + id + ".txt" << endl;
            }
        }
        else {
            cout << "Không tìm thấy tài khoản với ID: " << id << endl;
        }
    }

    // Mở khóa tài khoản
    void unlockAccount(const string& id) {
        for(auto& user : danhSachUser) {
            if(user.getID() == id) {
                if(user.isAccountLocked()) {
                    user.unlock(); // Mở khóa tài khoản
                    cout << "Mở khóa tài khoản thành công!" << endl;
                    // Cập nhật lại file
                    updateAccountFile(user);
                    return;
                }
                else {
                    cout << "Tài khoản không bị khóa!" << endl;
                    return;
                }
            }
        }
        cout << "Không tìm thấy tài khoản với ID: " << id << endl;
    }

    // Cập nhật thông tin tài khoản vào file
    void updateAccountFile(const User& user) {
        ofstream file(user.getID() + ".txt");
        if(file) {
            file << "ID: " << user.getID() << endl;
            file << "Ten: " << user.getName() << endl;
            file << "So du: " << user.getBalance() << endl;
            file << "Loai tien: " << user.getCurrency() << endl;
            file << "Trang thai: " << (user.isAccountLocked() ? "1" : "0") << endl;
        }
    }

    // Thêm tài khoản mới
    void themTaiKhoan(const string& id, const string& ten, double soDu, const string& loaiTien) {
        // Kiểm tra ID có trùng không
        if(kiemTraIDTrung(id)) {
            cout << "ID đã tồn tại. Không thể thêm tài khoản mới." << endl;
            return;
        }
        // Tạo tài khoản mới với mã PIN mặc định
        string defaultPIN = "123456"; // Mã PIN mặc định
        User user(id, ten, soDu, loaiTien, defaultPIN);
        // Tạo thẻ từ với mã PIN
        TheTu theTu(id, defaultPIN);
        // Thêm tài khoản mới vào danh sách
        danhSachUser.push_back(user);
        danhSachTheTu.push_back(theTu);
        // Lưu thông tin tài khoản vào file
        ofstream fileTaiKhoan(id + ".txt");
        fileTaiKhoan << "ID: " << id << endl;
        fileTaiKhoan << "Teb: " << ten << endl;
        fileTaiKhoan << "So du: " << fixed << setprecision(2) << soDu << endl;
        fileTaiKhoan << "Loai tien: " << loaiTien << endl;
        fileTaiKhoan << "Trang thai: " << false << endl; // Lưu trạng thái khóa
        fileTaiKhoan << "Ma PIN: " << defaultPIN << endl; // Lưu mã PIN
        fileTaiKhoan.close();
        // Tạo file lịch sử giao dịch
        ofstream fileLichSu("LichSu" + id + ".txt");
        fileLichSu << "ID: " << id << endl;
        fileLichSu << "Lich su giao dich:" << endl;
        fileLichSu.close();
        // Cập nhật dữ liệu cho file TheTu.txt
        ofstream fileTheTu("TheTu.txt", ios::app);
        fileTheTu << id << "," << defaultPIN << endl; // Ghi thẻ từ vào file
        fileTheTu.close();
        cout << "Them tai khoan thanh cong!" << endl; // Thông báo thành công
    }

    // Hàm kiểm tra thông tin tài khoản
    void xemThongTinTaiKhoan(const string& id) {
        for (const auto& user : danhSachUser) {
            if (user.getID() == id) {
                cout << "ID: " << user.getID() << ", Ten: " << user.getName()
                    << ", So du: " << fixed << setprecision(2) << user.getBalance()
                    << ", Loai tien: " << user.getCurrency()
                    << ", Trang thai: " << (user.isAccountLocked() ? "Khóa" : "Mở khóa") << endl;
                return;
            }
        }
        cout << "Khong tim thay tai khoan voi ID: " << id << endl;
    }

    // Hàm đăng nhập
    bool dangNhapUser(const string& id, const string& pin) {
        for (const auto& user : danhSachUser) {
            //cout << "Kiểm tra ID: " << user.getID() << ", PIN: " << user.getPIN() << endl; // In ra ID và PIN
            if (user.getID() == id && user.getPIN() == pin) {
                cout << "Dang nhap thanh cong!" << endl;
                return true;
            }
        }
        cout << "ID hoac ma PIN khong chinh xac." << endl;
        return false;
    }

    // Hàm ghi lại giao dịch rút tiền vào file lịch sử
    void ghiLichSuRutTien(const string& id, double soTien) {
        ofstream lichSuFile("LichSu" + id + ".txt", ios::app); // Mở file với chế độ append
        if (lichSuFile) {
            time_t now = time(0);
            tm ltm; // Biến lưu trữ thời gian
            localtime_s(&ltm, &now); // Sử dụng localtime_s

            lichSuFile << "Rut tien: " << soTien << " VND vao "
                << ltm.tm_mday << "/" << 1 + ltm.tm_mon << "/" << 1900 + ltm.tm_year << endl;
        }
        else {
            cout << "Khong the mo file lich su: " << "LichSu" + id + ".txt" << endl;
        }
    }

    // Hàm rút tiền
    void rutTien(const string& id, double soTien) {
        int attempts = 0;
        while(attempts < 3) {
            // Kiểm tra điều kiện nhập số tiền
            if(soTien < 50000) {
                cout << "So tien rut phai >= 50000." << endl;
                attempts++;
                return;
            }
            for (auto& user : danhSachUser) {
                if (user.getID() == id) {
                    if (user.getBalance() - soTien < 50000) {
                        cout << "So du khong du de rut so tien nay(phai giu lai 50000)." << endl;
                        attempts++;
                        return;
                    }
                    if (static_cast<int>(soTien) % 50000 != 0) {
                        cout << "So tien rut phai la boi so cua 50000." << endl;
                        attempts++;
                        return;
                    }
                    // Xác nhận việc rút tiền
                    char confirm;
                    cout << "Ban co chac chan muon rut " << soTien << " VND khong? (y/n): ";
                    cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') {
                        user.setBalance(user.getBalance() - soTien);
                        cout << "Rut tien thanh cong! So du hien tai: " << user.getBalance() << endl;
                        // Cập nhật lại thông tin vào file
                        updateAccountFile(user);
                        // Ghi lại lịch sử giao dịch
                        ghiLichSuRutTien(id, soTien);
                        return; // Thoát hàm
                    }
                    else {
                        cout << "Rut tien bi huy." << endl;
                        return; // Thoát hàm
                    }
                }
            }
            cout << "Khong tim thay tai khoan voi ID: " << id << endl;
            return;
        }
        cout << "Ban da nhap sai qua 3 lan. Tu dong thoat." << endl;
    }

    //N
    // Hàm ghi lại lịch sử giao dịch chuyển tiền
    void ghiLichSuChuyenTien(const string& fromID, const string& toID, const string& toName, double soTien) {
        ofstream lichSuFile("LichSu" + fromID + ".txt", ios::app);
        if (lichSuFile) {
            // Lấy thời gian hiện tại
            time_t now = time(0);
            tm localTime;
            localtime_s(&localTime, &now);
            lichSuFile << "Chuyen tien: " << soTien << " VND den tai khoan " << toID
                << " (" << toName << ") vao " << localTime.tm_mday << "/"
                << localTime.tm_mon + 1 << "/" << localTime.tm_year + 1900 << endl;
            lichSuFile.close();
        }
        else {
            cout << "Khong the ghi lich su giao dich." << endl;
        }
    }

    // N
    // Hàm chuyển tiền
    void chuyenTien(const string& fromID, const string& toID, double soTien) {
        User* fromUser = nullptr;
        User* toUser = nullptr;
        for(auto& user : danhSachUser) {
            if(user.getID() == fromID) fromUser = &user;
            if(user.getID() == toID) toUser = &user;
        }
        if(fromUser && toUser) {
            if(soTien < 50000 || static_cast<int>(soTien) % 50000 != 0) {
                cout << "So tien chuyen phai >= 50000 va la boi cua 50000." << endl;
                return;
            }
            if(fromUser->getBalance() - soTien < 50000) {
                cout << "So du tai khoan nguon khong du de chuyen tien." << endl;
                return;
            }
            // Xác nhận giao dịch
            char confirm;
            cout << "Ban co chac chan muon chuyen " << soTien << " VND den tai khoan " << toID << "? (y/n): ";
            cin >> confirm;
            if(confirm == 'y' || confirm == 'Y') {
                // Cập nhật số dư
                fromUser->setBalance(fromUser->getBalance() - soTien);
                toUser->setBalance(toUser->getBalance() + soTien);
                // Cập nhật file của tài khoản nguồn và tài khoản đích
                updateAccountFile(*fromUser);
                updateAccountFile(*toUser);
                // Ghi lại lịch sử giao dịch cho tài khoản nguồn
                ghiLichSuChuyenTien(fromID, toID, toUser->getName(), soTien);
                // Ghi lại lịch sử giao dịch cho tài khoản đích
                ghiLichSuNhanTien(toID, fromID, fromUser->getName(), soTien);
                cout << "Chuyen tien thanh cong!" << endl;
            }
            else {
                cout << "Chuyen tien bi huy." << endl;
            }
        }
        else {
            cout << "Khong tim thay tai khoan." << endl;
        }
    }

    // Hạ
    // ghi nhận lịch sử chuyển tiền cho tài khoản đích
    void ghiLichSuNhanTien(const string& toID, const string& fromID, const string& fromName, double soTien) {
        ofstream file("LichSu" + toID + ".txt", ios::app);
        if(file) {
            time_t now = time(0);
            tm localTime;
            localtime_s(&localTime, &now);
            file << "Nhan tien: " << soTien << " VND tu tai khoan " << fromID << " (" << fromName << ") "
                << "vao " << localTime.tm_mday << "/" << localTime.tm_mon + 1 << "/" << localTime.tm_year + 1900 << endl;
            file.close();
        }
        else {
            cout << "Khong the mo file de ghi lich su giao dich nhan tien." << endl;
        }
    }

    // hạ
    // Hàm xem nội dung giao dịch
    void xemNoiDungGiaoDich(const string& id) {
        string tenFile = "LichSu" + id + ".txt"; // Tên file lịch sử giao dịch
        ifstream file(tenFile);
        if(!file) { // Kiểm tra nếu không mở được file
            cout << "Khong the mo file lich su giao dich: " << tenFile << endl;
            return;
        }
        cout << "NOI DUNG GIAO DICH CUA TAI KHOAN " << id << ":" << endl;
        string line;
        bool hasContent = false; // Biến kiểm tra xem file có nội dung hay không
        // Đọc dòng đầu tiên là ID và dòng tiếp theo là tiêu đề "Lịch sử giao dịch:"
        if(getline(file, line)) {
            cout << line << endl; // In dòng chứa ID
            hasContent = true;
        }
        if(getline(file, line)) {
            cout << line << endl; // In dòng chứa "Lịch sử giao dịch:"
            hasContent = true;
        }
        // Đọc và in từng giao dịch
        while(getline(file, line)) {
            cout << line << endl;
            hasContent = true;
        }
        if(!hasContent) {
            cout << "Khong co giao dich nao trong lich su." << endl;
        }
        file.close();
    }

    // Hàm đổi mã PIN
    void doiMaPIN(const string& id, const string& newPin) {
        for (auto& user : danhSachUser) {
            if (user.getID() == id) {
                user.setPIN(newPin);
                cout << "Ma PIN da duoc thay doi!" << endl;
                return;
            }
        }
        cout << "Khong tim thay tai khoan voi ID: " << id << endl;
    }

    // Hàm khóa tài khoản
    void khoaTaiKhoan(const string& id) {
        for(auto& user : danhSachUser) {
            if(user.getID() == id) {
                // Cập nhật trạng thái khóa trong đối tượng User
                user.lock(); // Giả sử phương thức lock() đã được định nghĩa trong lớp User
                // Cập nhật lại file tài khoản với trạng thái khóa
                ofstream file(id + ".txt");
                if(file) {
                    file << "ID: " << user.getID() << endl;
                    file << "Ten: " << user.getName() << endl;
                    file << "So du: " << fixed << setprecision(2) << user.getBalance() << endl;
                    file << "Loai tien: " << user.getCurrency() << endl;
                    file << "Trang thai khoa: 1" << endl; //1: khoa roi a
                    cout << "Khoa tai khoan thanh cong!" << endl;
                }
                else {
                    cout << "Khong the mo file de cap nhat trang thai khoa." << endl;
                }
                return;
            }
        }
        cout << "Khong tim thay tai khoan voi ID: " << id << endl;
    }
};
