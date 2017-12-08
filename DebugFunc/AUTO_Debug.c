#include <stdio.h>	
#include <stdlib.h>	
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
#include "tcp.h"
#include "com.h"
#include <string.h>
#include "system.h"
#include "auxio.h"
#include "com.h"
#include "wifi.h"
#include "led_seg.h"
#include "led.h "
#include "lcd.h "
#include "tcp.h"
#include "gps.h"
#include "mifare1_operate.h"
#include "rc523_driver.h"
#include "picc_rc523_lib.h"
void Uart_SetSysDebug(uchar);
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern uchar LANGUAGE;

extern void IRQkey_Init(void);
extern void (* Key1_Handler)(void);
extern void (* Key2_Handler)(void);
extern uchar g_laohua_sign;
SYSTEMTIME_STTypePara  g_DateTime;	//ʱ��ṹ��
uchar g_ucDispDayChar[16] ={"2017��06��07��"};
uchar aucDispWeekDayChar[16]={"����X"};
uchar aucDispTimeChar[16]={"10ʱ13��00��"};

void AUTO_Debug(void)
{
	
	
	uchar i = 0;
//	uchar ucTemp = 0;
	uchar temp = 0;
	uchar ATRlen;
	uchar UID[12],atr[32];
	uchar info[32];
	uint uiTick[10]= {0};
//	uchar LanguageChoice = 0;  //����ѡ��
	char sprintfBUFF1[50] = {0};
	char sprintfBUFF2[50] = {0};
//	char sprintfBUFF3[50] = {0};
//	char sprintfBUFF4[50] = {0};

	uchar ucKeyValue =KEY_NONE;
	
	/*TCP*/
	uchar  APN[50] = {0}; 
	uchar *user = {0};
	uchar *pwd = {0};
	char *Type = {"TCP"};
	uchar Number = 1;
	char IP[20] = {"58.250.161.25"};//{"113.87.162.223"};//
	uint Port = 5756;//7321;//
	uchar Signal[2] = {0};
	uchar IPAdd[50] = {0};
//	uchar SimStatus[1] = {0};
	uchar Schedule[1] = {0};
	
	TCP_QueryConnectionSchedule(Schedule);
	TCP_Connection_Time_MAX(60*4);
	TCP_NetworkPara_Set(APN, user, pwd, (uchar*)Type, Number, (uchar*)IP, Port);
	TCP_SetCallBackFlag(1);  //
	Uart_SetTCPDebug(1);
	Uart_SetSysDebug(1);     //ϵͳ��ӡ����
	TCP_Interactive_Mode_Set(0);   //ģʽ0 ���Զ��շ���
	TCP_Connection_Mode(0);//����Ϊ������
	TCP_Init();

	/*��ȡϵͳʱ��*/
	SYS_GetSysDateTime(&g_DateTime); //���ϵͳʱ��
	sprintf((char*)g_ucDispDayChar,"%2d��%2d��", g_DateTime.usMonth, g_DateTime.usDay);
   
    switch(g_DateTime.usDayOfWeek)
	{
		case 0: sprintf((char*)aucDispTimeChar, "������%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
		break;
		case 1: sprintf((char*)aucDispTimeChar, "����һ%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
		break;
		case 2: sprintf((char*)aucDispTimeChar, "���ڶ�%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
		break;
		case 3: sprintf((char*)aucDispTimeChar, "������%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
        break;
        case 4: sprintf((char*)aucDispTimeChar, "������%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
		break;
		case 5: sprintf((char*)aucDispTimeChar, "������%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
		break;
		case 6: sprintf((char*)aucDispTimeChar, "������%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
		break;
        default:sprintf((char*)aucDispTimeChar, "������%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);	
	}
	

	
	SendToPC((uchar *)"���ڽ����ϻ����ԣ�", 1, 0, DISP_CENTER | DISP_CLRSCR);
	SYSTICK_DelayMs(1500);	
	
	/*��Ƶ��ʼ��*/
	PICC_vRC523SpiInit();
	SYSTICK_DelayMs(100);	
	PICC_u8PcdInit(); 
	
	/*�����*/
	LEDSEG_Init();
	



	
	uiTick[0] = SYS_GetTickCount();  //TCP
	
	for(i = 1; i < 5; i++)
	{
		LEDSEG_Display(i, 8, 3);
	}
	LEDSEG_ModeSelect(0);
	
	/*����ָʾ����*/
	LED_Display(LED_BLUE,   LED_ON);
	LED_Display(LED_YELLOW, LED_ON);
	LED_Display(LED_GREEN,  LED_ON);
	LED_Display(LED_RED,    LED_ON);
	
	while(1)
	{
		
		ucKeyValue = SYS_ReadKey();
        switch(ucKeyValue)
        {
            case KEY_CANCEL:  
				
				SendToPC((uchar *)"��ʼ����ʱ��:", 1, 0 ,DISP_CENTER | DISP_CLRSCR);
				SYS_DisplayCE(g_ucDispDayChar, 3, 0, DISP_POSITION  );				
				SYS_DisplayCE(aucDispTimeChar, 3, 0,  DISP_RIGHT);
				
				/*��ȡϵͳʱ��*/
				SYS_GetSysDateTime(&g_DateTime); //���ϵͳʱ��
				sprintf((char*)g_ucDispDayChar,"%2d��%2d��", g_DateTime.usMonth, g_DateTime.usDay);
				SYS_DisplayCE(g_ucDispDayChar, 7, 0, DISP_POSITION  );
				switch(g_DateTime.usDayOfWeek)
				{
					case 0: sprintf((char*)aucDispTimeChar, "������%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
					break;
					case 1: sprintf((char*)aucDispTimeChar, "����һ%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
					break;
					case 2: sprintf((char*)aucDispTimeChar, "���ڶ�%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
					break;
					case 3: sprintf((char*)aucDispTimeChar, "������%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
					break;
					case 4: sprintf((char*)aucDispTimeChar, "������%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
					break;
					case 5: sprintf((char*)aucDispTimeChar, "������%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
					break;
					case 6: sprintf((char*)aucDispTimeChar, "������%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);
					break;
					default:sprintf((char*)aucDispTimeChar, "������%2d:%02d", g_DateTime.usHour, g_DateTime.usMinute);	
				}
				
				
				SendToPC((uchar *)"��������ʱ��:", 5, 0 ,DISP_CENTER); 
				SYS_DisplayCE(aucDispTimeChar, 7, 0,  DISP_RIGHT);
                SYSTICK_DelayMs(3000);
//                LCD_Clrscr();
				g_laohua_sign = 0;
				
				/*�رղ���*/
				TCP_SetCallBackFlag(0);  //�ر�TCP����
					/*����ָʾ����*/
				LED_Display(LED_BLUE,   LED_OFF);
				LED_Display(LED_YELLOW, LED_OFF);
				LED_Display(LED_GREEN,  LED_OFF);
				LED_Display(LED_RED,    LED_OFF);
				LEDSEG_ModeSelect(1);  //����ʾ
                return;  
            default:				
				break;
        }

			if(2000 < (SYS_GetTickCount() - uiTick[0]))  //20s
			{
				TCP_QuerySignal(Signal);
				TCP_QueryIPAdd(IPAdd);
				TCP_QueryConnectionSchedule(Schedule);

				if(0 == LANGUAGE)
				{  
					sprintf(sprintfBUFF1,"�ź�ǿ��:%d", Signal[0]);
				}
				else if(1 == LANGUAGE)
				{
					sprintf(sprintfBUFF1,"CSQ:%d", Signal[0]);
				}
				
				SendToPC((uchar *)sprintfBUFF1, 1, 0 , DISP_POSITION | DISP_CLRSCR); 
				
				if(0 == LANGUAGE)
				{  
					sprintf(sprintfBUFF2,"�������ӽ���:%d", Schedule[0]);
				}
				else if(1 == LANGUAGE)
				{
					sprintf(sprintfBUFF2,"Progress bar:%d", Schedule[0]);
				}
				SendToPC((uchar *)sprintfBUFF2, 3, 0 , DISP_POSITION | DISP_CLRLINE);
				uiTick[0] = SYS_GetTickCount();  //TCP
				
			}
			
			if(100 < (SYS_GetTickCount() - uiTick[1] ))  //1s
			{
				uiTick[1] = SYS_GetTickCount();			
//				GPS_QueryLaLO(Latitude, Longitude, Time, SateNumber);  //�������⣬GPS���ݿ��Բ���ȡ
//				Time[12] = 0;
//				if(0 == LANGUAGE)
//				{  
//					sprintf(sprintfBUFF1,"����:%08f", Longitude[0]);
//					SendToPC((uchar *)sprintfBUFF1, 1, 0 , DISP_POSITION | DISP_CLRSCR); 
//					memset(sprintfBUFF1, 0, 50);
//					sprintf(sprintfBUFF2,"γ��:%08f", Latitude[0]);
//					SendToPC((uchar *)sprintfBUFF2, 3, 0 , DISP_POSITION | DISP_CLRLINE);
//					memset(sprintfBUFF1, 0, 50);
//					sprintf(sprintfBUFF3,"ʱ��:20%s", Time);
//					SendToPC((uchar *)sprintfBUFF3, 5, 0 , DISP_POSITION | DISP_CLRLINE);
//					memset(sprintfBUFF1, 0, 50);
//				}
//				else if(1 == LANGUAGE)
//				{
//					sprintf(sprintfBUFF1,"lon:%08f", Longitude[0]);
//					SendToPC((uchar *)sprintfBUFF1, 1, 0 , DISP_POSITION | DISP_CLRSCR); 
//					memset(sprintfBUFF1, 0, 50);
//					sprintf(sprintfBUFF2,"Lat:%08f", Latitude[0]);
//					SendToPC((uchar *)sprintfBUFF2, 3, 0 , DISP_POSITION | DISP_CLRLINE);
//					memset(sprintfBUFF1, 0, 50);
//					sprintf(sprintfBUFF3,"Time:20%s", Time);
//					SendToPC((uchar *)sprintfBUFF3, 5, 0 , DISP_POSITION | DISP_CLRLINE);
//					memset(sprintfBUFF1, 0, 50);
//				}
			}
			
			/*��Ƶ*/
			
			
			temp=PICC_u8PowerON(atr,&ATRlen);
			 if(temp==1)
			 {
				temp=PICC_u8GetPiccType();
				if(temp)SYS_Beep(200); 
				switch(temp)
				{
					
					case 0x00:
						if(0 == LANGUAGE)
						{  
							SendToPC((uchar*)"�޿�", 7, 0,DISP_CENTER | DISP_CLRLINE);
						}
						else if(1 == LANGUAGE)
						{
							SendToPC((uchar*)"No card!", 7, 0,DISP_CENTER | DISP_CLRLINE);
						}
						
						break;
					case 0x11:
						if(0 == LANGUAGE)
						{  
							SendToPC((uchar*)"�����ͣ� A", 5, 0, DISP_CENTER | DISP_CLRLINE);
							PICC_u8GetPiccUid(UID);
							sprintf((char*)info,"���ţ�%02x%02x%02x%02x", UID[1],UID[2],\
																		  UID[3],UID[4]);
							SendToPC(info, 7, 0, DISP_CENTER | DISP_CLRLINE);
						}
						else if(1 == LANGUAGE)
						{
							SendToPC((uchar*)"Card type�� A", 5, 0, DISP_CENTER | DISP_CLRLINE);
							PICC_u8GetPiccUid(UID);
							sprintf((char*)info,"Num��%02x%02x%02x%02x", UID[1],UID[2],\
																		UID[3],UID[4]);
							SendToPC(info, 7, 0, DISP_CENTER | DISP_CLRLINE);
						}
						
																 
						for(i=0;i<ATRlen;i++)
						{
							sprintf((char*)(info+2*i),"%02x",atr[i]);
						}	
						SendToPC(info,7, 0, DISP_CENTER | DISP_CLRLINE);
						break;
					case 0x21:
						if(0 == LANGUAGE)
						{  
							SendToPC((uchar*)"�����ͣ� B",5,0,DISP_CENTER | DISP_CLRLINE);
							PICC_u8GetPiccUid(UID);
							sprintf((char*)info,"���ţ�%02x%02x%02x%02x",UID[1],UID[2],\
																		 UID[3],UID[4]);
							SendToPC(info,7,0,DISP_CENTER|DISP_CLRLINE);		
						}
						else if(1 == LANGUAGE)
						{
							SendToPC((uchar*)"Card type�� B",5,0,DISP_CENTER | DISP_CLRLINE);
							PICC_u8GetPiccUid(UID);
							sprintf((char*)info,"Num��%02x%02x%02x%02x",UID[1],UID[2],\
																		UID[3],UID[4]);
							SendToPC(info,7,0,DISP_CENTER|DISP_CLRLINE);		
						}
						
						
						for(i=0;i<ATRlen;i++)
						{
							sprintf((char*)(info+2*i),"%02x",atr[i]);
						}	
						SendToPC(info,7,0,DISP_CENTER | DISP_CLRLINE);							
						break;
					case 0x1f:
						if(0 == LANGUAGE)
						{  
							SendToPC((uchar*)"������:M1+CPU",5,0,DISP_CENTER | DISP_CLRLINE);
							PICC_u8GetPiccUid(UID);
							sprintf((char*)info, "���ţ�%02x%02x%02x%02x", UID[1], UID[2],\
																		   UID[3],UID[4]);
							SendToPC(info, 7, 0, DISP_CENTER|DISP_CLRLINE);				
						}
						else if(1 == LANGUAGE)
						{
							SendToPC((uchar*)"Card type:M1+CPU",5,0,DISP_CENTER | DISP_CLRLINE);
							PICC_u8GetPiccUid(UID);
							sprintf((char*)info, "Num��%02x%02x%02x%02x", UID[1], UID[2],\
																		  UID[3],UID[4]);
							SendToPC(info, 7, 0, DISP_CENTER|DISP_CLRLINE);		
						}
						
						for(i=0;i<ATRlen;i++)
						{
							sprintf((char*)(info+2*i), "%02x", atr[i]);
						}	
						SendToPC(info,7,0,DISP_CENTER|DISP_CLRLINE);							
						break;	
					case 0x13:

						SendToPC((uchar*)"M1 S50",7, 0, DISP_CENTER | DISP_CLRLINE);

						
						break;
					case 0x14:
						SendToPC((uchar*)"M1 S70",7, 0, DISP_CENTER | DISP_CLRLINE);
						break;
					default:break;
					
				}
			 }
	}
}




