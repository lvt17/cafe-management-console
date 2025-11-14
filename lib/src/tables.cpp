#include "../headers/tables.h"

using namespace std;


void Table::DatBan(string id, string& cusName, vector<Table> tb) {
    
    Table table = findByID(tb, id);
    
    if(table.getState() && table.getCustomer() != null) {
        cout << "\nBan nay da co nguoi dat truoc, vui long chon ban khac!" << endl;
        return;
    }

    table.setState(true);
    table.setCustomer(cusName);

    ifstream in(tPath);
    string line;
    vector<string> lines;
    bool found = false;


    while (getline(in, line)) {
        vector<string> fields = TrimFields(id, line);

        if(!fields.empty() && fields[0] == id) {
            found = true;
            fields[1] = cusName;
            fields[2] = "1";
            lines.push_back(LinkedFields(fields));
        } else {
            lines.push_back(line);
        }
    }
    in.close();

    if(found) {
        ofstream out(tPath, ios::trunc);
        for(auto& l: lines) out << l << endl;
        out.close();
    }

    cout << "\n--- Khach \"" << cusName << "\" da dat ban " << id << " ---\n\n";
}

void Table::HuyDatBan(string id, vector<Table> tb) {

    Table table = findByID(tb, id);
    table.setState(false);
    table.setCustomer("null");

    ifstream in(tPath);
    string line;
    vector<string> lines;
    bool found = false;

    while (getline(in, line)) {
        vector<string> fields = TrimFields(id, line);

        if(!fields.empty() && fields[0] == id) {
            found = true;
            fields[1] = "null";
            fields[2] = "0";
            lines.push_back(LinkedFields(fields));
        } else {
            lines.push_back(line);
        }
    }
    in.close();

    if(found) {
        ofstream out(tPath, ios::trunc);
        for(auto& l: lines) out << l << endl;
        out.close();
    }

    cout << "\n--- Da huy dat ban " << id << " ---\n\n";
}

void Table::ThemBanMoi(string& id) {
    ofstream out(tPath, ios::app);
    if(!out) {
        cout << "Khong the mo file!";
        return;
    }

    if(!checkTableExist(id)) {
        out << id << "|" << "null" << "|" << "0" << endl;
        cout << "\nDa them ban moi co ID la: " << id << endl;
    } else {
        cout << "\nBan nay da ton tai!" << endl;
    }
    out.close();
}

void Table::XoaBan(string& deleteID) {
    ifstream in(tPath);
    vector<string> lines;
    string line, id;

    if(!in) {
        cout << "\n!!! LOI KHONG THE MO FILE !!!\n";
        return;
    }

    while (getline(in, line)) {
        size_t pos = line.find('|');
        id = (pos != string::npos) ? line.substr(0, pos) : line;

        if(id != deleteID) lines.push_back(line);
    }
    in.close();

    ofstream out(tPath, ios::trunc);
    for(auto& l : lines) out << l << endl;
    out.close();

    cout << "\n---- Da xoa ban: " << deleteID << " ----\n";
}

Table Table::findByID(vector<Table> tb, string id) {
    for (auto& t : tb)
        if (t.getID() == id)
            return t;
    return Table();
}

void Table::TinhTien(vector<Product> plist, int voucher, bool billPrint) {
    long prices = 0, cost = 0;
    map<string,int> bills;
    Product p;

    for (auto& ord : orders) {
        auto sp = p.findByID(plist, ord.first);
        bills[sp.getID()] += ord.second;
        prices += sp.getPrice() * ord.second;
        cost += sp.getCost() * ord.second;
    }

    cout << left  << setw(15) << "Ten mon"
         << right << setw(10) << "SL"
         << right << setw(12) << "Gia" << endl;
    cout << string(40, '-') << endl;

    for (auto& kv : bills) {
        auto sp = p.findByID(plist, kv.first);
        printBillLine(sp.getName(), kv.second, sp.getPrice());
    }

    cout << "\nDiscout: " << voucher << endl;
    prices -= voucher;
    cout << "Tong Tien: " << prices << endl;

    // ghi doanh thu
    long revenue = prices;
    long profit = prices - cost;
    string ods = serializeOrders(orders);

    DongTien dt(id, ods, revenue, profit, getDateTime());
    dt.save();

    // reset ban
    orders.clear();
    state = false;
    customer = "null";

    // in hoa don txt
    if (billPrint) {

        ensureDir(billPath);

        string filename = billPath + id + "-" + currentDateTime() + ".txt";
        ofstream out(filename);

        if(out.is_open()) {

            out << string(17,' ') << "HOA DON\n";
            out << string(40,'-') << "\n";

            out << left  << setw(20) << "TEN MON"
                << right << setw(10) << "SL"
                << right << setw(10) << "GIA" << "\n";

            out << string(40,'-') << "\n";

            for(auto& kv : bills) {
                auto sp = p.findByID(plist, kv.first);
                out << left  << setw(20) << sp.getName()
                    << right << setw(10) << kv.second
                    << right << setw(10) << sp.getPrice()
                    << "\n";
            }

            out << string(40,'-') << "\n";
            out << "Discout: " << voucher << "\n";
            out << "Tong Tien: " << prices << "\n";
            out << "Time: " << getDateTime() << "\n";
            out << string(40,'-') << "\n";

            out.close();
            cout << "Da xuat hoa don: " << filename << endl;

        } else {
            cout << "Khong xuat duoc hoa don!\n";
        }
    }
}

void Table::DanhSachBan() {
    centerText("DANH SACH BAN" );

    ifstream in(tPath);
    string line;
    bool hasData = false;

    while(getline(in, line)) {
        if(line.empty()) continue;
        hasData = true;

        stringstream ss(line);
        string id, cus, st;

        getline(ss, id, '|');
        getline(ss, cus, '|');
        getline(ss, st, '|');

        cout << left << setw(15) << id
             << right << setw(10) << st << endl;
    }
    in.close();

    if(!hasData) cout << "Chua co ban nao trong danh sach!\n";

    cout << string(40,'-') << endl << endl;
}

string Table::serializeOrders(vector<pair<string,int>>& orders) {
    string s = "";
    for(int i = 0; i < orders.size(); i++) {
        s += orders[i].first + ":" + to_string(orders[i].second);
        if(i != orders.size() - 1) s += ",";
    }
    return s;
}

void Table::SaveTable(const Table& t, vector<Table> list) {
    ofstream out(tPath, ios::trunc);

    for (auto& tb : list) {
        if (tb.getID() == t.getID()) {
            out << t.getID() << "|"
                << t.getCustomer() << "|"
                << (t.getState() ? "1" : "0") << endl;
        } else {
            out << tb.getID() << "|"
                << tb.getCustomer() << "|"
                << (tb.getState() ? "1" : "0") << endl;
        }
    }
}
