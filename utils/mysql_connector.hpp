//
// Created by linjk on 2020/9/27.
// 数据库读写工具

#ifndef JARVIS_MYSQL_CONNECTOR_HPP
#define JARVIS_MYSQL_CONNECTOR_HPP

#include <iostream>
#include <utility>
#include <mysql++/mysql++.h>
#include <gtest/gtest.h>

using namespace std;
using namespace mysqlpp;

class mysql_connector {
public:
    explicit mysql_connector(string host = "127.0.0.1", int port = 3306, string account = "root", string password = "root", string database = "jarvis")
        : host(std::move(host)), port(port), account(std::move(account)), password(std::move(password)), database(std::move(database)) {}

    bool connect();
    bool disconnect();
    vector<Row> query(string sql);

private:
    Connection connection;
    string host;
    int port;
    string account;
    string password;
    string database;
};

bool mysql_connector::connect() {
    if (!host.empty()) {
        try {
            connection =  Connection(true);
            return connection.connect(database.c_str(), host.c_str(), account.c_str(), password.c_str(), port);
        }
        catch (const Exception &er) {
            cerr << "#connect# Error: " << er.what() << endl;
            return false;
        }
    }
    cerr << "host is empty." << endl;
    return false;
}

bool mysql_connector::disconnect() {
    try {
        connection.disconnect();
    }
    catch (const Exception &er) {
        cerr << "#disconnect# Error: " << er.what() << endl;
        return false;
    }
    return false;
}

vector<Row> mysql_connector::query(string sql) {
    if (connection.connected()) {
        try {
            vector<Row> v;
            Query query = connection.query(sql);
            StoreQueryResult storeQueryResult = query.store();
            if (storeQueryResult) {
                StoreQueryResult::const_iterator it;
                for (it = storeQueryResult.begin(); it != storeQueryResult.end(); ++it) {
                    Row rowTmp = *it;
                    v.push_back(rowTmp);
                }
            }
            if (connection.errnum()) {
                cerr << "Error in fetch_row";
            }
            return v;
        }
        catch (BadQuery &er){
            cout << "Error:" << er.what() << endl;
        }
    }
    return vector<Row>();
}

TEST(mysql_connector, mysql_connector_test) { /* NOLINT */
    mysql_connector mysqlConnector("127.0.0.1", 3308, "root", "ljk121121");

    mysqlConnector.connect();

    try {
        vector<Row> useQueryResult = mysqlConnector.query("select * from car_oil");
        int size = useQueryResult.size();
        for (int i = 0; i < size; i++) {
            cout << "i = " << i << ", " << useQueryResult.at(i)["oil_summary"] << endl;
        }
    }
    catch (const BadConversion &er){
        cout << "Conversion error: " << er.what() << endl <<
             "\tretrieved data size: " << er.retrieved <<
             ", actual size: " << er.actual_size << endl;
    }

    mysqlConnector.disconnect();
    SUCCEED();
}

#endif //JARVIS_MYSQL_CONNECTOR_HPP
