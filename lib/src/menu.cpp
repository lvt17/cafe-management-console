#include "../headers/menu.h"

static Table currentTable;
static bool currentTableLoaded = false;


vector<Product> plist() {
    vector<Product> pTemp;
    ifstream in(pdPath);
    string line;
    int i = 1;
    while(getline(in, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string id, name, tCost, tPrice;
        long cost, price;
        
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, tCost, '|');
        getline(ss, tPrice, '|');

        if(!tCost.empty()) cost = stof(tCost);
        if(!tPrice.empty()) price = stof(tPrice);

        pTemp.push_back({id, name, cost, price});
    }
    return pTemp;
};

vector<Table> tablist() {
    vector<Table> pTemp;
    ifstream in(tPath);
    string line;
    int i = 1;
    while(getline(in, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string id, cusName, state;
        
        getline(ss, id, '|');
        getline(ss, cusName, '|');
        getline(ss, state, '|');
        //static_case<bool>: ep kieu int => bool; stoi: ep kieu string sang int;
        //vi mac dinh gia tri lay tu file len la string
        pTemp.push_back({id, cusName, static_cast<bool>(stoi(state))});
    }
    return pTemp;
};

vector<Staff> slist() {
    vector<Staff> sTemp;
    ifstream in(nvPath);
    string line;
    int i = 1;
    while(getline(in, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string id, name, age, phoneNum, temp;
        float salary = 0;
        
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, age, '|');
        getline(ss, phoneNum, '|');
        getline(ss, temp, '|');

        if(!temp.empty()) salary = stof(temp);

        sTemp.push_back({id, name, age, phoneNum, salary});
    }
    return sTemp;
};

void showMenu() {
    int choose;
    vector<pair<string,string>> orders;
    Product p;
    do {
        cout << "\n|" << string(5, '_') << "CAFE MANAGEMENT" << string(5, '_') << "|\n" << endl;
        cout << "1. Show Menu & Order" << endl
            << "2. Tinh tien"         << endl
            << "3. Quan li ban"       << endl
            << "4. Quan li san pham"  << endl
            << "5. Quan li nhan vien" << endl
            << "6. Quan li doanh thu" << endl
            << string(27, '_') << endl
            << "|" << string(25, ' ') << "|" << endl;

        cout << "\n: "; cin >> choose;
    switch(choose) {
        case 1: {
            string choose;
            int qty;
            string tableID;
            cout << "Nhap so ban cua khach: "; cin >> tableID; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (!currentTableLoaded || currentTable.getID() != tableID) {
                currentTable = currentTable.findByID(tablist(), tableID);
                currentTableLoaded = true;
            }
            
            do {
                cout << string(40, '-') << endl
                     << "Show Menu & Order" << endl
                     << string(40, '-') << endl;
                cout << "\n*Bam phim 0 de hoan tat order*\n" << endl;
                p.ShowMenuToCustomer();
                cout << "\nMon khach chon (id): "; cin >> choose; 
                if(choose != "0") {
                cout << "\nNhap so luong: "; cin >> qty; 
                    if(checkProduct(choose)) {
                        currentTable.addOrder(choose, qty);
                        currentTable.SaveTable(currentTable, tablist());
                    }
                    else {
                        cout << "Khong co mon do!";
                        continue;
                    }
                }
            }while(choose != "0");
            break;
        }
        case 2: {
            centerText("TINH TIEN");
            string tableID;
            cout << "\nNhap so ban: "; cin >> tableID; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(!checkTableExist(tableID)) {
                cout << endl << "Ban nay khong ton tai!" << endl;
            }
            else {
                if (!currentTableLoaded || currentTable.getID() != tableID) {
                    cout << "Ban nay chua order hoac chua duoc load!" << endl;
                    break;
                }
                char billPrint; bool print = false;
                cout << "\nBan co muon in hoa don khong? (y/n): "; cin >> billPrint; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(tolower(billPrint) == 'y') {
                    print = true;
                }
                int voucher = 0;
                cout << "\nVoucher: "; cin >> voucher; cout << endl;
                cout << string(16, ' ') << "HOA DON" << endl;
                currentTable.TinhTien(plist(), voucher, print);
                cout << string(40, '-') << endl << endl;
                currentTableLoaded = false;

            }
            break;
        }
        case 3: {
            int act;
            Table table;
            do {
                centerText("QUAN LI BAN");
                cout << endl;
                cout << "\n1. Them ban moi"            << endl
                    << "2. Xoa ban"                    << endl
                    << "3. Xem danh sach ban hien co"  << endl
                    << "4. Khach dat ban"              << endl
                    << "5. Xem ban da dat truoc"       << endl
                    << "6. Huy dat ban"                << endl
                    << "7. Xem order cua tung ban"     << endl
                    << "0. Thoat"                      << endl
                    << "\n: "; cin >> act;
                
                QuanLiBan(act, table);
            } while (act != 0);
            break;
        }
        case 4: {
            int act;
            Product p;
            do {
                centerText("QUAN LI SAN PHAM");
                cout << endl;
                cout << "\n1. Them mon moi"           << endl
                    << "2. Sua thong tin mon"      << endl
                    << "3. Xoa mon khoi menu" << endl
                    << "4. Show danh sach cac mon hien co"     << endl
                    << "0. Thoat"                        << endl
                    << "\n: "; cin >> act;
            if(act >= 1 && act <= 5) {
                QuanLiSanPham(p, act);
            }
            } while (act >= 1 && act <= 5);     
            break;
            break;
        }
        case 5: {
            int act;
            Staff nv;
            do {
                centerText("QUAN LI NHAN VIEN");
                cout << "\n1. Them nhan vien moi"           << endl
                    << "2. Sua thong tin nhan vien"      << endl
                    << "3. Xoa nhan vien khoi danh sach" << endl
                    << "4. Tinh luong nhan vien"         << endl
                    << "5. Show danh sach nhan vien"     << endl
                    << "0. Thoat"                        << endl
                    << "\n: "; cin >> act;
                if(act >= 1 && act <= 5) {
                    QuanLiNhanVien(nv, act, slist());
                }
            } while (act >= 1 && act <= 5);     
            break;
        }
        case 6: {
            int act;
            do {
                centerText("QUAN LI DOANH THU");
                cout << "\n1. Doanh thu hom nay"    << endl
                     << "2. Doanh thu tuan nay"    << endl
                     << "3. Doanh thu thang nay"   << endl
                     << "4. Loi nhuan hom nay"     << endl
                     << "5. Loi nhuan tuan nay"    << endl
                     << "6. Loi nhuan thang nay"   << endl
                     << "7. Tong san luong da ban" << endl
                     << "0. Thoat"                  << endl
                     << "\n: ";
                cin >> act;
        
                DongTien dt;               
                QuanLiDongTien(dt, act);   
        
            } while (act != 0);
            break;
        }
        default: {
            break;
        }
    }
} while(choose != 0);
}





void QuanLiNhanVien(Staff& s, int action, vector<Staff> slist) {
    switch(action) {
        case 1: {
            //them nhan vien
            string id;
            cout << "Nhap so cccd: "; cin >> id;
            if(checkExisted(id)) {
                cout << "Nhan vien nay da co trong danh sach!";
            }
            else {
                string name, age, phoneNum; float basicSalary;

                cout << "Nhap ten: "; cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                getline(cin, name); 

                cout << "Nhap tuoi: ";  
                getline(cin, age);

                cout << "Nhap so dien thoai: "; 
                getline(cin, phoneNum); 

                cout << "Nhap luong co ban (theo gio): "; cin >> ws >> basicSalary;
 
                s.ThemNhanVien(id, name, age, phoneNum, basicSalary);
            } 
            break;
        } //end case 1
        case 2: {
            //sua thong tin
            string id;
            cout << "Nhap so cccd: "; cin >> id;
            if(!checkExisted(id)) {
                cout << "Nhan vien nay khong co trong danh sach!";
            }
            else {
                int inforChosen;
                do {
                cout << "1. Chinh sua ten nhan vien"                << endl
                     << "2. Chinh sua tuoi cua nhan vien"           << endl
                     << "3. Chinh sua so dien thoai cua nhan vien"  << endl
                     << "4. Chinh sua luong co ban cua nhan vien"   << endl
                     << "0. Thoat"                                  << endl
                     << "\n: "; cin >> inforChosen;
                if(inforChosen >= 1 && inforChosen <= 6) {
                switch(inforChosen) {
                    case 1: {
                        s.ChinhSuaThongTin(id, 1);
                        break;
                    }
                    case 2: {
                        s.ChinhSuaThongTin(id, 2);
                        break;
                    }
                    case 3: {
                        s.ChinhSuaThongTin(id, 3);
                        break;
                    }
                    case 4: {
                        s.ChinhSuaThongTin(id, 4);
                        break;
                    }
                    default: {
                        cout << "Vui long chon (1-4) !!!";
                        break;
                    }
                }
            }
            } while (inforChosen >= 1 && inforChosen <= 5);
            }
            break;
        } //end case 2
        case 3: {
            string id;
            cout << "Nhap so cccd: "; cin >> id;
            if(!checkExisted(id)) {
                cout << "Nhan vien nay khong co trong danh sach!";
            }
            else {
                s.XoaNhanVien(id);
            }
            break;
        } //end case 3
        case 4: {
            string id;
            cout << "Nhap so cccd: "; cin >> id;
            if(!checkExisted(id)) {
                cout << "Nhan vien nay khong co trong danh sach!";
            }
            auto nv = s.findByID(slist, id);
            int SoGioCong; float TienThuong = 0, TienPhat = 0, TienUng = 0;
            cout << "Nhap so gio cong: "; cin >> SoGioCong;
            cout << "Nhap so tien thuong: "; cin >> TienThuong;
            cout << "Nhap so tien phat: "; cin >> TienPhat;
            cout << "Nhap so tien ung truoc: "; cin >> TienUng;
            float salary = 0;
            salary = nv.TinhLuong(SoGioCong, TienThuong, TienPhat, TienUng);
            cout.imbue(locale(""));
            cout << endl << string(3, '-') << " Luong cua nhan vien " << nv.getName() << ": "
                 << fixed << setprecision(0) << formatMoney((long long)salary) << " VND " << string(3, '-');
            cout << endl;
            break;
        }//end case 4
        case 5: {
            s.ShowDanhSach();
        }//end case 5
    }

}

void QuanLiSanPham(Product& p, int action) {
    switch(action) {
        case 1: {
            //them san pham
            string id;
            cout << "Nhap id mon: "; cin >> id;
            if(checkProduct(id)) {
                cout << "Mon nay da co trong menu!";
            }
            else {
                string name; long cost, price; 

                cout << "Nhap ten mon: "; cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                getline(cin, name); 

                cout << "Nhap tien von: ";  
                cin >> cost;

                cout << "Nhap doanh thu: "; 
                cin >> price; 
 
                p.ThemSanPham(id, name, cost, price);
            } 
            break;
        }
        case 2: {
            //sua thong tin
            string id;
            cout << "Nhap id mon: "; cin >> id;
            if(!checkProduct(id)) {
                cout << "Mon nay khong co trong menu!";
            }
            else {
                int inforChosen;
                do {
                cout << "1. Chinh sua ten mon"                      << endl
                     << "2. Chinh sua tien von"                     << endl
                     << "3. Chinh sua gia mon"                    << endl
                     << "0. Thoat"                                  << endl
                     << "\n: "; cin >> inforChosen;
                switch(inforChosen) {
                    case 1: {
                        p.SuaSanPham(id, 1);
                        break;
                    }
                    case 2: {
                        p.SuaSanPham(id, 2);
                        break;
                    }
                    case 3: {
                        p.SuaSanPham(id, 3);
                        break;
                    }
                    default: {
                        cout << "Vui long chon (1-3) !!!";
                        break;
                    }
                }
            } while (inforChosen != 0);
            }
            break;
        }
        case 3: {
            string id;
            cout << "Nhap id mon: "; cin >> id;
            if(!checkExisted(id)) {
                cout << "Mon nay khong co trong menu!";
            }
            else {
                p.XoaSanPham(id);
            }
            break;
        }
        case 4: {
            p.ShowSanPham();
        }
    }
}

void QuanLiBan(int act, Table& table) {
    switch(act) {
        case 1: {
            //them ban moi
            string id;
            cout << endl << "Nhap id ban: ";cin >> id; 
            table.ThemBanMoi(id);
            break;
        }
        case 2: {
            string id;
            cout << "Nhap id ban muon xoa: "; cin >> id;
            if(checkTableExist(id)) {
                table.XoaBan(id);
            } else {
                cout << "\nBan nay khong ton tai!" << endl;
            }
            break;
        }
        case 3: {
            table.DanhSachBan();
            break;
        }
        case 4:{
            //khach dat ban
            string id, cusName;

            cout << "Nhap id ban: ";
            cin >> id;

            cout << "Nhap ten khach dat ban: "; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, cusName); //vi cai nay co dau cach nen dung getline cho do bi mat chu

            if(checkTableExist(id)) {
                cout << "--- Ban nay da co trong danh sach roi!!! ---";
            }
            else {
                table.DatBan(id, cusName, tablist());
            }
            break;
        }
        case 5: {
            //xem ban da duoc dat truoc
            if(tablist().empty()) {
                cout << string(30, '-') << endl
                     << "  Hien tai chua co ai dat ban" << endl
                     << string(30, '-') << endl;
                break;
            }
            else {
                cout << string(40, '-') << endl
                    << "BAN DA DUOC KHACH DAT TRUOC" << endl
                    << string(40, '-') << endl;
                cout << endl;
                cout << left  << setw(10) << "ID"      
                    << left  << setw(15) << "Ten Khach"
                    << endl << string(40, '-') << endl;
                for(auto& tab: tablist()) {
                    if(tab.getState() == true) {
                        cout << left  << setw(10) << table.getID()          
                            << left  << setw(15) << table.getCustomer() 
                            << endl << string(40, '-') << endl;
                    }
                }
                break;
            }
        }
        case 6: {
            //Huy dat ban
            string id;
            cout << "Nhap id ban can huy: "; cin >> id;
            //check ban ton tai va trang thai ban true
            if(checkTableExist(id) && table.findByID(tablist(),id).getState()) {
            table.HuyDatBan(id, tablist());
            cout << endl << "--- Da huy ban " << id << " ---" << endl;
            }
            else {
                cout << endl << "Ban nay khong ton tai hoac chua co ai dat!" << endl;
            }
            break;
        }
        case 7: {
            //xem order tung ban
            string id;
            cout << endl << "Nhap id ban muon xem order: "; cin >> id;
            if(checkTableExist(id)) {
                Table thisTable = table.findByID(tablist(), id);
                if(thisTable.getOrders().empty()) {
                    cout << endl << string(30, '-') << endl
                         << "Ban nay chua order!" << endl
                         << string(30, '-') << endl;
                }
                else {
                    cout << endl << string(40, '-') << endl
                        << "ORDER CUA BAN" << id << endl
                        << string(60, '-') << endl;
                    cout << endl;
                    cout << left  << setw(10) << "ID"      
                        << left  << setw(15) << "Ten Mon"
                        << right << setw(10) << "So Luong" 
                        << endl << string(60, '-') << endl;
                    for(auto& p: thisTable.getOrders()) {
                        cout << left  << setw(10) << id      
                        << left  << setw(15) << p.first
                        << right << setw(10) << p.second 
                        << endl << string(60, '-') << endl;
                    }
                }
            }
            else {
                cout << endl << "--- Ban nay khong ton tai trong he thong! ---" << endl;
            }
            break;
        }

        default: {
            cout << endl << "--- Vui long chon tu 1 den 7!!! ---" << endl;
            break;
        }
    }
}

void QuanLiDongTien(DongTien& dt, int action) {
    switch(action) {
        case 1: {
            long money = dt.doanhThuHomNay();
            cout << "\nDoanh thu hom nay: "
                 << formatMoney(money) << " VND\n";
            break;
        }
        case 2: {
            long money = dt.doanhThuTuanNay();
            cout << "\nDoanh thu tuan nay: "
                 << formatMoney(money) << " VND\n";
            break;
        }
        case 3: {
            long money = dt.doanhThuThangNay();
            cout << "\nDoanh thu thang nay: "
                 << formatMoney(money) << " VND\n";
            break;
        }
        case 4: {
            long profit = dt.loiNhuanHomNay();
            cout << "\nLoi nhuan hom nay: "
                 << formatMoney(profit) << " VND\n";
            break;
        }
        case 5: {
            long profit = dt.loiNhuanTuanNay();
            cout << "\nLoi nhuan tuan nay: "
                 << formatMoney(profit) << " VND\n";
            break;
        }
        case 6: {
            long profit = dt.loiNhuanThangNay();
            cout << "\nLoi nhuan thang nay: "
                 << formatMoney(profit) << " VND\n";
            break;
        }
        case 7: {
            int sl = dt.tongSanLuong();
            cout << "\nTong san luong da ban: "
                 << sl << " mon\n";
            break;
        }
        case 0: {
            break;
        }
        default: {
            cout << "\nVui long chon tu 0 den 7!!!\n";
            break;
        }
    }
}
