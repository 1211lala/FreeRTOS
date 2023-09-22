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
									
									
									
	taskEXIT_CRITICAL();						/* 退出临界区 开启任务调度器*/
									
	vTaskDelete(start_task_handle);	/* 删除	start_task 任务 */
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




List_t TestList;									/* 定义列表变量 */
ListItem_t ListItem1;							/* 定义列表项变量 */
ListItem_t ListItem2;
ListItem_t ListItem3;


void task2(void *argument)
{
	vListInitialise(&TestList);							/* 初始化列表 */
	vListInitialiseItem(&ListItem1);				/* 初始化列表项 */
	vListInitialiseItem(&ListItem2);
	vListInitialiseItem(&ListItem3);
	
	ListItem1.xItemValue = 40;
	ListItem2.xItemValue = 50;
	ListItem3.xItemValue = 60;
	
	
	printf("*************列表和列表项的地址************\r\n");
	printf("/**************第二步：打印列表和列表项的地址**************/\r\n");
	printf("项目\t\t\t地址\r\n");
	printf("TestList\t\t0x%p\t\r\n", &TestList);
	printf("TestList->pxIndex\t0x%p\t\r\n", TestList.pxIndex);
	printf("TestList->xListEnd\t0x%p\t\r\n", (&TestList.xListEnd));
	printf("ListItem1\t\t0x%p\t\r\n", &ListItem1);
	printf("ListItem2\t\t0x%p\t\r\n", &ListItem2);
	printf("ListItem3\t\t0x%p\t\r\n", &ListItem3);
	printf("/**************************结束***************************/\r\n");
	printf("按下S1键继续!\r\n\r\n\r\n");
	while (Get_key(0) != s1_down);
	
	/* 第三步：列表项1插入列表 */
	printf("/*****************第三步：列表项1插入列表******************/\r\n");
	vListInsert((List_t*    )&TestList,         /* 列表 */
							(ListItem_t*)&ListItem1);       /* 列表项 */
	printf("项目\t\t\t\t地址\r\n");
	printf("TestList->xListEnd->pxNext\t0x%p\r\n", (TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext\t\t0x%p\r\n", (ListItem1.pxNext));
	printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious\t\t0x%p\r\n", (ListItem1.pxPrevious));
	printf("/**************************结束***************************/\r\n");
	printf("按下S1键继续!\r\n\r\n\r\n");
	while (Get_key(0) != s1_down);
	
	/* 第四步：列表项2插入列表 */
	printf("/*****************第四步：列表项2插入列表******************/\r\n");
	vListInsert((List_t*    )&TestList,         /* 列表 */
							(ListItem_t*)&ListItem2);       /* 列表项 */
	printf("项目\t\t\t\t地址\r\n");
	printf("TestList->xListEnd->pxNext\t0x%p\r\n", (TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext\t\t0x%p\r\n", (ListItem1.pxNext));
	printf("ListItem2->pxNext\t\t0x%p\r\n", (ListItem2.pxNext));
	printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious\t\t0x%p\r\n", (ListItem1.pxPrevious));
	printf("ListItem2->pxPrevious\t\t0x%p\r\n", (ListItem2.pxPrevious));
	printf("/**************************结束***************************/\r\n");
	printf("按下S1键继续!\r\n\r\n\r\n");
	while (Get_key(0) != s1_down);
	
	/* 第五步：列表项3插入列表 */
	printf("/*****************第五步：列表项3插入列表******************/\r\n");
	vListInsert((List_t*    )&TestList,         /* 列表 */
							(ListItem_t*)&ListItem3);       /* 列表项 */
	printf("项目\t\t\t\t地址\r\n");
	printf("TestList->xListEnd->pxNext\t0x%p\r\n", (TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext\t\t0x%p\r\n", (ListItem1.pxNext));
	printf("ListItem2->pxNext\t\t0x%p\r\n", (ListItem2.pxNext));
	printf("ListItem3->pxNext\t\t0x%p\r\n", (ListItem3.pxNext));
	printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious\t\t0x%p\r\n", (ListItem1.pxPrevious));
	printf("ListItem2->pxPrevious\t\t0x%p\r\n", (ListItem2.pxPrevious));
	printf("ListItem3->pxPrevious\t\t0x%p\r\n", (ListItem3.pxPrevious));
	printf("/**************************结束***************************/\r\n");
	printf("按下S1键继续!\r\n\r\n\r\n");
	while (Get_key(0) != s1_down);
	
	/* 第六步：移除列表项2 */
	printf("/*******************第六步：移除列表项2********************/\r\n");
	uxListRemove((ListItem_t*   )&ListItem2);   /* 移除列表项 */
	printf("项目\t\t\t\t地址\r\n");
	printf("TestList->xListEnd->pxNext\t0x%p\r\n", (TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext\t\t0x%p\r\n", (ListItem1.pxNext));
	printf("ListItem3->pxNext\t\t0x%p\r\n", (ListItem3.pxNext));
	printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious\t\t0x%p\r\n", (ListItem1.pxPrevious));
	printf("ListItem3->pxPrevious\t\t0x%p\r\n", (ListItem3.pxPrevious));
	printf("/**************************结束***************************/\r\n");
	printf("按下KEY0键继续!\r\n\r\n\r\n");
	printf("按下S1键继续!\r\n\r\n\r\n");
	while (Get_key(0) != s1_down);
	
	/* 第七步：列表末尾添加列表项2 */
	printf("/****************第七步：列表末尾添加列表项2****************/\r\n");
	vListInsertEnd((List_t*     )&TestList,     /* 列表 */
								 (ListItem_t* )&ListItem2);   /* 列表项 */
	printf("项目\t\t\t\t地址\r\n");
	printf("TestList->pxIndex\t\t0x%p\r\n", TestList.pxIndex);
	printf("TestList->xListEnd->pxNext\t0x%p\r\n", (TestList.xListEnd.pxNext));
	printf("ListItem1->pxNext\t\t0x%p\r\n", (ListItem1.pxNext));
	printf("ListItem2->pxNext\t\t0x%p\r\n", (ListItem2.pxNext));
	printf("ListItem3->pxNext\t\t0x%p\r\n", (ListItem3.pxNext));
	printf("TestList->xListEnd->pxPrevious\t0x%p\r\n", (TestList.xListEnd.pxPrevious));
	printf("ListItem1->pxPrevious\t\t0x%p\r\n", (ListItem1.pxPrevious));
	printf("ListItem2->pxPrevious\t\t0x%p\r\n", (ListItem2.pxPrevious));
	printf("ListItem3->pxPrevious\t\t0x%p\r\n", (ListItem3.pxPrevious));
	printf("/************************实验结束***************************/\r\n");
	while(1)
	{
		uint8_t num = Get_key(0);
	}
}







