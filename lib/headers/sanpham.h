#pragma once
#include "../untils/untils.h"
#include <iostream>
#include <vector>
#include <filesystem>
#include <limits> 
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Product {
    private:
        string pID, pName;
        long pCost, pPrice;
    public:
        Product() {}
        Product (string& pID, string& pName, long& pCost, long& pPrice) : pID(pID), pName(pName), pCost(pCost), pPrice(pPrice) {}

        //setter
        void setID(const string& newID) {pID = newID;}
        void setName(string& newName) {pName = newName;}
        void setCost(long& newCost) {pCost = newCost;}
        void setPrice(long& newPrice) {pPrice = newPrice;}
        //getter 
        string getID() {return pID;}
        string getName() {return pName;}
        long getCost() {return pCost;}
        long getPrice(){return pPrice;}

        void ThemSanPham(string& pID, string& pName, long& pCost, long& pPrice);
        void XoaSanPham(string& deleteID);
        void SuaSanPham(string& pID, int action);
        void ShowMenuToCustomer();
        void ShowSanPham();
        Product findByID(vector<Product>& ds, string id);
};