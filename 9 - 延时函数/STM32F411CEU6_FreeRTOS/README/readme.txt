	
	
	
/*************************************DEMO2 任务挂起和恢复****************************************/	

	函数挂起函数					vTaskSuspend()						不能放在中断中运行	
	
	
	函数解除挂起函数				vTaskResume()						 置 INCLUDE_vTaskSuspend 为 1
	
	
	中断中解除挂起函数				xTaskResumeFromISR()				 置	INCLUDE_vTaskSuspend & INCLUDE_xTaskResumeFromISR 为 1
									{
										返回参数 	pdTRUE		需要进行任务切换
													pdFALSE		不需要进行任务切换
													
										只有在FreeRTOS管理的中断才能使用FreeRTOS的中断函数 
									}      






/*************************************DEMO3 中断优先级管理 ****************************************/

系统时基 来自 TIM10 优先级默认为 15 我改成了0 不然在关闭中断时，时基系统不工作， HAL_Delay()函数无法使用
测试定时器 TIM5 中断优先级为 4 		并载回调函数中打印 uwtick 的值
		   TIM9 中断优先级为 9 
		   
			portDISABLE_INTERRUPTS();					失能中断
			portENABLE_INTERRUPTS();					使能中断




/*************************************DEMO4 4 - 临界段代码保护和调度器的挂起与恢复 ****************************************/

临界段代码保护 ---- 关闭中断调度
taskENABLE_INTERRUPTS()							函数进入临界段
taskEXIT_CRITICAL()								函数退出临界段

taskENTER_CRITICAL_FROM_ISR()					中断进入临界段	
taskEXIT_CRITICAL_FROM_ISR()					中断退出临界段	



调度器的挂起与恢复  ---- 关闭任务切换，不关闭中断
vTaskSuspendAll()
xTaskResumeAll()


/*************************************列表和列表项 ****************************************/
list.c
list.h

可以中途添加列表项



/************************************ 时间片调度 ****************************************/

打开下面两个宏
configUSE_TIME_SLICING == 1
configUSE_PREEMPTION  == 1

任务优先级改成相同

同时把滴答定时器的中断时间改成50ms一次








/************************************ 任务相关函数  ****************************************/

uxTaskPriorityGet() 				获取任务优先级
vTaskPrioritySet() 					设置任务优先级
uxTaskGetSystemState() 				获取所有任务状态信息			configUSE_TRACE_FACILITY == 1
vTaskGetInfo() 						获取单个任务信息
xTaskGetApplicationTaskTag() 		获取任务 Tag
xTaskGetCurrentTaskHandle() 		获取当前任务的任务句柄


vTaskGetRunTimeStats() 				获取任务的运行时间等信息
xTaskGetHandle() 					获取指定任务的任务句柄
xTaskGetIdleTaskHandle() 			获取空闲任务的任务句柄
uxTaskGetStackHighWaterMark() 		获取任务的任务栈历史剩余最小值		INCLUDE_uxTaskGetStackHighWaterMark == 1
eTaskGetState() 					获取任务状态
pcTaskGetName 						获取任务名
xTaskGetTickCount() 				获取系统时钟节拍计数器的值
xTaskGetTickCountFromISR() 			中断中获取系统使用节拍计数器的值
xTaskGetSchedulerState()			获取任务调度器状态
uxTaskGetNumberOfTasks() 			获取系统中任务的数量		

vTaskList() 						以“表格”形式获取所有任务的信息		configUSE_STATS_FORMATTING_FUNCTIONS == 1 configUSE_TRACE_FACILITY == 1

vTaskSetApplicationTaskTag() 		设置任务 Tag
SetThreadLocalStoragePointer() 		设置任务的独有数据记录数组指针
GetThreadLocalStoragePointer() 		获取任务的独有数据记录数组指针







/************************************ 获取任务运行时间函数  ****************************************/
vTaskGetRunTimeStats();		

将下面两个宏设置
#define configUSE_STATS_FORMATTING_FUNCTIONS            1
#define configGENERATE_RUN_TIME_STATS                   1      

再配置下面两个宏的接口函数
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()        ConfigureTimeForRunTimeStats()

#define portGET_RUN_TIME_COUNTER_VALUE()                FreeRTOSRunTimeTicks








/************************************ 延时函数  ****************************************/
绝对延时	xTaskDelayUntil()	把整个任务看成一个整体

相对延时 	VTaskDelay()		指从执行到VTaskDelay()这个函数开始延时

void task()
{
	printf();
	printf();
	printf();
	VTaskDelay(100)	/* 在这个时候开始计时100ms 再开始下面的语句 */
	printf();
	printf();
	printf();	
}

void task()
{
	xTaskDelayUntil(100)		/* 整个任务就一共100ms的时间 */
	printf();
	printf();
	printf();
		
	printf();
	printf();
	printf();	
}



















