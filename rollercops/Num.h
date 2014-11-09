//
//  Num.h
//  Rollercops
//
//  Created by kevin segaud on 11/9/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#ifndef ROLLERCOPS_NUM_H_
#define ROLLERCOPS_NUM_H_

#include <stdio.h>

#include <sstream>
#include <string>

#include "./RCObject.h"

class Num {
 public:
    virtual ~Num() {};

    virtual int toInt() const = 0;

    virtual double toDouble() const = 0;

    virtual float toFloat() const = 0;

    virtual std::string toString() const = 0;

    virtual std::string addPrefix(Num* minSize, Num* numberToAddBefore) const = 0;
};

class Int : public Num, protected RCObject {
 private:
    int _number;

 public:
    Int() : RCObject("Int") {
        _number = 0;
    }

    Int(int number) : RCObject("Int") {
        _number = number;
    }

    Int(const Int & number) : RCObject("Int") {
        _number = number.toInt();
    }

    Int(Int* number) : RCObject("Int") {
        _number = number->toInt();
    }

    ~Int() {};

    int toInt() const {
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
    
    void operator=(Int* number) {
        _number = number->toInt();
    }
    
    void operator=(const Int& number) {
        _number = number.toInt();
    }
    
    void operator=(int number) {
        _number = number;
    }

    std::string addPrefix(Num* minSize, Num* numberToAddBefore) const {
        std::string before = numberToAddBefore->toString();
        std::string base = toString();
        
        while (base.length() < minSize->toInt()) {
            base = before + base;
        }
        delete minSize;
        delete numberToAddBefore;
        return (base);
    }

};


#endif  // ROLLERCOPS_NUM_H_