#include "../headers/nhanvien.h"
#include "../headers/sanpham.h"
#include <map>
#include <vector>
#include <set>
#include <utility>
#include <string>
#include "../untils/untils.h"

void showMenu();
void QuanLiNhanVien(Staff s, int action);
void QuanLiSanPham(Product p, int action) ;
auto Order(int tableID, string &pID);
void TinhTien(vector<pair<int,string>> Order, vector<Product> plist, int tableID, int voucher);

vector<Product> plist();