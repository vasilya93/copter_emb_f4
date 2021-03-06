#include "Wire.h"
#include "stdint.h"

#ifndef MPU6050_H
#define MPU6050_H

#define MPU6050_ADDRESS 0x68

//-----------------register addresses----------------------

#define MPU6050_RA_SELFTESTX 0x0D
#define MPU6050_RA_SELFTESTY 0x0E
#define MPU6050_RA_SELFTESTZ 0x0F
#define MPU6050_RA_SELFTESTA 0x10

#define MPU6050_RA_SMPRTDIV 0x19
#define MPU6050_RA_CONFIG 0x1A
#define MPU6050_RA_GYROCONFIG 0x1B
#define MPU6050_RA_ACCELCONFIG 0x1C

#define MPU6050_RA_MOTTHR 0x1F
#define MPU6050_RA_FIFOEN 0x23
#define MPU6050_RA_MSTCTRL 0x24

#define MPU6050_RA_SLV0ADDR 0x25
#define MPU6050_RA_SLV0REG 0x26
#define MPU6050_RA_SLV0CTRL 0x27
#define MPU6050_RA_SLV1ADDR 0x28
#define MPU6050_RA_SLV1REG 0x29
#define MPU6050_RA_SLV1CTRL 0x2A
#define MPU6050_RA_SLV2ADDR 0x2B
#define MPU6050_RA_SLV2REG 0x2C
#define MPU6050_RA_SLV2CTRL 0x2D
#define MPU6050_RA_SLV3ADDR 0x2E
#define MPU6050_RA_SLV3REG 0x2F
#define MPU6050_RA_SLV3CTRL 0x30
#define MPU6050_RA_SLV4ADDR 0x31
#define MPU6050_RA_SLV4REG 0x32
#define MPU6050_RA_SLV4DO 0x33
#define MPU6050_RA_SLV4CTRL 0x34
#define MPU6050_RA_SLV4DI 0x35

#define MPU6050_RA_INTPINCFG 0x37
#define MPU6050_RA_INTENABLE 0x38

#define MPU6050_RA_ACCELXH 0x3B
#define MPU6050_RA_ACCELYH 0x3D
#define MPU6050_RA_ACCELZH 0x3F
#define MPU6050_RA_TEMPH 0x41
#define MPU6050_RA_GYROXH 0x43
#define MPU6050_RA_GYROYH 0x45
#define MPU6050_RA_GYROZH 0x47

#define MPU6050_RA_MSTDELAYCTRL 0x67
#define MPU6050_RA_SIGNALPATHRESET 0x68
#define MPU6050_RA_MOTDETECTCTRL 0x69
#define MPU6050_RA_USERCTRL 0x6A

#define MPU6050_RA_PWRMGMT1 0x6B
#define MPU6050_RA_PWRMGMT2 0x6C

#define MPU6050_RA_WHOAMI 0x75

//----------------------------------------

#define MPU6050_DD_WHOAMIREQ 1
#define MPU6050_DD_WHOAMIDATA 2

#define MPU6050_DD_ACCELXREQ 3
#define MPU6050_DD_ACCELXDATA 4
#define MPU6050_DD_ACCELYREQ 5
#define MPU6050_DD_ACCELYDATA 6
#define MPU6050_DD_ACCELZREQ 7
#define MPU6050_DD_ACCELZDATA 8
#define MPU6050_DD_GYROXREQ 9
#define MPU6050_DD_GYROXDATA 10
#define MPU6050_DD_GYROYREQ 11
#define MPU6050_DD_GYROYDATA 12
#define MPU6050_DD_GYROZREQ 13
#define MPU6050_DD_GYROZDATA 14

#define MPU6050_DD_SMPRTDIVDATAIN 15
#define MPU6050_DD_CONFIGDATAIN 16
#define MPU6050_DD_GYROCONFIGDATAIN 17
#define MPU6050_DD_ACCELCONFIGDATAIN 18

#define MPU6050_DD_MOTTHRDATAIN 20
#define MPU6050_DD_FIFOENDATAIN 21
#define MPU6050_DD_MSTCTRLDATAIN 22

#define MPU6050_DD_SLV0ADDRDATAIN 23
#define MPU6050_DD_SLV0REGDATAIN 24
#define MPU6050_DD_SLV0CTRLDATAIN 25
#define MPU6050_DD_SLV1ADDRDATAIN 26
#define MPU6050_DD_SLV1REGDATAIN 27
#define MPU6050_DD_SLV1CTRLDATAIN 28
#define MPU6050_DD_SLV2ADDRDATAIN 29
#define MPU6050_DD_SLV2REGDATAIN 30
#define MPU6050_DD_SLV2CTRLDATAIN 31
#define MPU6050_DD_SLV3ADDRDATAIN 32
#define MPU6050_DD_SLV3REGDATAIN 33
#define MPU6050_DD_SLV3CTRLDATAIN 34
#define MPU6050_DD_SLV4ADDRDATAIN 35
#define MPU6050_DD_SLV4REGDATAIN 36
#define MPU6050_DD_SLV4DODATAIN 37
#define MPU6050_DD_SLV4CTRLDATAIN 38
#define MPU6050_DD_SLV4DIDATAIN 39

#define MPU6050_DD_INTPINCFGDATAIN 40
#define MPU6050_DD_INTENABLEDATAIN 41

#define MPU6050_DD_MSTDELAYCTRLDATAIN 42
#define MPU6050_DD_SIGNALPATHRESETDATAIN 43
#define MPU6050_DD_MOTDETECTCTRLDATAIN 44
#define MPU6050_DD_USERCTRLDATAIN 45

#define MPU6050_DD_PWRMGMT1DATAIN 46
#define MPU6050_DD_PWRMGMT2DATAIN 47

#define MPU6050_DD_PWRMGMT1DATAREQ 48
#define MPU6050_DD_PWRMGMT1DATAOUT 49

//---------------------------------------

#define MPU6050_MSG_WHOAMI 36
#define MPU6050_MSG_GETNEXTINIT 37
#define MPU6050_MSG_PROCOPRES 38
#define MPU6050_MSG_GETNEXTREG 39
#define MPU6050_MSG_ACCELX 40
#define MPU6050_MSG_ACCELY 41
#define MPU6050_MSG_ACCELZ 42
#define MPU6050_MSG_PWR1 43
#define MPU6050_MSG_PWR1_BAD 44
#define MPU6050_MSG_PWR1_GOOD 45
#define MPU6050_MSG_INIT_COMP 46

#define MPU6050_ST_USE_GYRO_PRESET 0x00
#define MPU6050_ST_CALIBRATE_GYRO 0x01
#define MPU6050_ST_USE_ACCEL_PRESET 0x00
#define MPU6050_ST_CALIBRATE_ACCEL 0x02

#define MPU6050_ST_GRXCBTD 0x04 //gyro calibrated
#define MPU6050_ST_GRYCBTD 0x08
#define MPU6050_ST_GRZCBTD 0x10

#define MPU6050_ST_ACCXCBTD 0x20 //accel calibrated
#define MPU6050_ST_ACCYCBTD 0x40
#define MPU6050_ST_ACCZCBTD 0x80

#define MPU6050_CALIBRATION_CYCLES 500

#define MPU6050_LSB_PER_G 500

typedef enum coordinate_t {
	COORDINATE_X,
	COORDINATE_Y,
	COORDINATE_Z
}coordinate_t;

void MPU6050_Initialize(uint8_t startup_type);

uint8_t* MPU6050_GetNextInitOperation(uint16_t currentDataDescript, I2C_OpDescript_Type* opDescript);
uint8_t* MPU6050_GetNextRegOperation(uint16_t currentDataDescript, I2C_OpDescript_Type* opDescript);
void MPU6050_ProcessOperationResult(I2C_Operation_Type* operation);

int MPU6050_attach_accel_handler(void (*new_handler)(int16_t, int16_t, int16_t));
int MPU6050_attach_gyro_handler(void (*new_handler)(int16_t, int16_t, int16_t));

typedef struct MPU6050_Data_Type
{
	uint8_t state;
	uint8_t renew_state;
	uint8_t tmp;

	int16_t gyrox;
	int16_t gyroy;
	int16_t gyroz;

	int16_t gyrox_zero;
	int16_t gyroy_zero;
	int16_t gyroz_zero;

	int32_t gyrox_accum;
	int32_t gyroy_accum;
	int32_t gyroz_accum;

	uint16_t x_counter;
	uint16_t y_counter;
	uint16_t z_counter;

	int16_t accelx;
	int16_t accely;
	int16_t accelz;

	int16_t accelx_zero;
	int16_t accely_zero;
	int16_t accelz_zero;
	
	int32_t accelx_accum;
	int32_t accely_accum;
	int32_t accelz_accum;

	uint16_t accelx_counter;
	uint16_t accely_counter;
	uint16_t accelz_counter;

	void (**accel_handlers)(int16_t accelx, int16_t accely, int16_t accelz);
	uint8_t accel_handlers_num;

	void (**gyro_handlers)(int16_t accelx, int16_t accely, int16_t accelz);
	uint8_t gyro_handlers_num;
}MPU6050_Data_Type;

#endif
