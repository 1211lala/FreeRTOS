	
	
	
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









