#include <stdio.h>	
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
#include "version.h"
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern uchar LANGUAGE;
void Version_Debug(void)
{
	uchar BUFF[50] = {0};
	uchar DISPlayBUFF[100] = {0};
	if(0 == LANGUAGE)
	{  
		memcpy(BUFF, (uchar*)DEVICE_VERSION, strlen(DEVICE_VERSION)); //"P18.0102.DC4.SVN53.170401"  
		sprintf((char*)DISPlayBUFF, "版本:%s", &BUFF[13]); //SVN53.170401
		SendToPC((uchar*)"版本信息", 1, 0 ,DISP_CENTER|DISP_CLRSCR);
		
		
		SendToPC((uchar*)"型号:P18", 3, 0 ,DISP_POSITION);
		SendToPC((uchar*)DISPlayBUFF, 5, 0 ,DISP_POSITION);
		SendToPC((uchar*)"按取消键退出", 7, 0 ,DISP_POSITION);
	}
	else if(1 == LANGUAGE)
	{
		memcpy(BUFF, (uchar*)DEVICE_VERSION, strlen(DEVICE_VERSION)); //"P18.0102.DC4.SVN53.170401"  
		sprintf((char*)DISPlayBUFF, "%s", &BUFF[13]); //SVN53.170401
		SendToPC((uchar*)"version number", 1, 0 ,DISP_CENTER|DISP_CLRSCR);
		
		
		SendToPC((uchar*)"Device:P18", 3, 0 ,DISP_POSITION);
		SendToPC((uchar*)DISPlayBUFF, 5, 0 ,DISP_POSITION);
		SendToPC((uchar*)"cancel-to exit", 7, 0 ,DISP_POSITION);
	}
	
	while(1)
	{
		if(KEY_CANCEL == SYS_ReadKey())
		{
			return ;
		}
	}
}
