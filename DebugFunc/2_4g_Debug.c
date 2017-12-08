#include <stdlib.h>	
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
#include "com.h"
#include "_24g_.h"
extern uchar LANGUAGE;
void Uart_SetSysDebug(uchar);
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
//extern uchar  Uart6_GetData_DMA(uint* uiLen, uchar *acRecBuff1, uint time);

//uchar CMD_Poll[32]  ={"\x02\x00\x04\xa2\x31\xff\xff\x93\x03"};
//uchar CMD_Inqure[32]={"\x02\x00\x02\xE0\x02\xE2\x03"};
//uchar CMD_Cut[32]   ={"\x02\x00\x04\xa2\x32\x00\x00\x90\x03"};
uchar CMD_Poll[32]  ={0x02,0x00,0x04,0xa2,0x31,0x00,0x00,0x93,0x03};
uchar CMD_Inqure[32]={0x02,0x00,0x02,0xE0,0x02,0xE2,0x03};
uchar CMD_Cut[32]   ={0x02,0x00,0x04,0xa2,0x32,0x00,0x00,0x90,0x03};
void _2_4G_Debug(void)
{
	uint uiTick;
	uchar ucKeyValue = 0;
	ushort Pattern[1] = {0};
	uint length[1] = {0}; 
	uchar Data[100] = {0};
	uchar temp = 1;
	
	Uart_SetSysDebug(1);     //系统打印开启
	_24G_Set_Debug(0); //开打印
	_24g_Init();  //初始化模块
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"开始测试...", 3, 0 ,DISP_CLRSCR | DISP_CENTER); 
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"Start test...", 3, 0 ,DISP_CLRSCR | DISP_CENTER); 
	}
	
	
	while(1)
	{
		ucKeyValue = SYS_ReadKey();
		switch(ucKeyValue)
        {
            case KEY_CANCEL:  
                if(0 == LANGUAGE)
				{  
					SendToPC((uchar *)"退出测试", 5, 0 ,DISP_CLRSCR); 
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"Exit test", 5, 0 ,DISP_CENTER); 
				}
                SYSTICK_DelayMs(1000);
                SYS_CLS();
                return;  
            default:				
				break;
        }
		
//		printf("\r\n发送CMD_Cut\r\n");//发送命令总长度为9，要求函数将CMD推送出去9字节。
		_24G_SendCommand(9, 0, CMD_Cut);
		Pattern[0] = 0;
		_24G_ReadResponse(20, Pattern, length, Data);
		
//		printf("\r\n发送CMD_Poll\r\n");//发送命令总长度为9，要求函数将CMD推送出去9字节。
		_24G_SendCommand(9, 0, CMD_Poll);
		Pattern[0] = 0;  //不解析模式
		temp = _24G_ReadResponse(20, Pattern, length, Data);
//		printf("\r\nData[3]:%04d,Data[4]:%04d\r\n",Data[3],Data[4]);
		if(0 == temp)
		{			
			
			if((0 == ((Data[3] << 8) | Data[4] )) && ( 6 < length[0]) )
			{
				if(0 == LANGUAGE)
				{  
					SendToPC((uchar *)"有卡！", 5, 0 ,DISP_CLRLINE | DISP_CENTER);
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"A card！", 5, 0 ,DISP_CLRLINE | DISP_CENTER); 
				}
				 
				uiTick = SYS_GetTickCount();
				while(100*10 > (SYS_GetTickCount() - uiTick))  //10s
				{
					ucKeyValue = SYS_ReadKey();
					switch(ucKeyValue)
					{
						case KEY_CANCEL:  
							if(0 == LANGUAGE)
							{  
								SendToPC((uchar *)"退出测试", 5, 0 ,DISP_CLRSCR); 
							}
							else if(1 == LANGUAGE)
							{
								SendToPC((uchar *)"Exit test", 5, 0 ,DISP_CENTER); 
							}
							SYSTICK_DelayMs(1000);
							SYS_CLS();
							return;  
						default:				
							break;
					}
	//				printf("\r\n发送CMD_Inqure\r\n");//发送命令总长度为7，要求函数将CMD推送出去7字节。
					_24G_SendCommand(7, 0, CMD_Inqure);
					Pattern[0] = 0xE002;
					temp = _24G_ReadResponse(40, Pattern, length, Data);
//					printf("\r\nPattern[0]:%04d, length[0]:%04d,temp:%d\r\n",Pattern[0], length[0],temp);
//					printf("\r\nData[3]:%04d,Data[4]:%04d\r\n",Data[3],Data[4]);
					if(0 == temp)
					{
						if((0 == Pattern[0] ) && ( 0 != Data[5]) )
						{
							if(0 == LANGUAGE)
							{  
								SendToPC((uchar *)"有卡！", 5, 0 ,DISP_CLRLINE | DISP_CENTER);
							}
							else if(1 == LANGUAGE)
							{
								SendToPC((uchar *)"A card！", 5, 0 ,DISP_CLRLINE | DISP_CENTER); 
							}
						}
						else
						{
							if(0 == LANGUAGE)
							{  
								SendToPC((uchar *)"无卡！", 5, 0 ,DISP_CLRLINE | DISP_CENTER);
							}
							else if(1 == LANGUAGE)
							{
								SendToPC((uchar *)"No card!", 5, 0 ,DISP_CLRLINE | DISP_CENTER); 
							}
						break;
						}
					}
				}
			}
			else
			{
				if(0 == LANGUAGE)
				{  
					SendToPC((uchar *)"无卡！", 5, 0 ,DISP_CLRLINE | DISP_CENTER);
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"No card!", 5, 0 ,DISP_CLRLINE | DISP_CENTER); 
				}
			}

		}
	}
}

