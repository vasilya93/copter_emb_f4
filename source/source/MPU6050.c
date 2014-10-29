#include "MPU6050.h"
#include "Wire.h"
#include "I2C.h"
#include "stdlib.h"
#include "Serial.h"
#include "Messenger.h"

#define MPU6050_ST_GRXCBTD 0x01 //gyro calibrated
#define MPU6050_ST_GRYCBTD 0x02
#define MPU6050_ST_GRZCBTD 0x04

MPU6050_Data_Type MPU6050_Data={
	0, 0, 0,
	0, 0, 0,
	0, 0, 0,
	0, 0, 0,
	0, 0, 0,
	0, 0, 0
};

Wire_Device_Type MPU6050;

void add_gyro_val(uint16_t value, coordinate_t coord);
void set_gyro_val(uint16_t value, coordinate_t coord);
void gyro_calibrate(uint16_t value, coordinate_t coord);

void MPU6050_Initialize(mpu6050_startup_t startup_type)
{
	MPU6050_Data.startup_type = startup_type;

  MPU6050.GetNextInitOperation = &MPU6050_GetNextInitOperation;
  MPU6050.GetNextRegOperation = &MPU6050_GetNextRegOperation;
  MPU6050.ProcessOperationResult = &MPU6050_ProcessOperationResult;
	
	Wire_AttachDevice(&MPU6050);
}

uint8_t* MPU6050_GetNextInitOperation(uint16_t currentDataDescript, I2C_OpDescript_Type* opDescript)
{
	uint8_t *data;

  switch(currentDataDescript) {
	/*case WIRE_DD_NODATA:
		I2C_SetOpDescription(opDescript, MPU6050_DD_PWRMGMT1DATAREQ, MPU6050_ADDRESS, false, 1);
		data = (uint8_t*) malloc(1);
		data[0] = MPU6050_RA_PWRMGMT1;
		return data;
	case MPU6050_DD_PWRMGMT1DATAREQ:
		I2C_SetOpDescription(opDescript, MPU6050_DD_PWRMGMT1DATAOUT, MPU6050_ADDRESS, true, 1);
		return NULL;
	case MPU6050_DD_PWRMGMT1DATAOUT:
		I2C_SetOpDescription(opDescript, MPU6050_DD_PWRMGMT1DATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_PWRMGMT1;
		data[1] = 0;
		return data;*/
	case WIRE_DD_NODATA:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SMPRTDIVDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SMPRTDIV;
		data[1] = 0x07;
		return data;
	case MPU6050_DD_SMPRTDIVDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_CONFIGDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_CONFIG;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_CONFIGDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_GYROCONFIGDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_GYROCONFIG;
		data[1] = 0x08; //500 deg/s
		return data;
	case MPU6050_DD_GYROCONFIGDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_ACCELCONFIGDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_ACCELCONFIG;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_ACCELCONFIGDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_MOTTHRDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_MOTTHR;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_MOTTHRDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_FIFOENDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_FIFOEN;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_FIFOENDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_MSTCTRLDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_MSTCTRL;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_MSTCTRLDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV0ADDRDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV0ADDR;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SLV0ADDRDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV0REGDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV0REG;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SLV0REGDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV0CTRLDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV0CTRL;
		data[1] = 0x00;
		return data;	
	case MPU6050_DD_SLV0CTRLDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV1ADDRDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV1ADDR;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SLV1ADDRDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV1REGDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV1REG;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SLV1REGDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV1CTRLDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV1CTRL;
		data[1] = 0x00;
		return data;	
	case MPU6050_DD_SLV1CTRLDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV2ADDRDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV2ADDR;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SLV2ADDRDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV2REGDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV2REG;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SLV2REGDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV2CTRLDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV2CTRL;
		data[1] = 0x00;
		return data;	
	case MPU6050_DD_SLV2CTRLDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV3ADDRDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV3ADDR;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SLV3ADDRDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV3REGDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV3REG;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SLV3REGDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV3CTRLDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV3CTRL;
		data[1] = 0x00;
		return data;	
	case MPU6050_DD_SLV3CTRLDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV4ADDRDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV4ADDR;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SLV4ADDRDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV4REGDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV4REG;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SLV4REGDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV4DODATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV4DO;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SLV4DODATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV4CTRLDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV4CTRL;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SLV4CTRLDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SLV4DIDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SLV4DI;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SLV4DIDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_INTPINCFGDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_INTPINCFG;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_INTPINCFGDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_INTENABLEDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_INTENABLE;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_INTENABLEDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_MSTDELAYCTRLDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_MSTDELAYCTRL;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_MSTDELAYCTRLDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_SIGNALPATHRESETDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_SIGNALPATHRESET;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_SIGNALPATHRESETDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_MOTDETECTCTRLDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_MOTDETECTCTRL;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_MOTDETECTCTRLDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_USERCTRLDATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_USERCTRL;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_USERCTRLDATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_PWRMGMT1DATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_PWRMGMT1;
		data[1] = 0x00;
		return data;
	case MPU6050_DD_PWRMGMT1DATAIN:
		I2C_SetOpDescription(opDescript, MPU6050_DD_PWRMGMT2DATAIN, MPU6050_ADDRESS, false, 2);
		data = (uint8_t*) malloc(2);
		data[0] = MPU6050_RA_PWRMGMT2;
		data[1] = 0x00;
		return data;
  default:
    Messenger_SendByte(MPU6050_MSG_INIT_COMP);
    I2C_SetOpDescription(opDescript, WIRE_DD_NODATA, 0, false, 0);
    return NULL;
  }
}

uint8_t* MPU6050_GetNextRegOperation(uint16_t currentDataDescript, I2C_OpDescript_Type* opDescript)
{
  uint8_t *data;
	
  switch(currentDataDescript) {
	/*case WIRE_DD_NODATA:
		I2C_SetOpDescription(opDescript, MPU6050_DD_WHOAMIREQ, MPU6050_ADDRESS, false, 1);
		data = (uint8_t*) malloc(1);
		data[0] = MPU6050_RA_WHOAMI;
		return data;
	case MPU6050_DD_WHOAMIREQ:
		I2C_SetOpDescription(opDescript, MPU6050_DD_WHOAMIDATA, MPU6050_ADDRESS, true, 1);
		return NULL;*/

	/*case WIRE_DD_NODATA:
		I2C_SetOpDescription(opDescript, MPU6050_DD_PWRMGMT1DATAREQ, MPU6050_ADDRESS, false, 1);
		data = (uint8_t*) malloc(1);
		data[0] = MPU6050_RA_PWRMGMT1;
		return data;
	case MPU6050_DD_PWRMGMT1DATAREQ:
		I2C_SetOpDescription(opDescript, MPU6050_DD_PWRMGMT1DATAOUT, MPU6050_ADDRESS, true, 1);
		return NULL;*/
	case WIRE_DD_NODATA:
		I2C_SetOpDescription(opDescript, MPU6050_DD_ACCELXREQ, MPU6050_ADDRESS, false, 1);
		data = (uint8_t*) malloc(1);
		data[0] = MPU6050_RA_ACCELXH;
		return data;
	case MPU6050_DD_ACCELXREQ:
		I2C_SetOpDescription(opDescript, MPU6050_DD_ACCELXDATA, MPU6050_ADDRESS, true, 2);
		return NULL;
	case MPU6050_DD_ACCELXDATA:
		I2C_SetOpDescription(opDescript, MPU6050_DD_ACCELYREQ, MPU6050_ADDRESS, false, 1);
		data = (uint8_t*) malloc(1);
		data[0] = MPU6050_RA_ACCELYH;
		return data;
	case MPU6050_DD_ACCELYREQ:
		I2C_SetOpDescription(opDescript, MPU6050_DD_ACCELYDATA, MPU6050_ADDRESS, true, 2);
		return NULL;
	case MPU6050_DD_ACCELYDATA:
		I2C_SetOpDescription(opDescript, MPU6050_DD_ACCELZREQ, MPU6050_ADDRESS, false, 1);
		data = (uint8_t*) malloc(1);
		data[0] = MPU6050_RA_ACCELZH;
		return data;
	case MPU6050_DD_ACCELZREQ:
		I2C_SetOpDescription(opDescript, MPU6050_DD_ACCELZDATA, MPU6050_ADDRESS, true, 2);
		return NULL;
	case MPU6050_DD_ACCELZDATA:
		I2C_SetOpDescription(opDescript, MPU6050_DD_GYROXREQ, MPU6050_ADDRESS, false, 1);
		data = (uint8_t*) malloc(1);
		data[0] = MPU6050_RA_GYROXH;
		return data;
	case MPU6050_DD_GYROXREQ:
		I2C_SetOpDescription(opDescript, MPU6050_DD_GYROXDATA, MPU6050_ADDRESS, true, 2);
		return NULL;
	case MPU6050_DD_GYROXDATA:
		I2C_SetOpDescription(opDescript, MPU6050_DD_GYROYREQ, MPU6050_ADDRESS, false, 1);
		data = (uint8_t*) malloc(1);
		data[0] = MPU6050_RA_GYROYH;
		return data;
	case MPU6050_DD_GYROYREQ:
		I2C_SetOpDescription(opDescript, MPU6050_DD_GYROYDATA, MPU6050_ADDRESS, true, 2);
		return NULL;
	case MPU6050_DD_GYROYDATA:
		I2C_SetOpDescription(opDescript, MPU6050_DD_GYROZREQ, MPU6050_ADDRESS, false, 1);
		data = (uint8_t*) malloc(1);
		data[0] = MPU6050_RA_GYROZH;
		return data;
	case MPU6050_DD_GYROZREQ:
		I2C_SetOpDescription(opDescript, MPU6050_DD_GYROZDATA, MPU6050_ADDRESS, true, 2);
		return NULL;
  default:
    I2C_SetOpDescription(opDescript, WIRE_DD_NODATA, 0, false, 0);
    return NULL;
  }
}

void MPU6050_ProcessOperationResult(I2C_Operation_Type* operation)
{
	//Messenger_SendByte(MPU6050_MSG_PROCOPRES);
  switch(operation->Description.DataDescript) {
	case MPU6050_DD_PWRMGMT1DATAOUT:
		MPU6050_Data.tmp = operation->Bytes[0];

		if (MPU6050_Data.tmp == 0x40)
			Messenger_SendByte(MPU6050_MSG_PWR1_BAD);
		else if (MPU6050_Data.tmp == 0x00)
			Messenger_SendByte(MPU6050_MSG_PWR1_GOOD);
		else
			Messenger_SendByte(MPU6050_MSG_PWR1);

		Messenger_SendWord((uint16_t)MPU6050_Data.tmp, MSNR_DD_PWRMGMT1);
		break;
	case MPU6050_DD_WHOAMIDATA:
		MPU6050_Data.tmp = operation->Bytes[0];
		Messenger_SendByte(MPU6050_MSG_WHOAMI);
		Messenger_SendWord((uint16_t)MPU6050_Data.tmp, MSNR_DD_WHOAMI);
		break;
	case MPU6050_DD_ACCELXDATA:
		MPU6050_Data.accelx = operation->Bytes[0] << 8;
		MPU6050_Data.accelx |= operation->Bytes[1];
		Messenger_SendWord(MPU6050_Data.accelx, MSNR_DD_ACCELX); 
		//Messenger_SendByte(MPU6050_MSG_ACCELX);
		break;
	case MPU6050_DD_ACCELYDATA:
		MPU6050_Data.accely = operation->Bytes[0] << 8;
		MPU6050_Data.accely |= operation->Bytes[1];
		Messenger_SendWord(MPU6050_Data.accely, MSNR_DD_ACCELY);
		//Messenger_SendByte(MPU6050_MSG_ACCELY);
		break;
	case MPU6050_DD_ACCELZDATA:
		MPU6050_Data.accelz = operation->Bytes[0] << 8;
		MPU6050_Data.accelz |= operation->Bytes[1];
		Messenger_SendWord(MPU6050_Data.accelz, MSNR_DD_ACCELZ);
		//Messenger_SendByte(MPU6050_MSG_ACCELZ);
		break;
	case MPU6050_DD_GYROXDATA:
		//MPU6050_Data.gyrox = operation->Bytes[0] << 8;
		//MPU6050_Data.gyrox |= operation->Bytes[1];
		add_gyro_val((operation->Bytes[0] << 8) | operation->Bytes[1], COORDINATE_X);
		//Messenger_SendByte(MPU6050_MSG_ACCELX);
		break;
	case MPU6050_DD_GYROYDATA:
		//MPU6050_Data.gyroy = operation->Bytes[0] << 8;
		//MPU6050_Data.gyroy |= operation->Bytes[1];
		add_gyro_val((operation->Bytes[0] << 8) | operation->Bytes[1], COORDINATE_Y);
		//Messenger_SendWord(MPU6050_Data.gyroy, MSNR_DD_ANGSPEEDY);
		//Messenger_SendByte(MPU6050_MSG_ACCELY);
		break;
	case MPU6050_DD_GYROZDATA:
		//MPU6050_Data.gyroz = operation->Bytes[0] << 8;
		//MPU6050_Data.gyroz |= operation->Bytes[1];
		add_gyro_val((operation->Bytes[0] << 8) | operation->Bytes[1], COORDINATE_Z);
		//Messenger_SendWord(MPU6050_Data.gyroz, MSNR_DD_ANGSPEEDZ);
		//Messenger_SendByte(MPU6050_MSG_ACCELZ);
		break;
  default:
    break;
  }
}

void add_gyro_val(uint16_t value, coordinate_t coord)
{
	uint8_t coord_is_calibrated;
	switch (coord) {
	case COORDINATE_X:
		coord_is_calibrated = MPU6050_ST_GRXCBTD;
		break;
	case COORDINATE_Y:
		coord_is_calibrated = MPU6050_ST_GRYCBTD;
		break;
	case COORDINATE_Z:
		coord_is_calibrated = MPU6050_ST_GRZCBTD;
		break;
	}

	if ((MPU6050_Data.state & coord_is_calibrated) ||
	    (MPU6050_Data.startup_type == MPU6050_STUP_USEPRESET)) {
		set_gyro_val(value, coord);
		return;
	}

	gyro_calibrate(value, coord);
}

void set_gyro_val(uint16_t value, coordinate_t coord)
{
	uint16_t *gyro;
	uint8_t data_descr;

	switch (coord) {
	case COORDINATE_X:
		gyro = &MPU6050_Data.gyrox;
		data_descr = MSNR_DD_ANGSPEEDX;
		break;
	case COORDINATE_Y:
		gyro = &MPU6050_Data.gyroy;
		data_descr = MSNR_DD_ANGSPEEDY;
		break;
	case COORDINATE_Z:
		gyro = &MPU6050_Data.gyroz;
		data_descr = MSNR_DD_ANGSPEEDZ;
		break;
	}

	*gyro = value;
	Messenger_SendWord(*gyro, data_descr);
}

void gyro_calibrate(uint16_t value, coordinate_t coord)
{
	uint16_t *gyro_zero;
	uint32_t *accum;
	uint16_t *counter;
	uint8_t data_descr;
	uint8_t coord_is_calibrated;

	switch (coord) {
	case COORDINATE_X:
		gyro_zero = &MPU6050_Data.gyrox_zero;
		accum = &MPU6050_Data.gyrox_accum;
		counter = &MPU6050_Data.x_counter;
		data_descr = MSNR_DD_GYROXOFF;
		coord_is_calibrated = MPU6050_ST_GRXCBTD;;
		break;
	case COORDINATE_Y:
		gyro_zero = &MPU6050_Data.gyroy_zero;
		accum = &MPU6050_Data.gyroy_accum;
		counter = &MPU6050_Data.y_counter;
		data_descr = MSNR_DD_GYROYOFF;
		coord_is_calibrated = MPU6050_ST_GRYCBTD;;
		break;
	case COORDINATE_Z:
		gyro_zero = &MPU6050_Data.gyroz_zero;
		accum = &MPU6050_Data.gyroz_accum;
		counter = &MPU6050_Data.z_counter;
		data_descr = MSNR_DD_GYROZOFF;
		coord_is_calibrated = MPU6050_ST_GRZCBTD;;
		break;
	}

	*accum += value;
	if (++(*counter) >= MPU6050_CALIBRATION_CYCLES) {
		MPU6050_Data.state |= coord_is_calibrated;
		*gyro_zero = *accum / *counter;
		Messenger_SendWord(*gyro_zero, data_descr);
	}
}
