#include <stdio.h>
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h"
#include "system.h"
#include "QR_collection.h"
extern uchar LANGUAGE;
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);

/********************************************************************************************************
** �������ܣL����,���嶥��ͼ��
** ��    ������
** ��    �أ���
*********************************************************************************************************/
extern void LCD_Clrscr(void);

void QR_Scanning(void)
{
	uint puiRecLen = 0;
	uchar acRecBuff1[1000] = {0};
	uchar acRecBuff2[1000] = {0};
	uint timecount_2 = 0;
	uchar ucKeyValue = KEY_NONE;
	
	timecount_2 = SYS_GetTickCount();
	
	while(1)
	{
		ucKeyValue = SYS_ReadKey();
		if(KEY_CANCEL == ucKeyValue)
		{
			return;
		}
		QR_collection(&puiRecLen, acRecBuff1, 50 );
		if(acRecBuff1[0] != 0)
		{
			if(puiRecLen > 1)
			{
//				printf("\r\n%d\r\n",(SYS_GetTickCount() - timecount_2));
//				printf("\r\npuiRecLen:%d, acRecBuff2:%s \r\n",puiRecLen,acRecBuff2);
				if(0)//if((0 == memcmp(acRecBuff2,acRecBuff1,puiRecLen)) && ((SYS_GetTickCount() - timecount_2) < 200)  ) //���������ϴ�ɨ���������ͬ
				{
					puiRecLen = 0;
					memset(acRecBuff1,0,200);
				}
				else{
					LCD_Clrscr();
					printf("\r\npuiRecLen:%d, acRecBuff1:%s \r\n",puiRecLen,acRecBuff1);
					if(puiRecLen <= 20)		
					{
						SYS_DisplayCE(acRecBuff1,  1, 0, DISP_CENTER | DISP_CLRLINE );
					}
					else if(puiRecLen <= 40)
					{
						SYS_DisplayCE(acRecBuff1,  1, 0, DISP_CENTER | DISP_CLRLINE );
						SYS_DisplayCE(&acRecBuff1[20],  3, 0, DISP_RIGHT | DISP_CLRLINE );
					}
					else if(puiRecLen <= 60)
					{
						SYS_DisplayCE(acRecBuff1,  1, 0, DISP_CENTER | DISP_CLRLINE );
						SYS_DisplayCE(&acRecBuff1[20],  3, 0, DISP_CENTER | DISP_CLRLINE );
						SYS_DisplayCE(&acRecBuff1[40],  5, 0, DISP_RIGHT | DISP_CLRLINE );
					}
//					memcpy(acRecBuff2, acRecBuff1, puiRecLen);
//					SYS_Beep(200);
//					SYSTICK_DelayMs(1500);
//					LCD_Clrscr();
					puiRecLen = 0;
					
					memset(acRecBuff1,0,200);
					timecount_2 = SYS_GetTickCount();
				}

			}
		}
	}
}
/********************************************************************************************************
** �������ܣ���ά�����
             
** ��    ������						
** ��    �أ���
*********************************************************************************************************/
void QR_Debug(void)
{
    uchar ucKeyValue = KEY_NONE;

	QR_Debug_Start:
    SYS_CLS();
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"��ά�����", 1, 0 ,DISP_POSITION  | DISP_CLRSCR);
		SendToPC((uchar *)"1.ɨ�����", 3, 0 ,DISP_POSITION  | DISP_CLRLINE);
		SendToPC((uchar *)"2.��ʾ����", 5, 0 ,DISP_POSITION  | DISP_CLRLINE);
	}
	else if(1 == LANGUAGE)
	{
		 SendToPC((uchar *)"QR TEST", 1, 0 ,DISP_POSITION  | DISP_CLRSCR);
		SendToPC((uchar *)"1.Scan test", 3, 0 ,DISP_POSITION  | DISP_CLRLINE);
		SendToPC((uchar *)"2.Display test", 5, 0 ,DISP_POSITION  | DISP_CLRLINE);
	}
    
	
//	QR_Init();//��ʼ��ģ��
    while(1)
    {
        ucKeyValue = SYS_ReadKey();
        switch(ucKeyValue)
        {
			case KEY_1:  
				SYS_CLS();
				if(0 == LANGUAGE)
				{  
					SendToPC((uchar*)"��ά��ɨ����...", 7, 0,DISP_CENTER | DISP_CLRLINE);
				}
				else if(1 == LANGUAGE)
				{
					 SendToPC((uchar*)"Scan in...", 7, 0,DISP_CENTER | DISP_CLRLINE);
				}
					
				QR_Scanning();
				goto QR_Debug_Start;
			
            case KEY_CANCEL:
				if(0 == LANGUAGE)
				{  
					SendToPC((uchar *)"�˳�����", 5, 0 ,DISP_CLRSCR); 
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
    }
}
