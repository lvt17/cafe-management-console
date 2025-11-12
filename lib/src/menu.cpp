#include "../headers/menu.h"


auto Order(int tableID, string &pID) {
    return make_pair(tableID, pID);
}

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

void showMenu() {
    int choose;
    vector<pair<int,string>> orders;
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
            int tableID;
            cout << "Nhap so ban cua khach: "; cin >> tableID; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            do {
                cout << "*Bam phim 0 de hoan tat order*\n" << endl;
                p.ShowMenuToCustomer();
                cout << "\nMon khach chon (id): "; cin >> choose; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if(choose != "0") {
                    if(checkProduct(choose)) {
                        orders.push_back({Order(tableID, choose)});
                    }
                }
                else {
                    cout << "Khong co mon do!";
                    continue;
                }
            }while(choose != "0");
            break;
        }
        case 2: {
            int tableID;
            cout << "\nNhap so ban: "; cin >> tableID; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            char billPrint; bool print = false;
            cout << "\nBan co muon in hoa don khong? (y/n): "; cin >> billPrint; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(tolower(billPrint) == 'y' || tolower(billPrint) == 'n') {
                if(tolower(billPrint) == 'y') {
                    //cout << "\n-Tinh nang nay dang doi Vtoan lam xong!-" << endl;
                    print = true;
                }
            }
            else {
                cout << "lua chon khong hop le!";
                break;
            }
            int voucher = 0;
            cout << "\nVoucher: "; cin >> voucher; cout << endl;
            cout << string(16, ' ') << "HOA DON" << endl;
            TinhTien(orders, plist(), tableID, voucher, print);
            cout << string(40, '-') << endl << endl;
            break;
        }
        case 3: {
            break;
        }
        case 4: {
            int act;
            Product p;
            do {
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
            cout << "\n1. Them nhan vien moi"           << endl
                 << "2. Sua thong tin nhan vien"      << endl
                 << "3. Xoa nhan vien khoi danh sach" << endl
                 << "4. Tinh luong nhan vien"         << endl
                 << "5. Show danh sach nhan vien"     << endl
                 << "0. Thoat"                        << endl
                 << "\n: "; cin >> act;
            if(act >= 1 && act <= 5) {
                QuanLiNhanVien(nv, act);
            }
            } while (act >= 1 && act <= 5);     
            break;
        }
        case 6: {
            break;
        }
        default: {
            break;
        }
    }
} while(choose != 0);
}


void TinhTien(vector<pair<int,string>> Order, vector<Product> plist, int tableID, int voucher, bool billPrint) {
    long prices = 0;
    map<string, int> bills;
    string id;
    Product p;
    for(auto& ord: Order) {
        if(ord.first == tableID) {
            auto sp = p.findByID(plist, ord.second);
            bills[sp.getID()] += 1; 
            prices += sp.getPrice();
        }
    }
    
    cout << left  << setw(15) << "Ten mon"
         << right << setw(10) << "So luong"
         << right << setw(12) << "Don gia" << endl;
    cout << string(40, '-') << endl;
    for(auto& [key, value]: bills) {
        auto sp = p.findByID(plist, key);
        printBillLine(sp.getName(), value, sp.getPrice());
    }
    cout << "\nDiscout: " << voucher << endl;
    prices -= voucher;
    cout << "\nTong Tien: " << prices << endl;
    
    if(billPrint) {
        if (!filesystem::exists(billPath)) filesystem::create_directory(billPath);

    string filename = billPath + to_string(tableID) + "-" + currentDateTime() + ".txt";
    ofstream out(filename);
    if (out.is_open()) { 
        out << string(17, ' ') << "HOA DON" << endl;
        out << string(40, '-') << endl;
        out << left  << setw(15) << "TEN MON"
         << right << setw(10) << "SO LUONG"
         << right << setw(12) << "DON GIA" << endl
         << string(40, '-') << endl;
        for(auto& [key, value]: bills) {
            auto sp = p.findByID(plist, key);
            out << left  << setw(15) << sp.getName()    
                << right << setw(10) << value
                << right << setw(12) << fixed << setprecision(0) << sp.getPrice() 
                << endl;
        }
        out << string(40, '-') << endl;
        out << "\nDiscout: " << voucher << endl;
        prices -= voucher;
        out << "Tong Tien: " << prices << endl;
        out << "Time: " << getDateTime() << endl;
        out << string(40, '-') << endl;
        out.close();
        cout << "da xuat hoa don: " << filename << endl;
    } else cout << "Khong xuat duoc hoan don\n";
    }
}



void QuanLiNhanVien(Staff s, int action) {
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