#include <iostream>
#include <fstream>
#include <vector>
#include "../headers/nhanvien.h"
using namespace std;

bool checkExisted(string newID);
vector<string> TrimFields(string beChangeID, string filePath, const string& line);
string LinkedFields(vector<string>& fields) ;

#define nvPath "./cafe-management/data/nhanvien.txt" 