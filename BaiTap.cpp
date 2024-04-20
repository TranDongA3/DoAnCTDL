#include<bits/stdc++.h>
#include <set>

using namespace std;

struct SinhVien {
    string soThuTu, maSinhVien, hoLot, ten, maLop;
    float diem;
    void hienThi() {
        cout << "Sinh viên " << hoLot << " " << ten << endl;
        cout << "Số thứ tự " << soThuTu << endl;
        cout << "Có mã lớp " << maLop << endl;
    }
};

class FileReader {
public:
    vector<SinhVien> readFile(const string& filename) {
        vector<SinhVien> data;
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Không mở được file" << endl;
            return data;
        }

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

            data.push_back(sv);
        }

        file.close();
        set<string> uniqueID;
        for (auto& sv : data) {
            while (uniqueID.count(sv.maSinhVien) > 0) {
                cerr << "Lỗi: Mã sinh viên trùng lặp: " << sv.maSinhVien << endl;
                cout << "Vui lòng nhập lại mã sinh viên khác đối với sinh viên sau" << endl;
                sv.hienThi();
                cout << endl;
                cin >> sv.maSinhVien;
            }
            uniqueID.insert(sv.maSinhVien);
        }
        ofstream fileout("DSSV.csv");
        if (!fileout.is_open()) {
            cerr << "Không mở file được " << endl;
            return data;
        }
        else {
            fileout << "Stt,Mã SV,Họ lót,Tên,Mã lớp,Điểm\n"; // Ghi lại dòng tiêu đề

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

        return data;
    }
};

class QuanLiDuLieu {
public:
    virtual void docFile() = 0;
    virtual void hienThi() = 0;
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
            cout << "Số thứ tự của sinh viên: " << sv.soThuTu << endl;
            cout << "Mã sinh viên: " << sv.maSinhVien << endl;
            cout << "Họ lót: " << sv.hoLot << endl;
            cout << "Tên: " << sv.ten << endl;
            cout << "Mã lớp: " << sv.maLop << endl;
            cout << "Điểm: " << sv.diem << endl;
            cout << endl;
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
            cout << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << endl;
            cout << "Mã sinh viên: " << temp->sv.maSinhVien << endl;
            cout << "Họ lót: " << temp->sv.hoLot << endl;
            cout << "Tên: " << temp->sv.ten << endl;
            cout << "Mã lớp: " << temp->sv.maLop << endl;
            cout << "Điểm: " << temp->sv.diem << endl;
            cout << endl;
            temp = temp->next;
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
            cout << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << endl;
            cout << "Mã sinh viên: " << temp->sv.maSinhVien << endl;
            cout << "Họ lót: " << temp->sv.hoLot << endl;
            cout << "Tên: " << temp->sv.ten << endl;
            cout << "Mã lớp: " << temp->sv.maLop << endl;
            cout << "Điểm: " << temp->sv.diem << endl;
            cout << endl;
            temp = temp->next;
        } while (temp != head);

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
            cout << "Số thứ tự của sinh viên: " << temp->sv.soThuTu << endl;
            cout << "Mã sinh viên: " << temp->sv.maSinhVien << endl;
            cout << "Họ lót: " << temp->sv.hoLot << endl;
            cout << "Tên: " << temp->sv.ten << endl;
            cout << "Mã lớp: " << temp->sv.maLop << endl;
            cout << "Điểm: " << temp->sv.diem << endl;
            cout << endl;
            temp = temp->prev;
        }
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
    QuanLiDuLieuMang quanLiDuLieuMang;
    
    quanLiDuLieuMang.docFile();
    quanLiDuLieuMang.hienThi();

    QuanLiDuLieuDSLKDon quanLiDuLieuDSLKDon;
    
    quanLiDuLieuDSLKDon.docFile();
    quanLiDuLieuDSLKDon.hienThi();

    QuanLiDuLieuDSLKVong quanLiDuLieuDSLKVong;
    
    quanLiDuLieuDSLKVong.docFile();
    quanLiDuLieuDSLKVong.hienThi();

    QuanLiDuLieuDSLKKep quanLiDuLieuDSLKKep;
    
    quanLiDuLieuDSLKKep.docFile();
    quanLiDuLieuDSLKKep.hienThi();

    return 0;
}
