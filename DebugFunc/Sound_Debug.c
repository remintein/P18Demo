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
	TTS_SetTTSDebug(1); //����ӡ
	Uart_SetSysDebug(1);     //ϵͳ��ӡ����
	uchar ucCOMID = 4;

	if(0 == LANGUAGE)
	{  	
		SendToPC((uchar *)"TTS������ʼ��...", 1, 0, DISP_CENTER|DISP_CLRSCR );
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"TTS Tnt...", 1, 0, DISP_CENTER|DISP_CLRSCR );
	}
	
	Sound_Debug_Start:
	SYSTICK_DelayMs(500);
	if(0 == LANGUAGE)
	{  	
		SendToPC((uchar *)"��1����Ϊ��������", 1, 0, DISP_POSITION | DISP_CLRSCR );
		SendToPC((uchar *)"��2����ΪС����", 3, 0, DISP_POSITION | DISP_CLRLINE );
		SendToPC((uchar *)"��4����Ϊ������", 5, 0, DISP_POSITION | DISP_CLRLINE );
		SendToPC((uchar *)"��5��������", 7, 0, DISP_POSITION | DISP_CLRLINE );
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
					SendToPC((uchar *)"�˳�����", 5, 0 ,DISP_CENTER | DISP_CLRLINE); 
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
					SendToPC((uchar *)"��������...", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"Speed Set ", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}				
				
				if(0 == TTSSet(1, 1, 0))
				{
					if(0 == LANGUAGE)
					{  	
						SendToPC((uchar *)"���������ú�", 1, 0, DISP_POSITION | DISP_CLRSCR );
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
						SendToPC((uchar *)"��������ʧ��!", 3, 0, DISP_POSITION | DISP_CLRLINE );
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
					SendToPC((uchar *)"����Ϊ��С����...", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"volume   min", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				
				if(0 == TTSSet(1, 2, -25000))
				{
					if(0 == LANGUAGE)
					{  	
						SendToPC((uchar *)"������ΪС����", 3, 0, DISP_POSITION | DISP_CLRLINE );
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
						SendToPC((uchar *)"����ʧ��!", 3, 0, DISP_POSITION | DISP_CLRLINE );
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
					SendToPC((uchar *)"����Ϊ������...", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"volume   middle", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				
				if(0 == TTSSet(1, 2, 0))
				{
					if(0 == LANGUAGE)
					{  	
						SendToPC((uchar *)"������Ϊ������", 3, 0, DISP_POSITION | DISP_CLRLINE );
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
						SendToPC((uchar *)"����ʧ��!", 3, 0, DISP_POSITION | DISP_CLRLINE );
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
					SendToPC((uchar *)"����Ϊ������...", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"volume   MAX", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				
				if(0 == TTSSet(1, 2, 25000))
				{
					if(0 == LANGUAGE)
					{  	
						SendToPC((uchar *)"������Ϊ������", 3, 0, DISP_POSITION | DISP_CLRLINE );
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
						SendToPC((uchar *)"����ʧ��!", 3, 0, DISP_POSITION | DISP_CLRLINE );
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
					SendToPC((uchar *)"��������...", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"Speak...", 1, 0, DISP_POSITION | DISP_CLRSCR );
				}
				
				if(0 == LANGUAGE)
				{  	
					if(0 ==	TTSPlay(2, (uchar*)"[v6]msgaˢ���ɹ������ϳ�") )
					{
						SendToPC((uchar *)"���Գɹ�", 3, 0, DISP_POSITION | DISP_CLRLINE );
					}
					else SendToPC((uchar *)"����ʧ��", 3, 0, DISP_POSITION | DISP_CLRLINE );
					
				}
				else if(1 == LANGUAGE)
				{
					if(0 ==	TTSPlay(2, (uchar*)"Credit card success��") )
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
