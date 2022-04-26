#include "log.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <ctime>

std::fstream Logger::logstream{};
std::fstream Logger::img_proc_logstream{};

//bool om man vill logga i konstruktorn

/* Create and open log file, log time */
void Logger::init(bool log_img_proc) {
	logstream.open("log/log.txt", std::ios::app);
	if (!logstream) {
		throw std::runtime_error("Could not open file");
	}
	time_t now = time(nullptr);
	logstream << "\n" << std::put_time(localtime(&now), "%T") << " Log started " << std::endl;

	// Log img data
	img_proc_logstream.open("log/img_proc_log.txt", std::ios::app);
	if (!img_proc_logstream) {
		throw std::runtime_error("Could not open file");
	}
	now = time(nullptr);
	img_proc_logstream << "\n" << std::put_time(localtime(&now), "%T") << " Log started " << std::endl;
}

/* Close dsafthe log file upon destruction */
void Logger::close() {
	logstream.close();
	img_proc_logstream.close();
}

/*  Write to log file */
void Logger::log(int severity, std::string origin, std::string type, float value) {
    log(severity, origin, type, std::to_string(value));
}

void Logger::log(int severity, std::string origin, std::string type, std::string value) {
    time_t now = time(nullptr) ;
    logstream << std::put_time(localtime(&now), "%T") << ", " << EnumStrings[severity] << ", " << origin << ", " << type << ": " << value << std::endl;
}

void Logger::log_img_data(image_proc_t data) {
	time_t now = time(nullptr) ;
	img_proc_logstream << std::put_time(localtime(&now), "%T") << ", " << data.lateral_position <<" : "<< data.angle_left 
						<<" : "<< data.angle_right <<" : "<< data.stop_distance << std::endl;
}