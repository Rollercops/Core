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

class Error {
protected:
    const std::string type;
    
public:
    explicit Error(std::string type);
    
    virtual std::string toString();
};

#endif  // ROLLERCOPS_ERROR_H_
