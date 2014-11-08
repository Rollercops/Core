//
//  logging.cpp
//  logging
//
//  Created by kevin segaud on 11/5/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#include <string>
#include <map>

#include "./logging.h"

const Level Level::ALL = Level("ALL", 0);
const Level Level::OFF = Level("OFF", 2000);
const Level Level::FINEST = Level("FINEST", 300);
const Level Level::FINER = Level("FINER", 400);
const Level Level::FINE = Level("FINE", 500);
const Level Level::CONFIG = Level("CONFIG", 700);
const Level Level::INFO = Level("INFO", 800);
const Level Level::WARNING = Level("WARNING", 900);
const Level Level::SEVERE = Level("SEVERE", 1000);
const Level Level::SHOUT = Level("SHOUT", 1200);

Level::Level(std::string name, int value) : name(name), value(value) {}

Level::Level(const Level& level) : name(level.name), value(level.value) {}

Level::~Level() {}

bool Level::operator==(const Level& level) const {
    return (value == level.value);
}

bool Level::operator>=(const Level& level) const {
    return (value >= level.value);
}

bool Level::operator>(const Level& level) const {
    return (value > level.value);
}

bool Level::operator<=(const Level& level) const {
    return (value <= level.value);
}

bool Level::operator<(const Level& level) const {
    return (value < level.value);
}

void Level::operator=(const Level& level) {
    this->name = level.name;
    this->value = level.value;
}

int Level::compareTo(const Level& level) const {
    return (value - level.value);
}

std::string Level::toString() {
    return (name);
}

std::map<std::string, Logger*> Logger::loggers;
Logger* Logger::root = Logger::Singleton();
# if defined(__linux) || defined(__unix) || defined(__APPLE__)
pthread_mutex_t Logger::lock;
#endif

Logger::Logger() : _name(""), level(Level::INFO) {}

Logger::Logger(std::string name) : _name(name), level(Level::INFO) {}

Logger::~Logger() {}

Logger* Logger::Singleton(std::string name) {
    std::map<std::string, Logger*>::iterator it = Logger::loggers.find(name);
    if (it != loggers.end()) {
        return (it->second);
    } else {
        Logger *logger = new Logger(name);
        if (Logger::loggers.empty()) {
# if defined(__linux) || defined(__unix) || defined(__APPLE__)
            if (pthread_mutex_init(&Logger::lock, NULL) != 0) {
                throw Error("mutex init");
            }
#endif
        }
        Logger::loggers[name] = logger;
    }
    return (Logger::loggers[name]);
}

bool Logger::destroyLogger(std::string name) {
    for (std::map<std::string, Logger*>::iterator it = Logger::loggers.begin();
         it != Logger::loggers.end(); ++it) {
        if (it->first == name) {
            delete it->second;
            Logger::loggers.erase(it);
            return (true);
        }
    }
    return (false);
}

void Logger::destroyAllLogger() {
    for (std::map<std::string, Logger*>::iterator it = Logger::loggers.begin();
         it != Logger::loggers.end(); ++it) {
        delete it->second;
    }
    Logger::loggers.clear();
# if defined(__linux) || defined(__unix) || defined(__APPLE__)
    pthread_mutex_destroy(&Logger::lock);
#endif
}

bool Logger::isLoggable(const Level& lvl) const {
    return (level.value <= lvl.value);
}

void Logger::log(const Level& level, std::string message, bool addRC) const {
    if (isLoggable(level)) {
        LogRecord* lr = new LogRecord(level, message, _name);
# if defined(__linux) || defined(__unix) || defined(__APPLE__)
        pthread_mutex_lock(&Logger::lock);
#endif
        if (onRecord != NULL) {
            onRecord(lr);
            delete lr;
        } else {
            Logger::write(lr->toString(), addRC);
            delete lr;
        }
# if defined(__linux) || defined(__unix) || defined(__APPLE__)
        pthread_mutex_unlock(&Logger::lock);
#endif
    }
}

bool Logger::write(std::string message, bool addCr) {
    if (addCr) {
        message = message + "\n";
    }
    ssize_t ret = ::write(1, message.c_str(), message.length());
    if (ret == -1) {
        return (false);
    }
    return (true);
}

# if defined(__linux) || defined(__unix) || defined(__APPLE__)
pthread_mutex_t Logger::getMutex() {
    return (lock);
}
#endif

std::string Logger::getName() const {
    return (_name);
}

std::string Logger::toString() const {
    return (getName());
}

LogRecord::LogRecord(const Level& level,
                     std::string message,
                     std::string loggerName)
: _level(level),
_message(message),
_loggerName(loggerName),
_now(DateTime()) {}

std::string LogRecord::toString() const {
    return ("[" + _now.toString() + "]"
            + "[" + _level.name + "]"
            + _loggerName + ": "
            + _message);
}

void writerDebug(LogRecord *logRecord) {
    Logger::write(logRecord->toString());
}

