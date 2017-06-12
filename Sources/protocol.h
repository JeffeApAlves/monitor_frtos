/*
 * protocol.h
 *
 *  Created on: 09/06/2017
 *      Author: Suporte
 */

#include "PE_Types.h"

#ifndef SOURCES_PROTOCOL_H_
#define SOURCES_PROTOCOL_H_

#define TIME_TX			5
#define TIME_RX			5

#define LEN_CMD			5
#define LEN_ADDRESS		1
#define LEN_VALUE		1
#define LEN_MIN_PAYLOAD	2
#define LEN_MAX_PAYLOAD	16

/* [LED01]\r\n*/
#define CHAR_CMD_START	'['
#define CHAR_CMD_END	']'
#define CHAR_CR			'\r'
#define CHAR_LF			'\n'
#define CHAR_SEPARATOR	':'
#define CHAR_NAK		0x15
#define CHAR_STR_END	'\0'

typedef enum {

	EXEC_UNSUCCESS	= -3,
	INVALID_CMD		= -2,
	INVALID_PARAM	= -1,
	EXEC_SUCCESS	= 0,

}ResultExec;

typedef enum {

	CMD_LED,
	CMD_ANALOG,
	CMD_PWM,
	CMD_TOUCH,
	CMD_ACC

}IdCmd;

typedef enum {

	CMD_INIT,
	CMD_INIT_OK,
	CMD_RX_START,
	CMD_RX_PAYLOAD,
	CMD_RX_END,
	CMD_RX_NL,
	CMD_RX_CR,
	CMD_DECODER,
	CMD_EXEC,
	CMD_ERROR,
	CMD_ACK,
	CMD_NAK,

} StatusRx;

typedef struct {

	char	data[LEN_MAX_PAYLOAD];
	unsigned char count;

} RxFrame;

typedef struct{

	char	name_cmd[LEN_CMD];
	int		address;
	int		value;
	char	data[LEN_MAX_PAYLOAD];

} ParamCmd;


/**
 * Ponteiro para as call backs
 */
typedef ResultExec(*pCallBack)(ParamCmd*);

/**
 *
 */
typedef struct{

	char 		name_cmd[LEN_CMD];
	IdCmd		id_cmd;
	pCallBack	cb;

} Cmd;

void rxStartCMD (void);
void rxPayLoad (void);
void rxNL(void);
void rxCR(void);
void decoderCMD(void);
pCallBack getCallBack(void);
void initRxCMD(void);
void sendNAK(void);
void sendACK(void);
void sendResult(void);
void execCallBack();
void setStatusRx(StatusRx sts);
bool getRxData(char* ch);
bool putTxData(char data);
void sendString(const char* str);
void clearRxFrame(void);
void errorRx(void);
bool decoderFrame(void);
void formatCMD(void);
bool decoderFrame2(void);

/*interface*/
void processProtocol(void);
void setEventCMD(IdCmd id_cmd,pCallBack c);
bool putRxData(char ch);
bool getTxData(char* ch);
bool hasTxData(void);
void startTX(void);

extern unsigned int timeTx,timeRx;

#endif /* SOURCES_PROTOCOL_H_ */
