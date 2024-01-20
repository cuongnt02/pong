#ifndef LOG_H
#define LOG_H


#include <string>

void log_print(std::string message="undefined error message", std::string filename = __FILE__, int line = __LINE__);
int log_init(std::string filename);
void log_close();

#endif
