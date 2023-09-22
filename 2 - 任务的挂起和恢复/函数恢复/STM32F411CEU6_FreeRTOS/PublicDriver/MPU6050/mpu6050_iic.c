#include ".\MPU6050\mpu6050_iic.h"

/**
 * @brief       ����I2C�ٶȵ���ʱ
 * @param       ��
 * @retval      ��
 */
static void mpu_iic_delay(void)
{
    delay_us(&htim10, 2);
}

/**
 * @brief   IIC�ӿڳ�ʼ��
 */
void mpu_iic_init(void)
{
//    GPIO_InitTypeDef gpio_init_struct;
//    
//    MPU_IIC_SCL_GPIO_CLK_ENABLE();   /* SCL����ʱ��ʹ�� */
//    MPU_IIC_SDA_GPIO_CLK_ENABLE();   /* SDA����ʱ��ʹ�� */

//    gpio_init_struct.Pin = MPU_IIC_SCL_GPIO_PIN;
//    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_OD;             /* ��©��� */
//    gpio_init_struct.Pull = GPIO_PULLUP;                     /* ���� */
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;      /* ���� */
//    HAL_GPIO_Init(MPU_IIC_SCL_GPIO_PORT, &gpio_init_struct);  /* ��ʼ��SCL���� */
//    
//    gpio_init_struct.Pin = MPU_IIC_SDA_GPIO_PIN;
//    HAL_GPIO_Init(MPU_IIC_SDA_GPIO_PORT, &gpio_init_struct);  /* ��ʼ��SDA���� */
    /* SDA����ģʽ����,��©���,����, �����Ͳ���������IO������, ��©�����ʱ��(=1), Ҳ���Զ�ȡ�ⲿ�źŵĸߵ͵�ƽ */

    mpu_iic_stop();  /* ֹͣ�����������豸 */
}

/**
 * @brief       ����IIC��ʼ�ź�
 * @param       ��
 * @retval      ��
 */
void mpu_iic_start(void)
{
    MPU_IIC_SDA(1);
    MPU_IIC_SCL(1);
    mpu_iic_delay();
    MPU_IIC_SDA(0);      /* START�ź�: ��SCLΪ��ʱ, SDA�Ӹ߱�ɵ�, ��ʾ��ʼ�ź� */
    mpu_iic_delay();
    MPU_IIC_SCL(0);      /* ǯסI2C���ߣ�׼�����ͻ�������� */
    mpu_iic_delay();
}

/**
 * @brief       ����IICֹͣ�ź�
 * @param       ��
 * @retval      ��
 */
void mpu_iic_stop(void)
{
    MPU_IIC_SDA(0);      /* STOP�ź�: ��SCLΪ��ʱ, SDA�ӵͱ�ɸ�, ��ʾֹͣ�ź� */
    mpu_iic_delay();
    MPU_IIC_SCL(1);
    mpu_iic_delay();
    MPU_IIC_SDA(1);      /* ����I2C���߽����ź� */
    mpu_iic_delay();
}

/**
 * @brief       �ȴ�Ӧ���źŵ���
 * @param       ��
 * @retval      1������Ӧ��ʧ��
 *              0������Ӧ��ɹ�
 */
uint8_t mpu_iic_wait_ack(void)
{
    uint8_t waittime = 0;
    uint8_t rack = 0;
    
    MPU_IIC_SDA(1);      /* �����ͷ�SDA��(��ʱ�ⲿ������������SDA��) */
    mpu_iic_delay();
    MPU_IIC_SCL(1);      /* SCL=1, ��ʱ�ӻ����Է���ACK */
    mpu_iic_delay();

    while (MPU_READ_SDA) /* �ȴ�Ӧ�� */
    {
        waittime++;

        if (waittime > 250)
        {
            mpu_iic_stop();
            rack = 1;
            break;
        }

        mpu_iic_delay();
    }

    MPU_IIC_SCL(0);      /* SCL=0, ����ACK��� */
    mpu_iic_delay();
    return rack;
}


/**
 * @brief       ����ACKӦ��
 * @param       ��
 * @retval      ��
 */
void mpu_iic_ack(void)
{
    MPU_IIC_SDA(0);  /* SCL 0 -> 1  ʱSDA = 0,��ʾӦ�� */
    mpu_iic_delay();
    MPU_IIC_SCL(1);
    mpu_iic_delay();
    MPU_IIC_SCL(0);
    mpu_iic_delay(); 
    MPU_IIC_SDA(1);  /* �����ͷ�SDA�� */
    mpu_iic_delay(); 
}

/**
 * @brief       ������ACKӦ��
 * @param       ��
 * @retval      ��
 */
void mpu_iic_nack(void)
{
    MPU_IIC_SDA(1);  /* SCL 0 -> 1  ʱ SDA = 1,��ʾ��Ӧ�� */
    mpu_iic_delay();
    MPU_IIC_SCL(1);
    mpu_iic_delay();
    MPU_IIC_SCL(0);
    mpu_iic_delay();
}

/**
 * @brief       IIC����һ���ֽ�
 * @param       data: Ҫ���͵�����
 * @retval      ��
 */
void mpu_iic_send_byte(uint8_t data)
{
    uint8_t t;
    
    for (t = 0; t < 8; t++)
    {
        MPU_IIC_SDA((data & 0x80) >> 7); /* ��λ�ȷ��� */
        mpu_iic_delay();
        MPU_IIC_SCL(1);
        mpu_iic_delay();
        MPU_IIC_SCL(0);
        data <<= 1;     /* ����1λ,������һ�η��� */
    }

    MPU_IIC_SDA(1);      /* �������, �����ͷ�SDA�� */
}

/**
 * @brief       IIC����һ���ֽ�
 * @param       ack:  ack=1ʱ������ack; ack=0ʱ������nack
 * @retval      ���յ�������
 */
uint8_t mpu_iic_read_byte(unsigned char ack)
{
    uint8_t i, receive = 0;

    for (i = 0; i < 8; i++ )    /* ����1���ֽ����� */
    {
        receive <<= 1;          /* ��λ�����,�������յ�������λҪ���� */
        MPU_IIC_SCL(1);
        mpu_iic_delay();

        if (MPU_READ_SDA)
        {
            receive++;
        }
        
        MPU_IIC_SCL(0);
        mpu_iic_delay();

    }

    if (!ack)
    {
        mpu_iic_nack();  /* ����nACK */
    }
    else
    {
        mpu_iic_ack();   /* ����ACK */
    }

    return receive;
}







