#include <stdio.h>
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h"
#include "system.h"
#include "lcd.h"

extern uchar LCD_LoopDisplay(uchar *pucBuff, uchar y, uint number, uchar velocity, uchar Steps);
extern uchar LANGUAGE;


void LCD_Debug(void)
{
//	uint i = 0;

//   	SYS_LcdBackLight(OFF);
//	SYSTICK_DelayMs(1000);
//	SYS_LcdBackLight(ON);
	if(0 == LANGUAGE)
	{  
		SYS_DisplayCE((uchar*)"左对齐",1,0,DISP_POSITION | DISP_CLRLINE | DISP_REVERSE);	  //左对齐|清除当前行														  
		SYS_DisplayCE((uchar*)"右对齐",3,0,DISP_RIGHT | DISP_CLRLINE| DISP_REVERSE);	  //右对齐|清除当前行							 //清当前行，居中，英文字体6*8
		SYS_DisplayCE((uchar*)"居中",5,0,DISP_CENTER | DISP_CLRLINE | DISP_REVERSE);	  //居中|清除当前行	
		SYS_DisplayCE((uchar*)"根据坐标显示",7,3,DISP_CURRENT | DISP_CLRLINE | DISP_REVERSE);	  //根据坐标显示|清除当前行	
	}
	else if(1 == LANGUAGE)
	{
		SYS_DisplayCE((uchar*)"Align left",1,0,DISP_POSITION | DISP_CLRLINE | DISP_REVERSE);	  //左对齐|清除当前行														  
		SYS_DisplayCE((uchar*)"Right justify",3,0,DISP_RIGHT | DISP_CLRLINE| DISP_REVERSE);	  //右对齐|清除当前行							 //清当前行，居中，英文字体6*8
		SYS_DisplayCE((uchar*)"Center",5,0,DISP_CENTER | DISP_CLRLINE | DISP_REVERSE);	  //居中|清除当前行	
		SYS_DisplayCE((uchar*)"coordinate",7,3,DISP_CURRENT | DISP_CLRLINE | DISP_REVERSE);	  //根据坐标显示|清除当前行	
	}
	
	SYSTICK_DelayMs(2000); 
//	for(i = 0; i < (5 * 6); i++ )  //6S
//	{
//		SYSTICK_DelayMs(200);
//		LCD_LoopDisplay((uchar*)"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 3, 0, 10, 4);
//		LCD_LoopDisplay((uchar*)"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 5, 1, 10, 4);
//		LCD_LoopDisplay((uchar*)"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 7, 2, 10, 4);
//		LCD_LoopDisplay((uchar*)"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 9, 3, 10, 4);
//	} 
    SYS_CLS();    
}	

