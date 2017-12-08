#include <stdio.h>	
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
#include "led.h "
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
uint uiBlueLedTime = 0;
extern uchar LANGUAGE;
uint CALLBACK thisTickCallBack(void)	
{
    uiBlueLedTime++;
    if(uiBlueLedTime >= 200)
    {
        uiBlueLedTime = 0;
        LED_Reversal(LED_BLUE);
        LED_Reversal(LED_RED);
        LED_Reversal(LED_YELLOW);
    }
    return 0;
}
void LED_Debug(void)
{
	uchar ucKeyValue;
    
//    SYS_SetTickBack((TICK_CALLBACK) thisTickCallBack);

//    LEDSEG_Init();
    SYS_CLS();
	if(0 == LANGUAGE)
	{  	
		SendToPC((uchar *)"LED 测试", 1, 0, DISP_CENTER|DISP_CLRSCR );
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"LED TEST", 1, 0, DISP_CENTER|DISP_CLRSCR | DISP_CLRLINE );
	}
    
    SYSTICK_DelayMs(500);

//	//蓝色指示灯测试
//	if(0 == LANGUAGE)
//	{  	
//		SendToPC((uchar *)" 蓝色指示灯 亮  ", 3, 0 ,DISP_CENTER | DISP_CLRLINE);
//	}
//	else if(1 == LANGUAGE)
//	{
//		SendToPC((uchar *)" Blue light -ON  ", 3, 0 ,DISP_CENTER | DISP_CLRLINE);
//	}
//	
//	LED_Display(LED_BLUE, LED_ON);
//	SYSTICK_DelayMs(500);
//	if(0 == LANGUAGE)
//	{  	
//		SendToPC((uchar *)" 蓝色指示灯 灭  ", 3, 0, DISP_CENTER  | DISP_CLRLINE);
//	}
//	else if(1 == LANGUAGE)
//	{
//		SendToPC((uchar *)" Blue light -OFF  ", 3, 0, DISP_CENTER | DISP_CLRLINE );
//	}
//	
//	LED_Display(LED_BLUE, LED_OFF);
//	SYSTICK_DelayMs(500);
//	ucKeyValue = SYS_ReadKey();
//    if(ucKeyValue == KEY_CANCEL)
//    {
//        SYS_CLS();
//        return;
//    }

//    //黄色指示灯测试
//	if(0 == LANGUAGE)
//	{  	
//		SendToPC((uchar *)" 黄色指示灯 亮  ", 3, 0, DISP_CENTER | DISP_CLRLINE );
//	}
//	else if(1 == LANGUAGE)
//	{
//		SendToPC((uchar *)" Yellow light -ON  ", 3, 0,DISP_POSITION | DISP_CLRLINE );
//	}
//	LED_Display(LED_YELLOW, LED_ON);
//	SYSTICK_DelayMs(500);
//	if(0 == LANGUAGE)
//	{  	
//		SendToPC((uchar *)" 黄色指示灯 灭  ", 3, 0, DISP_CENTER | DISP_CLRLINE );
//	}
//	else if(1 == LANGUAGE)
//	{
//		SendToPC((uchar *)" Yellow light -OFF  ", 3, 0,DISP_POSITION  | DISP_CLRLINE);
//	}
//	LED_Display(LED_YELLOW, LED_OFF);
//	SYSTICK_DelayMs(500);
//	ucKeyValue = SYS_ReadKey();
//    if(ucKeyValue == KEY_CANCEL)
//    {
//        SYS_CLS();
//        return;
//    }

//    //绿色指示灯测试
//	if(0 == LANGUAGE)
//	{  	
//		SendToPC((uchar *)" 绿色指示灯 亮  ", 3, 0,DISP_POSITION | DISP_CLRLINE);
//	}
//	else if(1 == LANGUAGE)
//	{
//		SendToPC((uchar *)" green light -ON  ", 3, 0,DISP_POSITION | DISP_CLRLINE);
//	}
//	
//	LED_Display(LED_GREEN, LED_ON);
//	SYSTICK_DelayMs(500);
//	if(0 == LANGUAGE)
//	{  	
//		SendToPC((uchar *)" 绿色指示灯 灭  ", 3, 0,DISP_POSITION | DISP_CLRLINE);
//	}
//	else if(1 == LANGUAGE)
//	{
//		SendToPC((uchar *)" green light -OFF  ", 3, 0,DISP_POSITION | DISP_CLRLINE);
//	}
//	LED_Display(LED_GREEN, LED_OFF);
//	SYSTICK_DelayMs(500);
//	ucKeyValue = SYS_ReadKey();
//    if(ucKeyValue == KEY_CANCEL)
//    {
//        SYS_CLS();
//        return;
//    }

//    //红色指示灯测试
//	if(0 == LANGUAGE)
//	{  	
//		SendToPC((uchar *)" 红色指示灯 亮  ", 3, 0,DISP_POSITION | DISP_CLRLINE);
//	}
//	else if(1 == LANGUAGE)
//	{
//		SendToPC((uchar *)" Red light -ON ", 3, 0,DISP_POSITION | DISP_CLRLINE);
//	}
//	LED_Display(LED_RED, LED_ON);
//	SYSTICK_DelayMs(500);
//	if(0 == LANGUAGE)
//	{  	
//		SendToPC((uchar *)" 红色指示灯 灭  ", 3, 0,DISP_POSITION | DISP_CLRLINE);
//	}
//	else if(1 == LANGUAGE)
//	{
//		SendToPC((uchar *)" Red light -OFF ", 3, 0,DISP_POSITION | DISP_CLRLINE);
//	}
//	LED_Display(LED_RED, LED_OFF);
//	SYSTICK_DelayMs(500);
//	ucKeyValue = SYS_ReadKey();
//    if(ucKeyValue == KEY_CANCEL)
//    {
//        SYS_CLS();
//        return;
//    }

    //所有指示灯点亮
	if(0 == LANGUAGE)
	{  	
		SendToPC((uchar *)" 所有指示灯 亮  ", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)" ALL light -ON  ", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
	}
    LED_Display(LED_BLUE,   LED_ON);
    LED_Display(LED_YELLOW, LED_ON);
    LED_Display(LED_GREEN,  LED_ON);
    LED_Display(LED_RED,    LED_ON);
    SYSTICK_DelayMs(500);
    ucKeyValue = SYS_ReadKey();
    if(ucKeyValue == KEY_CANCEL)
    {
        SYS_CLS();
        return;
    }

    //所有指示灯熄灭
	if(0 == LANGUAGE)
	{  	
		SendToPC((uchar *)" 所有指示灯 灭  ", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)" ALL light -OFF  ", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
	}
    
    LED_Display(LED_BLUE,   LED_OFF);
    LED_Display(LED_YELLOW, LED_OFF);
    LED_Display(LED_GREEN,  LED_OFF);
    LED_Display(LED_RED,    LED_OFF);
    SYSTICK_DelayMs(500);
    ucKeyValue = SYS_ReadKey();
    if(ucKeyValue == KEY_CANCEL)
    {
        SYS_CLS();
        return;
    }
	if(0 == LANGUAGE)
	{  	
		SendToPC((uchar *)"    测试成功    ", 3,  0 ,DISP_POSITION | DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)" Test success ", 3,  0 ,DISP_POSITION | DISP_CLRSCR);
	}
   
    SYSTICK_DelayMs(500);
	SYS_CLS();    
}



