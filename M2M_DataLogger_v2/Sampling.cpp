#include "./Header/Sampling.h"

int connectToSensor()
{
	int fd = 0;
	char logBuffer[LOG_SIZE] = "";
	struct termios tty;

#ifdef DEBUG_LEVEL_3
	sprintf(logBuffer, "%s: [connectToSensor] Start\n", getTimeInString(TIME_MODE_YMDHMS));
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

	fd = open(M2M_SERIAL_DEVICE_NAME, O_RDWR | O_NOCTTY | O_NONBLOCK);

	memset(&tty, 0, sizeof(tty));
	tty.c_cflag = B19200;
	tty.c_cflag |= CS8 | CREAD | CLOCAL ;
	tty.c_iflag = IGNPAR | ICRNL;
	tty.c_oflag = 0;
	tty.c_lflag = ICANON;
	tty.c_cc[VTIME] = 0;
	tty.c_cc[VMIN] = 1;

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &tty);

#ifdef DEBUG_LEVEL_3
	sprintf(logBuffer, "%s: [connectToSensor] End\n", getTimeInString(TIME_MODE_YMDHMS));
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif
	return fd;
}

int checkDataIntegrity(char *str, int *column, int *code)
{
	int i = 0;
	int length = 0;
	char pastChar = 0;
	char currentChar = 0;
	char logBuffer[LOG_SIZE] = "";

#ifdef DEBUG_LEVEL_3
	sprintf(logBuffer,"%s: [checkDataIntegrity] Start\n", getTimeInString(TIME_MODE_YMDHMS));
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

	if(str == NULL)
		return checkEventFlag(ERR_DATA_INPUT_NULL);

	length = strlen(str);
#ifdef DEBUG_LEVEL_3
	sprintf(logBuffer, "%s: String Length: %d\n", getTimeInString(TIME_MODE_YMDHMS), length);
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

	*column = 1;
	for(i=0; i < length; i++) {
		currentChar = str[i];		// 32 blank 45 -  46 . 48~57 number
		if( currentChar == 32 || currentChar == 45 || currentChar == 46 || (currentChar >= 48 && currentChar <= 57) ) {
			if(pastChar == 32 && currentChar != 32)
				(*column)++;
		}
		else if(currentChar == 35 || currentChar == 63 || currentChar == 42 || currentChar == 126 || currentChar == 64) {		// # / ? / * / ~ / @
			*code = currentChar;
			if(pastChar == 32) {
				(*column)++;
				return checkEventFlag(ERR_DATA_INTEGRITY_TYPE1);
			}
			else if(pastChar >= 48 && pastChar <= 57)
				return checkEventFlag(ERR_DATA_INTEGRITY_TYPE2);
		}
		else {
			*code = 0;
			*column = 0;
			return checkEventFlag(ERR_DATA_INTEGRITY_TYPE3);
		}
		pastChar = currentChar;
	}

#ifdef DEBUG_LEVEL_3
	sprintf(logBuffer, "%s: [checkDataIntegrity] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif
	return DATA_INTEGRITY_CHK_DONE;
}

int analyzeSpecialChar(int errorType, int column, int code)
{
	if(errorType == ERR_DATA_INTEGRITY_TYPE1) {
		if(column == 3)
			switch(code) {
			case 35:	// #
				return ERR_COL_3RD_SHARP_T;
			case 63:	// ?
				return ERR_COL_3RD_QUESTION_T;
			case 42:	// *
				return ERR_COL_3RD_STAR_T;
			case 126:	// ~
				return ERR_COL_3RD_TILDE_T;
			case 64:	// @
				return ERR_COL_3RD_AT_T;
			default:
				break;
			}
		else if(column == 4)
			switch(code) {
			case 35:	// #
				return ERR_COL_4TH_SHARP_T;
			case 63:	// ?
				return ERR_COL_4TH_QUESTION_T;
			case 42:	// *
				return ERR_COL_4TH_STAR_T;
			case 126:	// ~
				return ERR_COL_4TH_TILDE_T;
			case 64:	// @
				return ERR_COL_4TH_AT_T;
			default:
				break;
			}
		else if(column == 5)
			switch(code) {
			case 35:	// #
				return ERR_COL_5TH_SHARP_T;
			case 63:	// ?
				return ERR_COL_5TH_QUESTION_T;
			case 42:	// *
				return ERR_COL_5TH_STAR_T;
			case 126:	// ~
				return ERR_COL_5TH_TILDE_T;
			case 64:	// @
				return ERR_COL_5TH_AT_T;
			default:
				break;
			}
		else if(column == 6)
			switch(code) {
			case 35:	// #
				return ERR_COL_6TH_SHARP_T;
			case 63:	// ?
				return ERR_COL_6TH_QUESTION_T;
			case 42:	// *
				return ERR_COL_6TH_STAR_T;
			case 126:	// ~
				return ERR_COL_6TH_TILDE_T;
			case 64:	// @
				return ERR_COL_6TH_AT_T;
			default:
				break;
			}
		else if(column == 7)
			switch(code) {
			case 35:	// #
				return ERR_COL_7TH_SHARP_T;
			case 63:	// ?
				return ERR_COL_7TH_QUESTION_T;
			case 42:	// *
				return ERR_COL_7TH_STAR_T;
			case 126:	// ~
				return ERR_COL_7TH_TILDE_T;
			case 64:	// @
				return ERR_COL_7TH_AT_T;
			default:
				break;
			}
		else if(column == 8)
			switch(code) {
			case 35:	// #
				return ERR_COL_8TH_SHARP_T;
			case 63:	// ?
				return ERR_COL_8TH_QUESTION_T;
			case 42:	// *
				return ERR_COL_8TH_STAR_T;
			case 126:	// ~
				return ERR_COL_8TH_TILDE_T;
			case 64:	// @
				return ERR_COL_8TH_AT_T;
			default:
				break;
			}

	}
	else if(errorType == ERR_DATA_INTEGRITY_TYPE2) {
		if(column == 3)
			switch(code) {
			case 35:	// #
				return ERR_COL_3RD_SHARP_P;
			case 63:	// ?
				return ERR_COL_3RD_QUESTION_P;
			case 42:	// *
				return ERR_COL_3RD_STAR_P;
			case 126:	// ~
				return ERR_COL_3RD_TILDE_P;
			case 64:	// @
				return ERR_COL_3RD_AT_P;
			default:
				break;
			}
		else if(column == 4)
			switch(code) {
			case 35:	// #
				return ERR_COL_4TH_SHARP_P;
			case 63:	// ?
				return ERR_COL_4TH_QUESTION_P;
			case 42:	// *
				return ERR_COL_4TH_STAR_P;
			case 126:	// ~
				return ERR_COL_4TH_TILDE_P;
			case 64:	// @
				return ERR_COL_4TH_AT_P;
			default:
				break;
			}
		else if(column == 5)
			switch(code) {
			case 35:	// #
				return ERR_COL_5TH_SHARP_P;
			case 63:	// ?
				return ERR_COL_5TH_QUESTION_P;
			case 42:	// *
				return ERR_COL_5TH_STAR_P;
			case 126:	// ~
				return ERR_COL_5TH_TILDE_P;
			case 64:	// @
				return ERR_COL_5TH_AT_P;
			default:
				break;
			}
		else if(column == 6)
			switch(code) {
			case 35:	// #
				return ERR_COL_6TH_SHARP_P;
			case 63:	// ?
				return ERR_COL_6TH_QUESTION_P;
			case 42:	// *
				return ERR_COL_6TH_STAR_P;
			case 126:	// ~
				return ERR_COL_6TH_TILDE_P;
			case 64:	// @
				return ERR_COL_6TH_AT_P;
			default:
				break;
			}
		else if(column == 7)
			switch(code) {
			case 35:	// #
				return ERR_COL_7TH_SHARP_P;
			case 63:	// ?
				return ERR_COL_7TH_QUESTION_P;
			case 42:	// *
				return ERR_COL_7TH_STAR_P;
			case 126:	// ~
				return ERR_COL_7TH_TILDE_P;
			case 64:	// @
				return ERR_COL_7TH_AT_P;
			default:
				break;
			}
		else if(column == 8)
			switch(code) {
			case 35:	// #
				return ERR_COL_8TH_SHARP_P;
			case 63:	// ?
				return ERR_COL_8TH_QUESTION_P;
			case 42:	// *
				return ERR_COL_8TH_STAR_P;
			case 126:	// ~
				return ERR_COL_8TH_TILDE_P;
			case 64:	// @
				return ERR_COL_8TH_AT_P;
			default:
				break;
			}
	}

	return ERR_ANALYZE_FAIL;
}

int parsingRawData(char *buf, lake_data *sampling_data)
{
	int i = 0;
	char logBuffer[LOG_SIZE] = "";
	char *ptr = NULL;
	char temp[10][20];

#ifdef DEBUG_LEVEL_3
	sprintf(logBuffer, "%s: [parseRawStringData] Start\n", getTimeInString(TIME_MODE_YMDHMS));
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

	if(buf == NULL)
		return ERR_DATA_INPUT_NULL;

	ptr = strtok(buf, " ");
	strcpy(temp[i++], buf);

#ifdef DEBUG_LEVEL_2
	sprintf(logBuffer, "%s: %dth Parsed Data %s\n", getTimeInString(TIME_MODE_YMDHMS), i, temp[i-1]);
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

	while( (ptr = strtok(NULL, " ")) != NULL ) {
		strcpy(temp[i++], ptr);
#ifdef DEBUG_LEVEL_2
		sprintf(logBuffer, "%s: %dth Parsed Data %s\n", getTimeInString(TIME_MODE_YMDHMS), i, temp[i-1]);
		writeDebugLog(logBuffer);
		puts(logBuffer);
#endif
		if(i == 10) {
			strcpy(sampling_data->currentDate, temp[0]);
			strcpy(sampling_data->currentTime, temp[1]);
			sampling_data->temp = atof(temp[2]);
			sampling_data->spCond = atof(temp[3]);
			sampling_data->sal = atof(temp[4]);
			sampling_data->depth10 = atof(temp[5]);
			sampling_data->chl = atof(temp[6]);
			sampling_data->ldo = atof(temp[7]);
			sampling_data->ivolt = atof(temp[8]);
			sampling_data->ovolt = atof(temp[9]);

#ifdef DEBUG_LEVEL_3
			sprintf(logBuffer, "%s: [parseRawStringData] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
			writeDebugLog(logBuffer);
			puts(logBuffer);
#endif
			return DATA_PARSE_DONE;
		}
	}

#ifdef DEBUG_LEVEL_3
	printf(logBuffer, "%s: [parseRawStringData] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif
	return ERR_INSUFFICIENT_DATA;
}

int checkDataRange(lake_data *data)
{
	char logBuffer[LOG_SIZE] = "";

#ifdef DEBUG_LEVEL_3
	sprintf(logBuffer,"%s: [checkDataRange] Start\n", getTimeInString(TIME_MODE_YMDHMS));
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

	if(data->spCond < 0 || data->spCond > 100000)
		return ERR_DATA_RANGE_SPCOND;

	if(data->sal < 0 || data->sal > 75)
		return ERR_DATA_RANGE_SAL;

	if(data->depth10 < -5 || data->depth10 > 20)
		return ERR_DATA_RANGE_DEPTH;

	if(data->chl < 0 || data->chl > 500)
		return ERR_DATA_RANGE_CHL;

	if(data->ldo < 0 || data->ldo > 50)
		return ERR_DATA_RANGE_LDO;

#ifdef DEBUG_LEVEL_3
	sprintf(logBuffer, "%s: [checkDataRange] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif
	return DATA_RANGE_CHK_DONE;
}

int samplingData(lake_data *data, char *timeStamp)
{
	int ret = 0;
	int fd = 0;
	int cnt = 0;
	int snsr_state = 0;
	int dataIntegrityCode = 0;
	int dataColumn = 0;
	int errorCode = 0;
	char buf[MSG_SIZE] = "";
	char bufReplica[MSG_SIZE] = "";
	char logBuffer[LOG_SIZE] = "";

#ifdef DEBUG_LEVEL_3
	sprintf(logBuffer, "%s: [samplingData] Start\n", getTimeInString(TIME_MODE_YMDHMS));
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

	fd = connectToSensor();

	snsr_state = 0;
	while(1){
		strcpy(buf, "");

		while(1){
#ifdef DEBUG_LEVEL_3
			sprintf(logBuffer, "%s: Reading data from Sensor...\n", getTimeInString(TIME_MODE_YMDHMS));
			writeDebugLog(logBuffer);
			puts(logBuffer);
#endif
			cnt = read(fd, buf, MSG_SIZE);
			if(cnt == -1) {
				snsr_state++;
				if(snsr_state == 3){
					return ERR_SENSOR_STATE;
				}
				sleep(1);
			}
			else {
				snsr_state = 0;
				break;
			}
		}

#ifdef DEBUG_LEVEL_2
		sprintf(logBuffer, "%s: Sampling Data String is \"%s\"\n", getTimeInString(TIME_MODE_YMDHMS), buf);
		writeDebugLog(logBuffer);
		puts(logBuffer);
#endif
		strcpy(bufReplica, buf);

		ret = parsingRawData(buf, data);
#ifdef DEBUG_LEVEL_2
		sprintf(logBuffer, "%s: [parseRawStringData] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
		writeDebugLog(logBuffer);
		puts(logBuffer);
#endif
		if(ret == ERR_INSUFFICIENT_DATA || ret == ERR_DATA_INPUT_NULL)
			continue;

		dataIntegrityCode = checkDataIntegrity(bufReplica, &dataColumn, &errorCode);
#ifdef DEBUG_LEVEL_2
		sprintf(logBuffer, "%s: [checkDataIntegrity] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), dataIntegrityCode);
		writeDebugLog(logBuffer);
		puts(logBuffer);

		sprintf(logBuffer, "%s: DataColumn: %d  ErrorCode: %d\n", getTimeInString(TIME_MODE_YMDHMS), dataColumn, errorCode);
		writeDebugLog(logBuffer);
		puts(logBuffer);
#endif

		if(dataIntegrityCode != DATA_INTEGRITY_CHK_DONE) {
			ret = analyzeSpecialChar(dataIntegrityCode, dataColumn, errorCode);
#ifdef DEBUG_LEVEL_2
			sprintf(logBuffer, "%s: [analyzeSpecialChar] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
			writeDebugLog(logBuffer);
			puts(logBuffer);
#endif
			checkEventFlag(ret);

			if(ret != ERR_COL_5TH_STAR_P) {		//For Testing
				parsingRawData(buf, data);
				sprintf(buf, "%s,%s,%.2f,%.2f,%.2f,%.3f,%.2f,%.2f,%.1f,%.1f\n", data->currentDate, timeStamp, data->temp,
						data->spCond, data->sal, data->depth10, data->chl, data->ldo, data->ivolt, data->ovolt);
				writeDataLog(buf);
				continue;
			}		//For Testing
		}

		ret = checkDataRange(data);
#ifdef DEBUG_LEVEL_2
		sprintf(logBuffer, "%s: [checkDataRange] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
		writeDebugLog(logBuffer);
		puts(logBuffer);
#endif
		if(ret == DATA_RANGE_CHK_DONE)
			break;
		else {
			puts("Some Value Range Problem");
			checkEventFlag(ret);
			strcat(buf, "\n");
			writeDataLog(buf);
			continue;
		}
	}

	close(fd);

#ifdef DEBUG_LEVEL_3
	sprintf(logBuffer, "%s: [samplingData] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif
	return SENSOR_SAMPLE_DONE;
}

void *thread_sampling(void * arg)
{
	int ret = 0;
	char timeStamp[10] = "";
	int waitingMin = 0;
	int stampMin = 0;
	lake_data data = {"", "", 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	char conversion_msg[MSG_SIZE]= "";
	char logBuffer[LOG_SIZE] = "" ;
	char currentHour[3] = "";
	char currentMin[3] = "";

#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [Sampling Thread] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif


#ifdef DEBUG_LEVEL_3
	sprintf(logBuffer,"%s: [Sampling Thread] Loop Start\n", getTimeInString(TIME_MODE_YMDHMS));
	writeDebugLog(logBuffer);
	puts(logBuffer);
#endif

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	while(t_flag == THREAD_ON) {
		strcpy(currentMin, getTimeInString(TIME_MODE_MIN));
		waitingMin = atoi(sampling_period) - (atoi(currentMin) % atoi(sampling_period));
		sleep(waitingMin * MINUTE + 1);
		strcpy(currentHour, getTimeInString(TIME_MODE_HOUR));
		stampMin = atoi(currentMin) + waitingMin;
		if(stampMin == 60)
			stampMin = 0;

		sprintf(timeStamp, "%s%02d00",currentHour, stampMin);

		ret = samplingData(&data, timeStamp);
#ifdef DEBUG_LEVEL_2
		sprintf(logBuffer, "%s: [samplingData] Return Value: %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
		writeDebugLog(logBuffer);
		puts(logBuffer);
#endif

		if(ret == SENSOR_SAMPLE_DONE) {
			sprintf(conversion_msg, "%s,%s,%.2f,%.2f,%.2f,%.3f,%.2f,%.2f,%.1f,%.1f", data.currentDate, timeStamp, data.temp,
					data.spCond, data.sal, data.depth10, data.chl, data.ldo, data.ivolt, data.ovolt);

			if(!isFullSamplingQueue(&sqinfo)) {
				pthread_mutex_lock(&mutex);
				ret = enqueueSamplingData(&sqinfo, conversion_msg);
				pthread_mutex_unlock(&mutex);

#ifdef DEBUG_LEVEL_2
				sprintf(logBuffer, "%s: [enqueueSamplingData] Return Value: %d\n	", getTimeInString(TIME_MODE_YMDHMS), ret);
				writeDebugLog(logBuffer);
				puts(logBuffer);
#endif
			}
			else
				checkEventFlag(ERR_FULL_QUEUE_BEFORE);

			//Saving Log to local mem
			strcat(conversion_msg, "\n");
			writeDataLog(conversion_msg);

			if(ret == ERR_FULL_QUEUE_AFTER)
				checkEventFlag(ERR_FULL_QUEUE_AFTER);
		}
		else if(ret == ERR_SENSOR_STATE) {
#ifdef DEBUG_LEVEL_1
			sprintf(logBuffer, "%s: Sensor Sampling Error\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
			writeDebugLog(logBuffer);
#else
			writeSystemLog(logBuffer);
#endif
			puts(logBuffer);
#endif
		}

		strcpy(t_timeStamp[0], getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_2
		sprintf(logBuffer, "%s: Sampling Thread Time Stamp: %s\n	", getTimeInString(TIME_MODE_YMDHMS),t_timeStamp[0]);
		writeDebugLog(logBuffer);
		puts(logBuffer);
#endif
	}


#ifdef DEBUG_LEVEL_1
	sprintf(logBuffer, "%s: [Sampling Thread] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
	writeDebugLog(logBuffer);
#else
	writeSystemLog(logBuffer);
#endif
	puts(logBuffer);
#endif

	return NULL;
}
