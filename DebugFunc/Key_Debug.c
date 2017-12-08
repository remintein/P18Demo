#include <stdio.h>
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h"
#include "system.h"
extern void IRQkey_Init(void);
extern void (* Key1_Handler)(void);
extern void (* Key2_Handler)(void);
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern uchar LANGUAGE;
extern void text_laohua(void);
void text1(void)
{
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"按键1", 1, 2 , DISP_POSITION | DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"KEY 1", 1, 2 , DISP_POSITION | DISP_CLRSCR);
	}

	SYSTICK_DelayMs(1000);  
}
void text2(void)
{
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"按键2", 1, 2 , DISP_POSITION | DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"KEY 2", 1, 2 , DISP_POSITION | DISP_CLRSCR);
	}
	

	SYSTICK_DelayMs(1000); 

}

/********************************************************************************************************
** 函数功能：按键测试，当按下不同按键时屏幕显示相应的按键信息，按 取消 键退出测试
             电源键无法测试
** 参    数：无						
** 返    回：无
*********************************************************************************************************/
void KEY_Debug(void)
{
    uchar ucKeyValue = KEY_NONE;
	uchar ucKeyValue1 = KEY_NONE;
	
    SYS_CLS();
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"按键测试", 1, 0 ,DISP_CENTER  | DISP_CLRSCR);
		SendToPC((uchar *)"请按键...", 1, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"KEY TEST", 1, 0 ,DISP_CENTER  | DISP_CLRSCR);
		SendToPC((uchar *)"press button...", 1, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}


	SYS_KeyInit();  //查询模式
    while(1)
    {
        ucKeyValue = SYS_ReadKey();  //串口按键
		ucKeyValue1 = SYS_ReadKeyInq();  //机器按键，按键查询模式
        switch(ucKeyValue)  //串口按键
        {
            case KEY_CANCEL:  
				if(0 == LANGUAGE)
				{  
					SendToPC((uchar *)"退出测试", 5, 0 ,DISP_CENTER); 
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
		 switch(ucKeyValue1)  //机器按键
        {
			case KEY_UP: 
				text1();
                break;
			case KEY_DOWN: 
				text2();
                break;
            default:			
				break;
        }
    }
}
