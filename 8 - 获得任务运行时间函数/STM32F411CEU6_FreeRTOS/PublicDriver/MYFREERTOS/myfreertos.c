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

void MY_FREERTOS_Init(void) 
{
	if (pdPASS !=  xTaskCreate(	(TaskFunction_t        )      start_task,										/* ָ����������ָ�� */
															(char*                 )     "start_task",									/* ��������� */
															(configSTACK_DEPTH_TYPE)      START_TASK_STACK_SIZE,				/* ����Ķ�ջ��С ��λ:�� */
															(void*                 )      NULL,													/* �����������Ĳ��� */
															(UBaseType_t           )      START_TASK_PRIORITY,					/* ��������ȼ� */
															(TaskHandle_t*         )      &start_task_handle	)	)				/* �����������������������ƿ� */
			{
				printf("start_task ����ʧ��\r\n");
			}
			
	osKernelStart();								/* ����������� */
}


void start_task(void *argument)
{
	taskENTER_CRITICAL();						/* �����ٽ��� �ر���������� */
	
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
									
	taskEXIT_CRITICAL();							/* �˳��ٽ��� �������������*/
									
	vTaskSuspend(start_task_handle);	/* ����	start_task ���� */
}



void task1(void *argument)
{
	while(1)
	{
		HAL_GPIO_TogglePin(led_red_GPIO_Port, led_red_Pin);
		vTaskDelay(10);
	}
}


void task2(void *argument)
{
	while(1)
	{
		HAL_GPIO_TogglePin(led_green_GPIO_Port, led_green_Pin);
		vTaskDelay(10);
	}
}

void task3(void *argument)
{
	HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led_blue_GPIO_Port, led_blue_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, GPIO_PIN_RESET);
	
	char *runtimebuf;

	while(1)
	{
		int key = Get_key(0);
		if(key == s1_down)
		{
			runtimebuf = pvPortMalloc(400);
			vTaskGetRunTimeStats(runtimebuf);
			printf("%s\r\n",runtimebuf);
			vPortFree(runtimebuf);
		}
		vTaskDelay(2);
	}
}





