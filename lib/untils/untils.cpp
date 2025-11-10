#include "untils.h"
using namespace std;


//check ton tai
bool checkExisted(string newID) {
    ifstream in(nvPath);
    string line, id;

    while (getline(in, line)) {
        //lay rieng phan id, khong lay cac phan khac
        size_t pos = line.find('|');
        if(pos != string::npos) { 
            /* neu pos khac npos tuc la '|' ton tai trong dong do
             => dong do co nhieu hon 1 du lieu can thiet la id,
             nen dung substr(0,pos) de tach phan tu dau tien trong line va sau dau '|',
             tuc la tach ra chi lay moi ID. */
            id = line.substr(0, pos);
        }
        else id = line;
        if(id == newID) return true;
    }
    in.close();
    return false;
}

bool checkProduct(string pID) {
    ifstream in(pdPath);
    string line, id;

    while (getline(in, line)) {
        //lay rieng phan id, khong lay cac phan khac
        size_t pos = line.find('|');
        if(pos != string::npos) { 
            /* neu pos khac npos tuc la '|' ton tai trong dong do
             => dong do co nhieu hon 1 du lieu can thiet la id,
             nen dung substr(0,pos) de tach phan tu dau tien trong line va sau dau '|',
             tuc la tach ra chi lay moi ID. */
            id = line.substr(0, pos);
        }
        else id = line;
        if(id == pID) return true;
    }
    in.close();
    return false;
}


// tach va ghep fields cho sua thong tin

// tach fields
vector<string> TrimFields(string beChangeID, string filePath, const string& line) {
    ifstream in(filePath);
    string id;
    vector<string> fields;
    size_t pos = line.find('|');
        if(pos != string::npos) { 
            id = line.substr(0, pos); //doan nay y chang o tren, lay id
        }
        else id = line;

        if(id == beChangeID) {
            size_t start = 0, end;
            while ((end = line.find("|", start)) != string::npos) {
                fields.push_back(line.substr(start, end - start));
                start = end + 1;
            }
            fields.push_back(line.substr(start));
        }
    return fields;
}

string LinkedFields(vector<string>& fields) {
    string result;
    for(int i = 0; i < fields.size(); ++i) {
        result += fields[i];
        if( i != fields.size() - 1) result += "|";
    }
    return result;
}
void printBillLine(const string& name, int quantity, float price) {
    cout << left  << setw(15) << name     // cột tên món, căn trái
         << right << setw(10) << quantity // cột số lượng, căn phải
         << right << setw(12) << fixed << setprecision(0) << price // cột đơn giá
         << endl;
}