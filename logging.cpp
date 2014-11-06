//
//  logging.cpp
//  logging
//
//  Created by kevin segaud on 11/5/14.
//  Copyright (c) 2014 kevin segaud. All rights reserved.
//

#include "logging.h"

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

Level::Level(std::string name, int value) : name(name), value(value)
{
    
}

Level::Level(const Level& level) : name(level.name), value(level.value)
{

}

Level::~Level()
{
    
}

bool Level::operator==(const Level& level) const
{
    return (value == level.value);
}

bool Level::operator>=(const Level& level) const
{
    return (value >= level.value);
}

bool Level::operator>(const Level& level) const
{
    return (value > level.value);
}

bool Level::operator<=(const Level& level) const
{
    return (value <= level.value);
}

bool Level::operator<(const Level& level) const
{
    return (value < level.value);
}

void Level::operator=(const Level& level)
{
    this->name = level.name;
    this->value = level.value;
}

int Level::compareTo(const Level& level) const
{
    return (value - level.value);
}

std::string Level::toString()
{
    return (name);
}

//  Logger
std::map<std::string, Logger*> Logger::loggers;
Logger* Logger::root = Logger::Singleton();

Logger::Logger() : _name(""), level(Level::INFO)
{

}

Logger::Logger(std::string name) : _name(name), level(Level::INFO)
{

}

Logger* Logger::Singleton(std::string name)
{
    std::map<std::string, Logger*>::iterator it = Logger::loggers.find(name);
    if (it != loggers.end())
    {
        return (it->second);
    }
    else
    {
        Logger *logger = new Logger(name);
        Logger::loggers[name] = logger;
    }
    return (Logger::loggers[name]);
}

bool Logger::isLoggable(const Level& lvl) const
{
    return (level.value <= lvl.value);
}

void Logger::log(const Level& level, std::string message) const
{
    if (isLoggable(level))
    {
        LogRecord* lr = new LogRecord(level, message, _name);
        //  push lr sur un stream histoire que la personne en fasse ce qu'elle veut
        if (onRecord != nullptr)
        {
            onRecord(lr);
        }
        else
        {
            std::cout << lr->toString() << std::endl;
        }
    }
}

std::string Logger::getName() const
{
    return (_name);
}

std::string Logger::toString() const
{
    return (getName());
}


LogRecord::LogRecord(const Level& level, std::string message, std::string loggerName) : level(level), message(message), loggerName(loggerName), now(DateTime())
{
    
}

std::string LogRecord::toString() const
{
    return ("[" + now.toString() + "]" + "[" + level.name + "]" + loggerName + ": " + message);
}

void writerDebug(LogRecord *logRecord)
{
    std::cout << logRecord->toString() << std::endl;
}
