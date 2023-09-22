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


/* ���о�� */
QueueHandle_t	key_queue;
QueueHandle_t	big_data_queue;

char data_buf[100] = "aaaaaaaaaaaaaaaaawwddw�ҵĴ�����";
	
void MY_FREERTOS_Init(void) 
{
	/* ��������Ϊ2,ÿ�����СΪһ���ֽڵĶ��� */
	key_queue = xQueueCreate(2, sizeof(uint8_t));
	if(key_queue == NULL)
	{
		printf("key_queue����ʧ��\r\n");
	}
	
	/* ��������Ϊ1,ÿ�����СΪ�ĸ��ֽڵĶ���(��ĵ�ַ) */
	big_data_queue = xQueueCreate(1, sizeof(char*));
	if(key_queue == NULL)
	{
		printf("big_data_queue����ʧ��\r\n");
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
	BaseType_t ret;
	char *buf;
	buf = &data_buf[0];
	while(1)
	{
		int key = Get_key(0);
		switch(key)
		{
			/* ��� */
			case(s1_down):	
						ret = xQueueSendToBack(key_queue, &key, portMAX_DELAY); 
						if(ret != pdTRUE)
						{
							printf("s1_down���з���ʧ��\r\n");
						}
						break;
						
			case(s2_down):	 	
						ret = xQueueSendToBack(key_queue, &key, portMAX_DELAY); 
						if(ret != pdTRUE)
						{
							printf("s2_down���з���ʧ��\r\n");
						}
						break;
			case(s3_down):
						ret = xQueueSend(big_data_queue, &buf, portMAX_DELAY); 
						if(ret != pdTRUE)
						{
							printf("s3_down���з���ʧ��\r\n");
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
			printf("����key_queue��ȡʧ��\r\n");
		}
		else
		{
			printf("����key_queue��ȡ�ɹ�%d\r\n", key);
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
	�̶�д  ����Ҫ
	*/
	BaseType_t ret;
	char *buf;			/* ����һ��ָ���������Ž��յĵ�ַ(�ĸ��ֽ�) */
	while(1)
	{																			/* ȡָ������ĵ�ַ ���յĵ�ַ */
		ret = xQueueReceive(big_data_queue, &buf, portMAX_DELAY);
		if(ret != pdTRUE)
		{
			printf("����big_data_queue��ȡʧ��\r\n");
		}
		else
		{
			printf("����big_data_queue��ȡ�ɹ� %s\r\n", buf);
		}
		vTaskDelay(10);
	}
} 





