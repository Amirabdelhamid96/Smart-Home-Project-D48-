/*
 * rtos2.c
 *
 * Created: 11/11/2022 8:21:58 PM
 * Author : Ahmed
 */ 

#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t myfierstTask = NULL; 
TaskHandle_t mysecondTask = NULL;
TaskHandle_t myTask = NULL;

void task1(void * p)
{
	while (1)
	{
		PORTA = 0xff;
		vTaskDelay(1000);
		PORTA = 0x00;
		vTaskDelay(1000);
	}
}

void task2(void * p)
{
	while (1)
	{
		PORTB = 0xff;
		vTaskDelay(1000);
		PORTB = 0x00;
		vTaskDelay(1000);
	}
}
/*
void task3(void * p)
{
	
	while (1)
	{
		vTaskSuspend(myfierstTask);
		vTaskResume(mysecondTask);
		vTaskDelay(6000);
		
		vTaskSuspend(mysecondTask);
		vTaskResume(myfierstTask);
		vTaskDelay(6000);
	}
}
*/

int main(void)
{
	DDRA = 0xff ;
	DDRB = 0xff ;
	xTaskCreate(task1,"test1",200,(void *)0,tskIDLE_PRIORITY,&myfierstTask);
/*	xTaskCreate(task3,"test3",200,(void *)0,tskIDLE_PRIORITY,&myTask);*/
	xTaskCreate(task2,"test2",200,(void *)0,tskIDLE_PRIORITY,&mysecondTask);
	vTaskStartScheduler();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

