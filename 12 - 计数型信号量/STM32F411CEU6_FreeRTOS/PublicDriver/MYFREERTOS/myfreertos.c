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

	/* �����������ź��� 100 ���ֵ  0 ��ʼֵ*/
	Semaphor_hander = xSemaphoreCreateCounting(100, 0);
	if(Semaphor_hander == NULL)
	{
		printf("�������ź���ʧ��\r\n");
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
									
									
	xTaskCreate(task2, "task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, &task2_handle);	
									
																	
									
	taskEXIT_CRITICAL();							/* �˳��ٽ��� �������������*/
									
	vTaskSuspend(start_task_handle);	/* ����	start_task ���� */
}



void task1(void *argument)
{
	BaseType_t ret;
	while(1)
	{
		int key = Get_key(0);
		if(key == s1_down)
		{
			/* �ж��ź�����û�б�������� */
			if(Semaphor_hander != NULL)	
			{
				/* �ͷ��ź��� +1 */
				ret = xSemaphoreGive(Semaphor_hander);
				if(ret == pdTRUE)
				{
					printf("�ź������ͷ�\r\n");
				}
				else
				{
					printf("�ź����ͷ�ʧ��\r\n");
				}
			}
		}
		else if(key == s2_down)
		{
			/* �ж϶�ֵ�ź�����û�б�������� */
			if(Semaphor_hander != NULL)	
			{
				/* ����û�н��յ��ź�����������������̬���� 100ms Ȼ��ִ��������� */
				ret = xSemaphoreTake(Semaphor_hander, 100);
				if(ret == pdTRUE)
				{
					printf("�ź����ѻ�ȡ\r\n");
				}
				else
				{
					printf("�ź�����ȡʧ��\r\n");
				}
			}
		}
	}
}


void task2(void *argument)
{
	while(1)
	{
		printf("��ǰ�ź��� %ld\r\n", uxSemaphoreGetCount(Semaphor_hander));
		vTaskDelay(1000);
	}
}







