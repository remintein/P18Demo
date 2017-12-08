#include <stdio.h>	
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
#include "IrDA.h"
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern void Uart_SetSysDebug(uchar); 
extern uchar LANGUAGE;

uchar pucReadBuff[1500] = {0};
void IrDA_Debug(void)
{
	uint i = 0;
	uchar j = 0;
	uchar temp = 1;
	uchar pucSendBuff[256];
	uint ReadCount[1] = {0};

	Uart_SetSysDebug(1);     //??????
	for(i = 0; i <= 0xFF; i++)
	{		
		pucSendBuff[i] = j;
		j++;
	}
//	IrDA_Init();
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar*)"红外测试", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"请将红外模块对接", 3, 0 ,DISP_POSITION);	
		SendToPC((uchar*)"按1发送", 5, 0 ,DISP_POSITION);
		SendToPC((uchar*)"按2接收", 7, 0 ,DISP_POSITION);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar*)"IrDA", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"Aimed...", 3, 0 ,DISP_POSITION);	
		SendToPC((uchar*)"Enter 1 Send", 5, 0 ,DISP_POSITION);
		SendToPC((uchar*)"Enter 2 Read", 7, 0 ,DISP_POSITION);
	}
	
	
	/*??????*/
//	while(1)
//	{
		/*??????*/
//		IrDA_SendNBytes(256, pucSendBuff);
//		SYSTICK_DelayMs(3000);
		/*??????*/
//		temp = IrDA_ReadData(ReadCount, pucReadBuff, 500);		
//		if(0 == temp)
//		{
//			temp = 1;
//			Uart1_DumpData("IrDA_Read<-",pucReadBuff,256);
//			memset(pucReadBuff, 0 , 1500);
//		}
//	}

	while(1)
	{
		if(KEY_CANCEL == SYS_ReadKey())
		{
			return ;
		}
		if(KEY_1 == SYS_ReadKey())
		{
			/*红外发射*/
			IrDA_SendNBytes(256, pucSendBuff);
			if(0 == LANGUAGE)
			{  	
				SendToPC((uchar*)"发送成功", 1,0,DISP_CENTER|DISP_CLRSCR);
			}
			else if(1 == LANGUAGE)
			{
				SendToPC((uchar*)"Send OK", 1,0,DISP_CENTER|DISP_CLRSCR);
			}
			
			SendToPC((uchar*)pucSendBuff, 5, 0 ,DISP_POSITION | DISP_CLRLINE);
			
		}
		if(KEY_2 == SYS_ReadKey())
		{
			if(0 == LANGUAGE)
			{  	
				SendToPC((uchar*)"进入接收模式", 1,0,DISP_CENTER|DISP_CLRSCR);
			}
			else if(1 == LANGUAGE)
			{
				SendToPC((uchar*)"Admission mode", 1,0,DISP_CENTER|DISP_CLRSCR);
			}
	
			while(1)
			{
				if(KEY_CANCEL == SYS_ReadKey())
				{
					Uart_SetSysDebug(0);   //关闭系统打印
					break;
				}
				temp = IrDA_ReadData(ReadCount, pucReadBuff, 50);		
				if(0 == temp)
				{
					printf("\r\nReadCount:%d\r\n",ReadCount[0]);
					temp = 1;
					Uart1_DumpData("IrDA_Read<-",pucReadBuff,256);
					memset(pucReadBuff, 0 , 1500);
				}
				
			}
		}
	}
}
