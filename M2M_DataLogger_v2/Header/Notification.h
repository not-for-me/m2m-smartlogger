/*
 * Notification.h
 *
 *  Created on: 2013. 4. 4.
 *      Author: Administrator
 */

#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_

#include "SMS.h"
#include "Main.h"
int checkEventFlag(int eventNo);
void makeTimeStamp(int i);
void *thread_notification(void * arg);

#endif /* NOTIFICATION_H_ */
