	
	
	
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











/************************************  ��Ϣ����   ****************************************/
	������д��ʱ�������ٽ���,�޷����������л�
	
	���е���Ӻͳ���	Ĭ���Ƚ��ȳ�(FIFO first in first out)

	���ݴ��ݵķ�ʽ		����ʵ��ֵ���ǵ�ַ
	
	
	������� 
		������������,���������״̬�б�����ڵ������б�, �����¼����ڵ��ȴ�����
	
	�������� 
		��������Ϊ��,���������״̬�б�����ڵ������б�, �����¼����ڵ��ȴ�����



	xQueueCreate();
		����ʧ��  ����NULL
		�����ɹ����ؾ��
		
	#define queueQUEUE_TYPE_BASE ( ( uint8_t ) 0U ) /* ���� */
	#define queueQUEUE_TYPE_SET ( ( uint8_t ) 0U ) /* ���м� */
	#define queueQUEUE_TYPE_MUTEX ( ( uint8_t ) 1U ) /* �����ź��� */
	#define queueQUEUE_TYPE_COUNTING_SEMAPHORE ( ( uint8_t ) 2U ) /* �������ź��� */
	#define queueQUEUE_TYPE_BINARY_SEMAPHORE ( ( uint8_t ) 3U ) /* ��ֵ�ź��� */
	#define queueQUEUE_TYPE_RECURSIVE_MUTEX ( ( uint8_t ) 4U ) /* �ݹ黥���ź��� */

	xQueueSend() �����е�β��д����Ϣ
	xQueueSendToBack() ͬ xQueueSend()
	xQueueSendToFront() �����е�ͷ��д����Ϣ
	xQueueOverwrite() ��д������Ϣ��ֻ���ڶ��г���Ϊ 1 �������
	
	xQueueSendFromISR() ���ж��������е�β��д����Ϣ
	xQueueSendToBackFromISR() ͬ xQueueSendFromISR()
	xQueueSendToFrontFromISR() ���ж��������е�ͷ��д����Ϣ
	xQueueOverwriteFromISR() ���ж��и�д������Ϣ��ֻ���ڶ��г���Ϊ 1 �������



	xQueueReceive() �Ӷ���ͷ����ȡ��Ϣ����ɾ����Ϣ
	xQueuePeek() �Ӷ���ͷ����ȡ��Ϣ
	xQueueReceiveFromISR() ���ж��дӶ���ͷ����ȡ��Ϣ����ɾ����Ϣ
	xQueuePeekFromISR() ���ж��дӶ���ͷ����ȡ��Ϣ








/************************************  ���м�   ****************************************/

xQueueCreateSet() �������м�
xQueueAddToSet() ������ӵ����м���
xQueueRemoveFromSet() �Ӷ��м����Ƴ�����
xQueueSelectFromSet() ��ȡ���м�������Ч��Ϣ�Ķ���
xQueueSelectFromSetFromISR() ���ж��л�ȡ���м�������Ч��Ϣ�Ķ���










/************************************  �ź���   ****************************************/


	��ֵ�ź���	Ĭ��Ϊ0
		
		����������ͬ��
	
		������ֵ�ź��� -> �ͷŶ�ֵ�ź��� -> ��ȡ��ֵ�ź���
		
		
		xSemaphoreCreateBinary() ʹ�ö�̬��ʽ l ��ֵ�ź���
		xSemaphoreCreateBinaryStatic() ʹ�þ�̬��ʽ������ֵ�ź���
		xSemaphoreTake() ��ȡ�ź���
		xSemaphoreTakeFromISR(). ���ж��л�ȡ�ź���
		xSemaphoreGive() �ͷ��ź���
		xSemaphoreGiveFromISR() ���ж����ͷ��ź���
		vSemaphoreDelete() ɾ���ź���
	
	
	
	�����������ź���	
		
		Ӧ�÷�Χ  
			�¼�����	��ʼ�ź���������������
			��Դ����	��ʼ�ź�������Ϊ���

		xSemaphoreCreateCounting() ʹ�ö�̬��ʽ�����������ź���
		xSemaphoreCreateCountingStatic() ʹ�þ�̬��ʽ�����������ź���
		xSemaphoreGive() �ͷ��ź���
		xSemaphoreGiveFromISR() ���ж����ͷ��ź���
		xSemaphoreTake() ��ȡ�ź���
		xSemaphoreTakeFromISR(). ���ж��л�ȡ�ź���
		uxSemaphoreGetCount() �õ�����ֵ
		vSemaphoreDelete() ɾ���ź���



	���������ź��� 	--Ĭ��Ϊ1    �������ȼ��̳еĶ�ֵ�ź���		����ʹ�����ж���
		
		�����ڻ���������	��һ�������ȼ�������͵����ȼ�������ͬ�²���һ�������ź���ʱ����������ź����������ȼ���ȡ����ô�����ȼ��ᱻ���������ǻ�ѵ����ȼ������ȼ���ߵ��͸����ȼ�һ��
		
		������ֵ�ź��� -> ��ȡ��ֵ�ź��� -> �ͷŶ�ֵ�ź��� 
		
		xSemaphoreCreateMutex() ʹ�ö�̬��ʽ���������ź���
		xSemaphoreCreateMutexStatic() ʹ�þ�̬��ʽ���������ź���
		xSemaphoreTake() ��ȡ�ź���
		xSemaphoreGive() �ͷ��ź���
		vSemaphoreDelete() ɾ���ź���
	







/******************************************* �¼���־�� *********************************************/
	xEventGroupCreate() ʹ�ö�̬��ʽ�����¼���־��
	xEventGroupCreateStstic() ʹ�þ�̬��ʽ�����¼���־��
	vEventGroupDelete() ɾ���¼���־��
	xEventGroupWaitBits() �ȴ��¼���־λ
	xEventGroupSetBits() �����¼���־λ
	xEventGroupSetBitsFromISR() ���ж��������¼���־λ
	xEventGroupClearBits() �����¼���־λ
	xEventGroupClearBitsFromISR() ���ж��������¼���־λ
	xEventGroupGetBits() ��ȡ�¼����и��¼���־λ��ֵ
	xEventGroupGetBitsFromISR() ���ж��л�ȡ�¼����и��¼���־λ��ֵ
	xEventGroupSync() �����¼���־λ�����ȴ��¼���־λ
	
	
https://www.freertos.org/zh-cn-cmn-s/xEventGroupWaitBits.html

	EventBits_t xEventGroupWaitBits(
		   const EventGroupHandle_t xEventGroup,
		   const EventBits_t uxBitsToWaitFor,
		   const BaseType_t xClearOnExit,
		   const BaseType_t xWaitForAllBits,
		   TickType_t xTicksToWait );
