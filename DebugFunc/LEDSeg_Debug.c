#include <stdio.h>					 
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
#include "led_seg.h"

extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern uchar LANGUAGE;
void  LEDSeg_Debug(void)
{

	uchar ucSegment;
//	uchar i = 0;
	uchar KeyValue;

	LEDSEG_Init();
    SYS_CLS();
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"   数码管测试   ", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"LEDSEG TEST", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
	}
    
    SYSTICK_DelayMs(1000);

	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"    数字显示    ", 3, 0 ,DISP_POSITION);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"LEDSEG Display", 3, 0 ,DISP_POSITION);
	}
    
	
	for(ucSegment = 1; ucSegment <= 4; ucSegment ++)
	{
		LEDSEG_Display(ucSegment, 8, 3);
		LEDSEG_ModeSelect(0);
		SYSTICK_DelayMs(300);
		KeyValue = SYS_ReadKey();
        if(KeyValue == KEY_CANCEL)
        {
            SYS_CLS();
			LEDSEG_ModeSelect(2);	//显示清除
			return;
		}  						
	}
	SYSTICK_DelayMs(1000);
	
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"     关显示     ", 3, 0 ,DISP_POSITION);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"Close display", 3, 0 ,DISP_POSITION);
	}
    
	LEDSEG_ModeSelect(1);	//关显示
	SYSTICK_DelayMs(1000);
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"     开显示     ", 3, 0 ,DISP_POSITION);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"Open display", 3, 0 ,DISP_POSITION);
	}	
	
	for(ucSegment = 1; ucSegment <= 4; ucSegment++)
	{
		LEDSEG_Display(ucSegment, 8, 3);
	}
	LEDSEG_ModeSelect(0);	//开显示 
	SYSTICK_DelayMs(1000);

	LEDSEG_ModeSelect(2);	//显示清除
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"    测试成功    ", 3, 0 ,DISP_POSITION);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"Test success", 3, 0 ,DISP_POSITION);
	}
    
    SYSTICK_DelayMs(1000);
	SYS_CLS();
}



