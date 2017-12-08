
#include <stdio.h>	
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
#include "com.h"
#include "cpu.h"
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern uchar LANGUAGE;
void SAM_Menu()
{
	uchar Get_Random[5] = {0x00,0x84,0x00,0x00,0x08};
	uchar t_Buff[50] = {0};
	uchar CNT_Buff[30]={0};
//	char info[20]={0};
	uchar tmp;
	uint uLen; 
	uchar  ucKeyValue;	

	CPU_PortInit();
	
	SAM_Start:
	SendToPC((uchar *)"1 SAM1   2 SAM2 ",3,0,DISP_POSITION | DISP_CLRSCR);
	SendToPC((uchar *)"3 SAM3   4 SAM4 ",5,0,DISP_POSITION);
	SendToPC((uchar *)"5 SAM5          ",7,0,DISP_POSITION);
	
	while(1)
	{
		ucKeyValue =  SYS_ReadKey();
		switch(ucKeyValue)
		{
			case KEY_1:	

				SYS_CLS(); 
				if(0 == LANGUAGE)
				{			
					SendToPC((uchar *)"SIM1测试",1,0, DISP_CENTER | DISP_CLRSCR);
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"SAM1 Test",1,0, DISP_CENTER | DISP_CLRSCR);
				}
				CPU_PowerDown(CardType_SAM1);
				CPU_Detect(CardType_SAM1);
				tmp = CPU_ColdReset(CardType_SAM1,0, 0,CNT_Buff);
				if(tmp)
				{
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"复位失败！      ",3,0, DISP_CENTER | DISP_CLRLINE); 
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Reset failed",3,0, DISP_CENTER | DISP_CLRLINE);
					}					
												
				}
				else
				{
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"复位成功！",3,0,  DISP_CENTER | DISP_CLRLINE);
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Reset success!",3,0,  DISP_CENTER | DISP_CLRLINE);
					}
					
				}
				uLen = sizeof(Get_Random);
				memcpy (t_Buff, Get_Random, uLen);
				tmp = CPU_Command(CardType_SAM1, &uLen, t_Buff);
				if(!tmp)
				{ 
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"取随机数成功!   ",5,0,  DISP_CENTER | DISP_CLRLINE);
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Get  numbers,OK",5,0,  DISP_CENTER | DISP_CLRLINE);
					}					
					
				}
				SYSTICK_DelayMs(1000);
				SYS_CLS();	
				goto SAM_Start;				
			case KEY_2:
            	SYS_CLS(); 		
				if(0 == LANGUAGE)
				{			
					SendToPC((uchar *)"SIM2测试",1,0, DISP_CENTER | DISP_CLRSCR);
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"SAM1 Test",1,0, DISP_CENTER | DISP_CLRSCR);
				}
				CPU_PowerDown(CardType_SAM2);
				CPU_Detect(CardType_SAM2);
				tmp = CPU_ColdReset(CardType_SAM2,0,0,CNT_Buff);
				if(tmp)
				{	
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"复位失败！      ",3,0, DISP_CENTER | DISP_CLRLINE); 
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Reset failed",3,0, DISP_CENTER | DISP_CLRLINE);
					}					
				}
				else
				{
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"复位成功！",3,0,  DISP_CENTER | DISP_CLRLINE);
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Reset success!",3,0,  DISP_CENTER | DISP_CLRLINE);
					}
				}
				uLen = sizeof(Get_Random);
				memcpy (t_Buff, Get_Random, uLen);
				tmp = CPU_Command(CardType_SAM2, &uLen, t_Buff);
				if(!tmp)
				{
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"取随机数成功!   ",5,0,  DISP_CENTER | DISP_CLRLINE);
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Get  numbers,OK",5,0,  DISP_CENTER | DISP_CLRLINE);
					}				 
				}
				SYSTICK_DelayMs(1000);
				SYS_CLS();
				goto SAM_Start;		
			case KEY_3:
            	SYS_CLS(); 		
				if(0 == LANGUAGE)
				{			
					SendToPC((uchar *)"SIM3测试",1,0, DISP_CENTER | DISP_CLRSCR);
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"SAM1 Test",1,0, DISP_CENTER | DISP_CLRSCR);
				}
				CPU_PowerDown(CardType_SAM3);
				CPU_Detect(CardType_SAM3);
				tmp = CPU_ColdReset(CardType_SAM3,0,0,CNT_Buff);
				if(tmp)
				{	
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"复位失败！      ",3,0, DISP_CENTER | DISP_CLRLINE); 
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Reset failed",3,0, DISP_CENTER | DISP_CLRLINE);
					}
	 					
				}
				else
				{
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"复位成功！",3,0,  DISP_CENTER | DISP_CLRLINE);
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Reset success!",3,0,  DISP_CENTER | DISP_CLRLINE);
					} 
				}
				uLen = sizeof(Get_Random);
				memcpy (t_Buff, Get_Random, uLen);
				tmp = CPU_Command(CardType_SAM3, &uLen, t_Buff);
				if(!tmp)
				{
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"取随机数成功!   ",5,0,  DISP_CENTER | DISP_CLRLINE);
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Get  numbers,OK",5,0,  DISP_CENTER | DISP_CLRLINE);
					}				 
				}
				SYSTICK_DelayMs(1000);
				SYS_CLS();
				goto SAM_Start;		
			case KEY_4:
            	SYS_CLS(); 		
				if(0 == LANGUAGE)
				{			
					SendToPC((uchar *)"SIM4测试",1,0, DISP_CENTER | DISP_CLRSCR);
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"SAM1 Test",1,0, DISP_CENTER | DISP_CLRSCR);
				}
				CPU_PowerDown(CardType_SAM4);
				CPU_Detect(CardType_SAM4);
				tmp = CPU_ColdReset(CardType_SAM4,0,0,CNT_Buff);
				if(tmp)
				{	
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"复位失败！      ",3,0, DISP_CENTER | DISP_CLRLINE); 
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Reset failed",3,0, DISP_CENTER | DISP_CLRLINE);
					}
	 					
				}
				else
				{
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"复位成功！",3,0,  DISP_CENTER | DISP_CLRLINE);
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Reset success!",3,0,  DISP_CENTER | DISP_CLRLINE);
					}
				}
				uLen = sizeof(Get_Random);
				memcpy (t_Buff, Get_Random, uLen);
				tmp = CPU_Command(CardType_SAM4, &uLen, t_Buff);
				if(!tmp)
				{
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"取随机数成功!   ",5,0,  DISP_CENTER | DISP_CLRLINE);
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Get  numbers,OK",5,0,  DISP_CENTER | DISP_CLRLINE);
					} 
				}
				SYSTICK_DelayMs(1000);
				SYS_CLS();                                                                                                                                    
				goto SAM_Start;		
			case KEY_5:
            	SYS_CLS(); 		
				if(0 == LANGUAGE)
				{			
					SendToPC((uchar *)"SIM5测试",1,0, DISP_CENTER | DISP_CLRSCR);
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar *)"SAM1 Test",1,0, DISP_CENTER | DISP_CLRSCR);
				}
				CPU_PowerDown(CardType_SAM5);
				CPU_Detect(CardType_SAM5);
				tmp = CPU_ColdReset(CardType_SAM5,0,0,CNT_Buff);
				if(tmp)
				{	
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"复位失败！      ",3,0, DISP_CENTER | DISP_CLRLINE); 
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Reset failed",3,0, DISP_CENTER | DISP_CLRLINE);
					}
	 					
				}
				else
				{
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"复位成功！",3,0,  DISP_CENTER | DISP_CLRLINE);
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Reset success!",3,0,  DISP_CENTER | DISP_CLRLINE);
					}
				}
				uLen = sizeof(Get_Random);
				memcpy (t_Buff, Get_Random, uLen);
				tmp = CPU_Command(CardType_SAM5, &uLen, t_Buff);
				if(!tmp)
				{
					if(0 == LANGUAGE)
					{			
						SendToPC((uchar *)"取随机数成功!   ",5,0,  DISP_CENTER | DISP_CLRLINE);
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar *)"Get  numbers,OK",5,0,  DISP_CENTER | DISP_CLRLINE);
					}
				}
				SYSTICK_DelayMs(1000);
				SYS_CLS();
				goto SAM_Start;		
			default : break;
		}
		if(ucKeyValue == KEY_CANCEL)
		{
			return;
		}	
	}
}

void Contact_Debug(void)
{
	uchar  ucKeyValue;	
	
	SYS_CLS();
	if(0 == LANGUAGE)
	{			
		SendToPC((uchar *)"接触式测试", 1, 0, DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar *)"1.SAM卡测试", 3, 0, DISP_POSITION | DISP_CLRLINE);
		SendToPC((uchar *)"2.           ", 5, 0, DISP_POSITION | DISP_CLRLINE);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"Contact     TEST ", 1, 0, DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar *)"1.SAM card test", 3, 0, DISP_POSITION | DISP_CLRLINE);
		SendToPC((uchar *)"2.           ", 5, 0, DISP_POSITION | DISP_CLRLINE);
	}
	
	CPU_PortInit();	
	
	while(1)
	{
		ucKeyValue =  SYS_ReadKey();
		switch(ucKeyValue)
		{
			case KEY_1:	SAM_Menu();
			default : break;
		}
		if(ucKeyValue == KEY_CANCEL)
		{
			return;
		}
	}
		


	
	
}

