
#include <stdio.h>
#include <stdlib.h>	
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
#include "mifare1_operate.h"
#include "rc523_driver.h"
#include "picc_rc523_lib.h"
#include "com.h"
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern void Uart_SetSysDebug(uchar);
extern void COM1_SendHexByte(uchar ucHexData);
void Mifare1_Debug(void);
extern uchar  COM1_ReceiveData(uchar *pRecBuff , uint *uiRecLen , uint TimeOutMs);
extern uchar LANGUAGE;

extern void RF_APDU_SetTimeOut(unsigned int uiTimeOut);
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
void CatactlessCPU_Debug(void)
{
	uchar temp,i;
	uchar ATRlen;
	uchar UID[12],atr[32];
	uchar info[32];
	uchar ucKeyValue = KEY_NONE;
	uchar USB_RecBuff[512] = {0x00,0x84,0x00,0x00,0x08},
	USB_SendBuff[512];
//	uint USB_RecLen=5;
	ushort USB_SendLen;
	uchar mode=0;
//	uint puiRecLen = 0;
//	uchar acRecBuff[50]={0};
//	uint puiRecLen1 = 0;
//	uchar acRecBuff1[50]={0};
	
	PICC_vRC523SpiInit();
	SYSTICK_DelayMs(100);	
	PICC_u8PcdInit(); 
	SYS_CLS();
//	RF_APDU_SetTimeOut(3000); //ֻ�в��ֿ�֧�֡�
	while(1)
	{
		if(0 == LANGUAGE)
		{  
			SendToPC((uchar*)"1 �����Ͳ�ѯ",1,0,DISP_POSITION | DISP_CLRSCR);
			SendToPC((uchar*)"2 CPU��APDUָ��",3,0,DISP_POSITION | DISP_CLRLINE);  //0084000008
			SendToPC((uchar*)"3 M1������",5,0,DISP_POSITION | DISP_CLRLINE);  //0084000008
		}
		else if(1 == LANGUAGE)
		{
			SendToPC((uchar*)"1 Card type query",1,0,DISP_POSITION | DISP_CLRSCR);
			SendToPC((uchar*)"2 CPU APDU CMD",3,0,DISP_POSITION | DISP_CLRLINE);  //0084000008
			SendToPC((uchar*)"3 M1 TEST",5,0,DISP_POSITION | DISP_CLRLINE);  //0084000008
		}
		
		while(1)
		{
			ucKeyValue =  SYS_ReadKey();
			if(ucKeyValue==KEY_CANCEL)
			{
				SYS_USBDisconnection();
				PICC_vFieldOff();
				return ;
			}
			if(ucKeyValue==KEY_1)
			{
				mode = 1;
				SYS_CLS();
				if(0 == LANGUAGE)
				{  
					SendToPC((uchar*)"��ſ�", 1, 0,DISP_CENTER | DISP_CLRSCR);
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar*)"Put the card...", 1, 0,DISP_CENTER | DISP_CLRSCR);
				}
				
				break;
			}
			if(ucKeyValue==KEY_2)
			{
				mode = 2;
				SYS_CLS();
				if(0 == LANGUAGE)
				{  
					SendToPC((uchar*)"��ſ�", 1, 0,DISP_POSITION | DISP_CLRSCR); //ͨ��USB�����������ָ��
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar*)"Put the card...", 1, 0,DISP_CENTER | DISP_CLRSCR);
				}
				
				break;
			}
			if(ucKeyValue==KEY_3)
			{
				Mifare1_Debug();
				break;
			}			
		}
		while(mode)
		{	 
			ucKeyValue =  SYS_ReadKey();
			if(ucKeyValue==KEY_CANCEL)
			{
//				puiRecLen = 0;
//				memset(acRecBuff, 0, 50);
				mode =0;
				break ;
			}
			 switch(mode)
			 {
			 	case 1:
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
					 break;
				 case 2: 
//					 SYS_OpenPortExt(1,1000,115200, 2);
//					 while(1)
//					 {
//						COM1_ReceiveData(&acRecBuff[puiRecLen1] , &puiRecLen , 100);
//						if(0 != puiRecLen )
//						{						
//							puiRecLen1 += puiRecLen;
//							printf("\r\nRead:%c", acRecBuff[puiRecLen1 - 1]);
//							if(10 <= puiRecLen1) //0084000008
//							{							
//								memcpy(acRecBuff1, acRecBuff, puiRecLen1);
//								for(i = 0; i < puiRecLen1; i++)
//								{
//									COM1_SendHexByte(acRecBuff1[i]);
//								}
////								Uart1_DumpData("\r\nRead<-",acRecBuff1,puiRecLen1);
//								SYS_OpenPortExt(1,1000,115200,0);
//								mode = 3;
//								break;
//							}								
//						}
//						puiRecLen = 0;
//						
//					}
					mode = 3;
				 	break;
				case 3:
					Uart_SetSysDebug(1);
					if(1 == PICC_u8PowerON(atr, &ATRlen))
					{													
						temp=PICC_u8GetPiccType();
						if((temp==0x11)||(temp==0x21))
						{
							if(1 == PICC_u8PcdAPUDTcl(USB_RecBuff, 5, USB_SendBuff,&USB_SendLen))
							{
//								COM1_SendNBytes(USB_SendLen, USB_SendBuff);
								Uart1_DumpData("\r\nRead<-",USB_SendBuff, USB_SendLen);
								if((0x90 == USB_SendBuff[USB_SendLen - 2]) &&(0x00 == USB_SendBuff[USB_SendLen - 1]) )
								{//9000
									if(0 == LANGUAGE)
									{  
										SendToPC((uchar*)"APDUָ����Գɹ�", 1, 0 , DISP_POSITION | DISP_CLRSCR);
									}
									else if(1 == LANGUAGE)
									{
										SendToPC((uchar*)"APDU TEST OK", 1, 0 , DISP_POSITION | DISP_CLRSCR);
									}

									
									SYSTICK_DelayMs(1000);									  
									break;
								}
								else{
									if(0 == LANGUAGE)
									{  
										SendToPC((uchar*)"APDUָ�����ʧ��", 1, 0 , DISP_POSITION | DISP_CLRSCR);
									}
									else if(1 == LANGUAGE)
									{
										SendToPC((uchar*)"APDU TEST Error", 1, 0 , DISP_POSITION | DISP_CLRSCR);
									}
									
									SYSTICK_DelayMs(1000);									  
									break;
									
								}
							}
						}							
			
					}
					break;
				default:break;
				 }
			 }
		
		}
  }
uchar ucBuff[50] ={0};
uchar mode = 0;
uchar M1_Snr[10] = {0};




void Mifare1_Debug(void)
{
	uchar info[40]	= {0};
	uchar temp = 0;
	uchar point = 0;	 
	uchar i = 0;
	uchar pNum;
	uchar count = 0;
//	uint yuan = 0, jiao = 0, fen = 0;
	uint Wallet_Blance = 0;
	uint Pay = 0;
	float a = 0;
	uchar Payment[10] ={0};
	uchar ucKeyValue = KEY_NONE; 


	PICC_vRC523SpiInit();
	SYSTICK_DelayMs(100);
	PICC_vRC523RstInit();
	SYSTICK_DelayMs(100); 
	PICC_vFieldOff();
    SYSTICK_DelayMs(100);
	SYS_CLS();
M1StarPostion:
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"1 ��ֵ    2 �۷�",1,0,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar *)"3 ����ѯ",3,0, DISP_POSITION | DISP_CLRLINE);
		SendToPC((uchar *)"4 ��ʼ��Ǯ��",5,0, DISP_POSITION | DISP_CLRLINE);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"1 Recharge 2 chargeback",1,0,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar *)"3 Check the balance",3,0, DISP_POSITION | DISP_CLRLINE);
		SendToPC((uchar *)"4 Init Wallet",5,0, DISP_POSITION | DISP_CLRLINE);
	}
	
	while(1)
	{	
		ucKeyValue =  SYS_ReadKey();
		if(ucKeyValue == KEY_CANCEL)
		{
			PICC_vFieldOff();
		    SYSTICK_DelayMs(100);
			return ;
		}
		switch(ucKeyValue)
		{
			case KEY_1:
				mode = 1;
				break;
			case KEY_2:
			    mode = 2;
				break;
			case KEY_3:
				mode = 3;
				break;
			case KEY_4:
				mode = 4;
				break;
			default :
				mode=0 ;
				break ;
		}
		if((mode==1)||(mode==2))
		{
			SYS_CLS();
			if(0 == LANGUAGE)
			{  
				SendToPC((uchar *)"������(F1=.)��", 1, 0, DISP_POSITION | DISP_CLRSCR);
				SendToPC((uchar *)"        Ԫ     ", 3, 0 , DISP_POSITION);
			}
			else if(1 == LANGUAGE)
			{
				SendToPC((uchar *)"money(F1=.)��", 1, 0, DISP_POSITION | DISP_CLRSCR);
				SendToPC((uchar *)"        ��     ", 3, 0 , DISP_POSITION);
			}
			

			memset(Payment,0,sizeof(Payment));
			i = 0;
			count = 0;
			point = 0; 		
			do
			{
				ucKeyValue =  SYS_ReadKey();  
				if((ucKeyValue >= KEY_0)&&( ucKeyValue <= KEY_9)&&(i < 6))	
				{
					if((point==0)&&(count<3))		  //С���㻹û����,������λΪ��
					 {
					 	 Payment[i]= ucKeyValue ;
						 SendToPC(Payment, 3, 56-count*8, DISP_POSITION | DISP_CLRLINE) ;	
						 count++;
						 i++;
					 }
					if((point==1)&&(pNum < 2))
					{
						Payment[i]= ucKeyValue ;
						SendToPC(Payment, 3, 56-count*8, DISP_POSITION | DISP_CLRLINE) ;	
						count++;
						pNum++;
						i++;	
					}	 
				}
				if((ucKeyValue == KEY_F1)&&(point==0))
				{
					 Payment[i]= '.';
					 SendToPC(Payment, 3, 56-count*8, DISP_POSITION | DISP_CLRLINE) ;
					 count++;
					 point = 1;		 //С�����־λ
					 pNum = 0;
					 i++;
				}
				if(ucKeyValue == KEY_CLEAR)
				{
					memset(Payment,0,sizeof(Payment));
					i = 0;
					count = 0;
					SendToPC((uchar *)"       ��     ", 3, 0 ,DISP_POSITION | DISP_CLRLINE);	
				}					
			}while((ucKeyValue != KEY_RETURN)&&(ucKeyValue != KEY_CANCEL));
			if(ucKeyValue == KEY_CANCEL)
			{
				SYS_CLS();
				PICC_vFieldOff();
    			SYSTICK_DelayMs(100);
				continue;	
			}
			Pay = atof((char*)Payment)*100;    //�ַ���ת��������		  	
			SYS_CLS();
			if(0 == LANGUAGE)
			{  
				SendToPC((uchar *)"     ��ˢ��     ", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
			}
			else if(1 == LANGUAGE)
			{
				SendToPC((uchar *)" Credit card ", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
			}			
			
							  
	 	}
		 if((mode == 3)||(mode == 4))
		 {
		    SYS_CLS();
			if(0 == LANGUAGE)
			{  
				SendToPC((uchar *)"     ��ˢ��     ", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
			}
			else if(1 == LANGUAGE)
			{
				SendToPC((uchar *)" Credit card ", 1, 0 ,DISP_POSITION | DISP_CLRSCR);
			}

		 }

	
		while(mode)
		{ 
			memset(M1_Snr,0,10);	      //�����������Ļ��棬������һ�εĻ�����ű��β���
			a = 0;
			ucKeyValue =  SYS_ReadKey();
			if(ucKeyValue == KEY_CANCEL) 
			{
				PICC_vFieldOff();
			    SYSTICK_DelayMs(100);
				break;		
			}
		   	temp=MIFARE1_Request();
			if(temp != MI_OK)
			{	
				continue ; 		
			}
			temp=MIFARE1_Anticoll(SELECT_CASCADE_LEVEL_1, M1_Snr); 
			if(temp != MI_OK)
			{
				continue ; 		
			}
			temp = MIFARE1_Select(SELECT_CASCADE_LEVEL_1, M1_Snr);
			if(temp != MI_OK)
			{  		
				continue ; 		
			}
			if(0 == LANGUAGE)
			{  
				sprintf((char*)info,"���ţ�%02x%02x%02x%02x",M1_Snr[0],M1_Snr[1],\
			                                       		     M1_Snr[2],M1_Snr[3]);
			}
			else if(1 == LANGUAGE)
			{
				sprintf((char*)info,"Number��%02x%02x%02x%02x",M1_Snr[0],M1_Snr[1],\
															   M1_Snr[2],M1_Snr[3]);
			}
			
			SendToPC(info,1, 2, DISP_POSITION | DISP_CLRSCR);
			MIFARE1_LoadKey(PICC_AUTHENT1A,0, 8, (uchar*)"\xff\xff\xff\xff\xff\xff");
			temp = MIFARE1_Authent(PICC_AUTHENT1A, M1_Snr, 0, 8);	
			if(temp == MI_OK )
			{
				switch(mode)
				{
					case 1:	 
						temp = MIFARE1_IncWallet(8, Pay);
						if(temp == MI_OK)
						{
							if(0 == LANGUAGE)
							{  
								SendToPC((uchar *)"��ֵ�ɹ�", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
							}
							else if(1 == LANGUAGE)
							{
								SendToPC((uchar *)"Recharge successfully", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
							}
							
							MIFARE1_ReadWallet(8,&Wallet_Blance);
							a = (float)Wallet_Blance/100;
							if(0 == LANGUAGE)
							{  
								sprintf((char*)(info),"����%0.2fԪ",a);			
							}
							else if(1 == LANGUAGE)
							{
								sprintf((char*)(info),"balance��%0.2F��",a);					
							}
												
							SendToPC(info, 5, 0 ,DISP_POSITION | DISP_CLRLINE);
							SYS_BeepCtrl(ON, 500);
							SYSTICK_DelayMs(2000);
							PICC_vFieldOff();   //�ر����ߣ����ڽ���Ӧ��������Ҫ							
							mode = 0;
							break;
						}
						else
						{
							if(0 == LANGUAGE)
							{  
								SendToPC((uchar *)"��ֵʧ��", 3, 0,DISP_POSITION | DISP_CLRLINE);	
							}
							else if(1 == LANGUAGE)
							{
								SendToPC((uchar *)"Recharge failed", 3, 0,DISP_POSITION | DISP_CLRLINE);			
							}
							
							PICC_vFieldOff();   //�ر����ߣ����ڽ���Ӧ��������Ҫ
							SYS_BeepCtrl(ON, 500);
							SYSTICK_DelayMs(2000);
							mode = 0;
							break;
						}	
				
					case 2:
						MIFARE1_ReadWallet(8, &Wallet_Blance);
						if(Wallet_Blance<Pay)
						{
							if(0 == LANGUAGE)
							{  
								SendToPC((uchar *)"����", 3, 0,DISP_POSITION | DISP_CLRLINE );
								a = (float)Wallet_Blance/100;
								sprintf((char*)(info),"����%0.2fԪ",a);
							}
							else if(1 == LANGUAGE)
							{
								SendToPC((uchar *)"No money", 3, 0,DISP_POSITION | DISP_CLRLINE );
								a = (float)Wallet_Blance/100;
								sprintf((char*)(info),"balance��%0.2fԪ",a);			
							}
						   
							SendToPC(info, 5, 0,DISP_POSITION | DISP_CLRLINE );
							SYS_BeepCtrl(ON, 500);
							SYSTICK_DelayMs(2000);
							PICC_vFieldOff();							
							mode = 0;
							break;
						}		
						temp = MIFARE1_DecWallet(8, Pay);
						if(temp == MI_OK)
						{
							if(0 == LANGUAGE)
							{  
								SendToPC((uchar *)"�۷ѳɹ�", 3, 0,DISP_POSITION  | DISP_CLRLINE);
								a = (float)(Wallet_Blance-Pay)/100;
								sprintf((char*)(info),"����%0.2fԪ", a);
							}
							else if(1 == LANGUAGE)
							{
								SendToPC((uchar *)"Chargeback success", 3, 0,DISP_POSITION  | DISP_CLRLINE);
								a = (float)(Wallet_Blance-Pay)/100;
								sprintf((char*)(info),"balance��%0.2F��", a);		
							}
							
							SendToPC(info, 5, 0 ,DISP_POSITION);
							SYS_BeepCtrl(ON, 500);
							SYSTICK_DelayMs(2000);
							PICC_vFieldOff();
							mode = 0;
							break;
						}
						else
						{
							if(0 == LANGUAGE)
							{  
								SendToPC((uchar *)"�۷�ʧ��", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
							}
							else if(1 == LANGUAGE)
							{
								SendToPC((uchar *)"Fail!", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
							}
							
							PICC_vFieldOff();
							SYS_BeepCtrl(ON, 500);
							SYSTICK_DelayMs(2000);
							mode = 0;
							break;
						}
					case 3:					
						MIFARE1_ReadWallet(8, &Wallet_Blance);  						
						a = (float)Wallet_Blance/100;
						if(0 == LANGUAGE)
						{  
							sprintf((char*)(info), "����%0.2fԪ", a);
						}
						else if(1 == LANGUAGE)
						{
							sprintf((char*)(info), "balance��%0.2f��", a);
						}
						
						SendToPC(info, 3, 0 ,DISP_POSITION | DISP_CLRLINE);
						SYS_BeepCtrl(ON, 500);
//						yuan = Wallet_Blance/100;
//						jiao = (Wallet_Blance%100)/10;
//						fen =  Wallet_Blance%10;
						SYSTICK_DelayMs(3000);
						PICC_vFieldOff();   //�ر����ߣ����ڽ���Ӧ��������Ҫ						
						mode = 0;
						break;
					case 4:
						temp = MIFARE1_InitWallet(8,100);
						if(temp == MI_OK)
						{
							if(0 == LANGUAGE)
							{  
								SendToPC((uchar *)"��ʼ��Ǯ���ɹ�", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
							}
							else if(1 == LANGUAGE)
							{
								SendToPC((uchar *)"Init wallet OK��", 3, 0 ,DISP_POSITION | DISP_CLRLINE);
							}
							
							PICC_vFieldOff();   //�ر����ߣ����ڽ���Ӧ��������Ҫ
							SYS_BeepCtrl(ON, 500);
							SYSTICK_DelayMs(2000);
							mode = 0;
							break;
						}
						else
						{
							if(0 == LANGUAGE)
							{  
								SendToPC((uchar *)"��ʼ��Ǯ��ʧ��", 3, 0,DISP_POSITION | DISP_CLRLINE );
							}
							else if(1 == LANGUAGE)
							{
								SendToPC((uchar *)"Init wallet ERROR��", 3, 0,DISP_POSITION | DISP_CLRLINE );
							}
							
							PICC_vFieldOff();   //�ر����ߣ����ڽ���Ӧ��������Ҫ
							SYS_BeepCtrl(ON, 500);
							SYSTICK_DelayMs(2000);
							mode = 0;
							break;
						}
						default:break;
					}					
	  		} 	
			goto M1StarPostion;
		}
	}	 
}
