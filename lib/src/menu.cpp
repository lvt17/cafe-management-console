#include "../headers/menu.h"

void showMenu() {
    cout << "1. Show Menu"         << endl
         << "2. Tinh tien"         << endl
         << "3. Quan li ban"       << endl
         << "4. Quan li san pham"  << endl
         << "5. Quan li nhan vien" << endl
         << "6. Quan li doanh thu" << endl;
    int choose;
    cout << "\n: "; cin >> choose;
    switch(choose) {
        case 1: {
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            break;
        }
        case 4: {
            break;
        }
        case 5: {
            int act;
            Staff nv;
            do {
            cout << "1. Them nhan vien moi"           << endl
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
                        cout << "Vui long chon (1-6) !!!";
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