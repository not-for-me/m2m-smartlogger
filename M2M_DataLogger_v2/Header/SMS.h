/*
 * SMS.h
 *
 *  Created on: 2013. 3. 6.
 *      Author: Administrator
 */

#ifndef SMS_H_
#define SMS_H_

#include "Log.h"
#include "Main.h"


typedef struct{
	char key[32];
	char value[16];
}sms_cmd;

#define SENSOR_ID_CMD "#sensor id"
#define SENSOR_SAMPLING_CMD "#sensor sam_prd"
#define MODEM_TRANSFER_CMD "#modem trans_prd"
#define ERROR_DUE_DATE_CMD "#modem notice_due"
#define MESSAGE_NUM_CMD "#msg num"
#define ADMIN_NUM_CMD "#admin num"
#define PROGRAM_MODE_CMD "#program mode"
#define SERVER_ADDR_CMD "#server addr"
#define SERVER_PORT_CMD "#server port"

//short sendSMSToAdmin(char *msg);
int pollSMSCommand();
int doSMSCommand();
void parseSMSCommand(char *str, sms_cmd *parsedResult);
void processSMSCommand(sms_cmd *parsedResult);

#endif /* SMS_H_ */
