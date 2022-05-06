#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

#include "raspi_common.h"

enum severity{INFO, DEBUG, WARNING, ERROR};
static const char * EnumStrings[] = { "INFO", "DEBUG", "WARNING", "ERROR" };

class Logger {
public:
    static void init(bool log_img_proc = false);
    static void close();

    /* Use by writing 'Logger::log(LEVEL, SOURCE, LABEL, VALUE)',
       where LEVEL is  one of [INFO, DEBUG, WARNING, ERROR], SOURCE is the current filename,
       LABEL describes the value (e.g. datatype or current method) */
    static void log(int serverity, std::string origin, std::string type, std::string value);
    static void log(int serverity, std::string origin, std::string type, float value);
    static void log_img_data(image_proc_t data);

private:
    Logger() {}
    static std::fstream logstream;
    static std::fstream img_proc_logstream;
    static std::mutex mtx;

};


#endif  // LOGGER_H
