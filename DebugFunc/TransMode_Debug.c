#include <stdio.h>	
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern uchar  Uart3_GetData_DMA(uint uiLen, uchar *acRecBuff1, uint time);
extern uchar LANGUAGE;

uchar  COM3_ReceiveData(uchar *pRecBuff , uint *uiRecLen , uint TimeOutMs)
{
	uint uiTick;
	uchar tmp;
	uint TmpLen = 0;
	uiTick = SYS_GetTickCount();
	
	while(SYS_GetTickCount() - uiTick < TimeOutMs)
	{	
		if(!Uart3_GetData_DMA(1,&tmp,10))
		{
			pRecBuff[TmpLen++] = tmp;
			while(!Uart3_GetData_DMA(1,&tmp,10))
			{
				pRecBuff[TmpLen++] = tmp;
			}
			*uiRecLen = TmpLen;
			return 0;
		}
	}
	
	return 2;
}

void COM_Debug()
{
	uint puiRecLen = 0;
	uchar acRecBuff[500]={0};
//	uchar acRecBuff1[500]={0};
	uint RecLen = 0;
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar*)"COM3接收、发送测试", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"请在COM3操作", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
		SendToPC((uchar*)"请发送10个字节...", 5, 0 ,DISP_POSITION | DISP_CLRLINE);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar*)"5PIN Uart TEST", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"5PIN Connection...", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
		SendToPC((uchar*)"Send 10 bytes...", 5, 0 ,DISP_POSITION | DISP_CLRLINE);
	}
	

	SYS_OpenPortExt(3, 1000, 115200, 2);

	
 	while(1)
	{
		COM3_ReceiveData(acRecBuff , &puiRecLen , 100);
		if(puiRecLen != 0)
		{
			RecLen += puiRecLen;			
			SYS_PortSend(3,(uchar*)acRecBuff, puiRecLen);
			puiRecLen = 0;
		}

		if(10 <= RecLen)
		{

			if(0 == LANGUAGE)
			{  
				SYS_PortSend(3,(uchar*)"\r\nCOM3畅通！\r\n", strlen("\r\nCOM3畅通！\r\n"));
				SYS_PortSend(3,(uchar*)"\r\n请回到COM1操作\r\n", strlen("\r\n请回到COM1操作\r\n"));
				SYS_PortSend(3,(uchar*)"\r\n通讯方式选择\r\n", strlen("\r\n通讯方式选择\r\n"));
				SYS_PortSend(3,(uchar*)"1.COM3通讯测试\r\n", strlen("1.COM3通讯测试\r\n"));
				SYS_PortSend(3,(uchar*)"2.\r\n", strlen("2.r\n"));
			}
			else if(1 == LANGUAGE)
			{
				SYS_PortSend(3,(uchar*)"\r\n5PIN is OK!\r\n", strlen("\r\n5PIN is OK!\r\n"));
				SYS_PortSend(3,(uchar*)"\r\n4PIN Connection\r\n", strlen("\r\n4PIN Connection\r\n"));
				SYS_PortSend(3,(uchar*)"\r\nSelect communication lines\r\n", strlen("\r\nSelect communication lines\r\n"));
				SYS_PortSend(3,(uchar*)"1.5PIN Uart TEST\r\n", strlen("1.5PIN Uart TEST\r\n"));
				SYS_PortSend(3,(uchar*)"2.\r\n", strlen("2.r\n"));
			}
			SYSTICK_DelayMs(1500);
			return;
		}
	} 	  
}

void TransMode_Debug()
{
	uchar ucKeyValue = KEY_NONE;
//	uchar Menu_Flag = 0;
	SYS_CLS();
	
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar*)"通讯方式选择", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"1.COM3通讯测试", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
		SendToPC((uchar*)"2.            ", 5, 0 ,DISP_POSITION | DISP_CLRLINE);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar*)"Select Uart", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"1.5PIN Uart TEST", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
		SendToPC((uchar*)"2.            ", 5, 0 ,DISP_POSITION | DISP_CLRLINE);
	}
	
	while(1)
	{			
		ucKeyValue =  SYS_ReadKey();
		switch(ucKeyValue)
		{
			case KEY_1:
				COM_Debug();
				if(0 == LANGUAGE)
				{  
					SendToPC((uchar*)"通讯方式选择", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
					SendToPC((uchar*)"1.COM3通讯测试", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
					SendToPC((uchar*)"2.            ", 5, 0 ,DISP_POSITION | DISP_CLRLINE);
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar*)"Select Uart", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
					SendToPC((uchar*)"1.5PIN Uart TEST", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
					SendToPC((uchar*)"2.            ", 5, 0 ,DISP_POSITION | DISP_CLRLINE);
				}
			break;

			case KEY_CANCEL:
				return;
			default:break;
		}
	}
}
