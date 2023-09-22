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

	/* �����������ź��� */
	Semaphor_hander = xSemaphoreCreateMutex();
	if(Semaphor_hander == NULL)
	{
		printf("�������ź�������ʧ��\r\n");
	}
	

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
	
	xTaskCreate(task1, "task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, &task1_handle);							
	xTaskCreate(task2, "task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, &task2_handle);	
	xTaskCreate(task3, "task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, &task3_handle);	
																			
	taskEXIT_CRITICAL();							/* �˳��ٽ��� �������������*/
									
	vTaskSuspend(start_task_handle);	/* ����	start_task ���� */
}



void task1(void *argument)
{
	while(1)
	{
		printf("L task ��ȡ�ź���!!��\r\n");
		xSemaphoreTake(Semaphor_hander, portMAX_DELAY);
		printf("L task runing!!��\r\n");
		HAL_Delay(3000);
		printf("L task �ͷ��ź���!!��\r\n");
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
		printf("H task ��ȡ�ź���!!��\r\n");
		xSemaphoreTake(Semaphor_hander, portMAX_DELAY);
		printf("H task runing!!��\r\n");
		HAL_Delay(1000);
		printf("H task �ͷ��ź���!!��\r\n");
		xSemaphoreGive(Semaphor_hander);
		vTaskDelay(1000);
	}
}





