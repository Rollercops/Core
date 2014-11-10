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
    virtual std::string addPrefix(Num* minSize,
                                  Num* numberToAddBefore) const = 0;

    virtual void operator=(Num* number) = 0;
    virtual void operator=(const Num& number) = 0;
    virtual void operator=(int number) = 0;
    virtual void operator=(float number) = 0;
    virtual void operator=(double number) = 0;
};

class Num : public INum, protected RCObject {
 public:
    virtual ~Num() {}
    virtual int toInt() const = 0;
    virtual double toDouble() const = 0;
    virtual float toFloat() const = 0;
    virtual std::string toString() const  = 0;
    virtual std::string addPrefix(Num* minSize,
                                  Num* numberToAddBefore) const = 0;
    
    virtual void operator=(Num* number) = 0;
    virtual void operator=(const Num& number) = 0;
    virtual void operator=(int number) = 0;
    virtual void operator=(float number) = 0;
    virtual void operator=(double number) = 0;

    Num() : RCObject("Num") {}
    Num(std::string type) : RCObject(type) {}
    Num(const Num& number) : RCObject("Int") {}
};

class Int : public Num {
 private:
    int _number;

 public:
    Int();
    explicit Int(int number);
    Int(const Num & number);
    explicit Int(Num* number);
    ~Int();

    int toInt() const;
    float toFloat() const;
    double toDouble() const;

    std::string toString() const;

    void operator=(Num* number);
    void operator=(const Num& number);
    void operator=(int number);
    void operator=(float number);
    void operator=(double number);

    std::string addPrefix(Num* minSize, Num* numberToAddBefore) const;
};


#endif  // ROLLERCOPS_NUM_H_
