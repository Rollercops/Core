//
//  Error.h
//  Rollercops
//
//  Created by kevin segaud on 11/8/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#ifndef ROLLERCOPS_ERROR_H_
#define ROLLERCOPS_ERROR_H_

#include <string>

#include "./RCObject.h"

class Error : protected RCObject {
 public:
    Error();
    explicit Error(std::string type);

    virtual std::string toString() const;
};

#endif  // ROLLERCOPS_ERROR_H_
