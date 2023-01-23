#pragma once
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/connection.h>
#include <regex>

using namespace std;
using namespace sql;




bool isValidEmail(const std::string& email) {
    // Regular expression for email validation
    std::regex pattern("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
    return std::regex_match(email, pattern);
}

bool isValidInteger(const std::string& input) {
    // check if all the characters are digits
    return input.find_first_not_of("0123456789") == std::string::npos;
}

bool isValidString(const std::string& input) {
    // check if the input contains only alphanumeric characters and spaces
    return input.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ") == std::string::npos;
}


class MySQLConnect {

private:


public:

    Driver *driver;
    Connection *con;
    PreparedStatement *pstmt;
    Statement *stmt;
    ResultSet *res;

    MySQLConnect(){
        // create connection object
        driver = get_driver_instance();
    }
    void connect(string server, string username, string password,string dbname) {
        con = driver->connect(server, username, password);
        con->setSchema(dbname);
    }
    void executeSQL(string sql) {
        // execute SQL statement
        stmt = con->createStatement();
        res = stmt->executeQuery(sql);
    }
    void printResult() {
        // print results
        while (res->next()) {
            for(int i=1;i<=res->getMetaData()->getColumnCount();i++){
                cout<<res->getMetaData()->getColumnLabel(i)<<"       ";
            }
            cout<<endl;
            for(int i=1;i<=res->getMetaData()->getColumnCount();i++){
                cout<<res->getString(i)<<"       ";
            }
            cout<<endl;
        }
    }

    void clearBuff(){
        // clean buff
        delete res;
        delete stmt;
    }
    void close() {
        // clean up
        delete res;
        delete stmt;
        delete con;
    }
};