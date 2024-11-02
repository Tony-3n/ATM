#include "Admin.h"
#include "QuanLyUser.h" // QuanLyUser
#include "User.h" // User

//T
using namespace std;

void displayMainMenu() {
    clearScreen();
    setColor(13);
    cout << "********************" << endl;
    cout << "*";
    setColor(6);
    cout << "     1. Admin     ";
    setColor(13);
    cout <<  "*" << endl;
    setColor(13);
    cout << "*";
    setColor(6);
    cout << "     2. User      ";
    setColor(13);
    cout << "*" << endl;
    setColor(13);
    cout << "*";
    setColor(2);
    cout << "     3. Exit      ";
    setColor(13);
    cout << "*" << endl;
    setColor(13);
    cout << "********************" << endl;
    setColor(14);
    cout << "Nhap lua chon cua ban: ";
}

int main() {
    Admin admin("", "");
    QuanLyUser quanLyUser;
    // Đọc dữ liệu từ file
    quanLyUser.docDuLieuTuFile(); // Đọc thẻ từ từ file
    quanLyUser.docDuLieuUser(); // Đọc dữ liệu người dùng từ file
    while(true) {
        displayMainMenu();
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: {
            if(admin.login()) {
                while(true) {
                    admin.showAdminMenu();
                    int adminChoice;
                    cin >> adminChoice;
                    switch(adminChoice) {
                        case 1: {
                            cout << "DANH SACH TAI KHOAN:" << endl;
                            quanLyUser.hienThiDanhSachUser();
                            Sleep(1000);
                            break;
                        }
                        case 2: {
                            string id, ten, loaiTien;
                            float soDu;
                            cout << "Nhap ID: ";
                            cin >> id;
                            cout << "Nhap Ten: ";
                            cin.ignore();
                            getline(cin, ten);
                            cout << "Nhap So Du: ";
                            cin >> soDu;
                            cout << "Nhap Loai Tien: ";
                            cin >> loaiTien;
                            quanLyUser.themTaiKhoan(id, ten, soDu, loaiTien);
                            break;
                        }
                        case 3: {
                            string id;
                            cout << "Nhap ID tai khoan can xoa: ";
                            cin >> id;
                            quanLyUser.xoaTaiKhoan(id); // Gọi chức năng xóa tài khoản
                            break;
                        }
                        case 4: {
                            string id;
                            cout << "Nhap ID tai khoan can mo khoa: ";
                            cin >> id;
                            admin.unlockAccount(id); // Gọi chức năng mở khóa tài khoản
                            break;
                        }
                        case 5:
                            admin.showAllAdmins();
                            break;
                        case 6: {
                            cout << "Quay lai man hinh Login." << endl;
                            break; 
                        }
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                        }
                        if(adminChoice == 6) {
                            break;
                        }
                    }
                } else {
            return 0;
            }
        break;
    }
        case 2: {
            string id, pin;
            int attempt = 0;
            while (attempt < 3) {
                cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
                cout << "*            DANG NHAP USER             *" << endl;
                cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
                cout << "ID: ";
                cin >> id;
                cout << "Pin: ";
                char ch;
                pin.clear();
                while ((ch = _getch()) != '\r') { // Ẩn mã pin
                    pin.push_back(ch);
                    cout << '*'; // Hiển thị dấu *
                }
                cout << endl;
                if(quanLyUser.dangNhapUser(id, pin)) {
                    bool exitUserMenu = false;
                    while (!exitUserMenu) {
                        cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
                        cout << "* MENU *" << endl;
                        cout << "1. Xem thong tin tai khoan" << endl;
                        cout << "2. Rut tien" << endl;
                        cout << "3. Chuyen tien" << endl;
                        cout << "4. Xem noi dung giao dich" << endl;
                        cout << "5. Doi ma PIN" << endl;
                        cout << "6. Thoat" << endl;
                        cout << "* * * * * * * * * * * * * * * * * * * * *" << endl;
                        cout << "Vui long nhap lua chon: ";
                        int userChoice;
                        cin >> userChoice;
                        switch(userChoice) {
                            case 1:
                                quanLyUser.xemThongTinTaiKhoan(id); 
                                break;
                            case 2: {
                                double soTien;
                                cout << "Nhap so tien can rut: ";
                                cin >> soTien; 
                                quanLyUser.rutTien(id, soTien); 
                                break;
                            }
                            case 3: {
                                string toID;
                                double soTien;
                                cout << "Nhap ID nguoi nhan: ";
                                cin >> toID;
                                cout << "Nhap so tien can chuyen: ";
                                cin >> soTien;
                                quanLyUser.chuyenTien(id, toID, soTien);
                                break;
                            }
                            case 4:
                                quanLyUser.xemNoiDungGiaoDich(id); 
                                break;
                            case 5: {
                                cout << "Nhap ma PIN moi: ";
                                string newPin;
                                cin >> newPin;
                                quanLyUser.doiMaPIN(id, newPin);
                                break;
                            }
                            case 6:
                                exitUserMenu = true;
                                break;
                            default:
                                cout << "Lua chon khong hop le!" << endl;
                                break;
                            }
                        }
                    break; // Thoát vòng đăng nhập
                    }
                else {
                    cout << "Dang nhap that bai. Vui long kiem tra ID va PIN." << endl;
                    attempt++;
                }
                if(attempt >= 3) {
                    cout << "Da nhap sai 3 lan, tai khoan da bi khoa!" << endl;
                    quanLyUser.khoaTaiKhoan(id);
                }
            }
            break;
        }
        case 3: {
            cout << "Exiting the program..." << endl;
            return 0;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
    return 0;
}
