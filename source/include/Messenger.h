#include "Serial.h"

#ifndef MESSENGER_H
#define MESSENGER_H

#define MSNR_MT_BYTE 0x01
#define MSNR_MT_WORD 0x02
#define MSNR_MT_DWRD 0x03

#define MSNR_DD_MASK 0xFC
#define MSNR_DD_NONE 0x04
#define MSNR_DD_ACCELX 0x08
#define MSNR_DD_ACCELY 0x0C
#define MSNR_DD_ACCELZ 0x10
#define MSNR_DD_WHOAMI 0x14
#define MSNR_DD_PWRMGMT1 0x18
#define MSNR_DD_ANGSPEEDX 0x1C
#define MSNR_DD_ANGSPEEDY 0x20
#define MSNR_DD_ANGSPEEDZ 0x24
#define MSNR_DD_GYROXOFF 0x28
#define MSNR_DD_GYROYOFF 0x2C
#define MSNR_DD_GYROZOFF 0x30

#define MSNR_PATTERNSIZE 5

#define MSNR_STARTOP_PATTERN "start"

typedef enum msnr_mode{
	MSNR_MODE_5BYTE = 1,
	MSNR_MODE_1BYTE
}msnr_mode;

void Messenger_Initialize(void (*start_operation)(void), msnr_mode mode);

void Messenger_SendByte(uint8_t);

void Messenger_SendWord(uint16_t word, uint8_t data_descr);

void Messenger_SendDWord(uint32_t dword, uint8_t data_descr);

#endif
