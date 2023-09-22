#include "./MYFREERTOS/myfreertos.h"



#define START_TASK_STACK_SIZE				128   
#define START_TASK_PRIORITY					1
TaskHandle_t start_task_handle;		


#define TASK1_STACK_SIZE				128   
#define TASK1_PRIORITY					1
TaskHandle_t task1_handle;		

#define TASK2_STACK_SIZE				128   
#define TASK2_PRIORITY					2
TaskHandle_t task2_handle;		

#define TASK3_STACK_SIZE				128   
#define TASK3_PRIORITY					3
TaskHandle_t task3_handle;		



QueueHandle_t Semaphor_hander;
	
void MY_FREERTOS_Init(void) 
{

	/* 创建互斥型信号量 */
	Semaphor_hander = xSemaphoreCreateMutex();
	if(Semaphor_hander == NULL)
	{
		printf("互斥型信号量创建失败\r\n");
	}
	

	if (pdPASS !=  xTaskCreate(	(TaskFunction_t        )      start_task,										/* 指向任务函数的指针 */
															(char*                 )     "start_task",									/* 任务的名字 */
															(configSTACK_DEPTH_TYPE)      START_TASK_STACK_SIZE,				/* 任务的堆栈大小 单位:字 */
															(void*                 )      NULL,													/* 传给任务函数的参数 */
															(UBaseType_t           )      START_TASK_PRIORITY,					/* 任务的优先级 */
															(TaskHandle_t*         )      &start_task_handle	)	)				/* 任务句柄，就是任务的任务控制块 */
			{
				printf("start_task 创建失败\r\n");
			}
			
	osKernelStart();								/* 开启任务调度 */
}


void start_task(void *argument)
{
	taskENTER_CRITICAL();						/* 进入临界区 关闭任务调度器 */
	
	xTaskCreate(task1, "task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, &task1_handle);							
	xTaskCreate(task2, "task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, &task2_handle);	
	xTaskCreate(task3, "task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, &task3_handle);	
																			
	taskEXIT_CRITICAL();							/* 退出临界区 开启任务调度器*/
									
	vTaskSuspend(start_task_handle);	/* 挂起	start_task 任务 */
}



void task1(void *argument)
{
	while(1)
	{
		printf("L task 获取信号量!!！\r\n");
		xSemaphoreTake(Semaphor_hander, portMAX_DELAY);
		printf("L task runing!!！\r\n");
		HAL_Delay(3000);
		printf("L task 释放信号量!!！\r\n");
		xSemaphoreGive(Semaphor_hander);
		vTaskDelay(1000);
	}
}


void task2(void *argument)
{
	while(1)
	{
		printf("task2 runing\r\n");
		vTaskDelay(1000);
	}
}


void task3(void *argument)
{
	while(1)
	{
		printf("H task 获取信号量!!！\r\n");
		xSemaphoreTake(Semaphor_hander, portMAX_DELAY);
		printf("H task runing!!！\r\n");
		HAL_Delay(1000);
		printf("H task 释放信号量!!！\r\n");
		xSemaphoreGive(Semaphor_hander);
		vTaskDelay(1000);
	}
}





