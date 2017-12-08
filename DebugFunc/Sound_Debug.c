#include <stdio.h>	
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
#include "tts.h"
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern uchar LANGUAGE;
//extern COM_Hardware_Para g_COM_Hardware_Para[10];
void Sound_Debug(void)
{
	uchar ucKeyValue;
//	TTSInit();
	TTS_SetTTSDebug(1); //开打印
	Uart_SetSysDebug(1);     //系统打印开启
	uchar ucCOMID = 4;

	if(0 == LANGUAGE)
	{  	
		SendToPC((uchar *)"TTS语音初始化...", 1, 0, DISP_CENTER|DISP_CLRSCR );
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"TTS Tnt...", 1, 0, DISP_CENTER|DISP_CLRSCR );
	}
	
	Sound_Debug_Start:
	SYSTICK_DelayMs(500);
	if(0 == LANGUAGE)
	{  	
		SendToPC((uchar *)"按1配置为正常语速", 1, 0, DISP_POSITION | DISP_CLRSCR );
		SendToPC((uchar *)"按2配置为小音量", 3, 0, DISP_POSITION | DISP_CLRLINE );
		SendToPC((uchar *)"按4配置为大音量", 5, 0, DISP_POSITION | DISP_CLRLINE );
		SendToPC((uchar *)"按5测试语音", 7, 0, DISP_POSITION | DISP_CLRLINE );
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"Enter 1 Speed 5", 1, 0, DISP_POSITION | DISP_CLRSCR );
		SendToPC((uchar *)"Enter 2 Volume 2", 3, 0, DISP_POSITION | DISP_CLRLINE );
		SendToPC((uchar *)"Enter 4 Volume 10", 5, 0, DISP_POSITION | DISP_CLRLINE );
		SendToPC((uchar *)"Enter 5 Speak", 7, 0, DISP_POSITION | DISP_CLRLINE );
	}	
	
	

	while(1)
    {
        ucKeyValue = SYS_ReadKey();
        switch(ucKeyValue)
        {
            case KEY_CANCEL:
				if(0 == LANGUAGE)
				{  	
					SendToPC((uchar *)"退出测试", 5, 0 ,DISP_CENTER | DISP_CLRLINE); 
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"Exit test", 5, 0 ,DISP_CENTER | DISP_CLRLINE); 
				}				
                
                SYSTICK_DelayMs(1000);
                SYS_CLS();
                return;  
			case KEY_1:
				if(0 == LANGUAGE)
				{  	
					SendToPC((uchar *)"配置语速...", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"Speed Set ", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}				
				
				if(0 == TTSSet(1, 1, 0))
				{
					if(0 == LANGUAGE)
					{  	
						SendToPC((uchar *)"语音已配置好", 1, 0, DISP_POSITION | DISP_CLRSCR );
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"OK!", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
				}
				else 
				{
					if(0 == LANGUAGE)
					{  	
						SendToPC((uchar *)"语速配置失败!", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Fail!", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
				}
				goto Sound_Debug_Start;
			case KEY_2:
				if(0 == LANGUAGE)
				{  	
					SendToPC((uchar *)"配置为最小音量...", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"volume   min", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				
				if(0 == TTSSet(1, 2, -25000))
				{
					if(0 == LANGUAGE)
					{  	
						SendToPC((uchar *)"已配置为小音量", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"OK!", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
					
				}
				else
				{
					if(0 == LANGUAGE)
					{  	
						SendToPC((uchar *)"配置失败!", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Fail!", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
				}					
				goto Sound_Debug_Start;
			case KEY_3:
				if(0 == LANGUAGE)
				{  	
					SendToPC((uchar *)"配置为中音量...", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"volume   middle", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				
				if(0 == TTSSet(1, 2, 0))
				{
					if(0 == LANGUAGE)
					{  	
						SendToPC((uchar *)"已配置为中音量", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"OK!", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
					
				}
				else
				{
					if(0 == LANGUAGE)
					{  	
						SendToPC((uchar *)"配置失败!", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Fail!", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
				}
				goto Sound_Debug_Start;
			case KEY_4:
				if(0 == LANGUAGE)
				{  	
					SendToPC((uchar *)"配置为大音量...", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"volume   MAX", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				
				if(0 == TTSSet(1, 2, 25000))
				{
					if(0 == LANGUAGE)
					{  	
						SendToPC((uchar *)"已配置为大音量", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"OK!", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
					
				}
				else
				{
					if(0 == LANGUAGE)
					{  	
						SendToPC((uchar *)"配置失败!", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Fail!", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
				}
				goto Sound_Debug_Start;
			case KEY_5:
				if(0 == LANGUAGE)
				{  	
					SendToPC((uchar *)"发音测试...", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"Speak...", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				
				if(0 == LANGUAGE)
				{  	
					if(0 ==	TTSPlay(2, (uchar*)"[v6]msga刷卡成功，请上车") )
					{
						SendToPC((uchar *)"测试成功", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
					else SendToPC((uchar *)"测试失败", 3, 0, DISP_POSITION | DISP_CLRLINE );
					
				}
				else if(1 == LANGUAGE)
				{
					if(0 ==	TTSPlay(2, (uchar*)"Credit card success！") )
					{
						SendToPC((uchar *)"Test success", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
					else SendToPC((uchar *)"Test failed", 3, 0, DISP_POSITION | DISP_CLRLINE );
				}
				goto Sound_Debug_Start;			
            default:				
				break;
        }
    }
}
