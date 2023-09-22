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



QueueSetHandle_t	queueset;
QueueHandle_t	queue;
QueueHandle_t semaphore;
QueueHandle_t	semaphorecount;

void MY_FREERTOS_Init(void) 
{

	queue = xQueueCreate(1, sizeof(uint8_t));
	if(queue != NULL)
	{
		printf("队列创建成功\r\n");
	}
	semaphore = xSemaphoreCreateBinary();
	if(semaphore != NULL)
	{
		printf("二值信号量创建成功\r\n");
	}
	/* 计数型信号量在加入队列集时不能有数据 所以这里为 0 */
//	semaphorecount = xSemaphoreCreateCounting(100, 0);
//	if(semaphorecount != NULL)
//	{
//		printf("计数信号量创建成功\r\n");
//	}
	
	/* 创建队列集容纳队列3 */
	queueset = xQueueCreateSet(3);
	if(queueset != NULL)
	{
		printf("队列集创建成功\r\n");
	}
	
	xQueueAddToSet(queue, queueset);
	xQueueAddToSet(semaphore, queueset);
	xQueueAddToSet(semaphorecount, queueset);
	
	
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
		uint8_t key = Get_key(0);
		switch(key)
		{
			case(s1_down):	
					if(xSemaphoreGive(semaphore) == pdTRUE)
					{
						printf("二值信号量释放成功\r\n");
					} break;
//			case(s2_down):	
//					if(xSemaphoreGive(semaphorecount) == pdTRUE)
//					{
//						printf("计数信号量释放成功\r\n");
//					} break;
//			case(s3_down):	
//					if(xSemaphoreTake(semaphorecount, portMAX_DELAY) == pdTRUE)
//					{
//						printf("计数信号量获取成功\r\n");
//					} break;
			case(s4_down):	
					if(xQueueSendToBack(queue, &key, portMAX_DELAY) == pdTRUE)
					{
						printf("队列数据发送成功\r\n");
					}
					break;
		}
		vTaskDelay(10);
	}
}

QueueHandle_t	queue;
QueueHandle_t semaphore;
QueueHandle_t	semaphorecount;
void task2(void *argument)
{
	QueueSetMemberHandle_t memberhandle;
	while(1)
	{
		memberhandle = xQueueSelectFromSet(queueset, portMAX_DELAY );
		/* 如果是队列消息 */
		if(memberhandle == queue)
		{
			uint8_t rec;
			xQueueReceive(queue, &rec, portMAX_DELAY);
			printf("已经读取队列消息:%d\r\n", rec);
			
		}/* 如果是二值信号量 */
		else if(memberhandle == semaphore)
		{
			xSemaphoreTake(semaphore,portMAX_DELAY);
			printf("二值量已获取\r\n");
		}
//		else if(memberhandle == semaphorecount)
//		{
//			uint8_t rec;
//			rec = uxSemaphoreGetCount(semaphorecount);
//			printf("已经读计数消息:%d\r\n", rec);
//		}
	}
}


void task3(void *argument)
{
	while(1)
	{
		vTaskDelay(10);
	}
}





