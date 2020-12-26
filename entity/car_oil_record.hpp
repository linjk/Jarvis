//
// Created by linjk on 2020/11/24.
// 车辆加油记录实体

#ifndef JARVIS_CAR_OIL_RECORD_HPP
#define JARVIS_CAR_OIL_RECORD_HPP

#include <iostream>
#include <vector>
#include "../utils/mysql_connector.hpp"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/smart_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace boost;
using namespace boost::gregorian;

class car_oil_record {
public:
    car_oil_record() : oilDate(date(day_clock::local_day())) {}
    explicit car_oil_record(
            float oc,
            double os,
            date oilDate = date(day_clock::local_day())
    )
    : oilCnt(oc), oilSummary(os), oilDate(oilDate) {}

    //CarOidRecord& operator += (const CarOidRecord&);

    int save(const car_oil_record&);
    int update(const car_oil_record&);
    vector<car_oil_record> getAll();

    float getOilCnt() const {
        return oilCnt;
    }
    date getOilDate() const {
        return oilDate;
    }
private:
    // 加油量
    float oilCnt{};
    // 加油金额
    double oilSummary{};
    // 加油日期
    date oilDate;
    // 距离上次加油距离天数
    days days;
    // 是否加满
    bool is_full{};


    boost::shared_ptr<mysql_connector> mySqlUtil;

    //friend CarOidRecord& __doapl(CarOidRecord* , const  CarOidRecord&);
};

int car_oil_record::save(const car_oil_record &) {
    return 0;
}

int car_oil_record::update(const car_oil_record &) {
    return 0;
}

vector<car_oil_record> car_oil_record::getAll() {
    return vector<car_oil_record>();
}

TEST(CarOilRecord, CarOilRecordInit) { /* NOLINT */
    car_oil_record carOilRecord;

    cout << "oilDate: " << to_iso_extended_string(carOilRecord.getOilDate()) << endl;

    SUCCEED();
}


#endif //JARVIS_CAR_OIL_RECORD_HPP
