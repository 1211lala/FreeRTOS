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


/* 队列句柄 */
QueueHandle_t	key_queue;
QueueHandle_t	big_data_queue;

char data_buf[100] = "aaaaaaaaaaaaaaaaawwddw我的大数组";
	
void MY_FREERTOS_Init(void) 
{
	/* 创建长度为2,每个项大小为一个字节的队列 */
	key_queue = xQueueCreate(2, sizeof(uint8_t));
	if(key_queue == NULL)
	{
		printf("key_queue创建失败\r\n");
	}
	
	/* 创建长度为1,每个项大小为四个字节的队列(存的地址) */
	big_data_queue = xQueueCreate(1, sizeof(char*));
	if(key_queue == NULL)
	{
		printf("big_data_queue创建失败\r\n");
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
									
									
	xTaskCreate(    (TaskFunction_t        )      task2,
									(char*                 )     "task2",
									(configSTACK_DEPTH_TYPE)      TASK2_STACK_SIZE,
									(void*                 )      NULL,
									(UBaseType_t           )      TASK2_PRIORITY,
									(TaskHandle_t*         )      &task2_handle);	
									
									
	xTaskCreate(    (TaskFunction_t        )      task3,
									(char*                 )     "task3",
									(configSTACK_DEPTH_TYPE)      TASK3_STACK_SIZE,
									(void*                 )      NULL,
									(UBaseType_t           )      TASK3_PRIORITY,
									(TaskHandle_t*         )      &task3_handle);									
									
	taskEXIT_CRITICAL();							/* 退出临界区 开启任务调度器*/
									
	vTaskSuspend(start_task_handle);	/* 挂起	start_task 任务 */
}



void task1(void *argument)
{
	BaseType_t ret;
	char *buf;
	buf = &data_buf[0];
	while(1)
	{
		int key = Get_key(0);
		switch(key)
		{
			/* 入队 */
			case(s1_down):	
						ret = xQueueSendToBack(key_queue, &key, portMAX_DELAY); 
						if(ret != pdTRUE)
						{
							printf("s1_down队列发送失败\r\n");
						}
						break;
						
			case(s2_down):	 	
						ret = xQueueSendToBack(key_queue, &key, portMAX_DELAY); 
						if(ret != pdTRUE)
						{
							printf("s2_down队列发送失败\r\n");
						}
						break;
			case(s3_down):
						ret = xQueueSend(big_data_queue, &buf, portMAX_DELAY); 
						if(ret != pdTRUE)
						{
							printf("s3_down队列发送失败\r\n");
						}

						break;
		}
		vTaskDelay(10);
	}
}


void task2(void *argument)
{
	uint8_t key;
	BaseType_t ret;
	while(1)
	{
		ret = xQueueReceive(key_queue, &key, portMAX_DELAY);
		if(ret != pdTRUE)
		{
			printf("队列key_queue读取失败\r\n");
		}
		else
		{
			printf("队列key_queue读取成功%d\r\n", key);
		}
		vTaskDelay(10);
	}
}


void task3(void *argument)
{
	HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led_blue_GPIO_Port, led_blue_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, GPIO_PIN_SET);
	
	
	/*
	固定写  很重要
	*/
	BaseType_t ret;
	char *buf;			/* 定义一个指针变量来存放接收的地址(四个字节) */
	while(1)
	{																			/* 取指针变量的地址 接收的地址 */
		ret = xQueueReceive(big_data_queue, &buf, portMAX_DELAY);
		if(ret != pdTRUE)
		{
			printf("队列big_data_queue读取失败\r\n");
		}
		else
		{
			printf("队列big_data_queue读取成功 %s\r\n", buf);
		}
		vTaskDelay(10);
	}
} 





