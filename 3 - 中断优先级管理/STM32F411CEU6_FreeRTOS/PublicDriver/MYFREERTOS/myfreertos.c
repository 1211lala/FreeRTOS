#include "./MYFREERTOS/myfreertos.h"



#define START_TASK_STACK_SIZE				128   
#define START_TASK_PRIORITY					1
TaskHandle_t start_task_handle;		


#define TASK1_STACK_SIZE				128   
#define TASK1_PRIORITY					2
TaskHandle_t task1_handle;		

#define TASK2_STACK_SIZE				128   
#define TASK2_PRIORITY					1
TaskHandle_t task2_handle;		



void MY_FREERTOS_Init(void) 
{
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
									
									
									
	taskEXIT_CRITICAL();						/* 退出临界区 开启任务调度器*/
									
	vTaskDelete(start_task_handle);	/* 删除	start_task 任务 */
}



void task1(void *argument)
{
	HAL_GPIO_WritePin(led_green_GPIO_Port,led_green_Pin,GPIO_PIN_SET);
	uint8_t num = 0;
	while(1)
	{
		if(num++ == 5)
		{
			num = 0;
			portDISABLE_INTERRUPTS();
			printf("中断已关闭！！！\r\n\r\n");
			HAL_Delay(5000);
			portENABLE_INTERRUPTS();
			printf("中断已打开！！！\r\n\r\n");
		}
		osDelay(1000);
	}
}



void task2(void *argument)
{
	while(1)
	{
		osDelay(1000);
	}
}





