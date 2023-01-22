#pragma once
#include <iostream>


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
        cout<<con<<endl;
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
            cout << res->getString("column_name") << endl;
        }
    }
    void close() {
        // clean up
        delete res;
        delete stmt;
        delete con;
    }
};