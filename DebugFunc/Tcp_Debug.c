#include <stdio.h>	
#include <stdlib.h>	
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
#include "tcp.h"
#include "com.h"

#include "mifare1_operate.h"
#include "rc523_driver.h"
#include "picc_rc523_lib.h"

void Uart_SetSysDebug(uchar);
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern uchar LANGUAGE;
extern uchar TCP_Production_Evaluation(void);
void TCP_Debug(void)
{
//	if(1) //��Ƶ���������
//	{
		uchar i;
		uchar ATRlen;
		uchar UID[12],atr[32];
		uchar info[32];
//	}
	
	/*���ڲ�������*/
//	char BUFF[50] = {0};
	
	/*����IP�Ͷ˿�*/
	uint count = 0;
	uchar ucKeyValue = KEY_NONE;
	uchar PORT[10] = {0}; //
	/*End*/
	
	uchar temp = 0xFF;
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
	uint puiRecLen = 10;
	uchar acRecBuff[500]={0};
	uchar acRecBuff1[500]={0};
	char sprintfBUFF1[50] = {0};
	char sprintfBUFF2[50] = {0};
	char sprintfBUFF3[50] = {0};
	char sprintfBUFF4[50] = {0};
	uint RecLen = 0;
	char aa[10] = {"0123456789"};
	uint uiTick;
	uiTick = SYS_GetTickCount();
	
	if(0) //��Ƶ���������
	{
		PICC_vRC523SpiInit();
		SYSTICK_DelayMs(100);	
		PICC_u8PcdInit(); 
	}

	Uart_SetTCPDebug(1);
	Uart_SetSysDebug(1);     //ϵͳ��ӡ����
	TCP_QueryConnectionSchedule(Schedule);
	if(100 == Schedule[0]) //����������
	{
		goto TCP_Schedule_100;
	}
	TCP_Connection_Time_MAX(60*2);
	TCP_NetworkPara_Set(APN, user, pwd, (uchar*)Type, Number, (uchar*)IP, Port);
//	TCP_Init();
//	TCP_Reconnection();
	TCP_SetCallBackFlag(0);  //�Ȳ�����
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"���ò����밴1", 1, 0, DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar *)"�����ò����밴2", 3, 0, DISP_POSITION | DISP_CLRLINE);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"Set Enter 1", 1, 0, DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar *)"Not set Enter 2", 3, 0, DISP_POSITION | DISP_CLRLINE);
	}


	while(1)
	{
		ucKeyValue =  SYS_ReadKey();   
		if(KEY_1 == ucKeyValue)	
		{
			break;
		}
		if(KEY_2 == ucKeyValue)	
		{
			TCP_SetCallBackFlag(1);
			goto TCP_Debug_1;
		}
		
	}
	
	{//���û������� ,�粻�����ã� ��һ�ο���ע�͵�����Ӱ��������С�
			TCP_SetCallBackFlag(0);  //�ؽ���
			SYS_CLS();
			if(0 == LANGUAGE)
			{  
				SendToPC((uchar *)"������IP( F1 = . ):", 1, 0, DISP_POSITION | DISP_CLRSCR);
			}
			else if(1 == LANGUAGE)
			{
				SendToPC((uchar *)"Enter IP( F1 = . ):", 1, 0, DISP_POSITION | DISP_CLRSCR);
			}
			
//			SendToPC((uchar *)"               ", 3, 0 , DISP_POSITION);
			memset(IP,0,sizeof(IP));
			do
			{
				ucKeyValue =  SYS_ReadKey();  
				if((ucKeyValue >= KEY_0)&&( ucKeyValue <= KEY_9))	
				{
					IP[count]= ucKeyValue ;					
					SendToPC((uchar*)IP, 3, 0, DISP_POSITION | DISP_CLRLINE) ;	
					count++; 
				}
				if(ucKeyValue == KEY_F1)
				{
					 IP[count]= '.';
					 SendToPC((uchar*)IP, 3, 0, DISP_POSITION | DISP_CLRLINE) ;
					 count++;
				}
				if(ucKeyValue == KEY_CLEAR)
				{
					memset(IP,0,sizeof(IP));
					count = 0;
					SendToPC((uchar *)"                 ", 3, 0 ,DISP_POSITION | DISP_CLRLINE);	
				}
				if(ucKeyValue == KEY_CANCEL)
				{
					TCP_SetCallBackFlag(0);
					if(0 == LANGUAGE)
					{  
						SendToPC((uchar *)"�˳�����", 5, 0 ,DISP_CENTER); 
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Exit test", 5, 0 ,DISP_CENTER); 
					}
					
					SYSTICK_DelayMs(1000);
					SYS_CLS();
					return;
				}				
			}while((ucKeyValue != KEY_RETURN) && (15 > count));
			
			if(0 == LANGUAGE)
			{  
				SendToPC((uchar *)"������˿ں�:", 5, 0, DISP_POSITION | DISP_CLRLINE);
			}
			else if(1 == LANGUAGE)
			{
				SendToPC((uchar *)"Enter port number:", 5, 0, DISP_POSITION | DISP_CLRLINE);
			}
			
//			SendToPC((uchar *)"             ", 7, 0 , DISP_POSITION | DISP_CLRLINE);
			
			memset(PORT,0,sizeof(PORT));
			count = 0;
			do
			{
				ucKeyValue =  SYS_ReadKey();  
				if((ucKeyValue >= KEY_0)&&( ucKeyValue <= KEY_9))	
				{
					PORT[count]= ucKeyValue ;
					SendToPC((uchar*)PORT, 7, 0, DISP_POSITION | DISP_CLRLINE) ;	
					count++; 
				}
				if(ucKeyValue == KEY_F1)
				{
					 PORT[count]= '.';
					 SendToPC((uchar*)PORT, 7, 0, DISP_POSITION | DISP_CLRLINE) ;
					 count++;
				}
				if(ucKeyValue == KEY_CLEAR)
				{
					memset(PORT,0,sizeof(PORT));
					count = 0;
					SendToPC((uchar *)"               ", 7, 0 ,DISP_POSITION | DISP_CLRLINE);	
				}
				if(ucKeyValue == KEY_CANCEL)
				{
					TCP_SetCallBackFlag(0);
					if(0 == LANGUAGE)
					{  
						SendToPC((uchar *)"�˳�����", 5, 0 ,DISP_CENTER); 
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Exit test", 5, 0 ,DISP_CENTER); 
					}
					
					SYSTICK_DelayMs(1000);
					SYS_CLS();
					return;
				}				
			}while((ucKeyValue != KEY_RETURN) && (10 > count));
			
			Port = atof((char*)PORT);    //�ַ���ת��������	
			TCP_NetworkPara_Set(APN, user, pwd, (uchar*)Type, Number, (uchar*)IP, Port);
			TCP_SetCallBackFlag(1); //������
	}
	TCP_Debug_1:
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar*)"���Կ�ʼ", 1, 0 , DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"��ȴ���������...", 3, 0 , DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"��ȡ�����˳�����", 5, 0 , DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar *)"����ʱ��F1��λ", 7, 0, DISP_POSITION | DISP_CLRLINE);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar*)"Test start", 1, 0 , DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"connection...", 3, 0 , DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"cancel-to exit", 5, 0 , DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar *)"F1-reset", 7, 0, DISP_POSITION | DISP_CLRLINE);
	}

	SYSTICK_DelayMs(1500);
	
	/*���ڲ�������*/
//	while(1)
//	{
//		TCP_QuerySignal(Signal);
//		SYSTICK_DelayMs(1000);
//		sprintf(BUFF,"Signal:%d",Signal[0]);
//		SYS_DisplayCE((uchar*)BUFF,5,0,DISP_CENTER | DISP_CLRLINE);	  //����|�����ǰ��	
//	}
	
	network_connections:
	while(1)
	{
					if(0) //��Ƶ���������
					{
					temp=PICC_u8PowerON(atr,&ATRlen);
					 if(temp==1)
					 {
					 	temp=PICC_u8GetPiccType();
						switch(temp)
						{
							case 0x00:
								if(0 == LANGUAGE)
								{  
									SendToPC((uchar*)"�޿�", 3, 0,DISP_POSITION | DISP_CLRLINE);
								}
								else if(1 == LANGUAGE)
								{
									SendToPC((uchar*)"No card!", 3, 0,DISP_POSITION | DISP_CLRLINE);
								}
								
								break;
							case 0x11:
								if(0 == LANGUAGE)
								{  
									SendToPC((uchar*)"�����ͣ� A", 3, 0, DISP_POSITION | DISP_CLRLINE);
									PICC_u8GetPiccUid(UID);
									sprintf((char*)info,"���ţ�%02x%02x%02x%02x", UID[1],UID[2],\
																				  UID[3],UID[4]);
									SendToPC(info, 5, 0, DISP_POSITION | DISP_CLRLINE);
								}
								else if(1 == LANGUAGE)
								{
									SendToPC((uchar*)"Card type�� A", 3, 0, DISP_POSITION | DISP_CLRLINE);
									PICC_u8GetPiccUid(UID);
									sprintf((char*)info,"Num��%02x%02x%02x%02x", UID[1],UID[2],\
																			    UID[3],UID[4]);
									SendToPC(info, 5, 0, DISP_POSITION | DISP_CLRLINE);
								}
								
							                                       		 
								for(i=0;i<ATRlen;i++)
								{
									sprintf((char*)(info+2*i),"%02x",atr[i]);
								}	
								SendToPC(info,7, 0, DISP_POSITION | DISP_CLRLINE);
								break;
							case 0x21:
								if(0 == LANGUAGE)
								{  
									SendToPC((uchar*)"�����ͣ� B",3,0,DISP_POSITION | DISP_CLRLINE);
									PICC_u8GetPiccUid(UID);
									sprintf((char*)info,"���ţ�%02x%02x%02x%02x",UID[1],UID[2],\
																			     UID[3],UID[4]);
									SendToPC(info,5,0,DISP_POSITION|DISP_CLRLINE);		
								}
								else if(1 == LANGUAGE)
								{
									SendToPC((uchar*)"Card type�� B",3,0,DISP_POSITION | DISP_CLRLINE);
									PICC_u8GetPiccUid(UID);
									sprintf((char*)info,"Num��%02x%02x%02x%02x",UID[1],UID[2],\
																			    UID[3],UID[4]);
									SendToPC(info,5,0,DISP_POSITION|DISP_CLRLINE);		
								}
								
								
								for(i=0;i<ATRlen;i++)
								{
									sprintf((char*)(info+2*i),"%02x",atr[i]);
								}	
								SendToPC(info,7,0,DISP_POSITION | DISP_CLRLINE);							
								break;
							case 0x1f:
								if(0 == LANGUAGE)
								{  
									SendToPC((uchar*)"������:M1+CPU",3,0,DISP_POSITION | DISP_CLRLINE);
									PICC_u8GetPiccUid(UID);
									sprintf((char*)info, "���ţ�%02x%02x%02x%02x", UID[1], UID[2],\
																				   UID[3],UID[4]);
									SendToPC(info, 5, 0, DISP_POSITION|DISP_CLRLINE);				
								}
								else if(1 == LANGUAGE)
								{
									SendToPC((uchar*)"Card type:M1+CPU",3,0,DISP_POSITION | DISP_CLRLINE);
									PICC_u8GetPiccUid(UID);
									sprintf((char*)info, "Num��%02x%02x%02x%02x", UID[1], UID[2],\
																				  UID[3],UID[4]);
									SendToPC(info, 5, 0, DISP_POSITION|DISP_CLRLINE);		
								}
								
								for(i=0;i<ATRlen;i++)
								{
									sprintf((char*)(info+2*i), "%02x", atr[i]);
								}	
								SendToPC(info,7,0,DISP_POSITION|DISP_CLRLINE);							
								break;	
							case 0x13:

								SendToPC((uchar*)"M1 S50",3, 0, DISP_POSITION | DISP_CLRLINE);

								
								break;
							case 0x14:
								SendToPC((uchar*)"M1 S70",3, 0, DISP_POSITION | DISP_CLRLINE);
								break;
							default:break;
							
						}
					 }
					 else
					 {
					 	SYS_CLS();
					 }
				 }
		ucKeyValue = SYS_ReadKey();
		switch(ucKeyValue)
        {
            case KEY_CANCEL:  
				TCP_SetCallBackFlag(0);
				if(0 == LANGUAGE)
				{  
					SendToPC((uchar *)"�˳�����", 5, 0 ,DISP_CENTER); 
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"Exit test", 5, 0 ,DISP_CENTER); 
				}
                
                SYSTICK_DelayMs(1000);
                SYS_CLS();
                return; 
			case KEY_F1: 
				if(0 == LANGUAGE)
				{  
					SendToPC((uchar *)"��������", 1, 0 , DISP_POSITION | DISP_CLRSCR);
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"connection...", 1, 0 , DISP_POSITION | DISP_CLRSCR);
				}				
				
				TCP_NetworkPara_Set(APN, user, pwd, (uchar*)Type, Number, (uchar*)IP, Port);
				TCP_Connection_Time_MAX(60*2);
				TCP_Reconnection();
				break;
            default:				
				break;
        }
		SYSTICK_DelayMs(50);
		TCP_QuerySignal(Signal);
		TCP_QueryIPAdd(IPAdd);
		TCP_QueryConnectionSchedule(Schedule);
		if(100 < (SYS_GetTickCount() - uiTick ))  //1s
		{
			uiTick = SYS_GetTickCount();
			
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
				sprintf(sprintfBUFF2,"IP��ַ:");
			}
			else if(1 == LANGUAGE)
			{
				sprintf(sprintfBUFF2,"IP:");
			}
			
			SendToPC((uchar *)sprintfBUFF2, 3, 0 , DISP_POSITION | DISP_CLRLINE);
			
			sprintf(sprintfBUFF3,"%s/%d", IP,Port);
			SendToPC((uchar *)sprintfBUFF2, 5, 0 , DISP_POSITION | DISP_CLRLINE);
			
			if(0 == LANGUAGE)
			{  
				sprintf(sprintfBUFF4,"�������ӽ���:%d", Schedule[0]);
			}
			else if(1 == LANGUAGE)
			{
				sprintf(sprintfBUFF4,"Progress bar:%d", Schedule[0]);
			}
			
			SendToPC((uchar *)sprintfBUFF3, 7, 0 , DISP_POSITION | DISP_CLRLINE);

		}
		
//		Schedule[0] = 100;
		TCP_Schedule_100:
		if(100 == Schedule[0])
		{
			
			if(0 == LANGUAGE)
			{  
				SendToPC((uchar*)"�����ɹ�", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
				SendToPC((uchar*)"��0����", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
				SendToPC((uchar*)"��1��2|���͡�����", 5, 0 ,DISP_POSITION | DISP_CLRLINE);
				SendToPC((uchar*)"��3�˳�", 7, 0 ,DISP_POSITION | DISP_CLRLINE);
				SYSTICK_DelayMs(1000);
				
				if(!TCP_Production_Evaluation())
				{
					SendToPC((uchar*)"�źż��ϸ�", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
				}
				else{
					SendToPC((uchar*)"�źż�ⲻ�ϸ�", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
				}
			}
			else if(1 == LANGUAGE)
			{
				SendToPC((uchar*)"Connect successfully", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
				SendToPC((uchar*)"0-reconnection", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
				SendToPC((uchar*)"1��2|Send��Read", 5, 0 ,DISP_POSITION | DISP_CLRLINE);
				SendToPC((uchar*)"3 Exit test", 7, 0 ,DISP_POSITION | DISP_CLRLINE);
				
				SYSTICK_DelayMs(1000);
				
				if(!TCP_Production_Evaluation())
				{
					SendToPC((uchar*)"CSQ��Qualified", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
				}
				else{
					SendToPC((uchar*)"CSQ��Unqualified", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
				}
			}
			
			
			
			
			while(1)
			{
				SYS_PortReceive(1, acRecBuff,  puiRecLen);
				if(acRecBuff[0] == 0x30)
				{
					acRecBuff[0] = 0;
					{
						if(0 == LANGUAGE)
						{  
							SendToPC((uchar *)"��������", 1, 0 , DISP_POSITION | DISP_CLRSCR);
						}
						else if(1 == LANGUAGE)
						{
							SendToPC((uchar *)"connection...", 1, 0 , DISP_POSITION | DISP_CLRSCR);
						}
						
						TCP_NetworkPara_Set(APN, user, pwd, (uchar*)Type, Number, (uchar*)IP, Port);
						TCP_Reconnection();
						goto network_connections;
					}
				}
				if(acRecBuff[0] == 0x31)
				{
					acRecBuff[0] = 0;
					temp = TCP_SendNETData(strlen(aa), (uchar*)aa);
					if(0 == LANGUAGE)
					{  
						if(0 == temp) SendToPC((uchar *)"�������ݳɹ�", 1, 0 , DISP_POSITION | DISP_CLRSCR);
						else SendToPC((uchar *)"��������ʧ��", 1, 0 , DISP_POSITION | DISP_CLRSCR);
					}
					else if(1 == LANGUAGE)
					{
						if(0 == temp) SendToPC((uchar *)"Send OK", 1, 0 , DISP_POSITION | DISP_CLRSCR);
						else SendToPC((uchar *)"Send error", 1, 0 , DISP_POSITION | DISP_CLRSCR);
					}
					
					
				}
				if(acRecBuff[0] == 0x32)
				{
					acRecBuff[0] = 0;
					temp = TCP_RecvNETData(&RecLen, (uchar *)acRecBuff1, 80 );
					if(0 == LANGUAGE)
					{  
						SendToPC((uchar *)"��������", 1, 0 , DISP_POSITION | DISP_CLRSCR);
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Read...", 1, 0 , DISP_POSITION | DISP_CLRSCR);
					}
					
					Uart1_DumpData("NetRec<-",acRecBuff1,RecLen);
					memset(acRecBuff1,0,500);
					if(0 == LANGUAGE)
					{  
						if(0 == temp) SendToPC((uchar *)"�������ݳɹ�", 1, 0 , DISP_POSITION | DISP_CLRSCR);
						else SendToPC((uchar *)"��������ʧ��", 1, 0 , DISP_POSITION | DISP_CLRSCR);
					}
					else if(1 == LANGUAGE)
					{
						if(0 == temp) SendToPC((uchar *)"Read OK", 1, 0 , DISP_POSITION | DISP_CLRSCR);
						else SendToPC((uchar *)"Read error", 1, 0 , DISP_POSITION | DISP_CLRSCR);
					}
					
				}
				if(acRecBuff[0] == 0x33)
				{
					acRecBuff[0] = 0;
					TCP_SetCallBackFlag(0);
					if(0 == LANGUAGE)
					{  
						SendToPC((uchar *)"�˳�����", 5, 0 ,DISP_CENTER | DISP_CLRSCR); 
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Exit test", 5, 0 ,DISP_CENTER | DISP_CLRSCR); 
					}
					
					SYSTICK_DelayMs(1000);
					SYS_CLS();
					return; 

				}
				acRecBuff[0] = 0;
			}
		}
		      
	}
}
