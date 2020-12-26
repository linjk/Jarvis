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
    Row query(string sql);

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

Row mysql_connector::query(string sql) {
    if (connection.connected()) {
        try {
            Query query = connection.query(sql);
            UseQueryResult res = query.use();
            Row row = res.fetch_row();
            if (connection.errnum()) {
                cerr << "Error in fetch_row";
            }
            row.value_list()
            return res.;
        }
        catch (BadQuery &er){
            cout << "Error:" << er.what() << endl;
        }
    }
    return Row();
}

TEST(mysql_connector, mysql_connector_test) { /* NOLINT */
    mysql_connector mysqlConnector("127.0.0.1", 3308, "root", "ljk121121");

    mysqlConnector.connect();

    try {
        Row useQueryResult = mysqlConnector.query("select * from car_oil");
        while (Row row = useQueryResult.fetch_row()) {
            cout << row["oil_summary"] << endl;
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
