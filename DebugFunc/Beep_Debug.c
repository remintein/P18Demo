#include <stdio.h>
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h"
#include "system.h"
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern uchar LANGUAGE;
/********************************************************************************************************
** �������ܣ����������ԣ�����1����,��Դ������9*5��delay=145Ч�����
** ��    ������						
** ��    �أ���
*********************************************************************************************************/
void BEEP_Debug(void)
{
	SYS_CLS();
	if(0 == LANGUAGE)
	{  
		SendToPC("����������", 1, 0 ,DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC("BEEP     TEST ", 1, 0 ,DISP_CENTER);
	}
	SYS_Beep(1000); 
	if(0 == LANGUAGE)
	{	
	SendToPC("�������", 1, 0 ,DISP_CENTER|DISP_CLRLINE);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC("test is over", 1, 0 ,DISP_CENTER|DISP_CLRLINE);
	}
	SYSTICK_DelayMs(1000);
}
