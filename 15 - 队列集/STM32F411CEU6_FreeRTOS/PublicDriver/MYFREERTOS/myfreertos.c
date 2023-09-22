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



QueueSetHandle_t	queueset;
QueueHandle_t	queue;
QueueHandle_t semaphore;
QueueHandle_t	semaphorecount;

void MY_FREERTOS_Init(void) 
{

	queue = xQueueCreate(1, sizeof(uint8_t));
	if(queue != NULL)
	{
		printf("���д����ɹ�\r\n");
	}
	semaphore = xSemaphoreCreateBinary();
	if(semaphore != NULL)
	{
		printf("��ֵ�ź��������ɹ�\r\n");
	}
	/* �������ź����ڼ�����м�ʱ���������� ��������Ϊ 0 */
//	semaphorecount = xSemaphoreCreateCounting(100, 0);
//	if(semaphorecount != NULL)
//	{
//		printf("�����ź��������ɹ�\r\n");
//	}
	
	/* �������м����ɶ���3 */
	queueset = xQueueCreateSet(3);
	if(queueset != NULL)
	{
		printf("���м������ɹ�\r\n");
	}
	
	xQueueAddToSet(queue, queueset);
	xQueueAddToSet(semaphore, queueset);
	xQueueAddToSet(semaphorecount, queueset);
	
	
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
		uint8_t key = Get_key(0);
		switch(key)
		{
			case(s1_down):	
					if(xSemaphoreGive(semaphore) == pdTRUE)
					{
						printf("��ֵ�ź����ͷųɹ�\r\n");
					} break;
//			case(s2_down):	
//					if(xSemaphoreGive(semaphorecount) == pdTRUE)
//					{
//						printf("�����ź����ͷųɹ�\r\n");
//					} break;
//			case(s3_down):	
//					if(xSemaphoreTake(semaphorecount, portMAX_DELAY) == pdTRUE)
//					{
//						printf("�����ź�����ȡ�ɹ�\r\n");
//					} break;
			case(s4_down):	
					if(xQueueSendToBack(queue, &key, portMAX_DELAY) == pdTRUE)
					{
						printf("�������ݷ��ͳɹ�\r\n");
					}
					break;
		}
		vTaskDelay(10);
	}
}

QueueHandle_t	queue;
QueueHandle_t semaphore;
QueueHandle_t	semaphorecount;
void task2(void *argument)
{
	QueueSetMemberHandle_t memberhandle;
	while(1)
	{
		memberhandle = xQueueSelectFromSet(queueset, portMAX_DELAY );
		/* ����Ƕ�����Ϣ */
		if(memberhandle == queue)
		{
			uint8_t rec;
			xQueueReceive(queue, &rec, portMAX_DELAY);
			printf("�Ѿ���ȡ������Ϣ:%d\r\n", rec);
			
		}/* ����Ƕ�ֵ�ź��� */
		else if(memberhandle == semaphore)
		{
			xSemaphoreTake(semaphore,portMAX_DELAY);
			printf("��ֵ���ѻ�ȡ\r\n");
		}
//		else if(memberhandle == semaphorecount)
//		{
//			uint8_t rec;
//			rec = uxSemaphoreGetCount(semaphorecount);
//			printf("�Ѿ���������Ϣ:%d\r\n", rec);
//		}
	}
}


void task3(void *argument)
{
	while(1)
	{
		vTaskDelay(10);
	}
}





