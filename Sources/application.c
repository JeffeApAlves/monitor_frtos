/*
 * application.c
 *
 *  Created on: 04/06/2017
 *      Author: Jefferson
 */

#include <stdio.h>
#include "LED_B.h"
#include "LED_G.h"
#include "LED_R.h"
#include "AD1.h"
#include "MMA1.h"
#include "application.h"

volatile	bool AD_finished=FALSE;
uint16_t	AD_Values[AD1_CHANNEL_COUNT];
uint8_t		xyz[3];

void initCallBacks(){

	setEventCMD(CMD_LED,	onLED);
	setEventCMD(CMD_ANALOG,	onAnalog);
	setEventCMD(CMD_ACC,	onAcel);
	setEventCMD(CMD_TOUCH,	onTouch);
	setEventCMD(CMD_PWM,	onPWM);
}
//-------------------------------------------------------------------------

ResultExec onLED(ParamCmd* cmd){

	switch(cmd->address){

		case LED_GREEN:			LED_G_Put(cmd->value);	break;
		case LED_RED:			LED_R_Put(cmd->value);	break;
		case LED_BLUE:			LED_B_Put(cmd->value);	break;
	}

	return EXEC_SUCCESS;
}
	//-------------------------------------------------------------------------

ResultExec onAnalog(ParamCmd* cmd){

	if(cmd->address>=AD1_CHANNEL_COUNT){

		return INVALID_PARAM;
	}

	sprintf(cmd->data,"%s%d:%d\0",cmd->name_cmd,cmd->address,AD_Values[cmd->address]);

	return EXEC_SUCCESS;
}
//-------------------------------------------------------------------------

ResultExec onAcel(ParamCmd* cmd){

	sprintf(cmd->data,"%s%d:%d:%d:%d\0",cmd->name_cmd,cmd->address,xyz[0],xyz[1],xyz[2]);

	return EXEC_SUCCESS;
}
//-------------------------------------------------------------------------

ResultExec onTouch(ParamCmd* cmd){

	return EXEC_SUCCESS;
}
//-------------------------------------------------------------------------

ResultExec onPWM(ParamCmd* cmd){

	return EXEC_SUCCESS;
}
//------------------------------------------------------------------------

void read_Channels_AD(){

//	if(AD_finished){
//		if(AD1_GetValue16(AD_Values)==ERR_OK){
			//TODO
//		}
//	}

	if(AD1_Measure(FALSE)==ERR_OK){

		AD_finished = FALSE;

		while (!AD_finished) {}

		if(AD1_GetValue16(AD_Values)==ERR_OK){
			//TODO
		}
	}
}
//------------------------------------------------------------------------

void read_accel() {

	MMA1_GetRaw8XYZ(xyz);
}
//------------------------------------------------------------------------

void initAccel(){

	MMA1_Init();

	MMA1_Enable();
}
//------------------------------------------------------------------------
