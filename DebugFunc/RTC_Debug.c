#include <stdio.h>	
#include <string.h>
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
#include "stdlib.h"
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
uchar RTC_SetSysDateTime(SYSTEMTIME_STTypePara a);
extern uchar LANGUAGE;
SYSTEMTIME_STTypePara   vGetPara;
char *str1,str2[12];
static uchar Menu_Brush = 1;

uint CALLBACK thisAlarmClockCallBack(uint MSGAlarmClock)	//内核在闲时有可能激活此函数（例如在while循环中不断刷屏就不能激活此函数）
{
    if(MSGAlarmClock)
	{
		if(0 == LANGUAGE)
		{  
			SendToPC((uchar*)"起床了吃饭了！",3,10,DISP_POSITION|DISP_CLRSCR);
		}
		else if(1 == LANGUAGE)
		{
			SendToPC((uchar*)"Wake up!",3,10,DISP_POSITION|DISP_CLRSCR);
		}
        
		SYS_Beep(500);        
        return 1;
	}else return 0;	
}
uchar RTC_DateModify()
{
	char i = 0;
	uchar KeyValue;
	char RTC_DataBuff[12] = {"XXXX-XX-XX"};
	
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar*)"年月日校准", 1, 0 ,DISP_CENTER|DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar*)"Time proof", 1, 0 ,DISP_CENTER|DISP_CLRSCR);
	}
	
    SendToPC((uchar*)RTC_DataBuff, 3, 0 ,DISP_CENTER);
    
	while(1)
	{
		KeyValue = SYS_ReadKey(); 			
		if((KeyValue>='0')&&(KeyValue<='9'))
		{			
			if(i<10)
			{  
				RTC_DataBuff[i] =  KeyValue;
				i++;
				SYS_ClearKeyFIFO();
				if((i==4)||(i==7))
				{
					i++;
				}
				SendToPC((uchar*)RTC_DataBuff, 3, 0 ,DISP_CENTER);			
			}
		}
		if(KeyValue==KEY_CLEAR)
		{
			SYS_ClearKeyFIFO();
			i--;
			if((i==4)||(i==7))
			{
				i--;
			}
			if(i==0)
			{
				i = 0;
			}
			RTC_DataBuff[i]='X'; 
			SendToPC((uchar*)RTC_DataBuff, 3, 0 ,DISP_CENTER);
		} 					
		if(KeyValue == KEY_CANCEL)
		{
			return 1;
		}
		if(KeyValue==KEY_ENTER)
		{
			memcpy(str2,RTC_DataBuff,10);
			str1 = strtok(RTC_DataBuff,"-");
			vGetPara.usYear = atoi(str1);
			str1 = strtok(NULL,"-");
			vGetPara.usMonth = atoi(str1);
			str1 = strtok(NULL,"-");
			vGetPara.usDay = atoi(str1) ;
			memcpy(RTC_DataBuff,str2,10);  		
			return 0;
		}
	}
	
}
uchar RTC_TimeModify()
{
	char i=0;
	uchar KeyValue;		
	char RTC_timeBuff[10] = {"XX:XX:XX"};
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"时分秒校准", 1, 0 ,DISP_CENTER|DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"Time proof", 1, 0 ,DISP_CENTER|DISP_CLRSCR);
	}
	
	SendToPC((uchar*)RTC_timeBuff, 3, 0 ,DISP_CENTER);

	while(1)
	{
		KeyValue = SYS_ReadKey();
		if((KeyValue>='0')&&(KeyValue<='9'))
		{ 			
			if(i<8)
			{ 
				RTC_timeBuff[i] =  KeyValue;
				SYS_ClearKeyFIFO();
				i++;
				if((i==2)||(i==5))
				{
					i++;
				}
			}
			SendToPC((uchar*)RTC_timeBuff, 3, 0 ,DISP_CENTER);
		}
		if(KeyValue==KEY_CLEAR)
		{
			SYS_ClearKeyFIFO();
			i--;
			if((i==2)||(i==5))
			{
				i--;
			}
			if(i==0)
			{
				i = 0;
			}
			RTC_timeBuff[i]='X'; 
			SendToPC((uchar*)RTC_timeBuff, 3, 0 ,DISP_CENTER);
		}
		if(KeyValue == KEY_CANCEL)
		{
			return 1;
		}
			
		if(KeyValue==KEY_ENTER)
		{
			memcpy(str2,RTC_timeBuff,8);
			str1 = strtok(RTC_timeBuff,":");
			vGetPara.usHour = atoi(str1) ;
			str1 = strtok(NULL,":");
			vGetPara.usMinute = atoi(str1) ;
			str1 = strtok(NULL,":");
			vGetPara.usSecond = atoi(str1) ;
			memcpy(RTC_timeBuff,str2,8);
			return 0;
		}
	}
}


void RTC_Display(void)
{		
	uchar ucKeyValue;
    uchar aucDispDayChar[16] ={"2013-04-03-"};
	uchar aucDispWeekDayChar[16]={"weekX"};
    uchar aucDispTimeChar[16]={"18:00:00"};
    uint  i;
//    SYS_SetAlarmClockBack((ALARMCLOCK_CALLBACK) thisAlarmClockCallBack);
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"当前时间:", 1, 0 ,DISP_POSITION|DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"current time:", 1, 0 ,DISP_POSITION|DISP_CLRSCR);
	}
    
    while(1)
    {
         SYS_GetSysDateTime(&vGetPara);
		 sprintf((char*)aucDispDayChar," %4d-%2d-%2d ",vGetPara.usYear,
		 								            vGetPara.usMonth,
		 								            vGetPara.usDay);
		 SendToPC(aucDispDayChar,3,0,DISP_CENTER);
		 sprintf((char*)aucDispWeekDayChar," week%d ",vGetPara.usDayOfWeek );
		 SendToPC(aucDispWeekDayChar,5,0,DISP_CENTER);
		 sprintf((char*)aucDispTimeChar," %4d:%2d:%2d",vGetPara.usHour,
		 										     vGetPara.usMinute,
		 								             vGetPara.usSecond);
		 SendToPC(aucDispTimeChar,7,0,DISP_CENTER);
		 SYSTICK_DelayMs(200);
		 i++; 

        ucKeyValue = SYS_ReadKey();
        if(ucKeyValue == KEY_CANCEL)
        {
            break;
        }         
    } 
	Sleep(200);
    SYS_GetSysDateTime(&vGetPara);
	vGetPara.usMinute+=1;
    SYS_SetSysAlarmClock(vGetPara);
	
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"测试闹钟", 1, 0,DISP_CENTER|DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"Test alarm clock", 1, 0,DISP_CENTER|DISP_CLRSCR);
	}
    sprintf((char*)aucDispTimeChar,"%4d:%2d:%2d ",vGetPara.usHour,
		 							 			      vGetPara.usMinute,
		 								              vGetPara.usSecond);
	SendToPC(aucDispTimeChar,7,0,DISP_CENTER);
    while(1)
    {
        SYS_GetSysDateTime(&vGetPara);
		sprintf((char*)aucDispDayChar," %4d-%2d-%2d ",vGetPara.usYear,
		 								            vGetPara.usMonth,
		 								            vGetPara.usDay);
		SendToPC(aucDispDayChar,3,0,DISP_CENTER);
		sprintf((char*)aucDispTimeChar," %4d:%2d:%2d ",vGetPara.usHour,
		 										     vGetPara.usMinute,
		 								             vGetPara.usSecond);
		SendToPC(aucDispTimeChar,5,0,DISP_CENTER);
		if(SYS_ReadKey()==KEY_CANCEL) break; 
    }
}


void RTC_Debug()
{
	uchar ucKeyValue;
	SYS_CLS();
	while(1)
	{
		if(Menu_Brush == 1)
		{
			if(0 == LANGUAGE)
			{  
				SendToPC((uchar *)"1.时间校准", 1, 0,DISP_POSITION | DISP_CLRSCR);
				SendToPC((uchar *)"2.当前时钟", 3, 0,DISP_POSITION);
			}
			else if(1 == LANGUAGE)
			{
				SendToPC((uchar *)"1.Time calibration", 1, 0,DISP_POSITION | DISP_CLRSCR);
				SendToPC((uchar *)"2.current time", 3, 0,DISP_POSITION);
			}
			
			Menu_Brush = 0;
		}
		ucKeyValue = SYS_ReadKey();	
		switch(ucKeyValue)
		{
			case KEY_1:
				if((!RTC_DateModify())&&(!RTC_TimeModify()))
				{
					RTC_SetSysDateTime(vGetPara);
					if(0 == LANGUAGE)
					{  
						SendToPC((uchar *)"校准完毕", 1, 0,DISP_CENTER|DISP_CLRSCR);
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"finished", 1, 0,DISP_CENTER|DISP_CLRSCR);
					}
					
				}
				else
				{
					if(0 == LANGUAGE)
					{  
						SendToPC((uchar *)"取消校准", 1, 0,DISP_CENTER|DISP_CLRSCR);	
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"cancel", 1, 0,DISP_CENTER|DISP_CLRSCR);	
					}
					
				}
				Menu_Brush = 1;
				SYSTICK_DelayMs(1000);
				SYS_CLS();
				break;
		    case KEY_2:
			   	RTC_Display();
				SYS_CLS();
				Menu_Brush = 1;
				break;
		   case KEY_CANCEL:
			   Menu_Brush = 1;
				return;	
			default:break;
		}
	}
}



