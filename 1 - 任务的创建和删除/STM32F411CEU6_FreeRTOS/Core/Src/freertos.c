/* USER CODE BEGIN Header */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "myFreeRTOS.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/* USER CODE END Variables */
/* Definitions for Task_LED_Red */
osThreadId_t Task_LED_RedHandle;
const osThreadAttr_t Task_LED_Red_attributes = {
  .name = "Task_LED_Red",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_LED_Green */
osThreadId_t Task_LED_GreenHandle;
const osThreadAttr_t Task_LED_Green_attributes = {
  .name = "Task_LED_Green",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void AppTask_LED_Red(void *argument);
void AppTask_LED_Green(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	MY_FREERTOS_Init();
	return;
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_LED_Red */
  Task_LED_RedHandle = osThreadNew(AppTask_LED_Red, NULL, &Task_LED_Red_attributes);

  /* creation of Task_LED_Green */
  Task_LED_GreenHandle = osThreadNew(AppTask_LED_Green, NULL, &Task_LED_Green_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_AppTask_LED_Red */
/* USER CODE END Header_AppTask_LED_Red */
void AppTask_LED_Red(void *argument)
{
  /* USER CODE BEGIN AppTask_LED_Red */
  /* USER CODE END AppTask_LED_Red */
}

/* USER CODE BEGIN Header_AppTask_LED_Green */
/* USER CODE END Header_AppTask_LED_Green */
void AppTask_LED_Green(void *argument)
{
  /* USER CODE BEGIN AppTask_LED_Green */
  /* USER CODE END AppTask_LED_Green */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */

