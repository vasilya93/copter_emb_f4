#include "stm32f4xx.h"
#include "ClockControl.h"
#include "Timer.h"
#include "Serial.h"
#include "Messenger.h"
#include "Wire.h"
#include "MPU6050.h"

int led_state;
bool are_devs_init = false;

void init_all(void);
void start_operation(void);
void toggle_led(void);
void delay(unsigned int cycles_num);
void send_message(void);
void begin_wire(void);

int main(void)
{
	init_all();
	
	while(1);
}

void init_all(void) 
{
	ClockControl_Initialize();
	
	Serial_Begin(115200);
	Serial_OutBufOver_Attach(&toggle_led);
	Messenger_Initialize(&start_operation, MSNR_MODE_5BYTE);
	
	Wire_Initialize();
	MPU6050_Initialize(MPU6050_ST_CALIBRATE_GYRO | MPU6050_ST_CALIBRATE_ACCEL);
	
	led_state = 0;
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;
	GPIOD->ODR &= ~(GPIO_ODR_ODR_12 | GPIO_ODR_ODR_13 | GPIO_ODR_ODR_14 | GPIO_ODR_ODR_15);
}

void start_operation(void)
{
	Timer_init(TIMER6);
	Timer_start(TIMER6, begin_wire, 20000, true);
}

void toggle_led(void)
{
	if (led_state) {
		led_state = 0;
		GPIOD->ODR &= ~(GPIO_ODR_ODR_12 | GPIO_ODR_ODR_13 | GPIO_ODR_ODR_14 | GPIO_ODR_ODR_15);
	} else {
		led_state = 1;
		GPIOD->ODR |= GPIO_ODR_ODR_12 | GPIO_ODR_ODR_13 | GPIO_ODR_ODR_14 | GPIO_ODR_ODR_15;
	}
}

void delay(unsigned int cycles_num)
{
	while (cycles_num--);
}

void send_message(void)
{
	Messenger_SendByte(I2C_MSG_ERR);
}

void begin_wire(void)
{
	if (are_devs_init) {
		Wire_BeginCycle();
		return;
	}
	
	are_devs_init = true;
	Wire_InitDevices();
}
