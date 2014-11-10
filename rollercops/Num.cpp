//
//  Num.cpp
//  Rollercops
//
//  Created by kevin segaud on 11/9/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#include <string>

#include "Num.h"

Int::Int() : RCObject("Int"), _number(0) {}

Int::Int(int number) : RCObject("Int"), _number(number) {}

Int::Int(float number) : RCObject("Int"), _number(static_cast<int>(number)) {}

Int::Int(double number) : RCObject("Int"), _number(static_cast<int>(number)) {}

Int::Int(const Num& number) : RCObject("Int"), _number(number.toInt()) {}

Int::Int(Num* number) : RCObject("Int"), _number(number->toInt()) {}

Int::~Int() {
    Logger::root->log(Level::INFO, "Int dtor");
}

int Int::toInt() const {
    return (_number);
}

float Int::toFloat() const {
    return (static_cast<float>(_number));
}

double Int::toDouble() const {
    return (static_cast<double>(_number));
}

std::string Int::toString() const {
    std::ostringstream ss;
    ss << _number;
    return (ss.str());
}

void Int::operator=(Num* number) {
    _number = number->toInt();
}

void Int::operator=(const Num& number) {
    _number = number.toInt();
}

void Int::operator=(int number) {
    _number = static_cast<int>(number);
}

void Int::operator=(float number) {
    _number = static_cast<int>(number);
}

void Int::operator=(double number) {
    _number = static_cast<int>(number);
}

std::string Int::addPrefix(Num* minSize, Num* numberToAddBefore) const {
    std::string before = numberToAddBefore->toString();
    std::string base = toString();

    while (base.length() < minSize->toInt()) {
        base = before + base;
    }
    delete minSize;
    delete numberToAddBefore;
    return (base);
}

std::string Int::addPrefix(const Num& minSize, const Num& numberToAddBefore) const {
    std::string before = numberToAddBefore.toString();
    std::string base = toString();
    
    while (base.length() < minSize.toInt()) {
        base = before + base;
    }
    return (base);
}
