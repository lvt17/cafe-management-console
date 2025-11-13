#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "../headers/sanpham.h"
#include "../headers/nhanvien.h"
#include <ctime>

#define nvPath "./cafe-management/data/nhanvien.txt" 
#define pdPath "./cafe-management/data/sanpham.txt"
#define billPath "./cafe-management/data/hoadon/ban_"
using namespace std;

bool checkExisted(string newID);
vector<string> TrimFields(string beChangeID, const string& line);
string LinkedFields(vector<string>& fields) ;
bool checkProduct(string pID);
void printBillLine(const string& name, int quantity, float price) ;

string currentDateTime();
string getDateTime();
string formatMoney(long long n) ;