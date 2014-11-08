//
//  number.h
//  Rollercops
//
//  Created by kevin segaud on 11/7/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#ifndef ROLLERCOPS_NUMBER_H_
#define ROLLERCOPS_NUMBER_H_

#include <string>
#include <sstream>

#include "./RCObject.h"

template<class T>
class Number : protected RCObject {
 private:
    T _number;

 public:
    explicit Number(T number) : RCObject("Number"), _number(number) {}

    Number() {}

    T getNumber() const {
        return (_number);
    }

    std::string const toString() const {
        std::ostringstream ss;
        ss << _number;
        return (ss.str());
    }

    void operator=(Number<T>* number) {
        _number = number->getNumber();
    }
    
    void operator=(Number<T> number) {
        _number = number.getNumber();
    }
    
    void operator=(T number) {
        _number = number;
    }

    std::string addPrefix(Number<T>* minSize,
                          Number<T>* numberToAddBefore) {
        std::string before = numberToAddBefore->toString();
        std::string base = toString();

        while (base.length() < minSize->getNumber()) {
            base = before + base;
        }
        delete minSize;
        delete numberToAddBefore;
        return (base);
    }
};

template<>
class Number <int> {
    int _number;

 public:
    explicit Number(int number) : _number(number) {}

    int getNumber() const {
        return (_number);
    }

    float toFloat() const {
        return (static_cast<float>(_number));
    }

    double toDouble() const {
        return (static_cast<double>(_number));
    }

    std::string const toString() const {
        std::ostringstream ss;
        ss << _number;
        return (ss.str());
    }

    void operator=(Number<int>* number) {
        _number = number->getNumber();
    }
    
    void operator=(Number<int> number) {
        _number = number.getNumber();
    }
    
    void operator=(int number) {
        _number = number;
    }

    std::string addPrefix(Number<int> minSize,
                          Number<int> numberToAddBefore) {
        std::string before = numberToAddBefore.toString();
        std::string base = toString();

        while (base.length() < minSize.getNumber()) {
            base = before + base;
        }
        return (base);
    }
};

template<>
class Number <float> {
    float _number;

 public:
    explicit Number(float number) : _number(number) {}

    float getNumber() const {
        return (_number);
    }

    int toInt() const {
        return (static_cast<int>(_number));
    }

    double toDouble() const {
        return (static_cast<double>(_number));
    }

    std::string const toString() const {
        std::ostringstream ss;
        ss << _number;
        return (ss.str());
    }

    void operator=(Number<float>* number) {
        _number = number->getNumber();
    }
    
    void operator=(Number<float> number) {
        _number = number.getNumber();
    }
    
    void operator=(float number) {
        _number = number;
    }

    std::string addPrefix(Number<float> minSize,
                          Number<float> numberToAddBefore) {
        std::string before = numberToAddBefore.toString();
        std::string base = toString();

        while (base.length() < minSize.getNumber()) {
            base = before + base;
        }
        return (base);
    }
};

template<>
class Number <double> {
    double _number;

 public:
    explicit Number(double number) : _number(number) {}

    double getNumber() const {
        return (_number);
    }

    int toInt() const {
        return (static_cast<int>(_number));
    }

    float toFloat() const {
        return (static_cast<float>(_number));
    }

    std::string const toString() const {
        std::ostringstream ss;
        ss << _number;
        return (ss.str());
    }

    void operator=(Number<double>* number) {
        _number = number->getNumber();
    }
    
    void operator=(Number<double> number) {
        _number = number.getNumber();
    }
    
    void operator=(double number) {
        _number = number;
    }

    std::string addPrefix(Number<double> minSize,
                          Number<double> numberToAddBefore) {
        std::string before = numberToAddBefore.toString();
        std::string base = toString();

        while (base.length() < minSize.getNumber()) {
            base = before + base;
        }
        return (base);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, Number<T>* number) {
    return (os << number->toString());
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Number<T>& number) {
    return (os << number.toString());
}




#endif  // ROLLERCOPS_NUMBER_H_
