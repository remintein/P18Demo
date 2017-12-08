#include <stdio.h>
#include <string.h>
#include "TCP.h"
#include "system.h"
#include "function.h"
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h"
#include "com.h"
#include "auxio.h"
#include "wifi.h"

extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
static uchar j = 0;

/********************************************************************************************************
** �������ܣ�GPRS�������룬IP�Լ��˿�
** ��    ������						
** ��    �أ�0-���������˳�
			0x73������ȡ�����ļ�ֵ
*********************************************************************************************************/
uchar Input_WIFIPara()
{
	uchar ucKeyValue = KEY_NONE;
	uint  i;
	SendToPC((uchar *)"����IP(F1='.'):",1,0,DISP_CENTER|DISP_CLRSCR);
	i=0; 
	memset((char *)NetSetting.ServerIP,0,15);
	do
	{ 	
		ucKeyValue = SYS_ReadKey();
		if((ucKeyValue >= '0') && (ucKeyValue <= '9'))
		{
			NetSetting.ServerIP[i++] = ucKeyValue;
			SendToPC((uchar *)NetSetting.ServerIP,3,0,DISP_POSITION|DISP_CLRLINE);
		}
		if(ucKeyValue == KEY_F1)
		{
			NetSetting.ServerIP[i++] = '.';
			SendToPC((uchar *)NetSetting.ServerIP,3,0,DISP_POSITION|DISP_CLRLINE);
		}
		if((ucKeyValue == KEY_CLEAR) && (i > 0))
		{
			i --;
			NetSetting.ServerIP[i] = 0;
			SendToPC((uchar *)NetSetting.ServerIP,3,0,DISP_POSITION|DISP_CLRLINE);
		}		 		
	}while(ucKeyValue != KEY_CANCEL && ucKeyValue != KEY_RETURN);
	if(ucKeyValue == KEY_CANCEL) 
	{
		return ucKeyValue;

	}
	SendToPC((uchar *)"����˿ں�:",1,0,DISP_CENTER|DISP_CLRSCR);
	i=0;
	memset((char *)NetSetting.ServerPort,0,10);
	do
	{
		ucKeyValue = SYS_ReadKey();
		if(ucKeyValue >= '0' && ucKeyValue <= '9')
		{
			NetSetting.ServerPort[i++] = ucKeyValue;
			SendToPC((uchar *)NetSetting.ServerPort,3,0,DISP_POSITION|DISP_CLRLINE);
		}
		if(ucKeyValue == KEY_CLEAR && i > 0)
		{
			i --;
			NetSetting.ServerPort[i] = 0;
			SendToPC((uchar *)NetSetting.ServerPort,3,0,DISP_POSITION|DISP_CLRLINE);
		} 		
	}while((ucKeyValue != KEY_CANCEL) && (ucKeyValue != KEY_RETURN));
	if(ucKeyValue == KEY_CANCEL) 
	{
		return ucKeyValue;

	}
	return 0;
}

void WIFI_Debug()
{
	uchar temp;
	uint uiRecLen,i;
	uchar ucKeyValue,ucBack;
	uchar aucIPBuff[20] = {0};
	uchar aucPortNum[10] = {0};
	uchar ucSendBuff[4096];
	char RecData[4096]={0};
	memset(NetSetting.APSSID,0,50);
	memset(NetSetting.APPassWord,0,50);
//	Uart_SetWIFIDebug(1);

	memcpy((char *)NetSetting.APSSID,"P10TEST",strlen("P10TEST"));
	memcpy((char *)NetSetting.APPassWord,"12345678",strlen("12345678"));
//	memcpy((char *)NetSetting.ServerIP,"45.78.44.79",strlen("45.78.44.79"));
//	memcpy((char *)NetSetting.ServerPort,"5756",strlen("5756"));

	
	SendToPC((uchar *)"WIFI����", 1,0,DISP_CENTER|DISP_CLRSCR);
	WIFI_ModuleInit();
	WIFI_PowerOn();
	if(aucIPBuff[0]==0)
	{
		SYS_CLS();	
		SendToPC((uchar *)"����IP(F1='.'):",1,0,DISP_CENTER|DISP_CLRSCR);
		i=0; 
		memset(aucIPBuff,0,20);
		do
		{ 	
			ucKeyValue = SYS_ReadKey();
			if((ucKeyValue >= '0') && (ucKeyValue <= '9'))
			{
				aucIPBuff[i++] = ucKeyValue;
				SendToPC((uchar *)aucIPBuff,3,0,DISP_POSITION|DISP_CLRLINE);
			}
			if(ucKeyValue == KEY_F1)
			{
				aucIPBuff[i++] = '.';
				SendToPC((uchar *)aucIPBuff,3,0,DISP_POSITION|DISP_CLRLINE);
			}
			if((ucKeyValue == KEY_CLEAR) && (i > 0))
			{
				i --;
				aucIPBuff[i] = 0;
				SendToPC((uchar *)aucIPBuff,3,0,DISP_POSITION|DISP_CLRLINE);
			}		 		
		}while(ucKeyValue != KEY_CANCEL && ucKeyValue != KEY_RETURN);
		if(ucKeyValue == KEY_CANCEL) 
		{
			goto WIFI_END;

		}

		SendToPC((uchar *)"����˿ں�:",1,0,DISP_CENTER|DISP_CLRSCR);
		i=0;
		memset(aucPortNum,0,10);
		do
		{
			ucKeyValue = SYS_ReadKey();
			if(ucKeyValue >= '0' && ucKeyValue <= '9')
			{
				aucPortNum[i++] = ucKeyValue;
				SendToPC((uchar *)aucPortNum,3,0,DISP_POSITION|DISP_CLRLINE);
			}
			if(ucKeyValue == KEY_CLEAR && i > 0)
			{
				i --;
				aucPortNum[i] = 0;
				SendToPC((uchar *)aucPortNum,3,0,DISP_POSITION|DISP_CLRLINE);
			} 		
		}while((ucKeyValue != KEY_CANCEL) && (ucKeyValue != KEY_RETURN));
		if(ucKeyValue == KEY_CANCEL) 
		goto WIFI_END;
	}
	memcpy(NetSetting.ServerIP,aucIPBuff,strlen(aucIPBuff));
	memcpy(NetSetting.ServerPort,aucPortNum,strlen(aucPortNum));
	SendToPC((uchar *)"SSID������..", 3,0,DISP_CENTER|DISP_CLRSCR);
	if(!WIFI_StatusGet())							//SSID���ˣ����µ��ô˺���
	{
		SendToPC((uchar *)"����SSID�ɹ�", 3,0,DISP_CENTER);
	}
	else
	{
		SendToPC((uchar *)"����SSIDʧ��", 3,0,DISP_CENTER);
		goto WIFI_END ;
	}
	SYSTICK_DelayMs(1000);

	if(!WIFI_TCPCheckLink())							//��TCP���Ӷ��ˣ�SSIDû�ϣ����µ��ô˺���
	{
		SendToPC((uchar *)"�����ɹ�", 5,0,DISP_CENTER);
		SYSTICK_DelayMs(1000);
	}
	else
	{
		SendToPC((uchar *)"����ʧ��", 5,0,DISP_CENTER);
		SYSTICK_DelayMs(1000);
		goto WIFI_END;
	}
	

	SendToPC((uchar *)"��1->������:",1,0,DISP_POSITION|DISP_CLRLINE);
	SendToPC((uchar *)"            ",3,0,DISP_POSITION|DISP_CLRLINE);
	SendToPC((uchar *)"2��->������:",5,0,DISP_POSITION|DISP_CLRLINE); 
	SendToPC((uchar *)"            ",7,0,DISP_POSITION|DISP_CLRLINE); 

	while(1)
	{

		ucKeyValue = SYS_ReadKey();
		switch(ucKeyValue)
		{
			case KEY_1 :
				for(i=0;i<10;i++)
				{
					ucSendBuff[i] = 0x30+j;
					j++;
				}
				if(j > 64)
				{
					j = 0;
				}
				ucBack = WIFI_SendTCPData(ucSendBuff,10);
				if(!ucBack)
				{
					SendToPC((uchar *)ucSendBuff,3,0,DISP_CENTER|DISP_CLRLINE);
				}
				else
				{
					SendToPC((uchar *)"����ʧ��",3,0,DISP_CENTER|DISP_CLRLINE);
				}
			break;
			case KEY_2 :
				memset(RecData,0,sizeof(RecData));
				ucBack = WIFI_ReceiveTCPData(&uiRecLen, RecData, 5);
				SendToPC((uchar *)"    ",7,0,DISP_CENTER|DISP_CLRLINE);

				if(!ucBack)
				{
					SendToPC((uchar *)RecData,7,0,DISP_CENTER|DISP_CLRLINE);	
				}
				else
				{
					SendToPC((uchar *)"���ճ�ʱ",7,0,DISP_CENTER|DISP_CLRLINE);
					if(!WIFI_ToCmdMode())
						{
							if(!WIFI_StatusGet())
							{
								if(WIFI_TCPCheckLink())
								{
									SYS_DisplayCE("�ѵ���",7,0,DISP_POSITION|DISP_CLRLINE);
									SYSTICK_DelayMs(2000);
									goto WIFI_END ;
								}
							}
						}					
					}
				memset(RecData,0,sizeof(RecData));
			break;
			case KEY_CANCEL: 
WIFI_END:
			if(!WIFI_CloseSocket())
			{
				SendToPC((uchar *)"TCP���ӶϿ�", 1,0,DISP_CENTER|DISP_CLRSCR);
			}
			else
			{
				SendToPC((uchar *)"TCP����δ��", 1,0,DISP_CENTER|DISP_CLRSCR);
			}
			if(!WIFI_DisconnectSSID())
			{
				SendToPC((uchar *)"SSID���ӶϿ�", 3,0,DISP_CENTER);
			}
			else
			{
				SendToPC((uchar *)"SSID����δ��", 3,0,DISP_CENTER);
			}
			
//				if(!WIFI_ModuleClose())
//				{
//					SendToPC((uchar *)"WIFI�ر�", 1,0,DISP_CENTER|DISP_CLRSCR);
//				}
//				else
//				{
//					SendToPC((uchar *)"WIFIδ�ر�", 1,0,DISP_CENTER|DISP_CLRSCR);
//				}
//				WIFI_PowerOff();
				SendToPC((uchar *)"�˳�����", 3,0,DISP_CENTER|DISP_CLRSCR);
				SYSTICK_DelayMs(1000);	
				WIFI_PowerOff();
				return ;
			default: 
			break;
				
		}
	}

}
