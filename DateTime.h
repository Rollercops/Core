//
//  DateTime.h
//  logging
//
//  Created by kevin segaud on 11/6/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#ifndef __logging__DateTime__
#define __logging__DateTime__

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>

class DateTime {
private:
    time_t now;
    
public:
    DateTime();
    ~DateTime();

    int year;
    int month;
    int day;
    
    int hours;
    int minutes;
    int seconds;
    
    std::string yearToString() const;
    std::string monthToString() const;
    std::string dayToString() const;
    std::string hoursToString() const;
    std::string minutesToString() const;
    std::string secondsToString() const;
    
    std::string toString() const;
};

template <typename T>
std::string numberToString(T number);
std::string addNumberBefore(int minSize, int numberToAddBefore, int number);

#endif /* defined(__logging__DateTime__) */
