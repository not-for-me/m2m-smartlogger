#include "./Header/Transferring.h"

int checkConnection()
{
#ifdef DEBUG_LEVEL_3
	printf("%s: [checkConnection] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	if( mnet_getstate() < 1 )
		return checkEventFlag(ERR_PPP_DISCONNECT);
	else {
#ifdef DEBUG_LEVEL_3
		printf("%s: Checking the Network Connection State... [OK]\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
		return PPP_CONNECTION_CHK_DONE;
	}
}

int tcpConnection(int *sock)
{
	struct sockaddr_in serv_addr;

#ifdef DEBUG_LEVEL_3
	printf("%s: [tcpConnection] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	*sock = socket(PF_INET, SOCK_STREAM, 0);
	if(*sock == -1)
		return checkEventFlag(ERR_SOCKET_CREATE);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(server_addr);
	serv_addr.sin_port = htons(atoi(server_port));

	if(connect(*sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		return checkEventFlag(ERR_SOCKET_CONNECT);


#ifdef DEBUG_LEVEL_3
	printf("%s: [tcpConnection] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	return TCP_CONNECTION_DONE;
}

int transferData(int sock)
{
	unsigned short i = 0;
	int ret = 0;
	char msg[MSG_SIZE]= "";
	char logBuffer[LOG_SIZE] ="";
	char *packaging_msg = NULL;
	char *message = NULL;
	header_info headerData;


#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [transferData] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	while(1){
		packaging_msg = (char *) malloc(sizeof(char) * atoi(message_max_num) * MSG_SIZE);
		strcpy(packaging_msg, "");

		for(i=0; i < atoi(message_max_num); i++) {
			if(i > 0)
				strcat(packaging_msg, MSG_DELIMITER);

			pthread_mutex_lock(&mutex);
			ret = dequeueSamplingData(&sqinfo, msg);
			pthread_mutex_unlock(&mutex);

			if(ret == ERR_EMPTY_QUEUE) {
				free(packaging_msg);
				return checkEventFlag(ERR_TRANSFER_DATA_NONE);
			}

			strcat(packaging_msg, msg);

			if(isEmptySamplingQueue(&sqinfo))
				break;
		}

#ifdef DEBUG_LEVEL_3
		sprintf(logBuffer, "%s: Packaged MSG: %s\n", getTimeInString(TIME_MODE_YMDHMS), packaging_msg);
		writeDebugLog(logBuffer);
		puts(logBuffer);
#endif

		//Make header Information
#ifdef DEBUG_LEVEL_3
		printf("%s: makeMessage Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
		headerData.msgType = MSG_TYPE_DATA;
		headerData.data_len = getTotalDataLength(packaging_msg);
		headerData.msg_num = i+1;
		headerData.msg_len = getMSGLength(packaging_msg);
		makeHeaderInfo(&headerData);
		message = (char *)malloc(sizeof(char) * getTotalDataLength(packaging_msg) + 1);
		strcpy(message, headerData.header_msg);
		strcat(message, "/");
		strcat(message, packaging_msg);
#ifdef DEBUG_LEVEL_3
		printf("%s: Message Result %s\n", getTimeInString(TIME_MODE_YMDHMS), message);
#endif

		ret = write(sock, message, strlen(message));
#ifdef DEBUG_LEVEL_3
		printf("%s: [write] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
#endif
		free(message);
		free(packaging_msg);
		if(isEmptySamplingQueue(&sqinfo))
			break;

	}
	close(sock);

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [transferData] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif
	return DATA_TRANSFER_DONE;
}

void makeHeaderInfo(header_info *headerData)
{
	char msgDate[9] = "";
	char msgTime[7] = "";
	char msg_type[3] = "";
	char data_len_str[5] = "";
	char modem_sn_str[12] = "";
	char sensor_sn_str[7] = "";
	char sampling_prd[3] = "";
	char msg_num_str[4] = "";
	char msg_len_str[5] = "";

#ifdef DEBUG_LEVEL_3
	printf("%s: [makeHeaderInfo] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	strcpy(msgDate, getTimeInString(TIME_MODE_YMD));
	strcpy(msgTime, getTimeInString(TIME_MODE_HMS));
	sprintf(msg_type, "%02d", headerData->msgType);
	sprintf(data_len_str, "%04d", headerData->data_len);
	strcpy(modem_sn_str, modem_ID);
	sprintf(sensor_sn_str, "%06d", atoi(sensor_ID));
	sprintf(sampling_prd, "%02d", atoi(sampling_period));
	sprintf(msg_num_str, "%03d", headerData->msg_num);
	sprintf(msg_len_str, "%04d", headerData->msg_len);
	sprintf(headerData->header_msg,"%s,%s,%s,%s,%s,%s,%s,%s,%s", msgDate, msgTime, msg_type, data_len_str, modem_sn_str, sensor_sn_str, sampling_prd, msg_num_str, msg_len_str);

#ifdef DEBUG_LEVEL_3
	printf("%s: [makeHeaderInfo] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
}


void *thread_transferring(void * arg)
{
	int sock = 0;
	int ret = 0;
	int delay = 0;
	char logBuffer[LOG_SIZE] = "";
	char debugLog[LOG_SIZE] = "";

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [Transferring Thread] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	while(t_flag == THREAD_ON){
		sleep(atoi(transferring_period) * MINUTE);


		if(delay == RECONN_1ST_PRD || delay == RECONN_2ND_PRD) {
			// Try Reconnection
#ifdef DEBUG_LEVEL_3
			sprintf(debugLog, "%s: Transferring Thread-Try Reconnection State\n", getTimeInString(TIME_MODE_YMDHMS));
			writeDebugLog(debugLog);
			puts(debugLog);
#endif
			ret = connectPPP(DEFAULT_CONN_WAIT_TIME);
			if(ret == ERR_CONNECT_PPP) {
				if(delay == RECONN_2ND_PRD)
					delay = RECONN_1ST_PRD;
				else {
					delay++;
					makeTimeStamp(1);
					continue;
				}
			}

			else if(ret == PPP_CONNECTION_DONE ) {
				delay = DELAY_FLAG_OFF;
				ret = registerModem();
			}
		}

		// Checking Communication State
#ifdef DEBUG_LEVEL_3
		sprintf(debugLog, "%s: Transferring Thread-Checking Communication State\n", getTimeInString(TIME_MODE_YMDHMS));
		writeDebugLog(debugLog);
		puts(debugLog);
#endif
		if(delay == DELAY_FLAG_OFF ) {
			ret = checkConnection();

			if(ret == ERR_PPP_DISCONNECT) {
				ret = connectPPP(DEFAULT_CONN_WAIT_TIME);
				if(ret == ERR_CONNECT_PPP) {
					delay++;
					makeTimeStamp(1);
					continue;
				}
			}
		}

		// Connect to the Server with Socket
#ifdef DEBUG_LEVEL_3
		sprintf(debugLog, "%s: Transferring Thread-Connect to the Server with Socket\n", getTimeInString(TIME_MODE_YMDHMS));
		writeDebugLog(debugLog);
		puts(debugLog);
#endif
		if(delay == DELAY_FLAG_OFF ) {
			ret = tcpConnection(&sock);
			if(ret != TCP_CONNECTION_DONE) {
				sleep(SOCK_CONN_WAIT_TIME);
				ret = tcpConnection(&sock);
				if(ret != TCP_CONNECTION_DONE) {
					delay++;
					ret = sms_msg_send(admin_phone_num, modem_ID,
							"Socket Error - Check Server' state");
					makeTimeStamp(1);
					continue;
				}
			}
		}

		// dequeue, packaging and making MSGs
#ifdef DEBUG_LEVEL_3
		sprintf(debugLog, "%s: Transferring Thread-dequeue, packaging and making MSGs\n", getTimeInString(TIME_MODE_YMDHMS));
		writeDebugLog(debugLog);
		puts(debugLog);
#endif
		if(delay == DELAY_FLAG_OFF)
			ret = transferData(sock);

		if(delay > 0)
			delay++;

		makeTimeStamp(1);
	}

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [Transferring Thread] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	return NULL;
}
