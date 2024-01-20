#include "log.h"
#include "globals.h"
#include <iostream>
#include <chrono>
#include <sstream>


int log_init(std::string filename) {
   outfile.open(filename, std::ios::out); 
   if (!outfile.is_open()) {
       return 0;
   }
   return 1;
}

void log_print(std::string message, std::string filename, int line) {
    outfile << "FILE: " << filename << " at line " << line << ": " << message << '.' << std::endl;
}

void log_close() {
    const auto time_now = std::chrono::system_clock::now();
    const std::time_t log_time = std::chrono::system_clock::to_time_t(time_now);
    
    log_print("INFO: " + std::string(std::ctime(&log_time)));
    log_print("INFO: Log closed.");

    outfile.close();
}


