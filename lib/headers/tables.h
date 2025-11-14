#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <map>
#include "../untils/untils.h"
#include "../headers/sanpham.h"
#include "../headers/dongtien.h"

using namespace std;

class Table {
private:
    string id;
    string customer;
    bool state = false;
    vector<pair<string, int>> orders;

public:
    // constructor
    Table() {}
    Table(string id_) : id(id_), customer("null"), state(false) {}
    Table(string id_, string cus_, bool st_) : id(id_), customer(cus_), state(st_) {}
    Table(string id_, bool state_, vector<pair<string,int>> order_)
        : id(id_), state(state_), orders(order_) {}

    // setter 
    void setID(const string& newID) { id = newID; }
    void setCustomer(const string& cusName) { customer = cusName; }
    void setState(bool newState) { state = newState; }

    // order
    void addOrder(string pID, int quantity) { orders.push_back({pID, quantity}); }
    void clearOrders() { orders.clear(); }

    // getter
    string getID() const { return id; }
    string getCustomer() const { return customer; }
    bool getState() const { return state; }
    vector<pair<string,int>> getOrders() const { return orders; }

    // methods
    void ThemBanMoi(string& id);
    void XoaBan(string& deleteID); 
    void DatBan(string id, string& cusName, vector<Table> tb);
    void HuyDatBan(string id, vector<Table> tb);
    void TinhTien(vector<Product> plist, int voucher, bool billPrint);
    void DanhSachBan();
    void SaveTable(const Table& t, vector<Table> list);
    Table findByID(vector<Table> tb, string id);
    string serializeOrders(vector<pair<string,int>>& orders);
};
