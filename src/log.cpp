#include "log.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <ctime>

using namespace std;

fstream Logger::logstream{};
fstream Logger::img_proc_logstream{};

//bool om man vill logga i konstruktorn

/* Create and open log file, log time */
void Logger::init(bool log_img_proc) {
	logstream.open("log/log.txt", ios::app);
	if (!logstream) {
		throw runtime_error("Could not open file");
	}
	time_t now = time(nullptr);
	logstream << "\n" << put_time(localtime(&now), "%T") << " Log started " << endl;

	// Log img data
	img_proc_logstream.open("log/img_proc_log.csv", ios::app);
	if (!img_proc_logstream) {
		throw runtime_error("Could not open file");
	}
	now = time(nullptr);
	img_proc_logstream << "lat_pos , angle_l , angle_r , stop_dist" << endl;
	// img_proc_logstream << "\n" << put_time(localtime(&now), "%T") << " Log started " << endl;
}

/* Close dsafthe log file upon destruction */
void Logger::close() {
	logstream.close();
	img_proc_logstream.close();
}

/*  Write to log file */
void Logger::log(int severity, string origin, string type, float value) {
    log(severity, origin, type, to_string(value));
}

void Logger::log(int severity, string origin, string type, string value) {
    time_t now = time(nullptr) ;
    logstream << put_time(localtime(&now), "%T") << ", " << EnumStrings[severity] << ", " << origin << ", " << type << ": " << value << endl;
}

void Logger::log_img_data(image_proc_t data) {
	time_t now = time(nullptr) ;
	img_proc_logstream << "  " << data.lateral_position <<"   ,    " << data.angle_left 
						<<"    ,    " << data.angle_right <<"    ,    " << data.stop_distance << endl;
}