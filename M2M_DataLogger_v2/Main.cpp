#include "./Header/Main.h"

char server_addr[20] = "";
char server_port[10] = "";
char admin_phone_num[15] = "";
char modem_ID[15] = "";
char sensor_ID[10];
char sampling_period[5] = "";
char transferring_period[5] = "";
char message_max_num[3] = "";
char error_due_date[2] = "";
int notificationFlag[NOTIFICATION_SIZE] = {0,};
int t_flag = THREAD_OFF;		// For thread on/off flag
int remote_power = POWER_ON;
char t_timeStamp[3][15] = {"",};

pthread_mutex_t mutex;			//For Thread and Critical Section
queue_info sqinfo;		// Sampling Queue

int main(int argc, char *argv[]) {
	int initDelayTime = 0;
	int initFailNum = 0;
	int i = 0;
	int ret = 0;
	char old_t_timeStamp[3][15]= {"",};
	char logBuffer[LOG_SIZE] = "";
	pthread_t t_id[3];			// For Thread (t_id[0]: Sampling, t_id[1]: Transferring, T_id[2]: Notification)
	pid_t pid;
	pid_t sid;


	for(i=0; i <10; i++)
		sleep(1);

	pid = fork();
	if (pid < 0) {
		checkEventFlag(ERR_DAEMON_CREATE);
		exit(EXIT_FAILURE);
	}

	if (pid > 0)
		exit(EXIT_SUCCESS);

	umask(0);
	sid = setsid();
	if (sid < 0) {
		checkEventFlag(ERR_SESSION_CREAT);
		exit(EXIT_FAILURE);
	}

	if ((chdir("/")) < 0)
		exit(EXIT_FAILURE);

	// Close File descriptor of Standard IO
#ifndef DEBUG_LEVEL_1
#ifndef DEBUG_LEVEL_2
#ifndef DEBUG_LEVEL_3
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	close(STDOUT_FILENO);
#endif // DEBUG_LEVEL_3
#endif // DEBUG_LEVEL_2
#endif // DEBUG_LEVEL_1


	ret = initSamplingQueue(&sqinfo);
	if(ret == ERR_QUEUE_INIT)
		checkEventFlag(ERR_QUEUE_INIT);

	while(1) {
		ret = initialize();
#ifdef DEBUG_LEVEL_3
		sprintf(logBuffer, "%s: [initialize] Return Value %d\n", getTimeInString(TIME_MODE_YMDHMS), ret);
		writeDebugLog(logBuffer);
		puts(logBuffer);
#endif
		if(ret == INITIAILIZE_DONE)
			break;
		else if(ret == ERR_INITIALIZE)
			if(initFailNum < 4)
				initFailNum++;

		switch (initFailNum) {
		case 1:
			initDelayTime = 10;
			break;
		case 2:
			initDelayTime = 30;
			break;
		case 3:
			initDelayTime = 60;
			break;
		default:
			initDelayTime = 180;
			break;
		}
		sleep(initDelayTime);
	}

	ret = sms_msg_send(admin_phone_num, modem_ID,
			"Complete M2M Initialization!");

	pthread_mutex_init(&mutex, NULL);

	while(1) {
		if(t_flag == THREAD_OFF && remote_power == POWER_ON) {
#ifdef DEBUG_LEVEL_1
			sprintf(logBuffer, "%s: Now Thread All Creation \n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
			writeDebugLog(logBuffer);
#else
			writeSystemLog(logBuffer);
#endif
			puts(logBuffer);
#endif
			pthread_mutex_lock(&mutex);
			t_flag = THREAD_ON;
			pthread_mutex_unlock(&mutex);

			pthread_create(&(t_id[0]), NULL, thread_sampling, NULL);
			pthread_create(&(t_id[1]), NULL, thread_transferring, NULL);
			pthread_create(&(t_id[2]), NULL, thread_notification, NULL);

#ifdef DEBUG_LEVEL_1
			sprintf(logBuffer, "%s: Thread Creation Complete\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
			writeDebugLog(logBuffer);
#else
			writeSystemLog(logBuffer);
#endif
			puts(logBuffer);
#endif
		}
		sleep(atoi(transferring_period) * MINUTE * 2);


#ifdef DEBUG_LEVEL_1
			sprintf(logBuffer, "%s: Check Thread Down State\n", getTimeInString(TIME_MODE_YMDHMS));
#ifdef DEBUG_LEVEL_3
			writeDebugLog(logBuffer);
#else
			writeSystemLog(logBuffer);
#endif
			puts(logBuffer);
#endif
		for(i=0; i < 3; i++) {
			if( !strncmp(old_t_timeStamp[i], t_timeStamp[i], 14) ){
#ifdef DEBUG_LEVEL_3
				sprintf(logBuffer, "%s: %d Thread Down!!! \n", getTimeInString(TIME_MODE_YMDHMS), i+1);
				writeDebugLog(logBuffer);
				puts(logBuffer);
#endif
				switch(i) {
				case 0:
					checkEventFlag(ERR_SAMPLING_T_DOWN);
					break;
				case 1:
					checkEventFlag(ERR_TRANSFERRING_T_DOWN);
					break;
				default:
					break;
				}

				pthread_cancel(t_id[i]);
				pthread_join(t_id[i], NULL);
#ifdef DEBUG_LEVEL_3
				sprintf(logBuffer, "%s: %d Thread Cancel Done\n", getTimeInString(TIME_MODE_YMDHMS), i+1);
				writeDebugLog(logBuffer);
				puts(logBuffer);
#endif
				pthread_create(&(t_id[i]), NULL, thread_sampling, NULL);
			}

			else
				strcpy(old_t_timeStamp[i], t_timeStamp[i]);
		}
	}

	freeSamplingQueue(&sqinfo);
	mnet_pppclose();
	exit(EXIT_SUCCESS);
}
