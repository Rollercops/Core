//
//  Error.cpp
//  Rollercops
//
//  Created by kevin segaud on 11/8/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#include "Error.h"

Error::Error(std::string type) : RCObject(type) {}

const std::string Error::toString() const {
    return (_type);
}