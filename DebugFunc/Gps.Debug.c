#include <stdio.h>
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h"
#include "system.h"
#include "gps.h"

extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern uchar LANGUAGE;
void GPS_Debug(void)
{
	uchar ucKeyValue = KEY_NONE;
	uchar uctemp = 0xFF;
	double Latitude[1] = {0};
	double Longitude[1] = {0};
	float Direction[1] = {0};
	float Speed[1] = {0};
	float altitude[1] = {0};
	
	uchar Hemisphere[1] = {0};
	uchar  Time[13] = {0};
	char sprintfBUFF1[50] = {0};
	char sprintfBUFF2[50] = {0};
	char sprintfBUFF3[50] = {0};
	uchar SateNumber[1];
	uint uiTick;
	uiTick = SYS_GetTickCount();
//	GPS_Init();
//	Uart_ClearBuff_DMA(5);
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar*)"GPS测试", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"请等待连接卫星...", 3, 0 , DISP_POSITION | DISP_CLRLINE);
		SendToPC((uchar*)"按取消键退出测试", 5, 0 , DISP_POSITION | DISP_CLRLINE);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar*)"GPS TEST", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"Link satellite...", 3, 0 , DISP_POSITION | DISP_CLRLINE);
		SendToPC((uchar*)"cancel-to exit", 5, 0 , DISP_POSITION | DISP_CLRLINE);
	}	

//	
	Uart_SetGPSDebug(1); //开打印
	while(0) //GPS连接卫星，连接完毕才会有定位信息
	{
		ucKeyValue = SYS_ReadKey();
		switch(ucKeyValue)
        {
            case KEY_CANCEL: 
				Uart_SetGPSDebug(0); //关打印
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
		SYSTICK_DelayMs(50);	
		if(100 < (SYS_GetTickCount() - uiTick ))  //1s
		{
			uiTick = SYS_GetTickCount();
			memset(sprintfBUFF1, 0, 50);
			uctemp = GPS_QueryInit();
			sprintf(sprintfBUFF1,"GPS_QueryInit:%d", uctemp);
			SendToPC((uchar *)sprintfBUFF1, 1, 0 , DISP_POSITION | DISP_CLRSCR); 
			if(0 == uctemp) break;
		}
		
	}
	while(1)  //GPS定位信息
	{
		ucKeyValue = SYS_ReadKey();
		switch(ucKeyValue)
        {
			
            case KEY_CANCEL:
				Uart_SetGPSDebug(0); //关打印
				if(0 == LANGUAGE)
				{  
					SendToPC((uchar *)"退出测试", 5, 0 ,DISP_CLRSCR); 
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"Exit test", 5, 0 ,DISP_CLRSCR); 
				}				
                
                SYSTICK_DelayMs(1000);
                SYS_CLS();
                return;  
            default:				
				break;
        }
		SYSTICK_DelayMs(50);
		if(100 < (SYS_GetTickCount() - uiTick ))  //1s
		{
			uiTick = SYS_GetTickCount();
			
			GPS_QueryLaLO(Latitude, Longitude, Direction,Speed,altitude, Time, SateNumber,Hemisphere);
			Time[12] = 0;
			if(0 == LANGUAGE)
			{  
				sprintf(sprintfBUFF1,"经度:%08f", Longitude[0]);
				SendToPC((uchar *)sprintfBUFF1, 1, 0 , DISP_POSITION | DISP_CLRSCR); 
				memset(sprintfBUFF1, 0, 50);
				sprintf(sprintfBUFF2,"纬度:%08f", Latitude[0]);
				SendToPC((uchar *)sprintfBUFF2, 3, 0 , DISP_POSITION | DISP_CLRLINE);
				memset(sprintfBUFF1, 0, 50);
				sprintf(sprintfBUFF3,"时间:20%s", Time);
				SendToPC((uchar *)sprintfBUFF3, 5, 0 , DISP_POSITION | DISP_CLRLINE);
				memset(sprintfBUFF1, 0, 50);
			}
			else if(1 == LANGUAGE)
			{
				sprintf(sprintfBUFF1,"lon:%08f", Longitude[0]);
				SendToPC((uchar *)sprintfBUFF1, 1, 0 , DISP_POSITION | DISP_CLRSCR); 
				memset(sprintfBUFF1, 0, 50);
				sprintf(sprintfBUFF2,"Lat:%08f", Latitude[0]);
				SendToPC((uchar *)sprintfBUFF2, 3, 0 , DISP_POSITION | DISP_CLRLINE);
				memset(sprintfBUFF1, 0, 50);
				sprintf(sprintfBUFF3,"Time:20%s", Time);
				SendToPC((uchar *)sprintfBUFF3, 5, 0 , DISP_POSITION | DISP_CLRLINE);
				memset(sprintfBUFF1, 0, 50);
			}
			
		}
	}
}
