//
//  RCObject.h
//  Rollercops
//
//  Created by kevin segaud on 11/8/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#ifndef ROLLERCOPS_RCObject_H_
#define ROLLERCOPS_RCObject_H_

#include <string>

class RCObject {
 protected:
    std::string _type;
    
 public:
    explicit RCObject(std::string type);
    ~RCObject();
    
    const std::string getType() const;
    
    virtual const std::string toString() const;
};

#endif  // ROLLERCOPS_RCObject_H_
