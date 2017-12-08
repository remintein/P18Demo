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
		SYS_DisplayCE((uchar*)"�����",1,0,DISP_POSITION | DISP_CLRLINE | DISP_REVERSE);	  //�����|�����ǰ��														  
		SYS_DisplayCE((uchar*)"�Ҷ���",3,0,DISP_RIGHT | DISP_CLRLINE| DISP_REVERSE);	  //�Ҷ���|�����ǰ��							 //�嵱ǰ�У����У�Ӣ������6*8
		SYS_DisplayCE((uchar*)"����",5,0,DISP_CENTER | DISP_CLRLINE | DISP_REVERSE);	  //����|�����ǰ��	
		SYS_DisplayCE((uchar*)"����������ʾ",7,3,DISP_CURRENT | DISP_CLRLINE | DISP_REVERSE);	  //����������ʾ|�����ǰ��	
	}
	else if(1 == LANGUAGE)
	{
		SYS_DisplayCE((uchar*)"Align left",1,0,DISP_POSITION | DISP_CLRLINE | DISP_REVERSE);	  //�����|�����ǰ��														  
		SYS_DisplayCE((uchar*)"Right justify",3,0,DISP_RIGHT | DISP_CLRLINE| DISP_REVERSE);	  //�Ҷ���|�����ǰ��							 //�嵱ǰ�У����У�Ӣ������6*8
		SYS_DisplayCE((uchar*)"Center",5,0,DISP_CENTER | DISP_CLRLINE | DISP_REVERSE);	  //����|�����ǰ��	
		SYS_DisplayCE((uchar*)"coordinate",7,3,DISP_CURRENT | DISP_CLRLINE | DISP_REVERSE);	  //����������ʾ|�����ǰ��	
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

