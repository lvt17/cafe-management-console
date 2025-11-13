#include "../headers/nhanvien.h"
#include "../headers/sanpham.h"
#include <map>
#include <vector>
#include <set>
#include <utility>
#include <string>
#include <ctime>
#include <filesystem>
#include "../untils/untils.h"
#include "../headers/dongtien.h"
#include "../headers/tables.h"

class Table;

void showMenu();
void QuanLiNhanVien(Staff& s, int action, vector<Staff> slist);
void QuanLiSanPham(Product& p, int action);
void QuanLiBan(int act, Table& table);
void QuanLiDongTien(DongTien& dt, int action);
vector<Product> plist();

