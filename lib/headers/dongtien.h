#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "../headers/sanpham.h"
#include "../untils/untils.h"

using namespace std;

class DongTien {
private:
    string tableID;      // id ban
    string orders;       // luu kieu: id:sl,id:sl,id:sl
    long revenue = 0;    // doanh thu
    long profit = 0;     // loi nhuan
    string datetime;     // thoi gian

public:
    DongTien() {}
    DongTien(string id_, string ods_, long rev_, long pro_, string dt_)
    : tableID(id_), orders(ods_), revenue(rev_), profit(pro_), datetime(dt_) {}

    // setter
    string setTableID(string newID) { return tableID = newID; }
    string setOrders(string ods) { return orders = ods; }
    long setRevenue(long r) { return revenue = r; }
    long setProfit(long p) { return profit = p; }
    string setDatetime(string dt) { return datetime = dt; }

    // getter
    string getTableID() { return tableID; }
    string getOrders() { return orders; }
    long getRevenue() { return revenue; }
    long getProfit() { return profit; }
    string getDatetime() { return datetime; }

    // ghi 1 dong xuong file
    void save();

    // doc toan bo file
    static vector<DongTien> loadAll();

    // thong ke doanh thu
    static long doanhThuHomNay();
    static long doanhThuTuanNay();
    static long doanhThuThangNay();

    // thong ke loi nhuan
    static long loiNhuanHomNay();
    static long loiNhuanTuanNay();
    static long loiNhuanThangNay();

    // san luong (tong so luong ban ra)
    static void inSanLuong();

};
