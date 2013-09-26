#include "./Header/Notification.h"
/*
There is no dependency
*/

char notificationString[NOTIFICATION_SIZE][LOG_SIZE] = {
		"000-[Unknown Error]",
		"001-[Daemon Process Create Error]",
		"002-[Daemon Session Create Error]",
		"003-[INI File Open Error]",
		"004-[Get Config Key Match Error]",
		"005-[Set Config Key Match Error]",
		"006-[Server Address Setting Error]",
		"007-[Server Port Setting Error]",
		"008-[Administrator ID Number Setting Error]",
		"009-[Modem ID Number Setting Error]",
		"010-[Modem ID Number Getting Error]",
		"011-[Sensor ID Setting Error]",
		"012-[Sampling Period Setting Error]",
		"013-[Transferring Period Setting Error]",
		"014-[Message Max Number Setting Error]",
		"015-[NotificationDue Date Setting Error]",
		"016-[PPP Default Wait Time Error]",
		"017-[PPP Connection State Error]",
		"018-[PPP Connection Error]",
		"019-[GPS Start Error]",
		"020-[GPS Option Error]",
		"021-[Socket Create Error]",
		"022-[Socket Connect Error]",
		"023-[Modem IP Address Get Error]",
		"024-[GPS Position Information Get Error]",
		"025-[Register Modem Error]",
		"026-[Sensor Initialization Error]",
		"027-[Initialization Error]",
		"028-[System Log File Open Error]",
		"029-[Data Log File Open Error]",
		"030-[Sampling Queue Initialization Error]",
		"031-[Before Enqueueing Sampling Queue Full Error]",
		"032-[After Enqueueing Sampling Queue Full Error]",
		"033-[Sampling Queue Empty Error]",
		"034-[Data Integirty One Column Error]",
		"035-[Data Integrity Partial Error]",
		"036-[Data Integrity Unknown Error]",
		"037-[Data(spCond) Range Error]",
		"038-[Data(sal) Range Error]",
		"039-[Data(depth10) Range Error]",
		"040-[Data(chl) Range Error]",
		"041-[Data(ldo) Range Error]",
		"042-[SMS Polling Function Error]",
		"043-[SMS Invalid Command Message Error]",
		"044-[SMS Authorization User Error]",
		"045-[SMS Receive Function Error]",
		"046-[Unstable Sensor Sampling Error]",
		"047-[Insufficient Data Error]",
		"048-[Data Input Null Error]",
		"049-[Data Input Over Error]",
		"050-[Data Integrity Analyze Fail Error]",
		"051-[3RD Column Data is totally viewed as a \"###\"]",
		"052-[3RD Column Data is totally viewed as a \"???\"]",
		"053-[3RD Column Data is totally viewed as a \"***\"]",
		"054-[3RD Column Data is totally viewed as a \"~~~\"]",
		"055-[3RD Column Data is totally viewed as a \"@@@\"]",
		"056-[4TH Column Data is totally viewed as a \"###\"]",
		"057-[4TH Column Data is totally viewed as a \"???\"]",
		"058-[4TH Column Data is totally viewed as a \"***\"]",
		"059-[4TH Column Data is totally viewed as a \"~~~\"]",
		"060-[4TH Column Data is totally viewed as a \"@@@\"]",
		"061-[5TH Column Data is totally viewed as a \"###\"]",
		"062-[5TH Column Data is totally viewed as a \"???\"]",
		"063-[5TH Column Data is totally viewed as a \"***\"]",
		"064-[5TH Column Data is totally viewed as a \"~~~\"]",
		"065-[5TH Column Data is totally viewed as a \"@@@\"]",
		"066-[6TH Column Data is totally viewed as a \"###\"]",
		"067-[6TH Column Data is totally viewed as a \"???\"]",
		"068-[6TH Column Data is totally viewed as a \"***\"]",
		"069-[6TH Column Data is totally viewed as a \"~~~\"]",
		"070-[6TH Column Data is totally viewed as a \"@@@\"]",
		"071-[7TH Column Data is totally viewed as a \"###\"]",
		"072-[7TH Column Data is totally viewed as a \"???\"]",
		"073-[7TH Column Data is totally viewed as a \"***\"]",
		"074-[7TH Column Data is totally viewed as a \"~~~\"]",
		"075-[7TH Column Data is totally viewed as a \"@@@\"]",
		"076-[8TH Column Data is totally viewed as a \"###\"]",
		"077-[8TH Column Data is totally viewed as a \"???\"]",
		"078-[8TH Column Data is totally viewed as a \"***\"]",
		"079-[8TH Column Data is totally viewed as a \"~~~\"]",
		"080-[8TH Column Data is totally viewed as a \"@@@\"]",
		"081-[3RD Column Data is partially viewed as a \"###\"]",
		"082-[3RD Column Data is partially viewed as a \"???\"]",
		"083-[3RD Column Data is partially viewed as a \"***\"]",
		"084-[3RD Column Data is partially viewed as a \"~~~\"]",
		"085-[3RD Column Data is partially viewed as a \"@@@\"]",
		"086-[4TH Column Data is partially viewed as a \"###\"]",
		"087-[4TH Column Data is partially viewed as a \"???\"]",
		"088-[4TH Column Data is partially viewed as a \"***\"]",
		"089-[4TH Column Data is partially viewed as a \"~~~\"]",
		"090-[4TH Column Data is partially viewed as a \"@@@\"]",
		"091-[5TH Column Data is partially viewed as a \"###\"]",
		"092-[5TH Column Data is partially viewed as a \"???\"]",
		"093-[5TH Column Data is partially viewed as a \"***\"]",
		"094-[5TH Column Data is partially viewed as a \"~~~\"]",
		"095-[5TH Column Data is partially viewed as a \"@@@\"]",
		"096-[6TH Column Data is partially viewed as a \"###\"]",
		"097-[6TH Column Data is partially viewed as a \"???\"]",
		"098-[6TH Column Data is partially viewed as a \"***\"]",
		"099-[6TH Column Data is partially viewed as a \"~~~\"]",
		"100-[6TH Column Data is partially viewed as a \"@@@\"]",
		"101-[7TH Column Data is partially viewed as a \"###\"]",
		"102-[7TH Column Data is partially viewed as a \"???\"]",
		"103-[7TH Column Data is partially viewed as a \"***\"]",
		"104-[7TH Column Data is partially viewed as a \"~~~\"]",
		"105-[7TH Column Data is partially viewed as a \"@@@\"]",
		"106-[8TH Column Data is partially viewed as a \"###\"]",
		"107-[8TH Column Data is partially viewed as a \"???\"]",
		"108-[8TH Column Data is partially viewed as a \"***\"]",
		"109-[8TH Column Data is partially viewed as a \"~~~\"]",
		"110-[8TH Column Data is partially viewed as a \"@@@\"]",
		"111-[Data Transferring Queue is Empty]",
		"112-[Sampling Thread Down Error]",
		"113-[Transferring Thread Down Error]"
};


int checkEventFlag(int eventNo)
{
	char errorLog[LOG_SIZE] = "";
	char logBuffer[LOG_SIZE] = "";

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [checkEventFlag] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	sprintf(errorLog, "%s: ", getTimeInString(TIME_MODE_YMDHMS));
	strcat(errorLog, notificationString[eventNo-ERR_NUMBER_OFFSET]);
	writeErrorLog(errorLog);

	if(notificationFlag[eventNo-ERR_NUMBER_OFFSET] == FALSE)
		notificationFlag[eventNo-ERR_NUMBER_OFFSET] = TRUE;

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [checkEventFlag] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif
	return eventNo;
}

void makeTimeStamp(int i){
	char logBuffer[LOG_SIZE] = "";

	strcpy(t_timeStamp[i], getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_2
	if(i == 0)
		sprintf(logBuffer, "%s: Sampling Thread Time Stamp: %s\n	", getTimeInString(TIME_MODE_YMDHMS),t_timeStamp[0]);
	else if(i == 1)
		sprintf(logBuffer, "%s: Transferring Thread Time Stamp: %s\n	", getTimeInString(TIME_MODE_YMDHMS), t_timeStamp[1]);
	else if(i == 2)
		sprintf(logBuffer, "%s: Notification Thread Time Stamp: %s\n	", getTimeInString(TIME_MODE_YMDHMS), t_timeStamp[2]);
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif
}

void *thread_notification(void * arg)
{
	int i = 0;
	int sock = 0;
	int ret = 0;
	char logBuffer[LOG_SIZE] = "";
	char msg[MSG_SIZE] = "";
	char *message = NULL;
	int	notificationSendFlag[NOTIFICATION_SIZE] = {0,};
	char notificationDueDate[NOTIFICATION_SIZE][10] = {"",};
	header_info headerData;

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [Notification Thread] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	while(1) {
		sleep(atoi(sampling_period) * MINUTE);
#ifdef DEBUG_LEVEL_3
		sprintf(logBuffer,"%s: [Notification Thread] Loop Start\n", getTimeInString(TIME_MODE_YMDHMS));
		writeDebugLog(logBuffer);
		puts(logBuffer);
#endif

		for(i=0; i < NOTIFICATION_SIZE; i++) {
			if(strncmp(notificationDueDate[i], getTimeInString(TIME_MODE_YMD), 8) == 0) {
				notificationSendFlag[i] = 0;
				strcpy(notificationDueDate[i], "");
			}
		}

		for(i = 0; i < NOTIFICATION_SIZE; i++) {
			if( notificationFlag[i] == 1 && notificationSendFlag[i] == 0) {

#ifdef DEBUG_LEVEL_3
				sprintf(logBuffer, "%s: Notification Generation %d\n", getTimeInString(TIME_MODE_YMDHMS), i);
				writeDebugLog(logBuffer);
				puts(logBuffer);
#endif

				ret = tcpConnection(&sock);
#ifdef DEBUG_LEVEL_3
				sprintf(logBuffer, "%s: [tcpConnection] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
				writeDebugLog(logBuffer);
				puts(logBuffer);
#endif
				if( ret != TCP_CONNECTION_DONE )
					checkEventFlag(ret);

				sprintf(msg, "%04d", i);
				//Make header Information
#ifdef DEBUG_LEVEL_3
				sprintf(logBuffer, "%s: makeMessage Start\n", getTimeInString(TIME_MODE_YMDHMS));
				writeDebugLog(logBuffer);
				puts(logBuffer);
#endif
				headerData.msgType = MSG_TYPE_NOTICE;
				headerData.data_len = getTotalDataLength(msg);
				headerData.msg_num = 1;
				headerData.msg_len = getMSGLength(msg);
				makeHeaderInfo(&headerData);
				message = (char *)malloc(sizeof(char) * getTotalDataLength(msg) + 1);
				strcpy(message, headerData.header_msg);
				strcat(message, "/");
				strcat(message, msg);
#ifdef DEBUG_LEVEL_3
				sprintf(logBuffer, "%s: Message Result %s\n", getTimeInString(TIME_MODE_YMDHMS), message);
				writeDebugLog(logBuffer);
				puts(logBuffer);
#endif
				if( ret == TCP_CONNECTION_DONE )
					ret = write(sock, message, strlen(message));

				notificationSendFlag[i] = TRUE;
				strcpy(notificationDueDate[i], getTimeInString(DUE_DATE_YMD));
				free(message);
#ifdef DEBUG_LEVEL_3
				sprintf(logBuffer, "%s: Notification %d DueDate %s\n",getTimeInString(TIME_MODE_YMDHMS), i, getTimeInString(DUE_DATE_YMD));
				writeDebugLog(logBuffer);
				puts(logBuffer);
#endif

				close(sock);
#ifdef DEBUG_LEVEL_3
				sprintf(logBuffer, "%s: [write] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
				writeDebugLog(logBuffer);
				puts(logBuffer);
#endif
				if(ret == -1)
					checkEventFlag(ERR_REGISTER_MODEM);
			}
		}

		ret = pollSMSCommand();			// ret variable means recived msg #
#ifdef DEBUG_LEVEL_2
		printf("%s: [pollSMSCommand] Return Value: %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
#endif
		if(ret > 0) {
			ret = doSMSCommand();
#ifdef DEBUG_LEVEL_2
			printf("%s: [doSMSCommand] Return Value: %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
#endif
		}

		 makeTimeStamp(2);
	}

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [Notification Thread] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	return NULL;
}
