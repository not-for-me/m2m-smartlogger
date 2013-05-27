#include "./Header/SMS.h"

int pollSMSCommand()
{
	int ret = 0;
	int recv_cnt = 0;
	int unread_cnt = 0;

#ifdef DEBUG_LEVEL_3
	printf("%s: [pollSMSCommand] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	ret = sms_recv_msg_count(&recv_cnt, &unread_cnt);
	if(ret != 1) {
		//Error Handling
		return ERR_SMS_POLLING;
	}

#ifdef DEBUG_LEVEL_3
	printf("%s: number of recv msg is %d, number of unread msg is %d\n", getTimeInString(TIME_MODE_YMDHMS), recv_cnt, unread_cnt);
#endif

	return unread_cnt;
}

int doSMSCommand()
{
	int ret = 0;
	int recv_cnt = 0;
	int unread_cnt = 0;
	unsigned short i = 0;
	sms_cmd parsedResult;
	sms_msg smsmsg;
	char msgbuf[80] = "";
	char adminNumBuf[20] = "";

#ifdef DEBUG_LEVEL_3
	printf("%s: [doSMSCommand] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	ret = sms_recv_msg_count(&recv_cnt, &unread_cnt);
	if(ret != 1) {
		//Error Handling
		return ERR_SMS_RCV;
	}

	i = unread_cnt;

	while(i > 0) {
		sms_read_msg(i-1, &smsmsg);
		strcpy(adminNumBuf, smsmsg.source_num);
		strcpy(msgbuf,smsmsg.messages);
#ifdef DEBUG_LEVEL_3
		printf("%s: SMS Message is \"%s\"\n", getTimeInString(TIME_MODE_YMDHMS), msgbuf);
#endif

		if(strncmp(adminNumBuf, admin_phone_num, strlen(admin_phone_num)) == 0) {
			if(strncmp("#", msgbuf, 1) == 0 ) {
				parseSMSCommand(msgbuf, &parsedResult);
				processSMSCommand(&parsedResult);
			}
			else
				checkEventFlag(ERR_SMS_INVALID_CMD);
		}
		else
			checkEventFlag(ERR_SMS_AUTHORITY);

		i--;
	}

#ifdef DEBUG_LEVEL_3
	printf("%s: [doSMSCommand] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
	return SMS_PROCESS_DONE;
}

void parseSMSCommand(char *str, sms_cmd *parsedResult)
{
	char *ptr = NULL;

#ifdef DEBUG_LEVEL_3
	printf("%s: [parseSMSCommand] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	if(strncmp(SENSOR_ID_CMD, str, strlen(SENSOR_ID_CMD)) == 0)
		strcpy(parsedResult->key, "sensor_ID");
	else if(strncmp(SENSOR_SAMPLING_CMD, str, strlen(SENSOR_SAMPLING_CMD)) == 0)
		strcpy(parsedResult->key, "sampling_period");
	else if(strncmp(MODEM_TRANSFER_CMD, str, strlen(MODEM_TRANSFER_CMD)) == 0)
		strcpy(parsedResult->key, "transferring_period");
	else if(strncmp(ERROR_DUE_DATE_CMD, str, strlen(ERROR_DUE_DATE_CMD)) == 0)
		strcpy(parsedResult->key, "error_due_date");
	else if(strncmp(MESSAGE_NUM_CMD, str, strlen(MESSAGE_NUM_CMD)) == 0)
		strcpy(parsedResult->key, "message_max_num");
	else if(strncmp(ADMIN_NUM_CMD, str, strlen(ADMIN_NUM_CMD)) == 0)
		strcpy(parsedResult->key, "admin_phone_num");
	else if(strncmp(PROGRAM_MODE_CMD, str, strlen(PROGRAM_MODE_CMD)) == 0)
		strcpy(parsedResult->key, "program_mode");
	else if(strncmp(SERVER_ADDR_CMD, str, strlen(SERVER_ADDR_CMD)) == 0)
		strcpy(parsedResult->key, "server_addr");
	else if(strncmp(SERVER_PORT_CMD, str, strlen(SERVER_PORT_CMD)) == 0)
		strcpy(parsedResult->key, "server_port");


	ptr = strtok(str, " ");
	ptr = strtok(NULL, " ");
	ptr = strtok(NULL, " ");	// ptr has value
	strcpy(parsedResult->value, ptr);

#ifdef DEBUG_LEVEL_3
	printf("%s: Parsed Value is %s\n", getTimeInString(TIME_MODE_YMDHMS), parsedResult->value);
#endif

#ifdef DEBUG_LEVEL_3
	printf("%s: [parseSMSCommand] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
}

void processSMSCommand(sms_cmd *parsedResult)
{
#ifdef DEBUG_LEVEL_3
	printf("%s: [processSMSCommand] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	if(strncmp(parsedResult->key, "program_mode", strlen("program_mode")) == 0){
		if(strncmp(parsedResult->value, "start", strlen("start")) == 0) {
			pthread_mutex_lock(&mutex);
			remote_power = POWER_ON;
			pthread_mutex_unlock(&mutex);
		}
		else if(strncmp(parsedResult->value, "stop", strlen("stop")) == 0) {
			pthread_mutex_lock(&mutex);
			t_flag = THREAD_OFF;
			remote_power = POWER_OFF;
			pthread_mutex_unlock(&mutex);
		}
		else if(strncmp(parsedResult->value, "stop", strlen("restart")) == 0) {
			pthread_mutex_lock(&mutex);
			t_flag = THREAD_OFF;
			remote_power = POWER_ON;
			pthread_mutex_unlock(&mutex);
		}
	}
	else {
		// SMS Command -> ini file?
		setConfValue(parsedResult->key, parsedResult->value);

		if(strncmp(parsedResult->key, "sensor_ID", strlen("sensor_ID")) == 0)
			strcpy(sensor_ID, parsedResult->value);
		else if(strncmp(parsedResult->key, "sampling_period", strlen("sampling_period")) == 0)
			strcpy(sampling_period, parsedResult->value);
		else if(strncmp(parsedResult->key, "transferring_period", strlen("transferring_period")) == 0)
			strcpy(transferring_period, parsedResult->value);
		else if(strncmp(parsedResult->key, "message_max_num", strlen("message_max_num")) == 0)
			strcpy(message_max_num, parsedResult->value);
		else if(strncmp(parsedResult->key, "admin_phone_num", strlen("admin_phone_num")) == 0)
			strcpy(admin_phone_num, parsedResult->value);
		else if(strncmp(parsedResult->key, "error_due_date", strlen("error_due_date")) == 0)
			strcpy(error_due_date, parsedResult->value);
		else if(strncmp(parsedResult->key, "server_addr", strlen("server_addr")) == 0)
			strcpy(server_addr, parsedResult->value);
		else if(strncmp(parsedResult->key, "server_port", strlen("server_port")) == 0)
			strcpy(server_port, parsedResult->value);
	}

#ifdef DEBUG_LEVEL_3
	printf("%s: [processSMSCommand] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
}
