#ifndef __MPU6050_IIC_H_
#define __MPU6050_IIC_H_


#include "main.h"
#include "gpio.h"
#include "tim.h"
/******************************************************************************************/
/* CT_IIC ���� ���� */

//#define MPU_IIC_SCL_GPIO_PORT            GPIOB
//#define MPU_IIC_SCL_GPIO_PIN             GPIO_PIN_0
//#define MPU_IIC_SCL_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB��ʱ��ʹ�� */

//#define MPU_IIC_SDA_GPIO_PORT            GPIOB
//#define MPU_IIC_SDA_GPIO_PIN             GPIO_PIN_1
//#define MPU_IIC_SDA_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB��ʱ��ʹ�� */

/******************************************************************************************/

/* IO���� */
#define MPU_IIC_SCL(x)     do{ x ? \
                              HAL_GPIO_WritePin(mpu6050_scl_GPIO_Port, mpu6050_scl_Pin, GPIO_PIN_SET) : \
                              HAL_GPIO_WritePin(mpu6050_scl_GPIO_Port, mpu6050_scl_Pin, GPIO_PIN_RESET); \
                          }while(0)       /* SCL */

#define MPU_IIC_SDA(x)     do{ x ? \
                              HAL_GPIO_WritePin(mpu6050_sda_GPIO_Port, mpu6050_sda_Pin, GPIO_PIN_SET) : \
                              HAL_GPIO_WritePin(mpu6050_sda_GPIO_Port, mpu6050_sda_Pin, GPIO_PIN_RESET); \
                          }while(0)       /* SDA */

#define MPU_READ_SDA       HAL_GPIO_ReadPin(mpu6050_sda_GPIO_Port, mpu6050_sda_Pin) /* ��ȡSDA */


/* IIC���в������� */
void mpu_iic_init(void);             /* ��ʼ��IIC��IO�� */
void mpu_iic_stop(void);             /* ����IICֹͣ�ź� */
void mpu_iic_start(void);            /* ����IIC��ʼ�ź� */

void mpu_iic_ack(void);              /* IIC����ACK�ź� */
void mpu_iic_nack(void);             /* IIC������ACK�ź� */
uint8_t mpu_iic_wait_ack(void);      /* IIC�ȴ�ACK�ź� */

void mpu_iic_send_byte(uint8_t txd);         /* IIC����һ���ֽ� */
uint8_t mpu_iic_read_byte(unsigned char ack);/* IIC��ȡһ���ֽ� */

#endif
