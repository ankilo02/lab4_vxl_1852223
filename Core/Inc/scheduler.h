/*
 * scheduler.h
 *
 *  Created on: Nov 22, 2022
 *      Author: IBM
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"
typedef struct{
	uint32_t TID;
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	void(*pTask)(void);
} sTask;
#define SCH_MAX_TASKS 	40
#define NO_TASK_ID 		0

typedef struct queue {
	sTask* task[SCH_MAX_TASKS];
	uint32_t size;
}queue_t;




sTask* createTask (uint32_t TID , uint32_t Period , uint32_t Delay , void (* pTask)());
uint32_t SCH_Add_Task (void (*func)(),uint32_t Delay,uint32_t Period );
void SCH_INIT();
void SCH_Update_Task ();
void SCH_Dispatch_Task();
void BlinkLed0();
void BlinkLed1();
void BlinkLed2();
void BlinkLed3();
void BlinkLed4();

#endif /* INC_SCHEDULER_H_ */
