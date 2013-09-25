#include "./Header/Queue.h"

/*
There is no dependency in this file.
*/

int initSamplingQueue(queue_info *qinfo)
{
	int i = 0;

#ifdef DEBUG_LEVEL_3
	printf("%s: [initSamplingQueue] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	qinfo->msg_queue = (char **) malloc(sizeof(char *) * S_QUEUE_SIZE);
	if(qinfo->msg_queue == NULL)
		return ERR_QUEUE_INIT;

	for(i=0; i < S_QUEUE_SIZE; i++)
		qinfo->msg_queue[i] = (char *) malloc(sizeof(char) * MSG_SIZE);

	for(i=0; i < S_QUEUE_SIZE; i++)
		if(qinfo->msg_queue[i] == NULL)
			return ERR_QUEUE_INIT;

	qinfo->head = qinfo->tail = qinfo->num = 0;

#ifdef DEBUG_LEVEL_3
	printf("%s: [initSamplingQueue] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
	return QUEUE_INIT_DONE;
}

void freeSamplingQueue(queue_info *qinfo)
{
	int i = 0;

#ifdef DEBUG_LEVEL_3
	printf("%s: [freeSamplingQueue] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	for(i=0; i < S_QUEUE_SIZE; i++)
		free(qinfo->msg_queue[i]);

	free(qinfo->msg_queue);

#ifdef DEBUG_LEVEL_3
	printf("%s: [freeSamplingQueue] Module Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
}

int enqueueSamplingData(queue_info *qinfo, char *msg)
{
	char logBuffer[256] = "";

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [enqueueSamplingData] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

#ifdef DEBUG_LEVEL_2
	sprintf(logBuffer, "%s: Enqueue MSG is \"%s\"\n", getTimeInString(TIME_MODE_YMDHMS), msg);
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

	if(isFullSamplingQueue(qinfo) || qinfo->num >= S_QUEUE_SIZE-1)
		return ERR_FULL_QUEUE_AFTER;

	strcpy(qinfo->msg_queue[qinfo->tail], msg);
	qinfo->tail = (qinfo->tail + 1) % S_QUEUE_SIZE;
	(qinfo->num)++;

#ifdef DEBUG_LEVEL_2
	sprintf(logBuffer, "%s: Current number of Queue: %d\n", getTimeInString(TIME_MODE_YMDHMS), qinfo->num);
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

#ifdef DEBUG_LEVEL_2
	sprintf(logBuffer, "%s: Queue Head Num: %d\n%s: Queue Tail Num: %d\n", getTimeInString(TIME_MODE_YMDHMS), qinfo->head, getTimeInString(TIME_MODE_YMDHMS), qinfo->tail);
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [enqueueSamplingData] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif
	return ENQUEUE_DONE;
}

int dequeueSamplingData(queue_info *qinfo, char *msg)
{
	char logBuffer[256] = "";

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [dequeueSamplingData] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	if(isEmptySamplingQueue(qinfo) || qinfo->num < 1)
		return ERR_EMPTY_QUEUE;

	strcpy(msg, qinfo->msg_queue[qinfo->head]);
	qinfo->head = (qinfo->head + 1) % S_QUEUE_SIZE;
	(qinfo->num)--;

#ifdef DEBUG_LEVEL_2
	sprintf(logBuffer, "%s: Current number of Queue: %d\n", getTimeInString(TIME_MODE_YMDHMS), qinfo->num);
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

#ifdef DEBUG_LEVEL_2
	sprintf(logBuffer, "%s: Queue Head Num: %d\n%s: Queue Tail Num: %d\n", getTimeInString(TIME_MODE_YMDHMS), qinfo->head, getTimeInString(TIME_MODE_YMDHMS), qinfo->tail);
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

#ifdef DEBUG_LEVEL_2
	sprintf(logBuffer, "%s: Dequeue MSG is \"%s\"\n", getTimeInString(TIME_MODE_YMDHMS), msg);
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [dequeueSamplingData] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif
	return DEQUEUE_DONE;
}

int isFullSamplingQueue(queue_info *qinfo)
{
#ifdef DEBUG_LEVEL_3
	printf("%s: [isFullSamplingQueue] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	if( ((qinfo->tail+1) % S_QUEUE_SIZE) == qinfo->head )
		return TRUE;
	else
		return FALSE;
}

int isEmptySamplingQueue(queue_info *qinfo)
{
#ifdef DEBUG_LEVEL_3
	printf("%s: [isEmptySamplingQueue] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	if(qinfo->tail == qinfo->head)
		return TRUE;
	else
		return FALSE;
}
