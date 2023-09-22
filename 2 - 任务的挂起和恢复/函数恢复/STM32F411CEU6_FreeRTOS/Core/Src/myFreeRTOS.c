#include "myFreeRTOS.h"

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
	osKernelStart();					/* 开启任务调度 */
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
									
	taskEXIT_CRITICAL();						/* 退出临界区 开启任务调度器*/
									
	vTaskDelete(start_task_handle);	/* 删除	start_task 任务 */
}



void task1(void *argument)
{
	while(1)
	{
		HAL_GPIO_TogglePin(led_green_GPIO_Port, led_green_Pin);
		osDelay(500);
	}
}



void task2(void *argument)
{
	HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, GPIO_PIN_RESET);
	while(1)
	{
		HAL_GPIO_TogglePin(led_red_GPIO_Port, led_red_Pin);
		osDelay(500);
	}
}


void task3(void *argument)
{
	uint8_t key_status = 0;
	uint8_t flag = 0;
	while(1)
	{
//		key_status = Get_key(0);
//		if(key_status == key_down)
//		{
//			if(flag == 0)
//			{
//				flag = 1;
//				vTaskSuspend(task2_handle);										/* 挂起 task2 */
//				printf("task_3被挂起!!\r\n");
//			}
//			else 
//			{
//				flag = 0;
//				vTaskResume(task2_handle);										/* 恢复 task2 */
//				printf("task_3重新运行!!\r\n");	
//			}
//		}
//		osDelay(10);
	}
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == Key_Pin)
	{
		printf("task_!!\r\n");
		static uint8_t flag = 0;
		if(flag == 0)
		{
			flag = 1;
			vTaskSuspend(task2_handle);														/* 挂起 task2 */
			printf("task_3被挂起!!\r\n");
		}
		else if(flag == 1)
		{
			flag = 0;
			BaseType_t xYieldRequired;
			xYieldRequired = xTaskResumeFromISR(task2_handle);		/* 恢复 task2 */
			if(xYieldRequired == pdTRUE)
			{
				portYIELD_FROM_ISR( xYieldRequired );
			}
			else if(xYieldRequired == pdFALSE)
			{         
			}
		}
		printf("task_3重新运行!!\r\n");	
	}
}


