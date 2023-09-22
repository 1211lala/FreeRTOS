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

	/* 创建二值信号量 */
	Semaphor_hander = xSemaphoreCreateBinary();
	if(Semaphor_hander == NULL)
	{
		printf("二值信号量创建失败\r\n");
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
			/* 判断二值信号量有没有被创建完成 */
			if(Semaphor_hander != NULL)	
			{
				ret = xSemaphoreGive(Semaphor_hander);
				if(ret == pdTRUE)
				{
					printf("二值信号量已释放\r\n");
				}
				else
				{
					printf("二值信号量释放失败\r\n");
				}
			}
		}
	}
}


void task2(void *argument)
{
	BaseType_t ret;
	uint8_t num = 0;
	while(1)
	{
		/* 判断二值信号量有没有被创建完成 */
		if(Semaphor_hander != NULL)	
		{
			/* 死等没有接收到信号量这个任务就是阻塞态 */
			ret = xSemaphoreTake(Semaphor_hander, portMAX_DELAY);
			if(ret == pdTRUE)
			{
				printf("信号量已接收 接收次数 %d\r\n", num +=1);
			}
			else
			{
				printf("信号量接收失败\r\n");
			}
		}
		
		/* 这个函数的末尾没写 vTaskDelay() 因为在xSemaphoreTake 没接收到信号量之前会一直保持阻塞状态 */
	}
}







