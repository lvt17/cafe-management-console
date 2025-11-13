#include "../headers/sanpham.h"

void Product::ThemSanPham(string& pID, string& pName, long& pCost, long& pPrice) {
    setID(pID);
    setName(pName);
    setCost(pCost);
    setPrice(pPrice);

    ofstream out(pdPath, ios::app);
    if(!out) {
        cout << "Khong mo duoc file!\nThem san pham that bai!" << endl;
        return;
    }
    else { 
    out << getID() << "|" << getName() << "|" 
        << getCost() << "|" << getPrice() << endl;
    
    cout << "Da them thanh cong san pham: " << getName() << endl;
    return;
    }
}

void Product::XoaSanPham(string& deleteID) {
    ifstream in(pdPath);
    vector<string> lines; //luu tam bang moi sau khi xoa nhan vien
    string line, id;

    if(!in) {
        cout << "\n!!! LOI KHONG THE MO FILE !!!\n" << endl;
        return;
    }

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
    ofstream out(pdPath, ios::trunc);
    for(auto& l : lines) out << l << endl;
    out.close();

    cout << endl << string(4, '-') << " Da xoa thanh cong mon: " << getName() 
    << " " << string(4, '-') << endl;
}

void Product::SuaSanPham(string& id, int action) {
    ifstream in(pdPath);
    string line;
    vector<string> lines;
    bool found = false;
    if(!checkProduct(id)) {
        cout << "Mon nay khong co trong menu!!!" << endl;
        return;
    }
    if(!in) {
        cout << "Loi khong mo duoc file!" << endl;
        return;
    }
    switch(action) {
        case 1: {
            // sua ten
            string newName;
            cout << "Nhap ten moi: "; cin >> newName;
            setName(newName);
            while (getline(in, line)) {
                vector<string> fields = TrimFields(id, line);
                if(!fields.empty() && fields[0] == id) {
                    found = true;
                    fields[1] = newName;
                    lines.push_back(LinkedFields(fields));
                } else {
                lines.push_back(line);
                }
            }
            in.close();

            if(found) {
                ofstream out(pdPath, ios::trunc);
                for(auto& l: lines) out << l << endl;
                out.close();
            }
            cout << endl << string(4, '-') << " Da sua thanh cong ten mon: " << getName() 
            << " " << string(4, '-') << endl;
            break;
        }
        case 2: {
            // sua von
            long newCost;
            cout << "Nhap tien von moi: "; cin >> newCost;
            setCost(newCost);
            while (getline(in, line)) {
                if(line.empty()) {
                    continue;
                }
                vector<string> fields = TrimFields(id, line);
                if(!fields.empty() && fields[0] == id) {
                    found = true;
                    fields[2] = to_string(newCost);
                    lines.push_back(LinkedFields(fields));
                } else {
                lines.push_back(line);
                }
            }
            in.close();

            if(found) {
                ofstream out(pdPath, ios::trunc);
                for(auto& l: lines) out << l << endl;
                out.close();
            }
            cout << endl << string(4, '-') << " Da sua thanh cong tien von cua mon: " << getName() 
            << " thanh " << getCost() << " " << string(4, '-') << endl;
            break;
        }
        case 3: {
            // sua gia ban
            long newPrice;
            cout << "Nhap gia moi: "; cin >> newPrice;
            setPrice(newPrice);
            while (getline(in, line)) {
                vector<string> fields = TrimFields(id, line);
                if(!fields.empty() && fields[0] == id) { 
                    found = true;
                    fields[3] = to_string(newPrice);
                    lines.push_back(LinkedFields(fields));
                } else {
                lines.push_back(line);
                }
            }
            in.close();

            if(found) {
                ofstream out(pdPath, ios::trunc);
                for(auto& l: lines) out << l << endl;
                out.close();
            }
            cout << endl << string(4, '-') << " Da sua thanh cong gia ban cua mon: " << getName() 
            << " thanh " << getPrice() << " " << string(4, '-') << endl;
            break;
        }
        default: {
            cout << "Vui long chon thong tin hop le!!!";
            break;
        }
    }
}
 
void Product::ShowMenuToCustomer() {
    cout <<  string(18, '-') << "MENU" << string(18, '-') << endl;
    bool hasData = false;
    ifstream in(pdPath);
    string line;
    int i = 1;
    while(getline(in, line)) {
        if(line.empty()) continue;
        hasData = true;
        stringstream ss(line);
        string id, name, tCost, tPrice;
        long cost, price;
        
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss,tCost, '|');
        getline(ss, tPrice, '|');

        if(!tPrice.empty()) price = stof(tPrice);

        cout << left  << setw(15) << name      
         << right << setw(10) << price 
         << right << setw(12) << fixed << setprecision(0) << "(" << id << ")"
         << endl;
        i++;
    }
    if(!hasData) {
        cout << "Quan hien tai da het mon!" << endl;
    }
    cout << string(40, '-');
    in.close();
}

void Product::ShowSanPham() {
    cout << string(28, '-') << "MENU" << string(28, '-') << endl << endl;
    cout << left  << setw(10) << "ID"          
     << left  << setw(15) << "TEN MON"           
     << right << setw(10) << "TIEN VON"       
     << right << setw(12) << fixed << setprecision(0) << "DOANH THU"  
     << endl << string(60, '-') << endl;
    bool hasData = false;
    ifstream in(pdPath);
    string line;
    int i = 1;
    while(getline(in, line)) {
        if(line.empty()) continue;
        hasData = true;
        stringstream ss(line);
        string id, name, tCost, tPrice;
        long cost, price;
        
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, tCost, '|');
        getline(ss, tPrice, '|');

        if(!tCost.empty()) cost = stof(tCost);
        if(!tPrice.empty()) price = stof(tPrice);

        cout << left  << setw(10) << id          
             << left  << setw(15) << name           
             << right << setw(10) << cost       
             << right << setw(12) << fixed << setprecision(0) << price  
             << endl << string(60, '-') << endl;
        i++;
    }
    if(!hasData) {
        cout << "Hien tai chua co san pham nao trong danh sach nay!" << endl;
        cout << string(60, '-');
    }
    in.close();
}

Product Product::findByID(vector<Product>& ds, string id) {
    for (auto& p : ds)
        if (p.getID() == id)
            return p;
    return Product();
}