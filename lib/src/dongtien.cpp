#include "../headers/dongtien.h"
#include <fstream>
#include <sstream>
#include <ctime>

#define DT_PATH "./cafe-management/data/dongtien.txt"

// ham tach datetime tu string sang tm de so sanh
static tm parseDT(const string& dt) {
    tm t = {};
    sscanf(dt.c_str(), "%d-%d-%d %d:%d:%d",
           &t.tm_year, &t.tm_mon, &t.tm_mday,
           &t.tm_hour, &t.tm_min, &t.tm_sec);

    t.tm_year -= 1900;
    t.tm_mon  -= 1;
    return t;
}

// kiem tra cung ngay
static bool sameDay(const string& dt) {
    tm t = parseDT(dt);
    time_t now = time(0);
    tm* n = localtime(&now);
    return (t.tm_year == n->tm_year &&
            t.tm_mon  == n->tm_mon &&
            t.tm_mday == n->tm_mday);
}

// kiem tra trong cung tuan (7 ngay tro lai)
static bool sameWeek(const string& dt) {
    tm t = parseDT(dt);
    time_t now = time(0);

    int day1 = (int)mktime(&t) / 86400;
    int day2 = (int)now / 86400;

    return abs(day1 - day2) < 7;
}

// kiem tra cung thang
static bool sameMonth(const string& dt) {
    tm t = parseDT(dt);
    time_t now = time(0);
    tm* n = localtime(&now);

    return (t.tm_year == n->tm_year &&
            t.tm_mon  == n->tm_mon);
}

//-------------------------------------------
// GHI 1 RECORD
//-------------------------------------------
void DongTien::save() {
    ofstream out(DT_PATH, ios::app);
    if(!out) return;

    out << tableID << "|"
        << orders << "|"
        << revenue << "|"
        << profit << "|"
        << datetime << endl;

    out.close();
}

//-------------------------------------------
// LOAD TAT CA
//-------------------------------------------
vector<DongTien> DongTien::loadAll() {
    vector<DongTien> list;
    ifstream in(DT_PATH);

    if(!in) {
        // tao auto tao file nếu chưa có
        ofstream create(DT_PATH);
        create.close();
        return list;
    }

    string line;
    while (getline(in, line)) {
        if(line.empty()) continue;

        stringstream ss(line);
        string id, ods, rev, prof, dt;

        getline(ss, id,   '|');
        getline(ss, ods,  '|');
        getline(ss, rev,  '|');
        getline(ss, prof, '|');
        getline(ss, dt); 

        if(id.empty() || dt.size() < 19) continue; // auto skip dòng lỗi

        list.push_back(DongTien(id, ods, stol(rev), stol(prof), dt));
    }
    return list;
}


//-------------------------------------------
// DOANH THU
//-------------------------------------------
long DongTien::doanhThuHomNay() {
    long sum = 0;
    for(auto& x : loadAll())
        if(sameDay(x.getDatetime())) sum += x.getRevenue();
    return sum;
}

long DongTien::doanhThuTuanNay() {
    long sum = 0;
    for(auto& x : loadAll())
        if(sameWeek(x.getDatetime())) sum += x.getRevenue();
    return sum;
}

long DongTien::doanhThuThangNay() {
    long sum = 0;
    for(auto& x : loadAll())
        if(sameMonth(x.getDatetime())) sum += x.getRevenue();
    return sum;
}

//-------------------------------------------
// LOI NHUAN
//-------------------------------------------
long DongTien::loiNhuanHomNay() {
    long sum = 0;
    for(auto& x : loadAll())
        if(sameDay(x.getDatetime())) sum += x.getProfit();
    return sum;
}

long DongTien::loiNhuanTuanNay() {
    long sum = 0;
    for(auto& x : loadAll())
        if(sameWeek(x.getDatetime())) sum += x.getProfit();
    return sum;
}

long DongTien::loiNhuanThangNay() {
    long sum = 0;
    for(auto& x : loadAll())
        if(sameMonth(x.getDatetime())) sum += x.getProfit();
    return sum;
}

//-------------------------------------------
// SAN LUONG
//-------------------------------------------
long DongTien::tongSanLuong() {
    long total = 0;

    for(auto& x : loadAll()) {
        string ods = x.getOrders();
        if(ods.empty()) continue;

        stringstream ss(ods);
        string item;

        while (getline(ss, item, ',')) {
            size_t pos = item.find(':');
            if(pos != string::npos) {
                total += stoi(item.substr(pos + 1));
            }
        }
    }
    return total;
}
