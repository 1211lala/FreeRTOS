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
									
	vTaskSuspend(start_task_handle);	/* 删除	start_task 任务 */
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
		/* 查看历史最小堆栈 */
		uint16_t stackmin;
		stackmin = uxTaskGetStackHighWaterMark( task2_handle );
		printf("task2历史剩余最小堆栈 %d * 4 Byte\r\n", stackmin);
		
		HAL_GPIO_TogglePin(led_red_GPIO_Port, led_red_Pin);
		vTaskDelay(1000);
	}
}


void task2(void *argument)
{
	uint8_t task1_priotity = 1;
	uint8_t task2_priotity = 2;
	
	/* 获取当前有多少个任务数量 */
	uint16_t task_num = (int)uxTaskGetNumberOfTasks();			
	printf("当前共有 %d 个任务\r\n", task_num);
	

	TaskStatus_t * alltaskstatus;		/* 分配内存 */
	alltaskstatus = pvPortMalloc(sizeof(TaskStatus_t) * task_num);
	
	TaskStatus_t * alonetaskstatus;
	alonetaskstatus = pvPortMalloc(sizeof(TaskStatus_t));
	/* 记得free  vPortFree(alonetaskstatus); */
	
	char * listbuf;
	while(1)
	{
		
		uint8_t num = Get_key(0);
		switch(num)
		{
			/* 获取任务的优先级 */
			case(s1_down): 
					printf("task1的优先级: %d\r\n", (int)uxTaskPriorityGet(task1_handle));
					printf("task2的优先级: %d\r\n", (int)uxTaskPriorityGet(task2_handle));					
					break;
			/* 任务的优先级 */
			case(s2_down):
					printf("task1的优先级重新设置为: %d\r\n", task1_priotity+=1);
					vTaskPrioritySet(task1_handle, task1_priotity);
					printf("task2的优先级重新设置为: %d\r\n", task2_priotity+=1);
					vTaskPrioritySet(task2_handle, task2_priotity);
					break;
			/* 获取所有任务的消息 */
			case(s3_down):
//					uxTaskGetSystemState( alltaskstatus, task_num , NULL);
//					printf("任务名\t\t 任务优先级\t\t 任务编号\r\n");
//					for(uint8_t i=0; i<task_num; i++)
//					{
//						printf("%s\t\t\t%ld\t\t\t%ld\r\n",alltaskstatus[i].pcTaskName, alltaskstatus[i].uxCurrentPriority, alltaskstatus[i].xTaskNumber);
//					}
						
						listbuf = pvPortMalloc(200);
						vTaskList(listbuf);
						printf("%s",listbuf);
						vPortFree(listbuf);
					break;
			/* 获取单个任务的消息 */
			case(s4_down):
						vTaskGetInfo(task1_handle, alonetaskstatus, pdTRUE, eInvalid);
						printf("任务名 %s\r\n",alonetaskstatus->pcTaskName);
						printf("任务编号 %ld\r\n",alonetaskstatus->xTaskNumber);
						printf("当前状态 %d\r\n",alonetaskstatus->eCurrentState);
						printf("当前优先级 %ld\r\n",alonetaskstatus->uxCurrentPriority);
						printf("运行时间 %d\r\n",alonetaskstatus->ulRunTimeCounter);
						
					break;
			default:break;
		}
		vTaskDelay(5);
	}
}







