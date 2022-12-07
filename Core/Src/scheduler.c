/*
 * scheduler.c
 *
 *  Created on: Nov 22, 2022
 *      Author: IBM
 */
#include "scheduler.h"
#include "stdlib.h"

static queue_t ReadyQueue;
static queue_t RunQueue;

void SCH_INIT(){
	ReadyQueue.size=0;
	RunQueue.size=0;
}
sTask * createTask (uint32_t TID , uint32_t Period , uint32_t Delay , void (* pTask )()){
	sTask* newTask = (sTask*)malloc(sizeof(sTask));
	newTask->TID = TID;
	newTask->Delay= Delay;
	newTask->Period = Period;
	newTask->pTask = pTask;
	newTask->RunMe = 0;
	return newTask;
}
uint32_t SCH_Add_Task(void (*func)(),uint32_t Delay,uint32_t Period ){
	if(ReadyQueue.size == SCH_MAX_TASKS ) return 0;
	sTask* newTask = createTask(1,Period,Delay,func);

	int32_t idx = ReadyQueue.size-1;
	while ( idx>= 0 && (int32_t)(newTask->Delay-ReadyQueue.task[idx]->Delay)>= 0){
		newTask->Delay-=ReadyQueue.task[idx]->Delay;
		ReadyQueue.task[idx+1]=ReadyQueue.task[idx];
		idx--;
	}
	idx+= 1;
	if (idx>0){
		ReadyQueue.task[idx-1]->Delay-=newTask->Delay ;
	}
	ReadyQueue.task [idx]=newTask ;
	ReadyQueue.size++;
	return newTask->TID ;
}
void SCH_Update_Task (){
	if(ReadyQueue.size!= 0){
		if (ReadyQueue.task[ReadyQueue.size-1]->Delay==0){
			ReadyQueue.size --;
			ReadyQueue.task [ReadyQueue.size]->RunMe+=1;
			ReadyQueue.task [ReadyQueue.size]->Delay=ReadyQueue.task[ReadyQueue.size]->Period ;
			RunQueue.task[RunQueue.size]=ReadyQueue.task [ReadyQueue.size];
			RunQueue.size++;
		}
		else{
			ReadyQueue.task[ReadyQueue.size-1]->Delay--;
		}
	}
}
void SCH_Dispatch_Task(){
	while(RunQueue.size!= 0){
		(*(RunQueue.task[RunQueue.size-1]->pTask))();
		RunQueue.task[RunQueue.size-1]->RunMe-= 1;
		if(RunQueue.task[RunQueue.size-1]->Period!= 0){
			SCH_Add_Task(RunQueue.task[RunQueue.size-1]->pTask,RunQueue.task[RunQueue.size-1]->Delay,RunQueue.task[RunQueue.size-1]->Period);
		}
		free(RunQueue.task[RunQueue.size-1]);
		RunQueue.task[RunQueue.size-1]=NULL;
		RunQueue.size--;
	}
}
void BlinkLed0(){
HAL_GPIO_TogglePin(GPIOA ,A0_Pin);
}
void BlinkLed1(){
HAL_GPIO_TogglePin(GPIOA , A1_Pin);
}
void BlinkLed2(){
HAL_GPIO_TogglePin(GPIOA ,A2_Pin);
}
void BlinkLed3(){
HAL_GPIO_TogglePin(GPIOA , A3_Pin);
}
void BlinkLed4(){
HAL_GPIO_TogglePin(GPIOA , A4_Pin);
}
