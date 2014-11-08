//
//  logging.h
//  logging
//
//  Created by kevin segaud on 11/5/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#ifndef ROLLERCOPS_LOGGING_H_
#define ROLLERCOPS_LOGGING_H_

#include <stdio.h>

#include <string>
#include <map>

#include "./DateTime.h"

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
    const Level _level;
    const std::string _message;
    const std::string _loggerName;
    const DateTime _now;
    
public:
    LogRecord(const Level& level, std::string message, std::string loggerName);

    std::string toString() const;
};

class Logger {
 private:
    const std::string _name;

    Logger();
    explicit Logger(std::string name);
    ~Logger();

 public:
    static Logger* root;
    static std::map<std::string, Logger*> loggers;
    static Logger* Singleton(std::string name = "");
    static bool write(std::string message, bool addRc = true);
    static bool destroyLogger(std::string name);
    static void destroyAllLogger();

    void (*onRecord)(LogRecord* logRecord);
    Level level;

    bool isLoggable(const Level& level) const;
    void log(const Level& level, std::string message, bool addRc = true) const;

    std::string getName() const;
    std::string toString() const;
};

void writerDebug(LogRecord* logRecord);

#endif  // ROLLERCOPS_LOGGING_H_
