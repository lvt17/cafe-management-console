#include "untils.h"
using namespace std;

//define null
const string null = "null";

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

bool checkTableExist(string tID) {
    ifstream in(tPath);
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
        if(id == tID) return true;
    }
    in.close();
    return false;
}

// tach va ghep fields cho sua thong tin

// tach fields
vector<string> TrimFields(string beChangeID, const string& line) {
    vector<string> fields;
    // tách id
    size_t pos = line.find('|');
    string id = (pos != string::npos) ? line.substr(0, pos) : line;

    // nếu id khớp thì mới split
    if (id == beChangeID) {
        size_t start = 0, end;
        while ((end = line.find('|', start)) != string::npos) {
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


string currentDateTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", ltm);
    return string(buffer);
}

string getDateTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

string formatMoney(long long n) {
    string s = to_string(n);
    int pos = s.length() - 3;
    while (pos > 0) {
        s.insert(pos, ",");
        pos -= 3;
    }
    return s;
}

void centerText(const string& text, int width, char fill) {
    cout << endl << string(width, '-') << endl;
    int pad = (width - text.size()) / 2;
    if (pad > 0)
        cout << string(pad, fill) << text << string(pad, fill);
    else
        cout << text;
    cout << endl;
    cout << string(width, '-') << endl;
}


