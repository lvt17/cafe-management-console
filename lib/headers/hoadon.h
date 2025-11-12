#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <filesystem>

using namespace std;

class Bill {
    private:
        string id, name, createAt;
        long cost, price;
    public:
        Bill() {}
        Bill(string id, string name, long cost, long price, string createAt) :
            id(id), name(name), cost(cost), price(price), createAt(createAt) {}

        void XuatHoaDon ();
};
