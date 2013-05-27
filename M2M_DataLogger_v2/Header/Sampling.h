#ifndef SAMPLING_H_
#define SAMPLING_H_


#include "Log.h"
#include "Queue.h"
#include "SMS.h"
#include "Main.h"

int connectToSensor();
int analyzeSpecialChar(char *str, int *column, int *code);
int parsingRawData(char *rawData, lake_data *sampling_data);
int checkDataRange(lake_data *data);
int samplingData(lake_data *data);
void *thread_sampling(void * arg);

#endif /* SAMPLING_H_ */
