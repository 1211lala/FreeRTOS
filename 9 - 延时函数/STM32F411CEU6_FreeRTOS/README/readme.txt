	
	
	
/*************************************DEMO2 �������ͻָ�****************************************/	

	����������					vTaskSuspend()						���ܷ����ж�������	
	
	
	�������������				vTaskResume()						 �� INCLUDE_vTaskSuspend Ϊ 1
	
	
	�ж��н��������				xTaskResumeFromISR()				 ��	INCLUDE_vTaskSuspend & INCLUDE_xTaskResumeFromISR Ϊ 1
									{
										���ز��� 	pdTRUE		��Ҫ���������л�
													pdFALSE		����Ҫ���������л�
													
										ֻ����FreeRTOS������жϲ���ʹ��FreeRTOS���жϺ��� 
									}      






/*************************************DEMO3 �ж����ȼ����� ****************************************/

ϵͳʱ�� ���� TIM10 ���ȼ�Ĭ��Ϊ 15 �Ҹĳ���0 ��Ȼ�ڹر��ж�ʱ��ʱ��ϵͳ�������� HAL_Delay()�����޷�ʹ��
���Զ�ʱ�� TIM5 �ж����ȼ�Ϊ 4 		���ػص������д�ӡ uwtick ��ֵ
		   TIM9 �ж����ȼ�Ϊ 9 
		   
			portDISABLE_INTERRUPTS();					ʧ���ж�
			portENABLE_INTERRUPTS();					ʹ���ж�




/*************************************DEMO4 4 - �ٽ�δ��뱣���͵������Ĺ�����ָ� ****************************************/

�ٽ�δ��뱣�� ---- �ر��жϵ���
taskENABLE_INTERRUPTS()							���������ٽ��
taskEXIT_CRITICAL()								�����˳��ٽ��

taskENTER_CRITICAL_FROM_ISR()					�жϽ����ٽ��	
taskEXIT_CRITICAL_FROM_ISR()					�ж��˳��ٽ��	



�������Ĺ�����ָ�  ---- �ر������л������ر��ж�
vTaskSuspendAll()
xTaskResumeAll()


/*************************************�б���б��� ****************************************/
list.c
list.h

������;����б���



/************************************ ʱ��Ƭ���� ****************************************/

������������
configUSE_TIME_SLICING == 1
configUSE_PREEMPTION  == 1

�������ȼ��ĳ���ͬ

ͬʱ�ѵδ�ʱ�����ж�ʱ��ĳ�50msһ��








/************************************ ������غ���  ****************************************/

uxTaskPriorityGet() 				��ȡ�������ȼ�
vTaskPrioritySet() 					�����������ȼ�
uxTaskGetSystemState() 				��ȡ��������״̬��Ϣ			configUSE_TRACE_FACILITY == 1
vTaskGetInfo() 						��ȡ����������Ϣ
xTaskGetApplicationTaskTag() 		��ȡ���� Tag
xTaskGetCurrentTaskHandle() 		��ȡ��ǰ�����������


vTaskGetRunTimeStats() 				��ȡ���������ʱ�����Ϣ
xTaskGetHandle() 					��ȡָ�������������
xTaskGetIdleTaskHandle() 			��ȡ���������������
uxTaskGetStackHighWaterMark() 		��ȡ���������ջ��ʷʣ����Сֵ		INCLUDE_uxTaskGetStackHighWaterMark == 1
eTaskGetState() 					��ȡ����״̬
pcTaskGetName 						��ȡ������
xTaskGetTickCount() 				��ȡϵͳʱ�ӽ��ļ�������ֵ
xTaskGetTickCountFromISR() 			�ж��л�ȡϵͳʹ�ý��ļ�������ֵ
xTaskGetSchedulerState()			��ȡ���������״̬
uxTaskGetNumberOfTasks() 			��ȡϵͳ�����������		

vTaskList() 						�ԡ������ʽ��ȡ�����������Ϣ		configUSE_STATS_FORMATTING_FUNCTIONS == 1 configUSE_TRACE_FACILITY == 1

vTaskSetApplicationTaskTag() 		�������� Tag
SetThreadLocalStoragePointer() 		��������Ķ������ݼ�¼����ָ��
GetThreadLocalStoragePointer() 		��ȡ����Ķ������ݼ�¼����ָ��







/************************************ ��ȡ��������ʱ�亯��  ****************************************/
vTaskGetRunTimeStats();		

����������������
#define configUSE_STATS_FORMATTING_FUNCTIONS            1
#define configGENERATE_RUN_TIME_STATS                   1      

����������������Ľӿں���
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()        ConfigureTimeForRunTimeStats()

#define portGET_RUN_TIME_COUNTER_VALUE()                FreeRTOSRunTimeTicks








/************************************ ��ʱ����  ****************************************/
������ʱ	xTaskDelayUntil()	���������񿴳�һ������

�����ʱ 	VTaskDelay()		ָ��ִ�е�VTaskDelay()���������ʼ��ʱ

void task()
{
	printf();
	printf();
	printf();
	VTaskDelay(100)	/* �����ʱ��ʼ��ʱ100ms �ٿ�ʼ�������� */
	printf();
	printf();
	printf();	
}

void task()
{
	xTaskDelayUntil(100)		/* ���������һ��100ms��ʱ�� */
	printf();
	printf();
	printf();
		
	printf();
	printf();
	printf();	
}



















