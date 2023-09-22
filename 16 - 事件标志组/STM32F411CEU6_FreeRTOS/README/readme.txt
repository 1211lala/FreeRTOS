	
	
	
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











/************************************  消息队列   ****************************************/
	队列在写的时候会进入临界区,无法进行任务切换
	
	队列的入队和出队	默认先进先出(FIFO first in first out)

	数据传递的方式		传入实际值不是地址
	
	
	入队阻塞 
		队列数据已满,将该任务的状态列表项挂在到阻塞列表, 任务事件挂在到等待发送
	
	出队阻塞 
		队列数据为空,将该任务的状态列表项挂在到阻塞列表, 任务事件挂在到等待接收



	xQueueCreate();
		创建失败  返回NULL
		创建成功返回句柄
		
	#define queueQUEUE_TYPE_BASE ( ( uint8_t ) 0U ) /* 队列 */
	#define queueQUEUE_TYPE_SET ( ( uint8_t ) 0U ) /* 队列集 */
	#define queueQUEUE_TYPE_MUTEX ( ( uint8_t ) 1U ) /* 互斥信号量 */
	#define queueQUEUE_TYPE_COUNTING_SEMAPHORE ( ( uint8_t ) 2U ) /* 计数型信号量 */
	#define queueQUEUE_TYPE_BINARY_SEMAPHORE ( ( uint8_t ) 3U ) /* 二值信号量 */
	#define queueQUEUE_TYPE_RECURSIVE_MUTEX ( ( uint8_t ) 4U ) /* 递归互斥信号量 */

	xQueueSend() 往队列的尾部写入消息
	xQueueSendToBack() 同 xQueueSend()
	xQueueSendToFront() 往队列的头部写入消息
	xQueueOverwrite() 覆写队列消息（只用于队列长度为 1 的情况）
	
	xQueueSendFromISR() 在中断中往队列的尾部写入消息
	xQueueSendToBackFromISR() 同 xQueueSendFromISR()
	xQueueSendToFrontFromISR() 在中断中往队列的头部写入消息
	xQueueOverwriteFromISR() 在中断中覆写队列消息（只用于队列长度为 1 的情况）



	xQueueReceive() 从队列头部读取消息，并删除消息
	xQueuePeek() 从队列头部读取消息
	xQueueReceiveFromISR() 在中断中从队列头部读取消息，并删除消息
	xQueuePeekFromISR() 在中断中从队列头部读取消息








/************************************  队列集   ****************************************/

xQueueCreateSet() 创建队列集
xQueueAddToSet() 队列添加到队列集中
xQueueRemoveFromSet() 从队列集中移除队列
xQueueSelectFromSet() 获取队列集中有有效消息的队列
xQueueSelectFromSetFromISR() 在中断中获取队列集中有有效消息的队列










/************************************  信号量   ****************************************/


	二值信号量	默认为0
		
		适用于任务同步
	
		创建二值信号量 -> 释放二值信号量 -> 获取二值信号量
		
		
		xSemaphoreCreateBinary() 使用动态方式 l 二值信号量
		xSemaphoreCreateBinaryStatic() 使用静态方式创建二值信号量
		xSemaphoreTake() 获取信号量
		xSemaphoreTakeFromISR(). 在中断中获取信号量
		xSemaphoreGive() 释放信号量
		xSemaphoreGiveFromISR() 在中断中释放信号量
		vSemaphoreDelete() 删除信号量
	
	
	
	二、计数型信号量	
		
		应用范围  
			事件计数	初始信号量可以自行设置
			资源管理	初始信号量设置为最大

		xSemaphoreCreateCounting() 使用动态方式创建计数型信号量
		xSemaphoreCreateCountingStatic() 使用静态方式创建计数型信号量
		xSemaphoreGive() 释放信号量
		xSemaphoreGiveFromISR() 在中断中释放信号量
		xSemaphoreTake() 获取信号量
		xSemaphoreTakeFromISR(). 在中断中获取信号量
		uxSemaphoreGetCount() 得到计数值
		vSemaphoreDelete() 删除信号量



	三、互斥信号量 	--默认为1    带有优先级继承的二值信号量		不能使用在中断中
		
		适用于互斥任务中	在一个高优先级的任务和低优先级的任务同事操作一个互斥信号量时，如果互斥信号量被低优先级获取，那么高优先级会被阻塞，但是会把低优先级的优先级提高到和高优先级一样
		
		创建二值信号量 -> 获取二值信号量 -> 释放二值信号量 
		
		xSemaphoreCreateMutex() 使用动态方式创建互斥信号量
		xSemaphoreCreateMutexStatic() 使用静态方式创建互斥信号量
		xSemaphoreTake() 获取信号量
		xSemaphoreGive() 释放信号量
		vSemaphoreDelete() 删除信号量
	







/******************************************* 事件标志组 *********************************************/
	xEventGroupCreate() 使用动态方式创建事件标志组
	xEventGroupCreateStstic() 使用静态方式创建事件标志组
	vEventGroupDelete() 删除事件标志组
	xEventGroupWaitBits() 等待事件标志位
	xEventGroupSetBits() 设置事件标志位
	xEventGroupSetBitsFromISR() 在中断中设置事件标志位
	xEventGroupClearBits() 清零事件标志位
	xEventGroupClearBitsFromISR() 在中断中清零事件标志位
	xEventGroupGetBits() 获取事件组中各事件标志位的值
	xEventGroupGetBitsFromISR() 在中断中获取事件组中各事件标志位的值
	xEventGroupSync() 设置事件标志位，并等待事件标志位
	
	
https://www.freertos.org/zh-cn-cmn-s/xEventGroupWaitBits.html

	EventBits_t xEventGroupWaitBits(
		   const EventGroupHandle_t xEventGroup,
		   const EventBits_t uxBitsToWaitFor,
		   const BaseType_t xClearOnExit,
		   const BaseType_t xWaitForAllBits,
		   TickType_t xTicksToWait );
