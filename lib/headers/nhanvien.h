#pragma once
#include <iostream>
#include "../untils/untils.h"
#include <filesystem>
#include <limits> 
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Staff {
    private:
        string id;
        string name;
        string age;
        string phoneNum;
        float basicSalary;
    public:
        //Constructor
        Staff () {}
        Staff (string id, string name, string age, string phoneNum, float basicSalary) 
        : id(id), name(name), age(age), phoneNum(phoneNum), basicSalary(basicSalary) {}

        //setter
        void setID(const string& newID) {id = newID;}
        void setName(const string& newName) {name = newName;}
        void setAge(const string& newAge) {age = newAge;}
        void setPhoneNum(const string& newPhoneNum) {phoneNum = newPhoneNum;}
        void setBasicSalary(const float& newBasicSalary) {basicSalary = newBasicSalary;}

        //getter
        string getID() {return id;}
        string getName() {return name;}
        string getAge() {return age;}
        string getPhoneNum() {return phoneNum;}
        float getBasicSalary() {return basicSalary;}
        
        //function
        float TinhLuong(int& SoGioCong, float& TienThuong, float& TienPhat, float& TienUng);
        void ThemNhanVien(string& id, string& name, string& age, string& phoneNum, float& basicSalary);
        void XoaNhanVien(string& id);
        void ChinhSuaThongTin(string id, int action);
        void ShowDanhSach();
        Staff findByID(vector<Staff> ds, string id);
};
