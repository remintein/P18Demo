#include <stdlib.h>	
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
#include "com.h"

#define INTERRUPT_MODE
uchar  COM3_ReceiveData(uchar *pRecBuff , uint *uiRecLen , uint TimeOutMs)
{
	uint uiTick;
	uiTick = SYS_GetTickCount();
	
#ifdef INTERRUPT_MODE
	
	//Ctrl_GPIO_CLR_LOW;
	while(SYS_GetTickCount() - uiTick < TimeOutMs)
	{
		if(!COM3_ReceiveByte())
		{
			while(!COM3_ReceiveByte());
			COM3_ReadData(uiRecLen, pRecBuff);
			COM3_ClearStore();
			return 0;
		}		
	}
	return 2;
#endif
#ifdef INQUIRE_MODE
	while(SYS_GetTickCount() - uiTick < TimeOutMs)
	{
		if(!COM3_ReceiveByte())
		{
			uiTick = SYS_GetTickCount();
		}
	}
	
#endif	
	
}
void Device_StandBy()
{
	SYS_LcdBackLight(OFF);
}	
void Device_WakeUp()
{
	SYS_LcdBackLight(ON);
	g_stCom3Para.uiMode = COM_MODE_INQUIRE;
	g_stCom3Para.uiBaut = 115200;
	g_stCom3Para.uiRecTime = 1;
	COM3_Init();
}
void COM_Debug()
{
	uchar KeyValue;
	uint RecLen,i;
	uchar ucRecBuff[1024] = {0};
	SendToPC("485测试", 1, 0 ,DISP_CENTER|DISP_CLRSCR);
/*	uchar info[200]={0};
	uchar DataLen;
	uchar Display1[30]={"欢迎使用打印机"};
	uchar Display2[30]={"abcdefghijklmnop"};
	uchar Display3[30]={":',./<>?\"`~!@#$"};
	uchar Display4[30]={"ABCDEFGHIJKLMNOP"};	
	i=0;
	SendToPC("打印机测试", 1, 0 ,DISP_CENTER|DISP_CLRSCR);
	SendToPC("打印中...", 3, 0 ,DISP_CENTER);
	g_stCom3Para.uiMode = COM_MODE_INQUIRE;
	g_stCom3Para.uiBaut = 9600;

	COM3_Init();
	
	
	ucRecBuff[0]=0x1b;
	ucRecBuff[1]=0x40;
	DataLen= strlen(Display1);
	ucRecBuff[DataLen+2]=0x0a;
	memcpy(&ucRecBuff[2],Display1,DataLen);
	COM3_SendNBytes(strlen(ucRecBuff),ucRecBuff);
	
	DataLen= strlen(Display2);
	ucRecBuff[DataLen+2]=0x0a;
	memcpy(&ucRecBuff[2],Display2,DataLen);
	COM3_SendNBytes(strlen(ucRecBuff),ucRecBuff);

	DataLen= strlen(Display3);
	ucRecBuff[DataLen+2]=0x0a;
	memcpy(&ucRecBuff[2],Display3,DataLen);
	COM3_SendNBytes(strlen(ucRecBuff),ucRecBuff);	

	SYSTICK_DelayMs(1000);*/
	g_stCom3Para.uiMode = COM_MODE_INQUIRE;
	g_stCom3Para.uiBaut = 115200;
	g_stCom3Para.uiRecTime = 10;

	COM3_Init();
//	Sys_EnterIdle(3);
//	Sys_ExitIdle();
	
 	while(1)
	{
		COM3_SendNBytes(5 , "hello");
		if(!COM3_ReceiveData(ucRecBuff,&RecLen,10))
		{
			COM1_SendNBytes(RecLen , ucRecBuff);
			COM3_SendNBytes(RecLen , ucRecBuff);
		}
		if(KEY_CANCEL == SYS_ReadKey())
		{
			SendToPC("退出测试", 3, 0 ,DISP_CENTER|DISP_CLRSCR);
			return;
		}
	} 	  
}
	
