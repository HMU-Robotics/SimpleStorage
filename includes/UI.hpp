#pragma once
#include <iostream>
#include <vector>
#include "./MySQLConnect.hpp"
#include "./sha-3.hpp"
#include "objects.hpp"


class Interface{

    private:
        bool _login = false;
        Member *loginMem;
        int loginType = 0;

        bool _isAdmin = false;
        bool _isUser = false;

        bool _appStatus = true;

        MySQLConnect db;

        std::vector<Member> Members;
        std::vector<Item> Items;


    std::vector<std::string> menu_choises = {
        "Reserve Item (Access Level 3)",
        "Add/Remove Item (Access Level 1,2)",
        "All Reserved Items (Access Level 1,2)",
        "Register member (Access Level 1)",
        "See all members (Access Level 1)"
    };

    void RegisterMember();

    protected:
        Member* getMember(std::string username);

    public:
        Interface(){
            std::cout<<"Connecting to db..."<<std::endl;
            this->db.connect("tcp://127.0.0.1:3306","HMU","HMUroboticsclub!@#123456","HMU_ROBOTICS_STORAGE");
        }
        void displayMainMenu();
        void Login();
        void printLogo();
};

void Interface::printLogo(){
    std::string logo = R"(

 #     # #     # #     #         ######                                                      #####                           #####                                           
 #     # ##   ## #     #         #     #  ####  #####   ####  ##### #  ####   ####          #     # #      #    # #####     #     # #####  ####  #####    ##    ####  ###### 
 #     # # # # # #     #         #     # #    # #    # #    #   #   # #    # #              #       #      #    # #    #    #         #   #    # #    #  #  #  #    # #      
 ####### #  #  # #     #         ######  #    # #####  #    #   #   # #       ####          #       #      #    # #####      #####    #   #    # #    # #    # #      #####  
 #     # #     # #     #         #   #   #    # #    # #    #   #   # #           #         #       #      #    # #    #          #   #   #    # #####  ###### #  ### #      
 #     # #     # #     #         #    #  #    # #    # #    #   #   # #    # #    #         #     # #      #    # #    #    #     #   #   #    # #   #  #    # #    # #      
 #     # #     #  #####          #     #  ####  #####   ####    #   #  ####   ####           #####  ######  ####  #####      #####    #    ####  #    # #    #  ####  ###### 
                         #######                                                    #######                                                                                  

)";

std::cout<<logo<<std::endl;

}

Member* Interface::getMember(std::string username){
    try{
        int id,role_id;
        std::string query ,first_name , last_name , email , ac_name , password , hashpass ;
        query = "SELECT id,username,email,first_name,last_name,password,role_id,password FROM user WHERE username=?";
        db.pstmt = db.con->prepareStatement(query);
        db.pstmt->setString(1,username);
        db.res = db.pstmt->executeQuery();

        while(db.res->next()){
            id = db.res->getInt("id");
            first_name = db.res->getString("first_name");
            last_name = db.res->getString("last_name");
            password = db.res->getString("password");
            ac_name = db.res->getString("username");
            role_id = db.res->getInt("role_id");
        }

        Member *tmp = new Member(id,first_name,last_name,password,ac_name,role_id);
        return tmp;
    } catch(sql::SQLException &e){
        std::cout<<"Faulted at fetching member from db..."<<std::endl;
    }

    
    return NULL;

};

void Interface::Login(){
    std::string username = "";
    std::string password = "";
    while(this->_appStatus){
        this->printLogo();
        std::cout<<"Login Username >> ";
        std::cin>>username;
        std::cout<<"Password >> ";
        std::cin>>password;

        if(password!="" && username!=""){
            std::string hash;
            std::string query = "SELECT password FROM user WHERE username=?";

        try{

            db.pstmt = db.con->prepareStatement(query);
            db.pstmt->setString(1,username);
            db.res = db.pstmt->executeQuery();

            while(db.res->next()){
                hash = db.res->getString("password");
            }


            if((hash == sha3_512(password)) && hash != ""){

                this->loginMem = this->getMember(username);
                if(loginMem == NULL) continue;
                if(loginMem->role_id == 1) this->loginType = ADMIN;
                else if(loginMem->role_id == 2) this->loginType = EDITOR;
                else if(loginMem->role_id == 3) this->loginType = VIEWER;

                this->_login = true;
            }
            else std::cout<<"Wrong Login..."<<std::endl;
            std::system("clear");

            while(this->_login){
                this->displayMainMenu();
                std::system("clear");
            }
            } catch(sql::SQLException &e){
                std::cout<<"Something went wrong..."<<std::endl;
            }
        }
    }
}

void Interface::displayMainMenu(){
    int index = 1;
    std::string choice ;
    std::cout<<"Welcome back , "<<this->loginMem->last_name<<" "<<this->loginMem->first_name<<std::endl;
    std::cout<<"Level of access : "<<this->loginType<<std::endl;
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

    if(choice == "1"){
        //reserve menu
        return;
    }

    else if(choice == "2" && this->loginMem->role_id >= 3){
        //add/remove menu
        return;
    }

    else if(choice == "3" && !this->loginMem->role_id >= 3){
        //print all reserved items and by who
        return; 
    }

    else if(choice == "4" && this->loginMem->role_id == 1){
        this->RegisterMember();
    }

    else if(choice == "5" && this->loginMem->role_id == 1){
        //print all members and dets
        return;
    }

    else std::cout<<"Not a valid choice"<<std::endl;
}

void Interface::RegisterMember(){
    bool validation = false;
    std::string query = "INSERT INTO user(username,email,first_name,last_name,password,role_id) VALUES (?,?,?,?,?,?)";
    std::string first_name , last_name , email ,role_id ,username , password , hashpass ;
    std::cout<<"Enter First Name >> ";
    std::cin>>first_name;
    validation = isValidString(first_name);
    std::cout<<"Enter Last Name >> ";
    std::cin>>last_name;
    validation = isValidString(last_name);
    std::cout<<"Enter email >> ";
    std::cin>>email;
    validation = isValidEmail(email);
    std::cout<<"Admin set role_id (1-3) >> ";
    std::cin>>role_id;
    validation = isValidInteger(role_id);
    std::cout<<"Enter Username>> ";
    std::cin>>username;
    validation = isValidString(username);
    std::cout<<"Enter Password >> ";
    std::cin>>password;
    validation = isValidString(password);

    hashpass = sha3_512(password);

    std::cout<<"username : "<<username<<"\npassword : "<<password<<"\nSalt : "<<hashpass<<std::endl;

    if(validation){
        db.pstmt = db.con->prepareStatement(query);
        db.pstmt->setString(1,username);
        db.pstmt->setString(2,email);
        db.pstmt->setString(3,first_name);
        db.pstmt->setString(4,last_name);
        db.pstmt->setString(5,hashpass);
        db.pstmt->setInt(6,std::stoi(role_id));
        
        db.res = db.pstmt->executeQuery();

        while(db.res->next()){
            std::cout<<"Query Status"<<db.res->rowInserted()<<std::endl;
        }
    }else{
        std::cout<<"bad character detected!"<<std::endl;
    }

}