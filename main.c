#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "queue.h"

/*task handelers*/
 TaskHandle_t T1;
 TaskHandle_t T2;
 TaskHandle_t T3;
 TaskHandle_t T4;
 TaskHandle_t T5;

  QueueHandle_t myqueue; // queue handlers

void T1_th(void *data) // first task
{
	int j = 0;
	TickType_t privious_tick;
	while(1)
	{
		printf("[%d] Task1 created\n",j);
		j++;
		printf("Task1 ends\n");
		privious_tick = xTaskGetTickCount(); // finding number of ticks
		vTaskDelayUntil(&privious_tick,pdMS_TO_TICKS(1000)); // make accurete delay 1000 ms
	}
}


void T2_th(void *data) // create task 2
	{
		TickType_t privious_tick;
		int i = 0;
		while(1)
		{
			printf("[%d] Task2 created\n",i);
			i++;
			printf("Task2 ends\n");
			privious_tick = xTaskGetTickCount();
               		vTaskDelayUntil(&privious_tick,pdMS_TO_TICKS(2000));
		}
	}


void T3_th(void *data) // task 3 create
        {
                TickType_t privious_tick;
                int k = 0;
                while(1)
                {
                        printf("[%d] Task3 created\n",k);
                        k++;
                        printf("Task3 ends\n");
                        privious_tick = xTaskGetTickCount();
                        vTaskDelayUntil(&privious_tick,pdMS_TO_TICKS(5000));
                }
        }

void T4_th(void *data) // task 4
        {
        	char txbuff[4]; // create a buffer
		myqueue = xQueueCreate(4,sizeof(txbuff));        
                
		sprintf(txbuff,"10");
		xQueueSend(myqueue, (void *)txbuff,(TickType_t)0);

		sprintf(txbuff,"11");
                xQueueSend(myqueue, (void *)txbuff,(TickType_t)0);
                          
	}

void T5_th(void *data)
        {
                char rxbuff[4];
		while(1)
                {
                        if(myqueue != 0)
               		{
                        	if(xQueueReceive(myqueue, (void *)rxbuff,(TickType_t)3))
                       	 	{
                                	printf("Data received from task 1: %s\n\r",rxbuff);
                        	}
                	}
			else
				break;
                vTaskDelay(pdMS_TO_TICKS(200));
                }
        }

void app_main(void)
{
    xTaskCreate(T1_th,"mytask_1",1024,NULL,0,&T1);
    xTaskCreate(T2_th,"mytask_2",1024,NULL,0,&T2);
    xTaskCreate(T3_th,"mytask_3",1024,NULL,0,&T3);
    xTaskCreate(T4_th,"mytask_4",2048,NULL,0,&T4);
    xTaskCreate(T5_th,"mytask_5",2048,NULL,0,&T5);
}
