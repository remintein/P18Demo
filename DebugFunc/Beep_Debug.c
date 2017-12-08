#include <stdio.h>
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h"
#include "system.h"
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern uchar LANGUAGE;
/********************************************************************************************************
** 函数功能：蜂鸣器测试，蜂鸣1秒钟,无源蜂鸣器9*5，delay=145效果最佳
** 参    数：无						
** 返    回：无
*********************************************************************************************************/
void BEEP_Debug(void)
{
	SYS_CLS();
	if(0 == LANGUAGE)
	{  
		SendToPC("蜂鸣器测试", 1, 0 ,DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC("BEEP     TEST ", 1, 0 ,DISP_CENTER);
	}
	SYS_Beep(1000); 
	if(0 == LANGUAGE)
	{	
	SendToPC("测试完毕", 1, 0 ,DISP_CENTER|DISP_CLRLINE);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC("test is over", 1, 0 ,DISP_CENTER|DISP_CLRLINE);
	}
	SYSTICK_DelayMs(1000);
}
