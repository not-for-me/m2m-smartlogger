#ifndef QUEUE_H_
#define QUEUE_H_

#include "Log.h"
#include "Main.h"

int initSamplingQueue(queue_info *qinfo);
void freeSamplingQueue(queue_info *qinfo);
int enqueueSamplingData(queue_info *qinfo, char *msg);
int dequeueSamplingData(queue_info *qinfo, char *msg);
int isFullSamplingQueue(queue_info *qinfo);
int isEmptySamplingQueue(queue_info *qinfo);

#endif /* QUEUE_H_ */
