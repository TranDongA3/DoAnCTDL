#include<bits/stdc++.h>
#include <unordered_set>
#include<Windows.h>
#include<chrono>
#define RESET   "\033[0m" // đặt màu của console về mặc định
#define RED     "\033[31m"// đặt màu đỏ
#define BOLD    "\033[1m"// đặt cho chữ in đậm
std::chrono::high_resolution_clock::time_point startTime;

void startTimer() {
    startTime = std::chrono::high_resolution_clock::now(); //set định nghĩa về thời gian 
}

void endTimer() {
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();// set định nghĩa về thời gian 
    std::cout << "Thời gian chạy: " << duration << " milliseconds." << std::endl;
}

using namespace std;
string daoNguocChuoi(const string& str) {
    return string(str.rbegin(), str.rend());
}

string chuanHoa(string s) {
    string result;
    for (char c : s) {
        result.push_back(toupper(c));
    }
    return result;
}



struct SinhVien {
    string soThuTu, maSinhVien, hoLot, ten, maLop;
    float diem;
    void hienThi() {
        cout << BOLD<<RED<<"Sinh viên : " << hoLot << " " << ten <<RESET<< endl;
        cout << BOLD << RED << "Số thứ tự : " << soThuTu <<RESET<< endl;
        cout << BOLD << RED << "Có mã lớp : " << maLop <<RESET<< endl;
        cout << BOLD << RED << "Điểm : " << diem << RESET << endl;
    }
};

class FileReader {
public:
    vector<SinhVien> readFile(const string& filename) {
        vector<SinhVien> data;
        bool kiemTra = true;
        unordered_set<string> uniqueID; // Sử dụng để kiểm tra mã sinh viên trùng lặp
        unordered_set<string> equalID;

        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Không mở được file" << endl;
            return data;
        }
        else {
            string line;
            getline(file, line); // Bỏ qua dòng tiêu đề

            while (getline(file, line)) {
                stringstream ss(line);
                SinhVien sv;

                getline(ss, sv.soThuTu, ',');
                getline(ss, sv.maSinhVien, ',');
                getline(ss, sv.hoLot, ',');
                getline(ss, sv.ten, ',');
                getline(ss, sv.maLop, ',');
                string diem_str;
                getline(ss, diem_str, ',');
                sv.diem = stof(diem_str);


                if (uniqueID.count(sv.maSinhVien) > 0) {
                    kiemTra = false;
                    equalID.insert(sv.maSinhVien);

                }
                uniqueID.insert(sv.maSinhVien);

                

                data.push_back(sv);
            }file.close();
        }
        if (kiemTra == false) {
            cout << setw(25) << "ERROR" << endl;
            cout << "Xin vui lòng nhập lại những sinh viên có mã bị trùng ! " << endl;
            for (auto& x : equalID) {
                cout <<setw(25)<< "Mã trùng " << x << endl;
                for (auto& y : data) {
                    if (x == y.maSinhVien) {
                        y.hienThi();
                        cout << "Nhập lại mã sinh viên : ";
                        cin >> y.maSinhVien;
                    }
                }
            }
            ofstream fileout("DSSV.csv");
            if (!fileout.is_open()) {
                cerr << "Không mở file được " << endl;
                return data;
            }
            else {
                fileout << "Stt,Mã SV,Họ lót,Tên,Mã lớp,Điểm\n";

                for (const auto& sv : data) {
                    fileout << sv.soThuTu << ",";
                    fileout << sv.maSinhVien << ",";
                    fileout << sv.hoLot << ",";
                    fileout << sv.ten << ",";
                    fileout << sv.maLop << ",";
                    fileout << sv.diem << "\n";

                }
                fileout.close();

            }


           
        } return data;
    }
};


class QuanLiDuLieu {
public:
    virtual void docFile() = 0;
    virtual void hienThi() = 0;
    virtual void timKiemTheoMa() = 0;
    virtual void timKiemTheoHo() = 0;
    virtual void timKiemTheoTen() = 0;
    virtual void timKiemTheoLop() = 0;
    virtual void timKiemTheoDiem() = 0;
        
    virtual ~QuanLiDuLieu() {}
};

class QuanLiDuLieuMang : public QuanLiDuLieu {
private:
    vector<SinhVien> mangSinhVien;

public:
    void docFile() override {
        FileReader reader;
        mangSinhVien = reader.readFile("DSSV.csv");
    }

    void hienThi() override {
        cout << "=============== Danh sách dưới dạng mảng================== " << endl;
        for (const auto& sv : mangSinhVien) {
            cout << endl;
            cout << BOLD << RED << "Số thứ tự của sinh viên: " << sv.soThuTu << RESET << endl;
            cout << BOLD << RED << "Mã sinh viên: " << sv.maSinhVien << RESET << endl;
            cout << BOLD << RED << "Họ lót: " << sv.hoLot << RESET << endl;
            cout << BOLD << RED << "Tên: " << sv.ten << RESET << endl;
            cout << BOLD << RED << "Mã lớp: " << sv.maLop << RESET << endl;
            cout << BOLD << RED << "Điểm: " << sv.diem << RESET << endl;

            cout << endl;
        }
    }
    void timKiemTheoMa() override {
        cin.ignore();
        string s;
        cout << "Nhập mã sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        for (auto& x : mangSinhVien) {
            if (chuanHoa(x.maSinhVien) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << x.maSinhVien << RESET << endl;
                if (c == 'y') {
                   
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(x.hoLot) << " " << daoNguocChuoi(x.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << x.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << x.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << x.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    
                    x.hienThi();
                    cout << endl;
                }
            }
        }endTimer();
    }

    void timKiemTheoHo() override {
        cin.ignore();
        string s;
        cout << "Nhập họ của sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        for (auto& x : mangSinhVien) {
            string e;
            stringstream ss(x.hoLot);
            ss >> e;
            if (chuanHoa(e) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << x.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(x.hoLot) << " " << daoNguocChuoi(x.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << x.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << x.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << x.diem << RESET << endl;
                    cout << endl;
                }
                else {
                   
                    x.hienThi();
                    cout << endl;
                }
            }
        }endTimer();
    }

    void timKiemTheoTen() override {
        cin.ignore();
        string s;
        cout << "Nhập tên sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        for (auto& x : mangSinhVien) {
            if (chuanHoa(x.ten) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << x.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(x.hoLot) << " " << daoNguocChuoi(x.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << x.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << x.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << x.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    
                    x.hienThi();
                    cout << endl;
                }
            }
        }endTimer();
    }

    void timKiemTheoLop() override {
        cin.ignore();
        string s;
        cout << "Nhập lớp của sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        for (auto& x : mangSinhVien) {
            if (chuanHoa(x.maLop) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << x.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(x.hoLot) << " " << daoNguocChuoi(x.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << x.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << x.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << x.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    
                    x.hienThi();
                    cout << endl;
                }
            }
        }endTimer();
    }

    void timKiemTheoDiem() override {
        float s;
        cout << "Nhập điểm của sinh viên bạn muốn tìm kiếm : ";
        cin >> s;
        cin.ignore();
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        for (auto& x : mangSinhVien) {
            if (x.diem == s) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << x.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(x.hoLot) << " " << daoNguocChuoi(x.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << x.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << x.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << x.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    
                    x.hienThi();
                    cout << endl;
                }
            }
        }endTimer();
    }

};

class QuanLiDuLieuDSLKDon : public QuanLiDuLieu {
private:
    struct Node {
        SinhVien sv;
        Node* next;
    };

    Node* head = nullptr;

public:
    void docFile() override {
        FileReader reader;
        vector<SinhVien> mangSinhVien = reader.readFile("DSSV.csv");

        for (const auto& sv : mangSinhVien) {
            Node* newNode = new Node{ sv, nullptr };
            if (!head)
                head = newNode;
            else {
                Node* temp = head;
                while (temp->next)
                    temp = temp->next;
                temp->next = newNode;
            }
        }
    }

    void hienThi() override {
        Node* temp = head;
        cout << "=============== Danh sách dưới dạng DSLKDon================ " << endl;
        while (temp) {
            cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
            cout << BOLD << RED << "Mã sinh viên: " << temp->sv.maSinhVien << RESET << endl;
            cout << BOLD << RED << "Họ lót: " << temp->sv.hoLot << RESET << endl;
            cout << BOLD << RED << "Tên: " << temp->sv.ten << RESET << endl;
            cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
            cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;

            cout << endl;
            temp = temp->next;
        }
    }
    void timKiemTheoMa() override {
        cin.ignore();
        string s;
        cout << "Nhập mã sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head;
        while (temp) {
            if (chuanHoa(temp->sv.maSinhVien) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();

                    cout << endl;
                }
            }
            temp = temp->next;
        }
        endTimer();
    }

    void timKiemTheoTen() override {
        cin.ignore();
        string s;
        cout << "Nhập tên sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head;
        while (temp) {
            if (chuanHoa(temp->sv.ten) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();

                    cout << endl;
                }
            }
            temp = temp->next;
        }
        endTimer();
    }

    void timKiemTheoHo() override {
        cin.ignore();
        string s;
        cout << "Nhập họ của sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head;
        while (temp) {
            // Tách lấy họ từ họ và tên của sinh viên
            string ho;
            stringstream ss(temp->sv.hoLot);
            ss >> ho;
            if (chuanHoa(ho) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();

                    cout << endl;
                }
            }
            temp = temp->next;
        }
        endTimer();
    }

    void timKiemTheoLop() override {
        cin.ignore();
        string s;
        cout << "Nhập lớp của sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head;
        while (temp) {
            if (chuanHoa(temp->sv.maLop) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();

                    cout << endl;
                }
            }
            temp = temp->next;
        }
        endTimer();
    }

    void timKiemTheoDiem() override {
        float s;
        cout << "Nhập điểm của sinh viên bạn muốn tìm kiếm : ";
        cin >> s;
        cin.ignore();
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head;
        while (temp) {
            if (temp->sv.diem == s) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();

                    cout << endl;
                }
            }
            temp = temp->next;
        }
        endTimer();
    }



    ~QuanLiDuLieuDSLKDon() {
        Node* temp = head;
        while (temp) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

class QuanLiDuLieuDSLKVong : public QuanLiDuLieu {
private:
    struct Node {
        SinhVien sv;
        Node* next;
    };

    Node* head = nullptr;

public:
    void docFile() override {
        FileReader reader;
        vector<SinhVien> mangSinhVien = reader.readFile("DSSV.csv");

        for (const auto& sv : mangSinhVien) {
            Node* newNode = new Node{ sv, nullptr };
            if (!head) {
                head = newNode;
                head->next = head;
            }
            else {
                newNode->next = head->next;
                head->next = newNode;
                head = newNode;
            }
        }
    }

    void hienThi() override {
        Node* temp = head->next;
        cout << "=============== Danh sách dưới dạng DSLKVong================" << endl;
        do {
            cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
            cout << BOLD << RED << "Mã sinh viên: " << temp->sv.maSinhVien << RESET << endl;
            cout << BOLD << RED << "Họ lót: " << temp->sv.hoLot << RESET << endl;
            cout << BOLD << RED << "Tên: " << temp->sv.ten << RESET << endl;
            cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
            cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;

            cout << endl;
            temp = temp->next;
        } while (temp != head);

    }
    void timKiemTheoMa() override {
        cin.ignore();
        string s;
        cout << "Nhập mã sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head->next;
        do {
            if (chuanHoa(temp->sv.maSinhVien) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();
                }
            }
            temp = temp->next;
        } while (temp != head->next);
        endTimer();
    }

    void timKiemTheoHo() override {
        cin.ignore();
        string s;
        cout << "Nhập họ của sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head->next;
        do {
            // Tách lấy họ từ họ và tên của sinh viên
            string ho;
            stringstream ss(temp->sv.hoLot);
            ss >> ho;
            if (chuanHoa(ho) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();
                }
            }
            temp = temp->next;
        } while (temp != head->next);
        endTimer();
    }

    void timKiemTheoTen() override {
        cin.ignore();
        string s;
        cout << "Nhập tên sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head->next;
        do {
            if (chuanHoa(temp->sv.ten) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();
                }
            }
            temp = temp->next;
        } while (temp != head->next);
        endTimer();
    }

    void timKiemTheoLop() override {
        cin.ignore();
        string s;
        cout << "Nhập lớp của sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head->next;
        do {
            if (chuanHoa(temp->sv.maLop) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();
                }
            }
            temp = temp->next;
        } while (temp != head->next);
        endTimer();
    }

    void timKiemTheoDiem() override {
        float s;
        cout << "Nhập điểm của sinh viên bạn muốn tìm kiếm : ";
        cin >> s;
        cin.ignore();
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head->next;
        do {
            if (temp->sv.diem == s) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();
                }
            }
            temp = temp->next;
        } while (temp != head->next);
        endTimer();
    }


    ~QuanLiDuLieuDSLKVong() {
        if (head) {
            Node* temp = head->next;
            while (temp != head) {
                Node* next = temp->next;
                delete temp;
                temp = next;
            }
            delete head;
        }
    }
};

class QuanLiDuLieuDSLKKep : public QuanLiDuLieu {
private:
    struct Node {
        SinhVien sv;
        Node* next;
        Node* prev;
    };

    Node* head = nullptr;

public:
    void docFile() override {
        FileReader reader;
        vector<SinhVien> mangSinhVien = reader.readFile("DSSV.csv");

        for (const auto& sv : mangSinhVien) {
            Node* newNode = new Node{ sv, nullptr, nullptr };
            if (!head) {
                head = newNode;
            }
            else {
                newNode->prev = head;
                head->next = newNode;
                head = newNode;
            }
        }
    }

    void hienThi() override {
        Node* temp = head;
        cout << "=============== Danh sách dưới dạng DSLKep================== " << endl;
        while (temp) {
            cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
            cout << BOLD << RED << "Mã sinh viên: " << temp->sv.maSinhVien << RESET << endl;
            cout << BOLD << RED << "Họ lót: " << temp->sv.hoLot << RESET << endl;
            cout << BOLD << RED << "Tên: " << temp->sv.ten << RESET << endl;
            cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
            cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;

            cout << endl;
            temp = temp->prev;
        }
    }
    void timKiemTheoMa() override {
        cin.ignore();
        string s;
        cout << "Nhập mã sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head;
        while (temp) {
            if (chuanHoa(temp->sv.maSinhVien) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();
                }
            }
            temp = temp->prev;
        }
        endTimer();
    }

    void timKiemTheoHo() override {
        cin.ignore();
        string s;
        cout << "Nhập họ của sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head;
        while (temp) {
            // Tách lấy họ từ họ và tên của sinh viên
            string ho;
            stringstream ss(temp->sv.hoLot);
            ss >> ho;
            if (chuanHoa(ho) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();
                }
            }
            temp = temp->prev;
        }
        endTimer();
    }

    void timKiemTheoTen() override {
        cin.ignore();
        string s;
        cout << "Nhập tên sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head;
        while (temp) {
            if (chuanHoa(temp->sv.ten) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();
                }
            }
            temp = temp->prev;
        }
        endTimer();
    }

    void timKiemTheoLop() override {
        cin.ignore();
        string s;
        cout << "Nhập lớp của sinh viên bạn muốn tìm kiếm : ";
        getline(cin, s);
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head;
        while (temp) {
            if (chuanHoa(temp->sv.maLop) == chuanHoa(s)) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();
                }
            }
            temp = temp->prev;
        }
        endTimer();
    }

    void timKiemTheoDiem() override {
        float s;
        cout << "Nhập điểm của sinh viên bạn muốn tìm kiếm : ";
        cin >> s;
        cin.ignore();
        cout << "Bạn có muốn đảo ngược họ và tên khi hiển thị không (y/n) ";
        char c;
        cin >> c;
        startTimer();
        Node* temp = head;
        while (temp) {
            if (temp->sv.diem == s) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot) << " " << daoNguocChuoi(temp->sv.ten) << RESET << endl;
                    cout << BOLD << RED << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << RESET << endl;
                    cout << BOLD << RED << "Mã lớp: " << temp->sv.maLop << RESET << endl;
                    cout << BOLD << RED << "Điểm: " << temp->sv.diem << RESET << endl;
                    cout << endl;
                }
                else {
                    temp->sv.hienThi();
                }
            }
            temp = temp->prev;
        }
        endTimer();
    }


    ~QuanLiDuLieuDSLKKep() {
        Node* temp = head;
        while (temp) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

int main() {
    QuanLiDuLieu* a = nullptr; 
    int luaChon = -1; 

    do {
        cout << setw(25) << "MENU" << endl;
        cout << "1.Chọn cách thức lưu trữ danh sách trên " << endl;
        cout << "2.Tìm kiếm các sinh viên dựa theo tiêu chí " << endl;
        cout << "3.Thêm mới sinh viên " << endl;
        cout << "4.Liệt kê " << endl;
        cout << "5.Chọn cách sắp xếp danh sách tăng dần " << endl;
        cout << "0.Thoát " << endl;
        cout << "Nhập lựa chọn của bạn : ";
        cin >> luaChon;

        switch (luaChon) {
        case 1:
            int x; // Khởi tạo biến x để lưu trữ cách thức lưu trữ đã chọn
            cout << "Nhập 1: Theo mảng " << endl;
            cout << "Nhập 2: Theo Danh sách liên kết đơn " << endl;
            cout << "Nhập 3: Theo Danh sách liên kết vòng " << endl;
            cout << "Nhập 4: Theo Danh sách liên kết kép " << endl;

            cin >> x;
            switch (x)
            {
            case 1:
                a = new QuanLiDuLieuMang();
                a->docFile();
                break;
            case 2:
                a = new QuanLiDuLieuDSLKDon();
                a->docFile();
                break;
            case 3:
                a = new QuanLiDuLieuDSLKVong();
                a->docFile();
                break;
            case 4:
                a = new QuanLiDuLieuDSLKKep();
                a->docFile();
                break;
            default:
                cout << "Nhập theo đúng định dạng yêu cầu ";
                break;
            }
            break;

        case 2:
            if (a != nullptr) { // Kiểm tra xem đã chọn cách thức lưu trữ chưa
                cout << "Nhập 1: Theo mã sinh viên " << endl;
                cout << "Nhập 2: Theo họ " << endl;
                cout << "Nhập 3: Theo tên " << endl;
                cout << "Nhập 4: Theo lớp " << endl;
                cout << "Nhập 5: Theo điểm " << endl;

                cin >> x;
                switch (x)
                {
                case 1:
                    a->timKiemTheoMa();
                    break;
                case 2:
                    a->timKiemTheoHo();
                    break;
                case 3:
                    a->timKiemTheoTen();
                    break;
                case 4:
                    a->timKiemTheoLop();
                    break;
                case 5:
                    a->timKiemTheoDiem();
                    break;
                default:
                    cout << "Vui lòng nhập đúng định dạng !" << endl;
                    break;
                }
            }
            else {
                cout << "Vui lòng chọn cách thức lưu trữ danh sách trước khi tìm kiếm." << endl;
            }
            break;

        case 3:
            // Thêm mới sinh viên
            break;

        case 4:
            // Liệt kê danh sách
            break;

        case 5:
            // Sắp xếp danh sách
            break;
        case 0:
            cout << "Hẹn gặp lại !";
            break;
        default:
            cout << "Vui lòng nhập đúng định dạng !" << endl;
            break;
        }
        
    } while (luaChon != 0);

    delete a; // Giải phóng bộ nhớ trước khi kết thúc chương trình

    return 0;
}


