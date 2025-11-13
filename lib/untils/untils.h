#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <iomanip>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "../headers/sanpham.h"
#include "../headers/nhanvien.h"
#include <ctime>

#define nvPath "./cafe-management/data/nhanvien.txt" 
#define pdPath "./cafe-management/data/sanpham.txt"
#define billPath "./cafe-management/data/hoadon/"
#define tPath "./cafe-management/data/tables.txt"
using namespace std;

extern const string null;

//importan
bool checkExisted(string newID);
bool checkTableExist(string newID);
vector<string> TrimFields(string beChangeID, const string& line);
string LinkedFields(vector<string>& fields) ;
bool checkProduct(string pID);
void printBillLine(const string& name, int quantity, float price) ;


//supliment
string currentDateTime();
string getDateTime();
string formatMoney(long long n);
void centerText(const string& text, int width = 40, char fill = ' ');
inline bool folderExists(const string& path) {
    DIR* dir = opendir(path.c_str());
    if (dir) {
        closedir(dir);
        return true;
    }
    return false;
}
// tao folder neu chua co
inline void ensureDir(const string& path) {
    if (!folderExists(path)) {
        mkdir(path.c_str(), 0777);
    }
}


