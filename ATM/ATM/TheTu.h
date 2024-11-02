#pragma once
#include <string>
#include <fstream>//

//T
using namespace std;

class TheTu {
private:
    string id;  // Mã ID
    string pin; // Mã PIN
public:
    // Constructor
    TheTu(const string& id, const string& pin) : id(id), pin(pin) {}

    // Getter ID
    string getID() const { return id; }

    // Getter PIN
    string getPIN() const { return pin; }

    // Setter PIN
    void setPIN(const string& newPin) { pin = newPin; }

    // Phương thức lưu thông tin thẻ từ vào file
    void saveToFile(ofstream& outFile) const {
        outFile << id << "," << pin << endl;
    }
};
