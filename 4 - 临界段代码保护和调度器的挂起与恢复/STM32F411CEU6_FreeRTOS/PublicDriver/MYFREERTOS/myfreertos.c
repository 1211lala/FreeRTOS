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
									
									
									
	taskEXIT_CRITICAL();						/* �˳��ٽ��� �������������*/
									
	vTaskDelete(start_task_handle);	/* ɾ��	start_task ���� */
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
			printf("�ж��ѹرգ�����\r\n\r\n");
			HAL_Delay(5000);
			portENABLE_INTERRUPTS();
			printf("�ж��Ѵ򿪣�����\r\n\r\n");
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





