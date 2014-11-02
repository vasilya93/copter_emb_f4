#include <stdint.h>
#include "sensors_fusion.h"
#include "MPU6050.h"
#include "Messenger.h"

void accel_received_callback(int16_t accelx, int16_t accely, int16_t accelz);
void gyro_received_callback(int16_t gyrox, int16_t gyroy, int16_t gyroz);

void sensors_fusion_init(void)
{
	MPU6050_attach_accel_handler(&accel_received_callback);
	MPU6050_attach_gyro_handler(&gyro_received_callback);
}

void accel_received_callback(int16_t accelx, int16_t accely, int16_t accelz)
{
	Messenger_SendByte(SENSFUS_MSG_ACC_INSIDE);
}

void gyro_received_callback(int16_t gyrox, int16_t gyroy, int16_t gyroz)
{
	Messenger_SendByte(SENSFUS_MSG_GYRO_INSIDE);
}
