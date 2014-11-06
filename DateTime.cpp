//
//  DateTime.cpp
//  logging
//
//  Created by kevin segaud on 11/6/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#include "DateTime.h"

DateTime::DateTime()
{
    time_t now;
    struct tm timeinfo;
    
    time(&now);
    timeinfo = *localtime(&now);
    
    year = timeinfo.tm_year + 1900;
    month = timeinfo.tm_mon + 1;
    day = timeinfo.tm_mday;
    
    hours = timeinfo.tm_hour;
    minutes = timeinfo.tm_min;
    seconds = timeinfo.tm_sec;
}

DateTime::~DateTime()
{
    
}

std::string DateTime::yearToString() const
{
    return (numberToString(year));
}

std::string DateTime::monthToString() const
{
    return (addNumberBefore(2, 0, month));
}

std::string DateTime::dayToString() const
{
    return (addNumberBefore(2, 0, day));
}

std::string DateTime::hoursToString() const
{
    return (addNumberBefore(2, 0, hours));
}

std::string DateTime::minutesToString() const
{
    return (addNumberBefore(2, 0, minutes));
}

std::string DateTime::secondsToString() const
{
    return (addNumberBefore(2, 0, seconds));
}

std::string DateTime::toString() const
{
    return (yearToString() + "/" + monthToString() + "/" + dayToString() + " " + hoursToString() + ":" + minutesToString() + ":" + secondsToString());
}

template <typename T>
std::string numberToString(T number)
{
    std::ostringstream ss;
    ss << number;
    return (ss.str());
}

std::string addNumberBefore(int minSize, int numberToAddBefore, int number)
{
    std::string before = numberToString(numberToAddBefore);
    std::string base = numberToString(number);
    
    while (base.length() < minSize)
    {
        base = before + base;
    }
    return (base);
}
