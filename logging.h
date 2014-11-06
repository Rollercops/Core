//
//  logging.h
//  logging
//
//  Created by kevin segaud on 11/5/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#ifndef __logging__logging__
#define __logging__logging__

#include <iostream>
#include <string>
#include <list>
#include <map>

#include "DateTime.h"

class Level {

public:
    static const Level ALL;
    static const Level OFF;
    static const Level FINEST;
    static const Level FINER;
    static const Level FINE;
    static const Level CONFIG;
    static const Level INFO;
    static const Level WARNING;
    static const Level SEVERE;
    static const Level SHOUT;

    Level(std::string name, int value);
    Level(const Level& level);
    ~Level();
    
    bool operator==(const Level& level) const;
    bool operator>=(const Level& level) const;
    bool operator>(const Level& level) const;
    bool operator<=(const Level& level) const;
    bool operator<(const Level& level) const;

    void operator=(const Level& level);
    
    int compareTo(const Level& level) const;
    
    std::string toString();
    
    std::string name;
    int value;
};

class LogRecord {
    
public:
    Level level;
    const std::string message;
    const std::string loggerName;
    
    //  ajoute la Date et l'heure
    const DateTime now;
    
    LogRecord(const Level& level, std::string message, std::string loggerName);
    
    std::string toString() const;
};

class Logger {
    
private:
    const std::string _name;
    
    Logger();
    Logger(std::string name);
    
public:
    static Logger* root;
    static std::map<std::string, Logger*> loggers;
    static Logger* Singleton(std::string name = "");
    
    void (*onRecord)(LogRecord* logRecord);
    Level level;
    
    bool isLoggable(const Level& level) const;
    void log(const Level& level, std::string message) const;
    
    std::string getName() const;
    std::string toString() const;
};

void writerDebug(LogRecord* logRecord);




#endif /* defined(__logging__logging__) */
