#include "../headers/nhanvien.h"
#include<iostream>
#include<vector>
#include <fstream>


float Staff::TinhLuong(int& SoGioCong, float& TienThuong, float& TienPhat, float& TienUng) {
    float total = (SoGioCong * getBasicSalary()) + TienThuong - TienPhat - TienUng;
    return total;
}

void Staff::ThemNhanVien(string& id, string& name, string& age, string& phoneNum, float& basicSalary) {
    setID(id);
    setName(name);
    setAge(age);
    setPhoneNum(phoneNum);
    setBasicSalary(basicSalary);

    ofstream out(nvPath, ios::app);
    cout << filesystem::absolute(nvPath) << endl;
    if(!out) {
        cout << "Khong mo duoc file!\nThem nhan vien that bai!" << endl;
        return;
    }
    else { 
    out << getID() << "|" << getName() << "|" 
        << getAge() << "|" << getPhoneNum() << "|"
        << getBasicSalary() << endl;
    
    cout << "Da them thanh cong nhan vien " << getName() << endl;
    return;
    }
}

void Staff::XoaNhanVien(string& deleteID) {
    ifstream in(nvPath);
    vector<string> lines; //luu tam bang moi sau khi xoa nhan vien
    string line, id;

    while (getline(in, line)) {
        /* doan nay duyet qua toan bo file */
        size_t pos = line.find('|');
        if(pos != string::npos) { 
            id = line.substr(0, pos);
        }
        else id = line; //cai nay tuong tu nhu ben untils.cpp, qua do xem

        // sau do chi giu lai cac nhan vien co id != id can xoa 
        if(id != deleteID) lines.push_back(line);
    }
    in.close();

    // sau khi luu tam file vo vector thi gio ghi de toan bo file cu
    ofstream out(nvPath, ios::trunc);
    for(auto& l : lines) out << l << endl;
    out.close();
}

void Staff::ChinhSuaThongTin(string id, int action) {
    ifstream in(nvPath);
    string line;
    vector<string> lines;
    bool found = false;
    switch(action) {
        case 1: {
            // sua ten
            string newName;
            cout << "Nhap ten moi: "; cin >> newName;
            setName(newName);
            while (getline(in, line)) {
                vector<string> fields = TrimFields(id, nvPath, line);
                if(fields.empty() && fields[0] == id) {
                    found = true;
                    fields[1] = newName;
                    lines.push_back(LinkedFields(fields));
                }
                lines.push_back(line);
            }
            in.close();

            if(found) {
                ofstream out(nvPath, ios::trunc);
                for(auto& l: lines) out << l << endl;
                out.close();
            }
            break;
        }
        case 2: {
            // sua tuoi
            string newAge;
            cout << "Nhap tuoi moi: "; cin >> newAge;
            setAge(newAge);
            while (getline(in, line)) {
                vector<string> fields = TrimFields(id, nvPath, line);
                if(fields.empty() && fields[0] == id) {
                    found = true;
                    fields[2] = newAge;
                    lines.push_back(LinkedFields(fields));
                }
                lines.push_back(line);
            }
            in.close();

            if(found) {
                ofstream out(nvPath, ios::trunc);
                for(auto& l: lines) out << l << endl;
                out.close();
            }
            break;
        }
        case 3: {
            // sua so dien thoai
            string newPhoneNum;
            cout << "Nhap so dien thoai moi: "; cin >> newPhoneNum;
            setPhoneNum(newPhoneNum);
            while (getline(in, line)) {
                vector<string> fields = TrimFields(id, nvPath, line);
                if(fields.empty() && fields[0] == id) {
                    found = true;
                    fields[3] = newPhoneNum;
                    lines.push_back(LinkedFields(fields));
                }
                lines.push_back(line);
            }
            in.close();

            if(found) {
                ofstream out(nvPath, ios::trunc);
                for(auto& l: lines) out << l << endl;
                out.close();
            }
            break;
        }
        case 4: {
            // sua luong
            float newSalary;
            cout << "Nhap luong moi: "; cin >> newSalary;
            setBasicSalary(newSalary);
            while (getline(in, line)) {
                vector<string> fields = TrimFields(id, nvPath, line);
                if(fields.empty() && fields[0] == id) {
                    found = true;
                    fields[4] = newSalary;
                    lines.push_back(LinkedFields(fields));
                }
                lines.push_back(line);
            }
            in.close();

            if(found) {
                ofstream out(nvPath, ios::trunc);
                for(auto& l: lines) out << l << endl;
                out.close();
            }
            break;
        }
        default: {
            cout << "Vui long chon thong tin hop le!!!";
            break;
        }
    }
}

void Staff::ShowDanhSach() {
    cout << "\n       Danh sach nhan vien          \n" << endl;
    bool hasData = false;
    ifstream in(nvPath);
    string line;
    while(getline(in, line)) {
        if(line.empty()) continue;
        hasData = true;
        stringstream ss(line);
        string id, name, age, phoneNum, temp;
        float basicSalary = 0;
        
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, age, '|');
        getline(ss, phoneNum, '|');
        getline(ss, temp, '|');

        if(!temp.empty()) basicSalary = stof(temp);

        cout << "- CCCD: " << id
             << " Ten: " << name
             << " Tuoi:" << age
             << " So dien thoai: " << phoneNum
             << " Luong co ban: " << endl;
    }
    if(!hasData) {
        cout << "Hien tai chua co nhan vien nao trong danh sach nay!" << endl;
    }
    in.close();
}