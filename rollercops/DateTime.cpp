//
//  DateTime.cpp
//  Rollercops
//
//  Created by kevin segaud on 11/6/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#include <string>

#include "./DateTime.h"

DateTime::DateTime() {
    time_t _date_time;
    struct tm timeinfo;

    time(&_date_time);
    localtime_r(&_date_time, &timeinfo);

    year = new Number<int>(timeinfo.tm_year + 1900);
    month =  new Number<int>(timeinfo.tm_mon + 1);
    day =  new Number<int>(timeinfo.tm_mday);

    hours = new Number<int>(timeinfo.tm_hour);
    minutes = new Number<int>(timeinfo.tm_min);
    seconds = new Number<int>(timeinfo.tm_sec);
}

DateTime::~DateTime() {
    delete year;
    delete month;
    delete day;
    delete hours;
    delete minutes;
    delete seconds;
}

std::string DateTime::toString() const {
    return (year->toString() + "/"
            + month->addPrefix(Number<int>(2),
                               Number<int>(0)) + "/"
            + day->addPrefix(Number<int>(2),
                             Number<int>(0)) + " "
            + hours->addPrefix(Number<int>(2),
                               Number<int>(0)) + ":"
            + minutes->addPrefix(Number<int>(2),
                                 Number<int>(0)) + ":"
            + seconds->addPrefix(Number<int>(2),
                                 Number<int>(0)));
}
