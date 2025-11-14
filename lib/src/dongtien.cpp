#include "../headers/dongtien.h"
#include <fstream>
#include <sstream>
#include <ctime>

#define DT_PATH "./cafe-management/data/dongtien.txt"

// =======================================
//  LOAD MENU 
// =======================================
vector<Product> loadProducts() {
    vector<Product> pTemp;
    ifstream in(pdPath);
    string line;

    while(getline(in, line)) {
        if(line.empty()) continue;
        
        stringstream ss(line);
        string id, name, tCost, tPrice;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, tCost, '|');
        getline(ss, tPrice, '|');

        long cost = stol(tCost);
        long price = stol(tPrice);

        pTemp.push_back(Product(id, name, cost, price));
    }
    return pTemp;
}

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

// kiem tra cung tuan (7 ngay tro lai)
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

        if(id.empty() || dt.size() < 19) continue;

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
// SAN LUONG CHI TIET (ID - TEN - SL - VON - DOANH THU)
//-------------------------------------------
void DongTien::inSanLuong() {
    vector<DongTien> all = loadAll();
    if(all.empty()) {
        cout << "Chua co hoa don nao!\n";
        return;
    }

    map<string, pair<long, pair<long,long>>> data;

    vector<Product> plist = loadProducts();
    Product p;

    for(auto& x : all) {
        string ods = x.getOrders();
        if(ods.empty()) continue;

        stringstream ss(ods);
        string item;

        while (getline(ss, item, ',')) {
            size_t pos = item.find(':');
            if(pos != string::npos) {
                string id = item.substr(0, pos);
                long sl = stol(item.substr(pos + 1));

                auto sp = p.findByID(plist, id);

                data[id].first += sl;
                data[id].second.first  = sp.getCost();
                data[id].second.second = sp.getPrice();
            }
        }
    }

    centerText("SAN LUONG DA BAN", 70);

    cout << left << setw(10) << "ID"
         << left << setw(20) << "TEN MON"
         << right << setw(12) << "SL"
         << right << setw(12) << "VON"
         << right << setw(12) << "DOANH THU" << "\n";

    cout << string(70, '-') << "\n";

    for(auto& kv : data) {
        auto sp = p.findByID(plist, kv.first);

        long sl = kv.second.first;
        long cost = kv.second.second.first;
        long price = kv.second.second.second;

        cout << left << setw(10) << kv.first
             << left << setw(20) << sp.getName()
             << right << setw(12) << sl
             << right << setw(12) << sl * cost
             << right << setw(12) << sl * price
             << "\n";

        cout << string(70, '-') << "\n";
    }
}
