#pragma once


#include <iostream>
#include <vector>
#include "./MySQLConnect.hpp"


class UI{

    private:
        bool _login = false;
        bool _isAdmin = false;
        bool _isUser = false;

        bool _appStatus = true;

        MySQLConnect db;


    std::vector<std::string> menu_choises = {
        "Add Item",
        "See all Items",
        "See available items"
        "Register member"
        "See all"
    };

    protected:

    public:
        UI(){
            this->db.connect("tcp://192.168.1.3:3306","HMU","hmuroboticsclub!@#123","HMU_ROBOTICS_STORAGE");
        }
        void displayMainMenu();
        void Login();
};


void UI::Login(){
    std::string username = "";
    std::string password = "";
    while(this->_appStatus){
        std::cout<<"Login Username >> ";
        std::cin>>username;
        std::cout<<"Password >> ";
        std::cin>>password;

        if(password!="" && username!=""){
            std::cout<<"Not empty"<<std::endl;
            db.executeSQL("SELECT * FROM user;");
            db.printResult();
            this->_login = true;
            while(this->_login){
                this->displayMainMenu();
            }
        }
    }
}

void UI::displayMainMenu(){
    int index = 1;
    std::string choice ;
    for(auto x : this->menu_choises){
        std::cout<<index<<") "<<x<<std::endl;
        index++;
    }
    std::cin>>choice;
    if(choice == "q"){
        this->_login = false;
        std::cout<<"Log out successful ..."<<std::endl;
        return;
    }
    else std::cout<<"Not a valid choice"<<std::endl;

}