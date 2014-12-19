//
//  RCObject.cpp
//  Rollercops
//
//  Created by kevin segaud on 11/8/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#include <string>

#include "RCObject.h"

RCObject::RCObject(std::string type) : _type(type) {}

RCObject::~RCObject() {}

const std::string RCObject::getType() const {
    return (_type);
}

std::string RCObject::toString() const {
    return (_type);
}
