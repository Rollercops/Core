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

template<class T>
class Num {
 private:
    T _number;

 public:
    explicit Num(T number) : _number(number) {}

    ~Num() {}

    T getNumber() const {
        return (_number);
    }

    std::string toString() const {
        std::ostringstream ss;
        ss << _number;
        return (ss.str());
    }

    void operator=(Num<T>* number) {
        _number = number->getNumber();
    }

    std::string addPrefix(Num<T>* minSize,
                          Num<T>* numberToAddBefore) {
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
class Num <int> {
    int _number;

 public:
    explicit Num(int number) : _number(number) {}

    int getNumber() const {
        return (_number);
    }

    float toFloat() const {
        return (static_cast<float>(_number));
    }

    double toDouble() const {
        return (static_cast<double>(_number));
    }

    std::string toString() const {
        std::ostringstream ss;
        ss << _number;
        return (ss.str());
    }

    void operator=(Num<int>* number) {
        _number = number->getNumber();
    }

    std::string addPrefix(Num<int>* minSize,
                          Num<int>* numberToAddBefore) {
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
class Num <float> {
    float _number;

 public:
    explicit Num(float number) : _number(number) {}

    float getNumber() const {
        return (_number);
    }

    int toInt() const {
        return (static_cast<int>(_number));
    }

    double toDouble() const {
        return (static_cast<double>(_number));
    }

    std::string toString() const {
        std::ostringstream ss;
        ss << _number;
        return (ss.str());
    }

    void operator=(Num<float>* number) {
        _number = number->getNumber();
    }

    std::string addPrefix(Num<float>* minSize,
                          Num<float>* numberToAddBefore) {
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
class Num <double> {
    double _number;

 public:
    explicit Num(double number) : _number(number) {}

    double getNumber() const {
        return (_number);
    }

    int toInt() const {
        return (static_cast<int>(_number));
    }

    float toFloat() const {
        return (static_cast<float>(_number));
    }

    std::string toString() const {
        std::ostringstream ss;
        ss << _number;
        return (ss.str());
    }

    void operator=(Num<double>* number) {
        _number = number->getNumber();
    }

    std::string addPrefix(Num<double>* minSize,
                          Num<double>* numberToAddBefore) {
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

template<typename T>
std::ostream& operator<<(std::ostream& os, Num<T>* number) {
    return (os << number->toString());
}

template<typename T>
std::ostream& operator<<(std::ostream& os, Num<T>& number) {
    return (os << number.toString());
}




#endif  // ROLLERCOPS_NUMBER_H_
