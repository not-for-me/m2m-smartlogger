#ifndef INIT_H_
#define INIT_H_

#include "Main.h"

#define INI_FILE_PATH "/data/m2m.ini"

int getConfValue(char *key, char *value);
int setConfValue(char *key, char *value);
int setConfiguration();
int connectPPP(int defaultTime);
int checkSensor();
int registerModem();
int initialize();

#endif /* INIT_H_ */
