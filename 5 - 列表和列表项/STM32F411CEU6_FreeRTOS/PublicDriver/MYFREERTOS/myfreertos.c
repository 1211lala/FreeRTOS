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
	while(1)
	{
		HAL_GPIO_TogglePin(led_green_GPIO_Port, led_green_Pin);
		osDelay(1000);
	}
}




List_t TestList;									/* �����б���� */
ListItem_t ListItem1;							/* �����б������ */
ListItem_t ListItem2;
ListItem_t ListItem3;


void task2(void *argument)
{
	vListInitialise(&TestList);							/* ��ʼ���б� */
	vListInitialiseItem(&ListItem1);				/* ��ʼ���б��� */
	vListInitialiseItem(&ListItem2);
	vListInitialiseItem(&ListItem3);
	
	ListItem1.xItemValue = 40;
	ListItem2.xItemValue = 50;
	ListItem3.xItemValue = 60;
	
	
	printf("*************�б���б���ĵ�ַ************\r\n");
	printf("/**************�ڶ�������ӡ�б���б���ĵ�ַ**************/\r\n");
	printf("��Ŀ\t\t\t��ַ\r\n");
	printf("TestList\t\t0x%p\t\r\n", &TestList);
	printf("TestList->pxIndex\t0x%p\t\r\n", TestList.pxIndex);
	printf("TestList->xListEnd\t0x%p\t\r\n", (&TestList.xListEnd));
	printf("ListItem1\t\t0x%p\t\r\n", &ListItem1);
	printf("ListItem2\t\t0x%p\t\r\n", &ListItem2);
	printf("ListItem3\t\t0x%p\t\r\n", &ListItem3);
	printf("/**************************����***************************/\r\n");
	printf("����S1������!\r\n\r\n\r\n");
	while (Get_key(0) != s1_down);
	
	/* ���������б���1�����б� */
	printf("/*****************���������б���1�����б�******************/\r\n");
	vListInsert((List_t*    )&TestList,         /* �б� */
							(ListItem_t*)&ListItem1);       /* �б��� */
	printf("��Ŀ\t\t\t\t��ַ\r\n");
	printf("TestList->xListEnd->pxNext\t0x%p\r\n", (TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext\t\t0x%p\r\n", (ListItem1.pxNext));
	printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious\t\t0x%p\r\n", (ListItem1.pxPrevious));
	printf("/**************************����***************************/\r\n");
	printf("����S1������!\r\n\r\n\r\n");
	while (Get_key(0) != s1_down);
	
	/* ���Ĳ����б���2�����б� */
	printf("/*****************���Ĳ����б���2�����б�******************/\r\n");
	vListInsert((List_t*    )&TestList,         /* �б� */
							(ListItem_t*)&ListItem2);       /* �б��� */
	printf("��Ŀ\t\t\t\t��ַ\r\n");
	printf("TestList->xListEnd->pxNext\t0x%p\r\n", (TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext\t\t0x%p\r\n", (ListItem1.pxNext));
	printf("ListItem2->pxNext\t\t0x%p\r\n", (ListItem2.pxNext));
	printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious\t\t0x%p\r\n", (ListItem1.pxPrevious));
	printf("ListItem2->pxPrevious\t\t0x%p\r\n", (ListItem2.pxPrevious));
	printf("/**************************����***************************/\r\n");
	printf("����S1������!\r\n\r\n\r\n");
	while (Get_key(0) != s1_down);
	
	/* ���岽���б���3�����б� */
	printf("/*****************���岽���б���3�����б�******************/\r\n");
	vListInsert((List_t*    )&TestList,         /* �б� */
							(ListItem_t*)&ListItem3);       /* �б��� */
	printf("��Ŀ\t\t\t\t��ַ\r\n");
	printf("TestList->xListEnd->pxNext\t0x%p\r\n", (TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext\t\t0x%p\r\n", (ListItem1.pxNext));
	printf("ListItem2->pxNext\t\t0x%p\r\n", (ListItem2.pxNext));
	printf("ListItem3->pxNext\t\t0x%p\r\n", (ListItem3.pxNext));
	printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious\t\t0x%p\r\n", (ListItem1.pxPrevious));
	printf("ListItem2->pxPrevious\t\t0x%p\r\n", (ListItem2.pxPrevious));
	printf("ListItem3->pxPrevious\t\t0x%p\r\n", (ListItem3.pxPrevious));
	printf("/**************************����***************************/\r\n");
	printf("����S1������!\r\n\r\n\r\n");
	while (Get_key(0) != s1_down);
	
	/* ���������Ƴ��б���2 */
	printf("/*******************���������Ƴ��б���2********************/\r\n");
	uxListRemove((ListItem_t*   )&ListItem2);   /* �Ƴ��б��� */
	printf("��Ŀ\t\t\t\t��ַ\r\n");
	printf("TestList->xListEnd->pxNext\t0x%p\r\n", (TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext\t\t0x%p\r\n", (ListItem1.pxNext));
	printf("ListItem3->pxNext\t\t0x%p\r\n", (ListItem3.pxNext));
	printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious\t\t0x%p\r\n", (ListItem1.pxPrevious));
	printf("ListItem3->pxPrevious\t\t0x%p\r\n", (ListItem3.pxPrevious));
	printf("/**************************����***************************/\r\n");
	printf("����KEY0������!\r\n\r\n\r\n");
	printf("����S1������!\r\n\r\n\r\n");
	while (Get_key(0) != s1_down);
	
	/* ���߲����б�ĩβ����б���2 */
	printf("/****************���߲����б�ĩβ����б���2****************/\r\n");
	vListInsertEnd((List_t*     )&TestList,     /* �б� */
								 (ListItem_t* )&ListItem2);   /* �б��� */
	printf("��Ŀ\t\t\t\t��ַ\r\n");
	printf("TestList->pxIndex\t\t0x%p\r\n", TestList.pxIndex);
	printf("TestList->xListEnd->pxNext\t0x%p\r\n", (TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext\t\t0x%p\r\n", (ListItem1.pxNext));
	printf("ListItem2->pxNext\t\t0x%p\r\n", (ListItem2.pxNext));
	printf("ListItem3->pxNext\t\t0x%p\r\n", (ListItem3.pxNext));
	printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious\t\t0x%p\r\n", (ListItem1.pxPrevious));
	printf("ListItem2->pxPrevious\t\t0x%p\r\n", (ListItem2.pxPrevious));
	printf("ListItem3->pxPrevious\t\t0x%p\r\n", (ListItem3.pxPrevious));
	printf("/************************ʵ�����***************************/\r\n");
	while(1)
	{
		uint8_t num = Get_key(0);
	}
}







