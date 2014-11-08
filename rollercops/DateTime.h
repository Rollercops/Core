//
//  DateTime.h
//  Rollercops
//
//  Created by kevin segaud on 11/6/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#ifndef ROLLERCOPS_DATETIME_H_
#define ROLLERCOPS_DATETIME_H_

#include <ctime>
#include <string>
#include <sstream>

#include "./number.h"

class DateTime {
 private:
    time_t _date_time;

 public:
    DateTime();
    ~DateTime();

    Number<int>* year;
    Number<int>* month;
    Number<int>* day;

    Number<int>* hours;
    Number<int>* minutes;
    Number<int>* seconds;

    std::string toString() const;
};

#endif  // ROLLERCOPS_DATETIME_H_
