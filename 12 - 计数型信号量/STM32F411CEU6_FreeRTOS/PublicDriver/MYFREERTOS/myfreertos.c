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

	/* 创建计数型信号量 100 最大值  0 初始值*/
	Semaphor_hander = xSemaphoreCreateCounting(100, 0);
	if(Semaphor_hander == NULL)
	{
		printf("计数型信号量失败\r\n");
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
	
	xTaskCreate(    (TaskFunction_t        )      task1,
									(char*                 )     "task1",
									(configSTACK_DEPTH_TYPE)      TASK1_STACK_SIZE,
									(void*                 )      NULL,
									(UBaseType_t           )      TASK1_PRIORITY,
									(TaskHandle_t*         )      &task1_handle);	
									
									
	xTaskCreate(task2, "task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, &task2_handle);	
									
																	
									
	taskEXIT_CRITICAL();							/* 退出临界区 开启任务调度器*/
									
	vTaskSuspend(start_task_handle);	/* 挂起	start_task 任务 */
}



void task1(void *argument)
{
	BaseType_t ret;
	while(1)
	{
		int key = Get_key(0);
		if(key == s1_down)
		{
			/* 判断信号量有没有被创建完成 */
			if(Semaphor_hander != NULL)	
			{
				/* 释放信号量 +1 */
				ret = xSemaphoreGive(Semaphor_hander);
				if(ret == pdTRUE)
				{
					printf("信号量已释放\r\n");
				}
				else
				{
					printf("信号量释放失败\r\n");
				}
			}
		}
		else if(key == s2_down)
		{
			/* 判断二值信号量有没有被创建完成 */
			if(Semaphor_hander != NULL)	
			{
				/* 死等没有接收到信号量这个任务就是阻塞态保持 100ms 然后执行下面操作 */
				ret = xSemaphoreTake(Semaphor_hander, 100);
				if(ret == pdTRUE)
				{
					printf("信号量已获取\r\n");
				}
				else
				{
					printf("信号量获取失败\r\n");
				}
			}
		}
	}
}


void task2(void *argument)
{
	while(1)
	{
		printf("当前信号量 %ld\r\n", uxSemaphoreGetCount(Semaphor_hander));
		vTaskDelay(1000);
	}
}







