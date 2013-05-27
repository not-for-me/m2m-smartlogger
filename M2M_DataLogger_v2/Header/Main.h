#ifndef MAIN_H_
#define MAIN_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <termios.h>
#include <pthread.h>
#include "m2m_common.h"
#include "m2m_netctl.h"
#include "m2m_eif.h"
#include "m2m_sms.h"
#include "m2m_gps.h"

// For Debugging MODE
#define DEBUG_LEVEL_1	// Basic System Log Level
#define DEBUG_LEVEL_2	// Print important variable, function retrun value
#define DEBUG_LEVEL_3	// Print all the debugging Message

// Structure Type Definition
typedef struct {
	char currentDate[10];
	char currentTime[8];
	float temp;
	float spCond;
	float sal;
	float depth10;
	float chl;
	float ldo;
	float ivolt;
	float ovolt;
}lake_data;

typedef struct {
	char **msg_queue;
	unsigned short head;
	unsigned short tail;
	unsigned short num;
}queue_info;


// User define header
#include "Init.h"
#include "Log.h"
#include "Notification.h"
#include "Queue.h"
#include "Sampling.h"
#include "SMS.h"
#include "Transferring.h"

#define TRUE 1
#define FALSE 0

#define GET_CONFIG_DONE 1001
#define SET_CONFIG_DONE 1002
#define CONFIGURATION_DONE 1003
#define PPP_CONNECTION_DONE 1004
#define TCP_CONNECTION_DONE 1005
#define REGISTER_MODEM_DONE 1006
#define SENSOR_INIT_DONE 1007
#define INITIAILIZE_DONE 1008
#define SYSTEM_LOG_DONE 1009
#define DATA_LOG_DONE 1010
#define QUEUE_INIT_DONE 1011
#define ENQUEUE_DONE 1012
#define DEQUEUE_DONE 1013
#define DATA_INTEGRITY_CHK_DONE 1014
#define DATA_PARSE_DONE 1015
#define DATA_CONVERSE_DONE 1016
#define DATA_RANGE_CHK_DONE 1017
#define SENSOR_SAMPLE_DONE 1018
#define SAMPLING_PERIOD_COME 1019
#define SAMPLING_PERIOD_YET 1020
#define SMS_PROCESS_DONE 1021
#define PPP_CONNECTION_CHK_DONE 1022
#define DATA_TRANSFER_DONE 1023


#define ERR_DAEMON_CREATE 4001
#define ERR_SESSION_CREAT 4002
#define ERR_INI_FILE_OPEN 4003
#define ERR_GETCONF_KEY_NOT_MATCH 4104
#define ERR_SETCONF_KEY_NOT_MATCH 4105
#define ERR_SERVER_ADDR_SET 4006
#define ERR_SERVER_PORT_SET 4007
#define ERR_ADMIN_NUM_SET 4008
#define ERR_MODEM_NUM_SET 4009
#define ERR_MODEM_NUM_GET 4010
#define ERR_SENSOR_ID_SET 4011
#define ERR_SAMPLING_PERIOD_SET 4012
#define ERR_TRANSFERRING_PERIOD_SET 4013
#define ERR_MSG_MAX_NUM_SET 4014
#define ERR_DUE_DATE_SET 4015
#define ERR_PPP_DEFAULT_TIME 4016
#define ERR_PPP_DISCONNECT 4017
#define ERR_CONNECT_PPP 4018
#define ERR_GPS_ON 4019
#define ERR_GPS_OPTION 4020
#define ERR_SOCKET_CREATE 4021
#define ERR_SOCKET_CONNECT 4022
#define ERR_GET_MODEM_IP 4023
#define ERR_GET_GPS_POSITION 4024
#define ERR_REGISTER_MODEM 4025
#define ERR_SENSOR_INIT 4026
#define ERR_INITIALIZE 4027
#define ERR_SYSTEM_FILE_OPEN 4028
#define ERR_DATA_FILE_OPEN 4029
#define ERR_QUEUE_INIT 4030
#define ERR_FULL_QUEUE_BEFORE 4031
#define ERR_FULL_QUEUE_AFTER 4032
#define ERR_EMPTY_QUEUE 4033
#define ERR_DATA_INTEGRITY_TYPE1 4034
#define ERR_DATA_INTEGRITY_TYPE2 4035
#define ERR_DATA_INTEGRITY_TYPE3 4036
#define ERR_DATA_RANGE_SPCOND 4037
#define ERR_DATA_RANGE_SAL 4038
#define ERR_DATA_RANGE_DEPTH 4039
#define ERR_DATA_RANGE_CHL 4040
#define ERR_DATA_RANGE_LDO 4041
#define ERR_SMS_POLLING 4042
#define ERR_SMS_INVALID_CMD 4043
#define ERR_SMS_AUTHORITY 4044
#define ERR_SMS_RCV 4045
#define ERR_SENSOR_STATE 4046
#define ERR_INSUFFICIENT_DATA 4047
#define ERR_DATA_INPUT_NULL 4048
#define ERR_DATA_INPUT_OVER 4049
#define ERR_ANALYZE_FAIL 4050

#define ERR_COL_3RD_SHARP_T 4051
#define ERR_COL_3RD_QUESTION_T 4052
#define ERR_COL_3RD_STAR_T 4053
#define ERR_COL_3RD_TILDE_T 4054
#define ERR_COL_3RD_AT_T 4055

#define ERR_COL_4TH_SHARP_T 4056
#define ERR_COL_4TH_QUESTION_T 4057
#define ERR_COL_4TH_STAR_T 4058
#define ERR_COL_4TH_TILDE_T 4059
#define ERR_COL_4TH_AT_T 4060

#define ERR_COL_5TH_SHARP_T 4061
#define ERR_COL_5TH_QUESTION_T 4062
#define ERR_COL_5TH_STAR_T 4063
#define ERR_COL_5TH_TILDE_T 4064
#define ERR_COL_5TH_AT_T 4065

#define ERR_COL_6TH_SHARP_T 4066
#define ERR_COL_6TH_QUESTION_T 4067
#define ERR_COL_6TH_STAR_T 4068
#define ERR_COL_6TH_TILDE_T 4069
#define ERR_COL_6TH_AT_T 4070

#define ERR_COL_7TH_SHARP_T 4071
#define ERR_COL_7TH_QUESTION_T 4072
#define ERR_COL_7TH_STAR_T 4073
#define ERR_COL_7TH_TILDE_T 4074
#define ERR_COL_7TH_AT_T 4075

#define ERR_COL_8TH_SHARP_T 4076
#define ERR_COL_8TH_QUESTION_T 4077
#define ERR_COL_8TH_STAR_T 4078
#define ERR_COL_8TH_TILDE_T 4079
#define ERR_COL_8TH_AT_T 4080

#define ERR_COL_3RD_SHARP_P 4081
#define ERR_COL_3RD_QUESTION_P 4082
#define ERR_COL_3RD_STAR_P 4083
#define ERR_COL_3RD_TILDE_P 4084
#define ERR_COL_3RD_AT_P 4085

#define ERR_COL_4TH_SHARP_P 4086
#define ERR_COL_4TH_QUESTION_P 4087
#define ERR_COL_4TH_STAR_P 4088
#define ERR_COL_4TH_TILDE_P 4089
#define ERR_COL_4TH_AT_P 4090

#define ERR_COL_5TH_SHARP_P 4091
#define ERR_COL_5TH_QUESTION_P 4092
#define ERR_COL_5TH_STAR_P 4093
#define ERR_COL_5TH_TILDE_P 4094
#define ERR_COL_5TH_AT_P 4095

#define ERR_COL_6TH_SHARP_P 4096
#define ERR_COL_6TH_QUESTION_P 4097
#define ERR_COL_6TH_STAR_P 4098
#define ERR_COL_6TH_TILDE_P 4099
#define ERR_COL_6TH_AT_P 4100

#define ERR_COL_7TH_SHARP_P 4101
#define ERR_COL_7TH_QUESTION_P 4102
#define ERR_COL_7TH_STAR_P 4103
#define ERR_COL_7TH_TILDE_P 4104
#define ERR_COL_7TH_AT_P 4105

#define ERR_COL_8TH_SHARP_P 4106
#define ERR_COL_8TH_QUESTION_P 4107
#define ERR_COL_8TH_STAR_P 4108
#define ERR_COL_8TH_TILDE_P 4109
#define ERR_COL_8TH_AT_P 4110

#define ERR_TRANSFER_DATA_NONE 4111
#define ERR_SAMPLING_T_DOWN 4112
#define ERR_TRANSFERRING_T_DOWN 4113


/*
 *  FLAG MACRO
 */
#define DELAY_FLAG_OFF 0
#define THREAD_OFF 0
#define THREAD_ON 1
#define POWER_OFF 0
#define POWER_ON 1


#define MSG_TYPE_REGISTER 1
#define MSG_TYPE_DATA 2
#define MSG_TYPE_NOTICE 3

// Data Size MACRO
#define S_QUEUE_SIZE 300
#define IP_ADDR_SIZE 20
#define BUFF_SIZE 1024
#define INI_FILE_SIZE 2048
#define RCV_MSG_SIZE (sizeof(t_data) - sizeof(long))

#define MSG_SIZE 100
#define NOTIFICATION_SIZE 114
#define LOG_SIZE 256

// For Period Timing
#define MINUTE 60
#define SMS_SEND_TRY_NUM 3
#define SMS_POLL_TIME 60
#define RE_CONN_TIME 5
#define RECONN_1ST_PRD 3
#define RECONN_2ND_PRD 9
#define DEFAULT_CONN_WAIT_TIME 10
#define SOCK_CONN_WAIT_TIME 10
#define MAX_SERIAL_DELAY_TIME 60


/*
 *	Global Variable Declaration
 */
extern int t_flag;
extern int remote_power;
extern char server_addr[20];
extern char server_port[10];
extern char admin_phone_num[15];
extern char modem_ID[15];
extern char sensor_ID[10];
extern char sampling_period[5];
extern char transferring_period[5];
extern char message_max_num[3];
extern char error_due_date[2];
extern int notificationFlag[NOTIFICATION_SIZE];
extern char notificationString[NOTIFICATION_SIZE][LOG_SIZE];
extern pthread_mutex_t mutex;
extern queue_info sqinfo;
extern char t_timeStamp[3][15];

#endif /* MAIN_H_ */
