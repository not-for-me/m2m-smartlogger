#ifndef LOG_H_
#define LOG_H_

#include "Main.h"

// FILE PATH MACRO
#define DEBUG_LOG_PATH "/data/log/m2m_debug.log"
#define SYSTEM_LOG_PATH "/data/log/m2m_system.log"
#define ERROR_LOG_PATH "/data/log/m2m_error.log"
#define DATA_LOG_PATH "/data/"
#define DATA_FILE_TYPE ".txt"


// TIME STRING TYPE MACRO
#define TIME_MODE_YMDHMS_HYPHEN 201
#define TIME_MODE_YMDHMS 202
#define TIME_MODE_YMD_HYPHEN 203
#define TIME_MODE_YMD 204
#define TIME_MODE_HMS 205
#define TIME_MODE_HOUR 206
#define TIME_MODE_MIN 207
#define TIME_MODE_SEC 208
#define TIME_MODE_YEAR 209
#define TIME_MODE_MONTH 210
#define TIME_MODE_DAY 211
#define DUE_DATE_YMD 212

void writeDebugLog(char* str);
int writeSystemLog(char* str);
void writeErrorLog(char* str);
int writeDataLog(char* str);
char *getTimeInString(int mode);

#endif /* LOG_H_ */
