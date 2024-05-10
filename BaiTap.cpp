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
    if (str.empty()) return "";

    string hoTenDaoNguoc;
    stack<string> hoTen;

    stringstream ss(str);

    string word;
    while (ss >> word) {
        word = string(word.rbegin(), word.rend());
        hoTen.push(word);
    }


    while (!hoTen.empty()) {
        hoTenDaoNguoc += hoTen.top() + " ";
        hoTen.pop();
    }

    // Loại bỏ dấu cách thừa ở cuối chuỗi
    hoTenDaoNguoc.pop_back();

    return hoTenDaoNguoc;
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
    string diem;
    void hienThi() {
        cout << BOLD << RED << "Sinh viên : " << hoLot << " " << ten << RESET << endl;
        cout << BOLD << RED << "Số thứ tự : " << soThuTu << RESET << endl;
        cout << BOLD << RED << "Có mã lớp : " << maLop << RESET << endl;
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
            getline(file, line); // bỏ qua cái tiêu đề stt này nọ 

            while (getline(file, line)) {
                stringstream ss(line);
                SinhVien sv;

                getline(ss, sv.soThuTu, ',');
                getline(ss, sv.maSinhVien, ',');
                getline(ss, sv.hoLot, ',');
                getline(ss, sv.ten, ',');
                getline(ss, sv.maLop, ',');
                getline(ss, sv.diem, ',');
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
                cout << setw(25) << "Mã trùng " << x << endl;
                for (auto& y : data) {
                    if (x == y.maSinhVien) {
                        y.hienThi();
                        cout << "Nhập lại mã sinh viên : ";
                        cin >> y.maSinhVien;
                        y.maSinhVien = chuanHoa(y.maSinhVien);
                    }
                }
            }
            ofstream fileout(filename);
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
    virtual void themSinhVien() = 0;
    virtual void xoaSinhVien() = 0;
    

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

                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(x.hoLot + " " + x.ten) << RESET << endl;
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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(x.hoLot + " " + x.ten) << RESET << endl;
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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(x.hoLot + " " + x.ten) << RESET << endl;
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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(x.hoLot + " " + x.ten) << RESET << endl;
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
            if (stof(x.diem) == s) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << x.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(x.hoLot + " " + x.ten) << RESET << endl;
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
    bool kiemTra(string& s) {
        for (auto& x : mangSinhVien) {
            if (chuanHoa(x.maSinhVien) == chuanHoa(s)) {
                return false;
            }

        }return true;
    }
    void themSinhVien() override {

        int i = mangSinhVien.size()+1;
        SinhVien sv;
        sv.soThuTu = to_string(i++);
        cout << setw(25) << "NHẬP THÔNG TIN SINH VIÊN " << endl;
        cout << " Nhập mã sinh viên :";
        cin.ignore();
        getline(cin, sv.maSinhVien);
        cout << " Nhập họ lót của sinh viên :";
        getline(cin, sv.hoLot);
        cout << " Nhập tên của sinh viên :";
        getline(cin, sv.ten);
        cout << " Nhập mã lớp cho sinh viên :";
        getline(cin, sv.maLop);
        cout << " Nhập điểm cho sinh viên :";
        getline(cin, sv.diem);
        while (!kiemTra(sv.maSinhVien)) {
            cout << "ERROR: Mã sinh viên bạn nhập vào bị trùng vui lòng nhập lại mã cho sinh viên này :";
            getline(cin, sv.maSinhVien);

        }sv.maSinhVien = chuanHoa(sv.maSinhVien);

        mangSinhVien.push_back(sv);

        // cập nhật 
        ofstream fileout("DSSV.csv", ios::app);
        if (!fileout.is_open()) {
            cerr << "Không mở file được " << endl;
            return;
        }
        else {

            fileout << sv.soThuTu << ",";
            fileout << sv.maSinhVien << ",";
            fileout << sv.hoLot << ",";
            fileout << sv.ten << ",";
            fileout << sv.maLop << ",";
            fileout << sv.diem << "\n";

            fileout.close();
        }



    }
    void xoaSinhVien()override {
        string s;
        int soThuTu; // để đánh dấu số thứ tự vừa xóa
        cout << "Vui lòng nhập mã sinh viên bạn muốn xóa: ";
        cin.ignore();
        getline(cin, s);
        bool kiemTra = true;
        for (auto& x : mangSinhVien) {
            if (chuanHoa(x.maSinhVien) == chuanHoa(s)) {
                kiemTra = false;
                soThuTu = stoi(x.soThuTu);
                mangSinhVien.erase(mangSinhVien.begin() + (stoi(x.soThuTu)-1));
                // sau khi xóa ta sẽ cập nhật số thứ tự sau đó
                ofstream fileout("DSSV.csv");
                if (!fileout.is_open()) {
                    cerr << "Không mở được file";
                    return;
                }
                else {
                    fileout << "Stt,Mã SV,Họ lót,Tên,Mã lớp,Điểm\n";
                    for (auto& x : mangSinhVien) {
                        if (stoi(x.soThuTu) > soThuTu) {
                            fileout << to_string(stoi(x.soThuTu) - 1)<<",";
                            x.soThuTu = to_string(stoi(x.soThuTu) - 1);// cập nhật cả cho mảng sinh viên
                        }
                        else {
                            fileout << x.soThuTu << ",";
                        }
                        fileout << x.maSinhVien << ",";
                        fileout << x.hoLot << ",";
                        fileout << x.ten << ",";
                        fileout << x.maLop << ",";
                        fileout << x.diem << "\n";

                    }

                    fileout.close();
                }
            }
        }if (kiemTra == true) {
            cout << "Không tồn tại sinh viên bạn muốn xóa trong danh sách ";
        }
        else {
            cout << "Xóa sinh viên thành công";
        }

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
    FileReader reader;
    vector<SinhVien> mangSinhVien;
    void docFile() override {
        mangSinhVien = reader.readFile("DSSV.csv");


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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
            if (stof(temp->sv.diem) == s) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
    bool kiemTra(string& s) {
        for (auto& x : mangSinhVien) {
            if (chuanHoa(x.maSinhVien) == chuanHoa(s)) {
                return false;
            }

        }return true;
    }
    void themSinhVien() override {

        int i = mangSinhVien.size()+1;
        SinhVien sv;
        sv.soThuTu = to_string(i++);

        cout << setw(25) << "NHẬP THÔNG TIN SINH VIÊN " << endl;

        cout << "Nhập mã sinh viên: ";
        cin.ignore();
        getline(cin, sv.maSinhVien);
        cout << "Nhập họ lót của sinh viên: ";
        getline(cin, sv.hoLot);
        cout << "Nhập tên của sinh viên: ";
        getline(cin, sv.ten);
        cout << "Nhập mã lớp cho sinh viên: ";
        getline(cin, sv.maLop);
        cout << "Nhập điểm cho sinh viên: ";
        cin >> sv.diem;
        cin.ignore();
        while (!kiemTra(sv.maSinhVien)) {
            cout << "ERROR: Mã bạn nhập vào đã bị trùng vui lòng nhập lại :";
            getline(cin, sv.maSinhVien);
        }sv.maSinhVien = chuanHoa(sv.maSinhVien);
        mangSinhVien.push_back(sv);

        // Thêm sinh viên vào DSLKDon
        Node* newNode = new Node{ sv, nullptr };
        if (!head)
            head = newNode;
        else {
            Node* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
        }

        // Cập nhật vào file
        ofstream fileout("DSSV.csv", ios::app);
        if (!fileout.is_open()) {
            cerr << "Không mở file được " << endl;
            return;
        }
        else {
            fileout << sv.soThuTu << ",";
            fileout << sv.maSinhVien << ",";
            fileout << sv.hoLot << ",";
            fileout << sv.ten << ",";
            fileout << sv.maLop << ",";
            fileout << sv.diem << "\n";
            fileout.close();
        }
    }
    void xoaSinhVien() override {
        string s;
        cout << "Vui lòng nhập mã sinh viên bạn muốn xóa: ";
        cin.ignore();
        getline(cin, s);

        Node* current = head;
        Node* previous = nullptr;
        bool kiemTra = false;
        int soThuTu;
        if (current == nullptr) {
            cout << "Danh sách rỗng!";
        }
        while (current != nullptr) {
            
            if (chuanHoa(current->sv.maSinhVien) == chuanHoa(s)) {
                kiemTra = true;
                soThuTu = stoi(current->sv.soThuTu);
                if (previous == nullptr) { // Nếu nút cần xóa là nút đầu tiên
                    head = current->next;
                    delete current;
                    current = head;
                }
                else {
                    previous->next = current->next;
                    delete current;
                    current = previous->next;
                }

                
                ofstream fileout("DSSV.csv");
                if (!fileout.is_open()) {
                    cerr << "Không mở được file";
                    return;
                }
                else {
                    fileout << "Stt,Mã SV,Họ lót,Tên,Mã lớp,Điểm\n";
                    Node* temp = head;
                    
                    while (temp != nullptr) {
                        if (stoi(temp->sv.soThuTu) > soThuTu) {
                            fileout << to_string(stoi(temp->sv.soThuTu) - 1) << ",";
                            temp->sv.soThuTu = to_string(stoi(temp->sv.soThuTu) - 1);
                            
                        }
                        else {
                            fileout << temp->sv.soThuTu<<",";
                        }
                        fileout << temp->sv.maSinhVien << ",";
                        fileout << temp->sv.hoLot << ",";
                        fileout << temp->sv.ten << ",";
                        fileout << temp->sv.maLop << ",";
                        fileout << temp->sv.diem << ",";
                        fileout << "\n";
                        temp = temp->next;
                    }
                    fileout.close();
                }
                break;
            }
            else {
                previous = current;
                current = current->next;
            }
        }

        if (!kiemTra) {
            cout << "Không tồn tại sinh viên bạn muốn xóa trong danh sách" << endl;
        }
        else {
            cout << "Xóa sinh viên thành công";
        }
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
    FileReader reader;
    vector<SinhVien> mangSinhVien;
    void docFile() override {
        mangSinhVien = reader.readFile("DSSV.csv");

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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
            if (stof(temp->sv.diem) == s) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
    bool kiemTra(string& s) {
        for (auto& x : mangSinhVien) {
            if (chuanHoa(x.maSinhVien) == chuanHoa(s)) {
                return false;
            }

        }return true;
    }
    void themSinhVien() override {

        int i = mangSinhVien.size()+1;
        SinhVien sv;
        sv.soThuTu = to_string(i++);

        cout << setw(25) << "NHẬP THÔNG TIN SINH VIÊN " << endl;

        cout << "Nhập mã sinh viên: ";
        cin.ignore();
        getline(cin, sv.maSinhVien);
        cout << "Nhập họ lót của sinh viên: ";
        getline(cin, sv.hoLot);
        cout << "Nhập tên của sinh viên: ";
        getline(cin, sv.ten);
        cout << "Nhập mã lớp cho sinh viên: ";
        getline(cin, sv.maLop);
        cout << "Nhập điểm cho sinh viên: ";
        cin >> sv.diem;
        cin.ignore();
        while (!kiemTra(sv.maSinhVien)) {
            cout << "ERROR: Mã bạn nhập vào đã bị trùng vui lòng nhập lại mã cho sinh viên này: ";
            getline(cin, sv.maSinhVien);
        }sv.maSinhVien = chuanHoa(sv.maSinhVien);
        Node* newNode = new Node{ sv, nullptr };
        if (!head) {
            head = newNode;
            newNode->next = head;
        }
        else {
            Node* temp = head;
            while (temp->next != head)
                temp = temp->next;
            temp->next = newNode;
            newNode->next = head;
        }
        mangSinhVien.push_back(sv);


        // Cập nhật vào file
        ofstream fileout("DSSV.csv", ios::app);
        if (!fileout.is_open()) {
            cerr << "Không mở file được " << endl;
            return;
        }
        else {
            fileout << sv.soThuTu << ",";
            fileout << sv.maSinhVien << ",";
            fileout << sv.hoLot << ",";
            fileout << sv.ten << ",";
            fileout << sv.maLop << ",";
            fileout << sv.diem << "\n";
            fileout.close();
        }
    }
    void xoaSinhVien() override {
        string s;
        cout << "Vui lòng nhập mã sinh viên bạn muốn xóa: ";
        cin.ignore();
        getline(cin, s);

        if (head == nullptr) {
            cout << "Danh sách rỗng!";
            return;
        }

        Node* current = head->next;
        Node* previous = head;

        bool kiemTra = false;
        int soThuTu = 0; // Khởi tạo số thứ tự để lưu lại vị trí của sinh viên cần xóa

        do {
            if (chuanHoa(current->sv.maSinhVien) == chuanHoa(s)) {
                kiemTra = true;
                soThuTu = stoi(current->sv.soThuTu);

                // Nếu nút cần xóa là nút đầu tiên
                if (current == head->next) {
                    previous->next = current->next;

                    // Nếu chỉ còn một nút trong danh sách
                    if (head->next == head) {
                        delete current;
                        head = nullptr;
                        break;
                    }
                    head->next = current->next;
                    delete current;
                }
                else {
                    // Nếu nút cần xóa không phải nút đầu tiên
                    previous->next = current->next;
                    delete current;
                }
                break;
            }
            previous = current;
            current = current->next;
        } while (current != head->next);

        if (!kiemTra) {
            cout << "Không tồn tại sinh viên bạn muốn xóa trong danh sách" << endl;
            return;
        }

        // Cập nhật file
        ofstream fileout("DSSV.csv");
        if (!fileout.is_open()) {
            cerr << "Không mở được file để cập nhật!" << endl;
            return;
        }

        fileout << "Stt,Mã SV,Họ lót,Tên,Mã lớp,Điểm\n";
        Node* temp = head->next;
        do {
            
            if (stoi(temp->sv.soThuTu) > soThuTu) {
                fileout << to_string(stoi(temp->sv.soThuTu) - 1) << ",";
                temp->sv.soThuTu = to_string(stoi(temp->sv.soThuTu) - 1);
            }
            else {
                fileout << temp->sv.soThuTu << ",";
            }
            fileout << temp->sv.maSinhVien << ",";
            fileout << temp->sv.hoLot << ",";
            fileout << temp->sv.ten << ",";
            fileout << temp->sv.maLop << ",";
            fileout << temp->sv.diem << "\n";
            temp = temp->next;
        } while (temp != head->next);

        fileout.close();
        cout << "Xóa sinh viên thành công!" << endl;
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
    Node* tail = nullptr;

public:
    FileReader reader;
    vector<SinhVien> mangSinhVien;
    void docFile() override {
        mangSinhVien = reader.readFile("DSSV.csv");

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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
            if (stof(temp->sv.diem) == s) {
                cout << endl;
                cout << BOLD << RED << "Mã sinh viên : " << temp->sv.maSinhVien << RESET << endl;
                if (c == 'y') {
                    cout << BOLD << RED << "Họ và tên sinh viên " << daoNguocChuoi(temp->sv.hoLot + " " + temp->sv.ten) << RESET << endl;
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
    bool kiemTra(string& s) {
        for (auto& x : mangSinhVien) {
            if (chuanHoa(x.maSinhVien) == chuanHoa(s)) {
                return false;
            }

        }return true;
    }
    
    void themSinhVien() override {

        int i = mangSinhVien.size()+1;
        SinhVien sv;
        sv.soThuTu = to_string(i++);

        cout << setw(25) << "NHẬP THÔNG TIN SINH VIÊN " << endl;

        cout << "Nhập mã sinh viên: ";
        cin.ignore();
        getline(cin, sv.maSinhVien);
        cout << "Nhập họ lót của sinh viên: ";
        getline(cin, sv.hoLot);
        cout << "Nhập tên của sinh viên: ";
        getline(cin, sv.ten);
        cout << "Nhập mã lớp cho sinh viên: ";
        getline(cin, sv.maLop);
        cout << "Nhập điểm cho sinh viên: ";
        cin >> sv.diem;
        cin.ignore();
        while (!kiemTra(sv.maSinhVien)) {
            cout << "ERROR: Mã bạn nhập vào đã bị trùng vui lòng nhập lại mã cho sinh viên này: ";
            getline(cin, sv.maSinhVien);
        }sv.maSinhVien = chuanHoa(sv.maSinhVien);
        mangSinhVien.push_back(sv);


        Node* newNode = new Node{ sv, nullptr, nullptr };
        if (!head) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
            newNode->prev = temp;
        }

        // Cập nhật vào file
        ofstream fileout("DSSV.csv", ios::app);
        if (!fileout.is_open()) {
            cerr << "Không mở file được " << endl;
            return;
        }
        else {
            fileout << sv.soThuTu << ",";
            fileout << sv.maSinhVien << ",";
            fileout << sv.hoLot << ",";
            fileout << sv.ten << ",";
            fileout << sv.maLop << ",";
            fileout << sv.diem << "\n";
            fileout.close();
        }
    }
  

    void xoaSinhVien()override {

    }// dang do dang


   



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
        cout << "4.Xóa sinh viên theo mã " << endl;
        cout << "5.Chọn cách sắp xếp danh sách tăng dần " << endl;
        cout << "0.Thoát " << endl;
        cout << "Nhập lựa chọn của bạn : ";
        cin >> luaChon;

        switch (luaChon) {
        case 1:
            int x;
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
            if (a != nullptr) {
                a->themSinhVien();
                
            }
            else {
                cout << "Vui lòng chọn cách thức lưu trữ danh sách trước khi tìm kiếm." << endl;

            }break;

        case 4:
            if (a != nullptr) {
                a->xoaSinhVien();

            }
            else {
                cout << "Vui lòng chọn cách thức lưu trữ danh sách trước khi tìm kiếm." << endl;

            }break;

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