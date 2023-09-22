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
									
	vTaskSuspend(start_task_handle);	/* ɾ��	start_task ���� */
}



void task1(void *argument)
{
	HAL_GPIO_WritePin(led_red_GPIO_Port, led_red_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led_blue_GPIO_Port, led_blue_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, GPIO_PIN_SET);
	while(1)
	{
		uint8_t state;
		
		printf("eRunning=0  eReady=1  eBlocked=2  eSuspended=3  eDeleted=4 \r\n");
		state = eTaskGetState(task1_handle);
		printf("task1 state :%d\r\n",state);
		state = eTaskGetState(task2_handle);
		printf("task2 state :%d\r\n",state);
		state = eTaskGetState(start_task_handle);
		printf("start_task state :%d\r\n",state);
		/* �鿴��ʷ��С��ջ */
		uint16_t stackmin;
		stackmin = uxTaskGetStackHighWaterMark( task2_handle );
		printf("task2��ʷʣ����С��ջ %d * 4 Byte\r\n", stackmin);
		
		HAL_GPIO_TogglePin(led_red_GPIO_Port, led_red_Pin);
		vTaskDelay(1000);
	}
}


void task2(void *argument)
{
	uint8_t task1_priotity = 1;
	uint8_t task2_priotity = 2;
	
	/* ��ȡ��ǰ�ж��ٸ��������� */
	uint16_t task_num = (int)uxTaskGetNumberOfTasks();			
	printf("��ǰ���� %d ������\r\n", task_num);
	

	TaskStatus_t * alltaskstatus;		/* �����ڴ� */
	alltaskstatus = pvPortMalloc(sizeof(TaskStatus_t) * task_num);
	
	TaskStatus_t * alonetaskstatus;
	alonetaskstatus = pvPortMalloc(sizeof(TaskStatus_t));
	/* �ǵ�free  vPortFree(alonetaskstatus); */
	
	char * listbuf;
	while(1)
	{
		
		uint8_t num = Get_key(0);
		switch(num)
		{
			/* ��ȡ��������ȼ� */
			case(s1_down): 
					printf("task1�����ȼ�: %d\r\n", (int)uxTaskPriorityGet(task1_handle));
					printf("task2�����ȼ�: %d\r\n", (int)uxTaskPriorityGet(task2_handle));					
					break;
			/* ��������ȼ� */
			case(s2_down):
					printf("task1�����ȼ���������Ϊ: %d\r\n", task1_priotity+=1);
					vTaskPrioritySet(task1_handle, task1_priotity);
					printf("task2�����ȼ���������Ϊ: %d\r\n", task2_priotity+=1);
					vTaskPrioritySet(task2_handle, task2_priotity);
					break;
			/* ��ȡ�����������Ϣ */
			case(s3_down):
//					uxTaskGetSystemState( alltaskstatus, task_num , NULL);
//					printf("������\t\t �������ȼ�\t\t ������\r\n");
//					for(uint8_t i=0; i<task_num; i++)
//					{
//						printf("%s\t\t\t%ld\t\t\t%ld\r\n",alltaskstatus[i].pcTaskName, alltaskstatus[i].uxCurrentPriority, alltaskstatus[i].xTaskNumber);
//					}
						
						listbuf = pvPortMalloc(200);
						vTaskList(listbuf);
						printf("%s",listbuf);
						vPortFree(listbuf);
					break;
			/* ��ȡ�����������Ϣ */
			case(s4_down):
						vTaskGetInfo(task1_handle, alonetaskstatus, pdTRUE, eInvalid);
						printf("������ %s\r\n",alonetaskstatus->pcTaskName);
						printf("������ %ld\r\n",alonetaskstatus->xTaskNumber);
						printf("��ǰ״̬ %d\r\n",alonetaskstatus->eCurrentState);
						printf("��ǰ���ȼ� %ld\r\n",alonetaskstatus->uxCurrentPriority);
						printf("����ʱ�� %d\r\n",alonetaskstatus->ulRunTimeCounter);
						
					break;
			default:break;
		}
		vTaskDelay(5);
	}
}







