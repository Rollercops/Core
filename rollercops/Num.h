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

#include "./Logging.h"
#include "./RCObject.h"

class Num {
 public:
    virtual ~Num() {}
    virtual int toInt() const = 0;
    virtual double toDouble() const = 0;
    virtual float toFloat() const = 0;
    virtual std::string toString() const = 0;
    virtual std::string addPrefix(Num* minSize,
                                  Num* numberToAddBefore) const = 0;
    virtual std::string addPrefix(const Num& minSize,
                                  const Num& numberToAddBefore) const = 0;

    virtual void operator=(Num* number) = 0;
    virtual void operator=(const Num& number) = 0;
    virtual void operator=(int number) = 0;
    virtual void operator=(float number) = 0;
    virtual void operator=(double number) = 0;
};

class Int : public Num, public RCObject {
 private:
    int _number;

 public:
    Int();
    Int(int number);
    Int(float number);
    Int(double number);
    Int(const Num& number);
    explicit Int(Num* number);
    ~Int();

    int toInt() const;
    float toFloat() const;
    double toDouble() const;

    std::string toString() const;
    std::string addPrefix(Num* minSize, Num* numberToAddBefore) const;
    std::string addPrefix(const Num& minSize,
                          const Num& numberToAddBefore) const;

    void operator=(Num* number);
    void operator=(const Num& number);
    void operator=(int number);
    void operator=(float number);
    void operator=(double number);
};


#endif  // ROLLERCOPS_NUM_H_
