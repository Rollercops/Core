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

class Num;

class INum {
 public:
    virtual ~INum() {}
    virtual int toInt() const = 0;
    virtual double toDouble() const = 0;
    virtual float toFloat() const = 0;
    virtual std::string toString() const = 0;
    virtual std::string addPrefix(INum* minSize,
                                  INum* numberToAddBefore) const = 0;

    virtual void operator=(INum* number) = 0;
    virtual void operator=(const INum& number) = 0;
    virtual void operator=(int number) = 0;
    virtual void operator=(float number) = 0;
    virtual void operator=(double number) = 0;
};

class Int : public INum, public RCObject {
 private:
    int _number;

 public:
    Int();
    Int(int number);
    Int(float number);
    Int(double number);
    Int(const INum & number);
    explicit Int(INum* number);
    ~Int();

    int toInt() const;
    float toFloat() const;
    double toDouble() const;

    std::string toString() const;

    void operator=(INum* number);
    void operator=(const INum& number);
    void operator=(int number);
    void operator=(float number);
    void operator=(double number);

    std::string addPrefix(INum* minSize, INum* numberToAddBefore) const;
};


#endif  // ROLLERCOPS_NUM_H_
