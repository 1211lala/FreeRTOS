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
#define TASK3_PRIORITY					2
TaskHandle_t task3_handle;		


#define EVENTBIT_0			1 << 0
#define EVENTBIT_1			1 << 1
#define EVENTBIT_2			1 << 2

EventGroupHandle_t eventgroup;


void MY_FREERTOS_Init(void) 
{
	
	eventgroup = xEventGroupCreate();
	if(eventgroup != NULL)
	{
		printf("事件标志组创建成功\r\n");
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
		uint8_t key = Get_key(0);
		switch(key)
		{
			case(s1_down):
					printf("设置事件标志组bit0\r\n");
					xEventGroupSetBits(eventgroup, EVENTBIT_0);
					break;
			case(s2_down):
					printf("设置事件标志组bit1\r\n");
					xEventGroupSetBits(eventgroup, EVENTBIT_1);
					break;
			case(s3_down):
					printf("设置事件标志组bit2\r\n");
					xEventGroupSetBits(eventgroup, EVENTBIT_2);
					break;
			case(s4_down):break;
		}
		vTaskDelay(10);
	}
}


void task2(void *argument)
{
	while(1)
	{
		EventBits_t rec;
		rec = xEventGroupWaitBits(eventgroup, 0x01, pdTRUE, pdTRUE, portMAX_DELAY);
		printf("事件标志 %#x\r\n",rec);
		HAL_GPIO_TogglePin(led_red_GPIO_Port, led_red_Pin);
	}
}

void task3(void *argument)
{
	HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led_blue_GPIO_Port, led_blue_Pin, GPIO_PIN_SET);
	while(1)
	{
		EventBits_t rec;
		rec = xEventGroupWaitBits(eventgroup, EVENTBIT_1|EVENTBIT_2, pdTRUE, pdTRUE, portMAX_DELAY);
		printf("事件标志 %#x\r\n",rec);
		HAL_GPIO_TogglePin(led_green_GPIO_Port, led_green_Pin);
	}
}




