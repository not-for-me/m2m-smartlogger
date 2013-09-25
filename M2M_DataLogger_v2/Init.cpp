#include "./Header/Init.h"

int getConfValue(char *key, char *value)
{
	char buf[INI_FILE_SIZE] = "";
	char *ptr = NULL;
	FILE *fp = NULL;

#ifdef DEBUG_LEVEL_3
	printf("%s: [getConfValue] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	if (key == NULL || strcmp(key, "") == 0)
		return ERR_DATA_INPUT_NULL;
	else if( (fp = fopen(INI_FILE_PATH, "r")) != NULL ) {
		while( fgets(buf, INI_FILE_SIZE, fp) ) {
			if( strncmp(buf, key, strlen(key)) == 0 ) {
				ptr = strtok(buf, " ");
				ptr = strtok(NULL, " ");
				ptr = strtok(NULL, " ");
				ptr[strlen(ptr)-1] = '\0';
				strncpy(value, ptr, strlen(ptr));
				fclose(fp);
#ifdef DEBUG_LEVEL_3
				printf("%s: After Configuration-Key is \"%s\", Value is \"%s\"\n", getTimeInString(TIME_MODE_YMDHMS), key, value);
#endif

#ifdef DEBUG_LEVEL_3
				printf("%s: [getConfValue] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
				return GET_CONFIG_DONE;
			}
		}
		fclose(fp);
		return ERR_GETCONF_KEY_NOT_MATCH;
	}
	else
		return checkEventFlag(ERR_INI_FILE_OPEN);
}

int setConfValue(char *key, char *value)
{
	char buf[INI_FILE_SIZE] = "";
	char mem[INI_FILE_SIZE] = "";
	char *temp = NULL;
	char *ptr = NULL;
	char *temp_ptr = NULL;
	FILE *fp = NULL;

#ifdef DEBUG_LEVEL_3
	printf("%s: [setConfValue] Start\n", getTimeInString(TIME_MODE_YMDHMS));
	printf("%s: Setting Configuration-Key is \"%s\", Value is \"%s\"\n", getTimeInString(TIME_MODE_YMDHMS), key, value);
#endif

	if (key == NULL || strcmp(key, "") == 0)
		return ERR_DATA_INPUT_NULL;
	else if(value == NULL)
		return ERR_DATA_INPUT_NULL;
	else if ( (fp = fopen(INI_FILE_PATH, "r+")) != NULL ) {
		memset(mem, 0, INI_FILE_SIZE);

		while(fgets(buf, INI_FILE_SIZE, fp))
			strcat(mem, buf);

		ptr = strstr(mem, key);
		if(ptr == NULL)
			return ERR_SETCONF_KEY_NOT_MATCH;

		temp_ptr = strchr(ptr, '\n');
		temp = strdup(temp_ptr+1);
		sprintf(ptr,"%s = %s\n",key, value);
		strcat(mem, temp);
		rewind(fp);
		fputs(mem, fp);
		fclose(fp);

#ifdef DEBUG_LEVEL_3
		printf("%s: [setConfValue] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
		return SET_CONFIG_DONE;
	}
	else
		return checkEventFlag(ERR_INI_FILE_OPEN);
}

int setConfiguration()
{
	int ret = 0;
	char logBuffer[LOG_SIZE] = "";

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [setConfiguration] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

#ifdef DEBUG_LEVEL_3
	printf("%s: Server IP Address Configuration\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
	if( (ret = getConfValue("server_addr", server_addr)) != GET_CONFIG_DONE )
		return checkEventFlag(ret);

#ifdef DEBUG_LEVEL_3
	printf("%s: Server Port Number Configuration\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
	if ( (ret = getConfValue("server_port", server_port)) != GET_CONFIG_DONE )
		return checkEventFlag(ret);

#ifdef DEBUG_LEVEL_3
	printf("%s: Administrator Phone Number Configuration\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
	if ( (ret = getConfValue("admin_phone_num", admin_phone_num)) != GET_CONFIG_DONE )
		return checkEventFlag(ret);

// SKT API Dependency Secntion ---------------- Start
#ifdef DEBUG_LEVEL_3
	printf("%s: Modem ID Configuration\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
	ret = device_getnumber(modem_ID);	// SKT API - get device phone #
	if(ret == 1) {
#ifdef DEBUG_LEVEL_2
		printf("%s: Modem ID(Phone #) Value: %s\n", getTimeInString(TIME_MODE_YMDHMS), modem_ID);
		writeDebugLog(logBuffer);
#endif
		ret = setConfValue("modem_ID", modem_ID);
		if(ret != SET_CONFIG_DONE)
			return checkEventFlag(ret);
	}
	else
		return checkEventFlag(ERR_MODEM_NUM_GET);
// SKT API Dependency Secntion ---------------- End

#ifdef DEBUG_LEVEL_3
	printf("%s: Sensor ID Configuration\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
	if( (ret = getConfValue("sensor_ID", sensor_ID)) != GET_CONFIG_DONE )
		return checkEventFlag(ret);

#ifdef DEBUG_LEVEL_3
	printf("%s: Sampling Period Configuration\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
	if( (ret = getConfValue("sampling_period", sampling_period)) != GET_CONFIG_DONE )
		return checkEventFlag(ret);

#ifdef DEBUG_LEVEL_3
	printf("%s: Transferring Period Configuration\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
	if( (ret = getConfValue("transferring_period", transferring_period)) != GET_CONFIG_DONE )
		return checkEventFlag(ret);

#ifdef DEBUG_LEVEL_3
#endif
	if( (ret = getConfValue("message_max_num", message_max_num)) != GET_CONFIG_DONE )
		return checkEventFlag(ret);

#ifdef DEBUG_LEVEL_3
#endif
	if( (ret = getConfValue("error_due_date", error_due_date)) != GET_CONFIG_DONE )
		return checkEventFlag(ret);

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [setConfiguration] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	return CONFIGURATION_DONE;
}

int connectPPP(int defaultTime)
{
	char logBuffer[LOG_SIZE] = "";

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [connectPPP] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	if(defaultTime < 1)
		return checkEventFlag(ERR_PPP_DEFAULT_TIME);

#ifdef DEBUG_LEVEL_3
	printf("%s: Default Waiting Time is %dsec\n", getTimeInString(TIME_MODE_YMDHMS), defaultTime);
#endif

// SKT API Dependency Secntion ---------------- Start
	if( mnet_pppopen(defaultTime) < 1 ){	// SKT API
#ifdef DEBUG_LEVEL_3
		printf("%s: Connecting to the PPP... [Fail]: First Try\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
		defaultTime *= 2;
		if( mnet_pppopen(defaultTime) < 1 ){	// SKT API
#ifdef DEBUG_LEVEL_3
			printf("%s: Connecting to the PPP... [Fail]: Second Try\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
			return checkEventFlag(ERR_CONNECT_PPP);
		}
	}
// SKT API Dependency Secntion ---------------- End


#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [connectPPP] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif
	return PPP_CONNECTION_DONE;
}

int checkSensor()
{
	int fd = 0;
	int count = 0;
	int ret = 0;
	char buf[BUFF_SIZE] = "";
	char logBuffer[LOG_SIZE] = "";

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [checkSensor] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif
	fd = connectToSensor();

	do{
		ret = read(fd, buf, MSG_SIZE);
		if(ret == -1)
			count++;
		else {
#ifdef DEBUG_LEVEL_3
			sprintf(logBuffer, "%s: [checkSensor] Return Value %s\n", getTimeInString(TIME_MODE_YMDHMS), buf);
			writeDebugLog(logBuffer);
			puts(logBuffer);
#endif


#ifdef DEBUG_LEVEL_1
			sprintf(logBuffer, "%s: [checkSensor] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
			writeDebugLog(logBuffer);
#else
			writeSystemLog(logBuffer);
#endif
			puts(logBuffer);
#endif
			return SENSOR_INIT_DONE;
		}
		sleep(1);
	}while( count < MAX_SERIAL_DELAY_TIME);

	return checkEventFlag(ERR_SENSOR_INIT);
}

int registerModem()
{
	int sock = 0;
	int clnt_addr_size = 0;
	int ret = 0;
	char modem_addr[IP_ADDR_SIZE] = "";
	char logBuffer[LOG_SIZE] = "";
	char msg[MSG_SIZE] = "";
	char *message = NULL;
	struct sockaddr_in clnt_addr;
	gpslog gpslog;
	header_info headerData;

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [registerModem] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	ret = gps_on();
	if (ret < 0)
		return checkEventFlag(ERR_GPS_ON);

	ret = gps_optmod(3);
	if (ret < 0)
		return checkEventFlag(ERR_GPS_OPTION);

	ret = tcpConnection(&sock);
#ifdef DEBUG_LEVEL_3
	printf("%s: [tcpConnection] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
#endif
	if( ret != TCP_CONNECTION_DONE ) {
#ifdef DEBUG_LEVEL_3
		printf("%s: [tcpConnection] Fail to connect the server %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
#endif
		ret = tcpConnection(&sock);
#ifdef DEBUG_LEVEL_3
		printf("%s: [tcpConnection-Retry] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
#endif
		if( ret != TCP_CONNECTION_DONE )
			return checkEventFlag(ret);
	}

#ifdef DEBUG_LEVEL_3
	printf("%s: Check Modem IP Address\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
	clnt_addr_size = sizeof(clnt_addr);
	ret = getsockname(sock, (struct sockaddr*)&clnt_addr, (socklen_t*)&clnt_addr_size);
	if(ret == -1)
		return checkEventFlag(ERR_GET_MODEM_IP);

	strcpy(modem_addr, inet_ntoa(clnt_addr.sin_addr));
#ifdef DEBUG_LEVEL_2
	printf("%s: Modem IP Address is \"%s\"\n", getTimeInString(TIME_MODE_YMDHMS), modem_addr);
	writeDebugLog(logBuffer);
#endif

#ifdef DEBUG_LEVEL_3
	printf("%s: Register Modem Configuration to Server\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

#ifdef DEBUG_LEVEL_3
	printf("%s: Waiting GPS Information Setup\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
	sleep(60);
	ret = gps_get_current_position(&gpslog);
	if (ret < 0) {
#ifdef DEBUG_LEVEL_3
	printf("%s: GPS Information First Fail\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
		sleep(60);
		ret = gps_get_current_position(&gpslog);
		if (ret < 0) {
#ifdef DEBUG_LEVEL_3
	printf("%s: GPS Information Second Fail\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
			checkEventFlag(ERR_GET_GPS_POSITION);
			gpslog.lat = 0.0;
			gpslog.lon = 0.0;
		}
	}
	gps_off();
	sprintf(msg, "%s,%s,%.6f,%.6f", admin_phone_num, modem_addr,gpslog.lat, gpslog.lon);
	//Make header Information
#ifdef DEBUG_LEVEL_3
	printf("%s: makeMessage Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
	headerData.msgType = MSG_TYPE_REGISTER;
	headerData.data_len = getTotalDataLength(msg);
	headerData.msg_num = 1;
	headerData.msg_len = getMSGLength(msg);
	makeHeaderInfo(&headerData);
	message = (char *)malloc(sizeof(char) * headerData.data_len + 1);
	strcpy(message, headerData.header_msg);
	strcat(message, "/");
	strcat(message, msg);
#ifdef DEBUG_LEVEL_3
	printf("%s: Message Result %s\n", getTimeInString(TIME_MODE_YMDHMS), message);
#endif

	ret = write(sock, message, strlen(message));
#ifdef DEBUG_LEVEL_3
	printf("%s: [write] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
#endif
	if(ret == -1)
		return checkEventFlag(ERR_REGISTER_MODEM);

	free(message);
	close(sock);

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [registerModem] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	return REGISTER_MODEM_DONE;
}

int initialize()
{
	int ret = 0;
	char logBuffer[LOG_SIZE] = "";

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [Initialize] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	ret = setConfiguration();
#ifdef DEBUG_LEVEL_3
	printf("%s: [setConfiguration] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
#endif
	if( ret != CONFIGURATION_DONE )
		return checkEventFlag(ERR_INITIALIZE);

	ret = connectPPP(DEFAULT_CONN_WAIT_TIME);
#ifdef DEBUG_LEVEL_3
	printf("%s: [connectPPP] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
#endif
	if( ret != PPP_CONNECTION_DONE )
		return checkEventFlag(ERR_INITIALIZE);

	ret = checkSensor();
#ifdef DEBUG_LEVEL_3
	printf("%s: [checkSensor] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
#endif
	if( ret != SENSOR_INIT_DONE)
		return checkEventFlag(ERR_INITIALIZE);

	ret = registerModem();
#ifdef DEBUG_LEVEL_3
	printf("%s: [registerModem] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
#endif
	if( ret != REGISTER_MODEM_DONE )
		return checkEventFlag(ERR_INITIALIZE);

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [Initialize] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	return INITIAILIZE_DONE;
}
