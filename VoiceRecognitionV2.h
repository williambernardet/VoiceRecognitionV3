/**
  ******************************************************************************
  * @file    VoiceRecognitionV2.h
  * @author  Elechouse Team
  * @version V1.0
  * @date    2013-6-6
  * @brief   This file provides all the VoiceRecognitionV2 firmware functions.
  ******************************************************************************
    @note
         This driver is for elechouse Voice Recognition V2 Module(LINKS here)
  ******************************************************************************
  * @section  HISTORY
  
    V1.0    Initial version.
  
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, ELECHOUSE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 ELECHOUSE</center></h2>
  ******************************************************************************
  */
  
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "wiring_private.h"

#include "SoftwareSerial.h"
#include <avr/pgmspace.h>

#define DEBUG

#ifdef DEBUG
#define DBGSTR(message)     Serial.print(message)
#define DBGBUF(buf, len)	Serial.write(buf, len)
#define DBGLN(message)		Serial.println(message)
#define DBGFMT(msg, fmt)	Serial.print(msg, fmt)
#define DBGCHAR(c)			Serial.write(c)
#else
#define DBG(message)
#endif // DEBUG

#define VR_DEFAULT_TIMEOUT						(1000)

/***************************************************************************/
#define FRAME_HEAD							(0xAA)
#define FRAME_END							(0x0A)

/***************************************************************************/
#define FRAME_CMD_SYS_STATUS				(0x00)
#define FRAME_CMD_CHECK_TRAIN				(0x01)
#define FRAME_CMD_CHECK_SIG					(0x14)
#define FRAME_CMD_CHECK_BSR					(0x16)

#define FRAME_CMD_SET_BR					(0x03)	//baud rate
#define FRAME_CMD_SET_IOM					(0x04)	//IO mode
#define FRAME_CMD_SET_PW					(0x05)	//pulse width					
#define FRAME_CMD_SET_AL					(0x07)	// Auto load
#define FRAME_CMD_RESET						(0x06)	//reset configuration

#define FRAME_CMD_TRAIN						(0x02)
#define FRAME_CMD_SIG_TRAIN					(0x13)
#define FRAME_CMD_SET_SIG					(0x0E)
#define FRAME_CMD_DELETE					(0x0B)

#define FRAME_CMD_START						(0x0F)
#define FRAME_CMD_LOAD						(0x10)	//Load N records
#define FRAME_CMD_CLEAR						(0x12)	//Clear BSR buffer
#define FRAME_CMD_LSGRP						(0x08)	//Load system group
#define FRAME_CMD_LUGRP						(0x09)	//Load user defined group						
#define FRAME_CMD_GROUP						(0x15)  //
	#define FRAME_CMD_GROUP_SET							(0x00)  //
	#define FRAME_CMD_GROUP_SUGRP						(0x01)  //
	#define FRAME_CMD_GROUP_LSGRP						(0x02)  //
	#define FRAME_CMD_GROUP_LUGRP						(0x03)  //
	#define FRAME_CMD_GROUP_CUGRP						(0x04)  //

#define FRAME_CMD_TEST						(0x0C)
	#define FRAME_CMD_TEST_READ							(0x01)	
	#define FRAME_CMD_TEST_WRITE						(0x00)	

#define FRAME_CMD_VR						(0x0D)	//Voice recognized

#define FRAME_CMD_PROMPT					(0x0A)
#define FRAME_CMD_ERROR						(0x11)

/***************************************************************************/
#define FRAME_ERR_UDCMD						(0x00)
#define FRAME_ERR_LEN						(0x01)
#define FRAME_ERR_DATA						(0x02)
#define FRAME_ERR_SUBCMD					(0x03)

//#define FRAME_ERR_
#define FRAME_STA_SUCCESS					(0x00)
#define FRAME_STA_FAILED					(0xFF)
/***************************************************************************/


class VR : public SoftwareSerial{
public:
	VR(uint8_t receivePin, uint8_t transmitPin);
	
	static VR* getInstance() {
	   return instance;
	}
	
	int recognize(uint8_t *buf, int timeout = VR_DEFAULT_TIMEOUT);
	
	int train(uint8_t *records, uint8_t len=1);
	int load(uint8_t *records, uint8_t len=1);
	int clear();
	
	int addSignature(uint8_t record, uint8_t *buf, uint8_t len);
	int addSignature(uint8_t record, char *buf);
	
	int checkRecognizer(uint8_t *buf);
	int checkRecord(uint8_t *buf, uint8_t *records = 0, uint8_t len = 0);
	
	int test(uint8_t cmd, uint8_t *bsr);
	
	int writehex(uint8_t *buf, uint8_t len);
	
/***************************************************************************/
	/** low level */
	int len(PROGMEM uint8_t *buf);
	int cmp(uint8_t *buf, PROGMEM uint8_t *bufcmp, int len  );
	void cpy(char *buf,  PROGMEM char * pbuf);
	void sort(uint8_t *buf, int len);
	int cleanDup(uint8_t *des, uint8_t *buf, int len);
	void send_pkt(uint8_t cmd, uint8_t *buf, uint8_t len);
	void send_pkt(uint8_t cmd, uint8_t subcmd, uint8_t *buf, uint8_t len);
	int receive(uint8_t *buf, int len, int timeout = VR_DEFAULT_TIMEOUT);
	int receive_pkt(uint8_t *buf, int timeout = VR_DEFAULT_TIMEOUT);
/***************************************************************************/
private:
	static VR*  instance;
};

