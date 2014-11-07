//
//  DateTime.cpp
//  logging
//
//  Created by kevin segaud on 11/6/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#include <string>

#include "./DateTime.h"

DateTime::DateTime() {
    time_t now;
    struct tm timeinfo;

    time(&now);
    localtime_r(&now, &timeinfo);

    year = new Num<int>(timeinfo.tm_year + 1900);
    month =  new Num<int>(timeinfo.tm_mon + 1);
    day =  new Num<int>(timeinfo.tm_mday);

    hours = new Num<int>(timeinfo.tm_hour);
    minutes = new Num<int>(timeinfo.tm_min);
    seconds = new Num<int>(timeinfo.tm_sec);
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
            + month->addPrefix(new Num<int>(2),
                               new Num<int>(0)) + "/"
            + day->addPrefix(new Num<int>(2),
                             new Num<int>(0)) + " "
            + hours->addPrefix(new Num<int>(2),
                               new Num<int>(0)) + ":"
            + minutes->addPrefix(new Num<int>(2),
                                 new Num<int>(0)) + ":"
            + seconds->addPrefix(new Num<int>(2),
                                 new Num<int>(0)));
}
