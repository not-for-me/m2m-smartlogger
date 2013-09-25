#include "./Header/Log.h"
/*
There is no dependency
*/

void writeDebugLog(char* str)
{
	FILE *fp = NULL;

	fp = fopen(DEBUG_LOG_PATH, "a");
	if(fp==NULL) {
		puts("Can't Open Debug Log File");
		exit(-1);
	}

	fprintf(fp, "%s\n", str);
	fclose(fp);
}

int writeSystemLog(char* str)
{
	int ret = 0;
	FILE *fp = NULL;

	fp = fopen(SYSTEM_LOG_PATH, "a");
	if(fp == NULL)
		return checkEventFlag(ERR_SYSTEM_FILE_OPEN);

	ret = fprintf(fp, "%s\n", str);
	fclose(fp);

	return SYSTEM_LOG_DONE;
}

void writeErrorLog(char*str)
{
	FILE *fp = NULL;

	fp = fopen(ERROR_LOG_PATH, "a");
	if(fp==NULL) {
		puts("Can't Open Error Log File");
		exit(-1);
	}

	fprintf(fp, "%s\n", str);
	fclose(fp);
}

int writeDataLog(char* str)
{
	char fileName[12]= "";
	char filePath[36] = "";
	FILE *fp = NULL;

#ifdef DEBUG_LEVEL_2
	printf("%s: [writeDataLog] Start\n", getTimeInString(TIME_MODE_YMDHMS));
#endif

	strcpy(filePath, DATA_LOG_PATH);
	strcpy(fileName, getTimeInString(TIME_MODE_YEAR));
	strcat(filePath, fileName);
	strcat(filePath, DATA_FILE_TYPE);

	fp = fopen(filePath, "a");
	if(fp == NULL)
		return checkEventFlag(ERR_DATA_FILE_OPEN);

	fputs(str, fp);
	fclose(fp);

#ifdef DEBUG_LEVEL_2
	printf("%s: [writeDataLog] Stop\n", getTimeInString(TIME_MODE_YMDHMS));
#endif
	return DATA_LOG_DONE;
}

char *getTimeInString(int mode)
{
	int year = 0;
	int month = 0;
	int day = 0;
	int dueDay = 0;
	int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	static char buf[15] = "";
	static time_t current_time;
	static struct tm *st_time;

	time(&current_time);
	st_time = localtime(&current_time);

	//if(mode == TIME_MODE_YMDHMS)
	//	strftime(buf, BUFF_SIZE, "%Y%m%d-%H-%M-%S", st_time);
	if(mode == TIME_MODE_YMDHMS)
		strftime(buf, BUFF_SIZE, "%Y%m%d%H%M%S", st_time);
	//else if(mode == TIME_MODE_YMD_HYPHEN)
	//	strftime(buf, BUFF_SIZE, "%Y-%m-%d", st_time);
	else if(mode == TIME_MODE_YMD)
		strftime(buf, BUFF_SIZE, "%Y%m%d", st_time);
	else if(mode == TIME_MODE_HMS)
		strftime(buf, BUFF_SIZE, "%H%M%S", st_time);
	else if(mode == TIME_MODE_HOUR)
		strftime(buf, BUFF_SIZE, "%H", st_time);
	else if(mode == TIME_MODE_MIN)
		strftime(buf, BUFF_SIZE, "%M", st_time);
	else if(mode == TIME_MODE_SEC)
		strftime(buf, BUFF_SIZE, "%S", st_time);
	else if(mode == TIME_MODE_YEAR)
		strftime(buf, BUFF_SIZE, "%Y", st_time);
	else if(mode == TIME_MODE_MONTH)
		strftime(buf, BUFF_SIZE, "%m", st_time);
	else if(mode == TIME_MODE_DAY)
		strftime(buf, BUFF_SIZE, "%d", st_time);
	else if(mode == DUE_DATE_YMD) {
		strftime(buf, BUFF_SIZE, "%Y", st_time);
		year = atoi(buf);
		strftime(buf, BUFF_SIZE, "%m", st_time);
		month = atoi(buf);
		strftime(buf, BUFF_SIZE, "%d", st_time);
		day = atoi(buf);

		dueDay = day + atoi(error_due_date);

		//leap Year
		if( year == 2016 || year == 2020 ){
			if(dueDay > 29){
				sprintf(buf,"%d%02d%02d", year, (month+1), (dueDay-29));
			}
			else
				sprintf(buf,"%d%02d%02d", year,month,dueDay);
		}
		else if(dueDay > monthDays[month]){
			sprintf(buf,"%d%02d%02d", year, (month+1), (dueDay-monthDays[month]));
		}
		else
			sprintf(buf,"%d%02d%02d", year,month,dueDay);
	}

	return buf;
}
