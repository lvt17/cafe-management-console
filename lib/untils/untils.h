#include <iostream>
#include <fstream>
#include <vector>
#include "../headers/nhanvien.h"
using namespace std;

bool checkExisted(string newID);
vector<string> TrimFields(string beChangeID, string filePath, const string& line);
string LinkedFields(vector<string>& fields) ;
bool checkProduct(string pID);
void printBillLine(const string& name, int quantity, float price) ;
#define nvPath "./cafe-management/data/nhanvien.txt" 
#define pdPath "./cafe-management/data/sanpham.txt"