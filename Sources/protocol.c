#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "RingBuffer.h"
#include "utils.h"
#include "protocol.h"

unsigned int timeTx = TIME_TX;
unsigned int timeRx = TIME_RX;

StatusRx	statusRx = CMD_INIT;
RingBuffer	bufferRx,bufferTx;
RxFrame		rxFrame;
ParamCmd	param_cmd;

Cmd			ListCmd[]	= {	{.id_cmd=CMD_LED,	.name_cmd = "LED\0",	.cb=NULL},
							{.id_cmd=CMD_ANALOG,.name_cmd = "AN\0",		.cb=NULL},
							{.id_cmd=CMD_PWM,	.name_cmd = "PWM\0",	.cb=NULL},
							{.id_cmd=CMD_ACC,	.name_cmd = "ACC\0",	.cb=NULL},
							{.id_cmd=CMD_TOUCH,	.name_cmd = "TOU\0",	.cb=NULL},
							};

const unsigned char SIZE_LIST_CMD = sizeof(ListCmd)/sizeof(Cmd);

void processProtocol(void) {

	switch(statusRx){

		default:
		case CMD_INIT:			initRxCMD();			break;
		case CMD_INIT_OK:		rxStartCMD();			break;
		case CMD_RX_START:		rxPayLoad();			break;
		case CMD_RX_PAYLOAD:	rxPayLoad();			break;
		case CMD_RX_END:		rxCR();					break;
		case CMD_RX_CR:			rxNL();					break;
		case CMD_RX_NL:			decoderCMD();			break;
		case CMD_DECODER:		execCallBack();			break;

		case CMD_ERROR:			errorRx();				break;
		case CMD_ACK:			sendACK();				break;
		case CMD_NAK:			sendNAK();				break;
		case CMD_EXEC:			sendResult();			break;
	}

	startTX();
}
//------------------------------------------------------------------------

void rxStartCMD (void) {

	char ch;

	if(getRxData(&ch)){

		if(ch==CHAR_CMD_START){

			clearRxFrame();

			setStatusRx(CMD_RX_START);
		}
	}
}
//------------------------------------------------------------------------

void rxPayLoad (void) {

	char ch;

	if(getRxData(&ch)){

		if(ch==CHAR_CMD_START || rxFrame.count>=LEN_MAX_PAYLOAD){

			setStatusRx(CMD_ERROR);

		}else if(ch==CHAR_CMD_END){

			if(rxFrame.count>=LEN_MIN_PAYLOAD){

				setStatusRx(CMD_RX_END);

			}else{

				setStatusRx(CMD_ERROR);
			}

		}else {

			setStatusRx(CMD_RX_PAYLOAD);

			rxFrame.data[(rxFrame.count++)%LEN_MAX_PAYLOAD] = ch;
		}
	}
}
//------------------------------------------------------------------------

void rxNL(void) {

	char ch;

	if(getRxData(&ch)){

		if(ch==CHAR_LF){

			setStatusRx(CMD_RX_NL);

		}else {

			setStatusRx(CMD_ERROR);
		}
	}
}
//------------------------------------------------------------------------

void rxCR(void) {

	char ch;

	if(getRxData(&ch)){

		if(ch==CHAR_CR){

			setStatusRx(CMD_RX_CR);

		}else{

			setStatusRx(CMD_ERROR);
		}
	}
}
//------------------------------------------------------------------------

void decoderCMD(void) {

	formatCMD();

	if(decoderFrame2()){

		setStatusRx(CMD_DECODER);

	}else{

		setStatusRx(CMD_ERROR);
	}
}
//------------------------------------------------------------------------

void formatCMD(void) {

	char delim[] = {CHAR_SEPARATOR,0};

	if(strstr(rxFrame.data,delim)==NULL){

		char size_cmd = 0;

		while(size_cmd < rxFrame.count && (rxFrame.data[size_cmd] < '0' || rxFrame.data[size_cmd] > '9')){

			size_cmd++;
		};

		if(rxFrame.count >= (size_cmd+1)){

			str_append(rxFrame.data,delim, size_cmd);

			if((size_cmd+LEN_ADDRESS+1)<strlen(rxFrame.data)){

				str_append(rxFrame.data,delim, size_cmd+LEN_ADDRESS+1);
			}
		}
	}
}
//------------------------------------------------------------------------

bool decoderFrame2(void) {

	List	list;

	str_split(&list,rxFrame.data,CHAR_SEPARATOR);

	if(list.itens!=NULL){

		for(char i=0;i < list.size;i++){

			if(list.itens[i]!=NULL){

				switch(i){

					case 0:	strcpy(param_cmd.name_cmd, list.itens[0]);	break;
					case 1:	param_cmd.address	= atoi(list.itens[1]);	break;
					case 2:	param_cmd.value		= atoi(list.itens[2]);	break;
				}

				_free(list.itens[i]);
			}
		}

		_free(list.itens);
	}

	return list.size>=2;
}
//------------------------------------------------------------------------

void setEventCMD(IdCmd id_cmd,pCallBack c) {

	for(char i=0;i<SIZE_LIST_CMD;i++){

		if(ListCmd[i].id_cmd==id_cmd){

			ListCmd[i].cb = c;
			break;
		}
	}
}
//------------------------------------------------------------------------

pCallBack getCallBack(void) {

	pCallBack cb = NULL;

	for(char i=0;i < SIZE_LIST_CMD;i++){

		if(strcmp(ListCmd[i].name_cmd,param_cmd.name_cmd)==0){

			cb = ListCmd[i].cb;
			break;
		}
	}

	return cb;
}
//------------------------------------------------------------------------

void execCallBack(void) {

	pCallBack cb = getCallBack();

	if(cb!=NULL && cb(&param_cmd)==EXEC_SUCCESS){

		if(*param_cmd.data!=CHAR_STR_END){

			setStatusRx(CMD_EXEC);

		}else {

			setStatusRx(CMD_ACK);
		}

	}else{

		setStatusRx(CMD_NAK);
	}
}
//------------------------------------------------------------------------

void initRxCMD(void) {

	clearRxFrame();

	initBuffer(&bufferRx);

	initBuffer(&bufferTx);

	setStatusRx(CMD_INIT_OK);
}
//------------------------------------------------------------------------

void sendACK(void) {

	sprintf(param_cmd.data,"[%s%d%d]\0",param_cmd.name_cmd,param_cmd.address,param_cmd.value);

	sendString(param_cmd.data);

	setStatusRx(CMD_INIT_OK);
}
//------------------------------------------------------------------------

void sendNAK(void) {

	sprintf(param_cmd.data,"[%s%d%d]%s\0",param_cmd.name_cmd,param_cmd.address,param_cmd.value,CHAR_NAK);

	sendString(param_cmd.data);

	setStatusRx(CMD_INIT_OK);
}
//------------------------------------------------------------------------

void sendResult(void){

	sendString(param_cmd.data);

	setStatusRx(CMD_INIT_OK);
}
//------------------------------------------------------------------------

void sendString(const char* str){

	char* p = str;

	if(p!=NULL){

		while(*p!=CHAR_STR_END){

			putTxData(*p++);
		}

		putTxData(CHAR_CR);
		putTxData(CHAR_LF);
	}
}
//------------------------------------------------------------------------

inline void setStatusRx(StatusRx sts) {

	statusRx = sts;
}
//------------------------------------------------------------------------

inline bool putTxData(char data) {

	return putData(&bufferTx,data);
}
//------------------------------------------------------------------------

inline bool putRxData(char data) {

	return putData(&bufferRx,data);
}
//------------------------------------------------------------------------

inline bool getTxData(char* ch){

	return getData(&bufferTx,ch);
}
//------------------------------------------------------------------------

inline bool getRxData(char* ch){

	return getData(&bufferRx,ch);
}
//------------------------------------------------------------------------

void errorRx(void){

	/**/

	setStatusRx(CMD_INIT_OK);
}
//------------------------------------------------------------------------

void clearRxFrame(void){

	param_cmd.address	= 0;
	param_cmd.value		= 0;
	rxFrame.count		= 0;

	for(char i=0;i<LEN_MAX_PAYLOAD;i++){

		rxFrame.data[i]		= CHAR_STR_END;
		param_cmd.data[i]	= CHAR_STR_END;
	}
}
//------------------------------------------------------------------------

bool hasTxData(void){

	return hasData(&bufferTx);
}
//------------------------------------------------------------------------

/**
 * Verifica se o buffer de TX esta vazio. Se sim, chama a call back
 * da transmissao de caracter para iniciar a transmissao do buffer
 *
 */
void startTX(void){

	if(hasTxData() && AS1_GetCharsInTxBuf()==0){

		AS1_OnTxChar();
	}
}
//------------------------------------------------------------------------
