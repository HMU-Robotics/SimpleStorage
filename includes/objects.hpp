#pragma once
#include <iostream>
#include <vector>

using namespace std;

enum roleType{
    ADMIN = 1,
    EDITOR = 2,
    VIEWER = 3
};


struct Member{
    int id;
    string first_name;
    string last_name;
    string hashPassword;
    string username;
    int role_id;
    vector<string> reservations = {};
    Member(int id,string first_name,string last_name,string hashPassword,string username,int role_id){
        this->id = id;
        this->first_name = first_name;
        this->last_name = last_name;
        this->hashPassword = hashPassword;
        this->username = username;
        this->role_id = role_id;
    }
};

struct Item{
    int id;
    string name;
    string desc;
    string code;
    bool isReserved = false;
    string ReservedBy = "";
    int reservation_id = 0;
    Item(int id , string name ,string desc,string code){
        this->id = id;
        this->name = name;
        this->desc = desc;
        this->code = code;
    }
};