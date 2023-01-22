#pragma once
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/connection.h>

using namespace std;
using namespace sql;


class MySQLConnect {

private:
    Driver *driver;
    Connection *con;
    Statement *stmt;
    ResultSet *res;

public:
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
                cout<<res->getString(i)<<"         ";
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