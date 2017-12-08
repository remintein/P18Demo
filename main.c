
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "system.h"
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h"
#include "auxio.h"
#include "com.h"
#include "wifi.h"
//#include "protocol.h"
#include "led_seg.h"
#include "tcp.h"
#include "gps.h"
#include "IrDA.h"
#include "QR_collection.h"
#include "gps.h"
#include "tts.h"

extern void	 DBMain_Demo(void);
extern int	 DBMain_Init(void);
extern void	 DBMain_Add_One_Record(uint);
extern void	 DBMain_Del_One_Record(void);
extern void	 DBMain_Find_One_Record(void);
extern void	 DBMain_Check_One_Record(void);
extern void	 DBMain_Check_Capacity(void);
extern void	 DBMain_Del_All_Record(void);
extern void	 DBMain_Check_Count(void);
extern void	 DBMain_Display_Record(uint);
extern short Input_Charnum(ushort minnum,ushort maxnum,uchar *retbuf);
extern short Input_Num(    ushort minnum,ushort maxnum,uchar *retbuf);
extern short Table_Match(void *rec);

extern void TTSInit(void);
extern void LCD_Debug(void);  
extern void LED_Debug(void);  
extern void KEY_Debug(void);  
extern void LEDSeg_Debug(void);  
extern void BEEP_Debug(void);  
extern void BT_Debug(void);  
extern void RTC_Debug(void);  
extern void Sound_Debug(void);
extern void TransMode_Debug(void);
extern void TCP_Debug(void);
extern void GPS_Debug(void);
extern void Contact_Debug(void);
extern void CatactlessCPU_Debug(void);
extern void  _2_4G_Debug(void);
extern void  Flash_Debug(void);
extern void QR_Debug(void);
extern void Version_Debug(void);
extern void IrDA_Debug(void);
extern void MxFlash_Debug(void);
extern void AUTO_Debug(void);
uchar LANGUAGE  = 0;
#define PAGE_MAXID  5
static uchar m_PageID   = 0; 
uchar  g_ucComState = 0;  //ͨѶ״̬��0-�����ݣ�1-���յ�USBЭ�����ݣ�2-���յ�����Э������ 3-��������
extern uint g_uiTime1Cnt;    //��ʱ��1����
extern uint g_uiComRecTime; 
//extern PROTOCOL_TypeDef * g_pstRecCmd;  //�����������
//extern PROTOCOL_TypeDef g_stRecProtocol, \
//						g_stSndProtocol;
uchar g_laohua_sign = 0;  //�ϻ���������־
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType)
{

    COM1_SendNBytes(strlen((char*)buff),buff);
    COM1_SendNBytes(2,(uchar *)"\r\n");
   
	SYS_DisplayCE(buff,ucRow,ucCol,uiDispType); 
}
extern uchar  Uart1_GetData_DMA(uint uiLen, uchar *acRecBuff1, uint time);
extern uchar Uart_SetSysDebug(uchar);
uchar  COM1_ReceiveData(uchar *pRecBuff , uint *uiRecLen , uint TimeOutMs)
{
	uint uiTick;
	uchar tmp;
	uint TmpLen = 0;
	uiTick = SYS_GetTickCount();
	
	while(SYS_GetTickCount() - uiTick < TimeOutMs)
	{	
		if(!Uart1_GetData_DMA(1,&tmp,10))
		{
			pRecBuff[TmpLen++] = tmp;
			while(!Uart1_GetData_DMA(1,&tmp,10))
			{
				pRecBuff[TmpLen++] = tmp;
			}
			*uiRecLen = TmpLen;
			return 0;
		}
	}
	
	return 2;
}

void App2_FirstMenu()
{

    COM1_SendNBytes(2,(uchar *)"\r\n");
	if(0 == LANGUAGE)
	{
		SendToPC((uchar *)"P18����ϵͳ",1,0,DISP_POSITION|DISP_CLRSCR);
		SendToPC((uchar *)"F1:����ϵͳ",3,0,DISP_POSITION);
		SendToPC((uchar *)"F2:���Ϸ�ҳ",5,0,DISP_POSITION);
		SendToPC((uchar *)"F3:���·�ҳ",7,0,DISP_POSITION);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"P18 DEMO",1,0,DISP_POSITION|DISP_CLRSCR);
		SendToPC((uchar *)"F1:RESET",3,0,DISP_POSITION);
		SendToPC((uchar *)"F2:PAGE UP",5,0,DISP_POSITION);
		SendToPC((uchar *)"F3:PAGE DOWN",7,0,DISP_POSITION);
	}
}
void App2_Page0Menu(void)
{

    COM1_SendNBytes(2,(uchar *)"\r\n");
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar *)"1 Һ������      ", 1,0,DISP_POSITION|DISP_CLRSCR);
		SendToPC((uchar *)"2 LED�Ʋ���     ", 3,0,DISP_POSITION);
		SendToPC((uchar *)"3 ����ܲ���    ", 5,0,DISP_POSITION);
		SendToPC((uchar *)"4 ��������      ", 7,0,DISP_POSITION);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"1 LCD     TEST ", 1,0,DISP_POSITION|DISP_CLRSCR);
		SendToPC((uchar *)"2 LED     TEST ", 3,0,DISP_POSITION);
		SendToPC((uchar *)"3 LEDSEG  TEST ", 5,0,DISP_POSITION);
		SendToPC((uchar *)"4 KEY     TEST ", 7,0,DISP_POSITION);
	}
}

void App2_Page1Menu(void)
{

    COM1_SendNBytes(2, (uchar*)"\r\n");
 	if(0 == LANGUAGE)
	{   
		SendToPC((uchar *)"1 ����������    ", 1,0,DISP_POSITION|DISP_CLRSCR);
		SendToPC((uchar *)"2 ��������      ", 3,0,DISP_POSITION);
		SendToPC((uchar *)"3 ʵʱʱ�Ӳ���  ", 5,0,DISP_POSITION);
		SendToPC((uchar *)"4 ͨѶ��ʽ����  ", 7,0,DISP_POSITION);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"1 BEEP     TEST ", 1,0,DISP_POSITION|DISP_CLRSCR);
		SendToPC((uchar *)"2 SOUND    TEST ", 3,0,DISP_POSITION);
		SendToPC((uchar *)"3 CLOCK    TEST ", 5,0,DISP_POSITION);
		SendToPC((uchar *)"4 COM_X    TEST ", 7,0,DISP_POSITION);
	}
}

void App2_Page2Menu(void)											  
{

    COM1_SendNBytes(2,(uchar *)"\r\n");
  	if(0 == LANGUAGE)
	{    
		SendToPC((uchar *)"1 ȫ��ͨ����      ", 1,0,DISP_POSITION|DISP_CLRSCR);
		SendToPC((uchar *)"2 GPS����		 ", 3,0,DISP_POSITION);  
		SendToPC((uchar *)"3 �������� 		 ", 5,0,DISP_POSITION);  
		SendToPC((uchar *)"4 �������		 ", 7,0,DISP_POSITION);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"1 LTE     TEST ", 1,0,DISP_POSITION|DISP_CLRSCR);
		SendToPC((uchar *)"2 GPS     TEST ", 3,0,DISP_POSITION);  
		SendToPC((uchar *)"3 BT      TEST ", 5,0,DISP_POSITION);  
		SendToPC((uchar *)"4 IrDA    TEST ", 7,0,DISP_POSITION);	
	}		
}
void App2_Page3Menu(void)
{

    COM1_SendNBytes(2,(uchar *)"\r\n");
  	if(0 == LANGUAGE)
	{    
		SendToPC((uchar *)"1 �Ӵ�ʽ������      ", 1,0,DISP_POSITION|DISP_CLRSCR);
		SendToPC((uchar *)"2 �ǽӴ�ʽ������ ", 3,0,DISP_POSITION);
		SendToPC((uchar *)"3 Flash����  ", 5,0,DISP_POSITION);
		SendToPC((uchar *)"4 2.4G����      ", 7,0,DISP_POSITION);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"1 Contact     TEST ", 1,0,DISP_POSITION|DISP_CLRSCR);
		SendToPC((uchar *)"2 Contactless TEST", 3,0,DISP_POSITION);
		SendToPC((uchar *)"3 Flash       TEST", 5,0,DISP_POSITION);
		SendToPC((uchar *)"4 2.4G        TEST", 7,0,DISP_POSITION);
	}		
}

void App2_Page4Menu(void)
{

    COM1_SendNBytes(2,(uchar *)"\r\n");
  	if(0 == LANGUAGE)
	{       
		SendToPC((uchar *)"1 ��ά�����      ", 1,0,DISP_POSITION|DISP_CLRSCR);
		SendToPC((uchar *)"2 ���� ", 3,0,DISP_POSITION);
		SendToPC((uchar *)"3 ����  ", 5,0,DISP_POSITION);
		SendToPC((uchar *)"4 �汾��Ϣ��ѯ    ", 7,0,DISP_POSITION);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"1 QR       TEST ", 1,0,DISP_POSITION|DISP_CLRSCR);
		SendToPC((uchar *)"2 ??       TEST ", 3,0,DISP_POSITION);
		SendToPC((uchar *)"3 ??       TEST ", 5,0,DISP_POSITION);
		SendToPC((uchar *)"4 Query version ", 7,0,DISP_POSITION);
	}
}
uchar App2_Page0Func(void)
{
    uchar ucKeyValue =KEY_NONE;
    App2_Page0Menu();
    while(1)
    {
		if(g_laohua_sign) AUTO_Debug();
        ucKeyValue = SYS_ReadKey();
//		printf("\r\nucKeyValue:%02X\r\n",ucKeyValue);
        switch(ucKeyValue)
        {
            case KEY_CANCEL : 
                 return KEY_CANCEL;
            case KEY_F2: 
                 m_PageID--;
                 if(m_PageID<1) 
                 {
                     m_PageID = 1;
                     return KEY_F2;
                 } else return KEY_F2; 
            case KEY_F3:
                 m_PageID ++;
                 if(m_PageID > PAGE_MAXID) 
                 {
                     m_PageID = PAGE_MAXID;
                     return KEY_F3;
                 } else return KEY_F3;

			case KEY_1 :
				LCD_Debug();              App2_Page0Menu();
				break;
			case KEY_2 :
			    LED_Debug();              App2_Page0Menu();
				break;
			case KEY_3:
			    LEDSeg_Debug();			  App2_Page0Menu();	
				break;
			case KEY_4:					
				KEY_Debug();              App2_Page0Menu();	
				break;			
	        default: break;
        }
    }
}

uchar App2_Page1Func(void)
{
	uchar ucKeyValue =KEY_NONE;
    App2_Page1Menu();
	while(1)
	{
		if(g_laohua_sign) AUTO_Debug();
		ucKeyValue = SYS_ReadKey();
//		printf("\r\nucKeyValue:%02X\r\n",ucKeyValue);
		switch(ucKeyValue)
		{
			case KEY_CANCEL : return KEY_CANCEL;
            case KEY_F2: 
                 m_PageID--;
                 if(m_PageID<1) 
                 {
                     m_PageID = 1;
                     return KEY_F2;
                 } else return KEY_F2; 
            case KEY_F3:
                 m_PageID ++;
                 if(m_PageID>PAGE_MAXID) 
                 {
                     m_PageID = PAGE_MAXID;
                     return KEY_F3;
                 } else return KEY_F3;

		   case KEY_1:
				BEEP_Debug();
                App2_Page1Menu();
				break;
			case KEY_2:
				Sound_Debug();
                App2_Page1Menu();	
				break;
			case KEY_3 :
				RTC_Debug();
                App2_Page1Menu();	
				break;
			case KEY_4 :
				TransMode_Debug();
                App2_Page1Menu();	
				break;			
			default: break;
		}
	}
}

uchar App2_Page2Func(void)
{
    uchar ucKeyValue =KEY_NONE;
    App2_Page2Menu();
    while(1)
    {
		if(g_laohua_sign) AUTO_Debug();
        ucKeyValue = SYS_ReadKey();
//		printf("\r\nucKeyValue:%02X\r\n",ucKeyValue);
        switch(ucKeyValue)
        {
            case KEY_CANCEL : return KEY_CANCEL;
            case KEY_F2: 
                 m_PageID--;
                 if(m_PageID<1) 
                 {
                     m_PageID = 1;
                     return KEY_F2;
                 } else return KEY_F2; 
            case KEY_F3:
                 m_PageID ++;
                 if(m_PageID>PAGE_MAXID) 
                 {
                     m_PageID = PAGE_MAXID;
                     return KEY_F3;
                 } else return KEY_F3;

            case KEY_1 :
				TCP_Debug(); App2_Page2Menu();
				break;
			case KEY_2 :
			    GPS_Debug(); App2_Page2Menu();
				break;
			case KEY_3:
				 BT_Debug(); App2_Page2Menu();
				break;
			case KEY_4:
				IrDA_Debug(); 
				App2_Page2Menu();
				break;
	        default: break;		
	    }
    }
}
uchar App2_Page3Func(void)
{
    uchar ucKeyValue =KEY_NONE;
    App2_Page3Menu();
    while(1)
    {
		if(g_laohua_sign) AUTO_Debug();
        ucKeyValue = SYS_ReadKey();
//		printf("\r\nucKeyValue:%02X\r\n",ucKeyValue);
        switch(ucKeyValue)
		{
			case KEY_CANCEL : return KEY_CANCEL;
	        case KEY_F2: 
	             m_PageID--;
	             if(m_PageID<1) 
	             {
	                 m_PageID = 1;
	                 return KEY_F2;
	             } else return KEY_F2; 
	        case KEY_F3:
	             m_PageID ++;
	             if(m_PageID>PAGE_MAXID) 
	             {
	                 m_PageID = PAGE_MAXID;
	                 return KEY_F3;
	             } else return KEY_F3;

			case KEY_1:
				Contact_Debug(); App2_Page3Menu();
				break;
			case KEY_2:
				CatactlessCPU_Debug(); App2_Page3Menu();
				break;
			case KEY_3:
				Flash_Debug();
				App2_Page3Menu();
				break;
			case KEY_4:
				_2_4G_Debug();
				App2_Page3Menu();
				break;			
	        default: break;
		}
	}		
}

uchar App2_Page4Func(void)
{
    uchar ucKeyValue =KEY_NONE;
    App2_Page4Menu();
    while(1)
    {
		if(g_laohua_sign) AUTO_Debug();
        ucKeyValue = SYS_ReadKey();
//		printf("\r\nucKeyValue:%02X\r\n",ucKeyValue);
        switch(ucKeyValue)
		{
			case KEY_CANCEL : return KEY_CANCEL;
	        case KEY_F2: 
	             m_PageID--;
	             if(m_PageID<1) 
	             {
	                 m_PageID = 1;
	                 return KEY_F2;
	             } else return KEY_F2; 
	        case KEY_F3:
	             m_PageID ++;
	             if(m_PageID>PAGE_MAXID) 
	             {
	                 m_PageID = PAGE_MAXID;
	                 return KEY_F3;
	             } else return KEY_F3;

			case KEY_1:
				QR_Debug(); App2_Page4Menu();
				break;
			case KEY_2:
				CatactlessCPU_Debug(); App2_Page4Menu();
				break;
			case KEY_3:
				Flash_Debug();
				App2_Page4Menu();
				break;
			case KEY_4:
				Version_Debug();
				App2_Page4Menu();
				break;			
	        default: break;
		}
	}		
}
extern void IRQkey_Init(void);
extern void (* Key1_Handler)(void);
extern void (* Key2_Handler)(void);

void text_laohua(void)
{
	g_laohua_sign = 1;
}
extern void SYS_InitSysKeyborad(uint);
extern uchar g_ucKeyBoardExt;


void App3_Init(void)
{
    SYS_Init();	
	
	GPS_Init(); //2017/7/29

	TTSInit();

	QR_Init();//��ʼ��ģ��
	
	
	
	IrDA_Init();

	
	TTS_SetTTSDebug(1); //����ӡ
	Uart_SetSysDebug(1);     //ϵͳ��ӡ����
	Uart_SetSysDebug(1);

	TCP_Init();
	TCP_SetCallBackFlag(0);  //�Ȳ�����
//	
	

	SYS_KeyInit();  //��ѯģʽ


		//����ģʽ

	SYS_InitSysKeyborad(9600); //��ʼ������ 
	g_ucKeyBoardExt = SYS_CheckKeyBoard();
	if(g_ucKeyBoardExt != 0x00)
	{
		g_ucKeyBoardExt = 1;
		SYS_InitSysKeyborad(115200); 
	}
	
}


//uint puiRecLen = 10;
//uchar pucRecBuff_main[1024] = {0};
extern void DEVICE_DeviceParaInit(void);
int main(void)
{

		/*����ר��*/
//	uchar acRecBuff[1000], acRecBuff1[1000];
//	uint puiRecLen;


	uchar ucTemp = 0;
	uchar LanguageChoice = 0;  //����ѡ��
	uchar ucKeyValue =KEY_NONE;
	uchar ucKeyValue1 =KEY_NONE;
	uint uiTick, i = 0;
//	
	App3_Init();
	Uart_SetSysDebug(1);

	SendToPC((uchar*)"����ѡ��", 1, 0,DISP_CENTER | DISP_CLRSCR);
	SendToPC((uchar*)"1-Chinese", 3, 0,DISP_CENTER | DISP_CLRLINE);
	SendToPC((uchar*)"2-English", 5, 0,DISP_CENTER | DISP_CLRLINE);
    while(1)
    {
		if(g_laohua_sign) AUTO_Debug();
        ucKeyValue = SYS_ReadKey();
		ucKeyValue1 = SYS_ReadKeyInq();  //������ѯģʽ
        switch(ucKeyValue)  //���ڰ���
        {
			case KEY_1:  
				LANGUAGE = 0;
				LanguageChoice = 0xFF;
				break;
			case KEY_2:  
				LANGUAGE = 1;
				LanguageChoice = 0xFF;
				break;
            case KEY_CANCEL: 
				LanguageChoice = 0xFF;				
                break;
            default:			
				break;
        }
		switch(ucKeyValue1)  //��������
        {
			case KEY_UP: 
				text_laohua();			
                break;
			case KEY_DOWN: 
				text_laohua();			
                break;
            default:			
				break;
        }
		if(0xFF == LanguageChoice) break;
    }

	{
		App2_FirstMenu();
		m_PageID= 1;
		while(1)
		{
			ucKeyValue = KEY_NONE;
			if(g_laohua_sign) AUTO_Debug();
			switch(m_PageID)
			{
				case 1:SYS_CLS(); ucKeyValue = App2_Page0Func();break;
				case 2:SYS_CLS(); ucKeyValue = App2_Page1Func();break;
				case 3:SYS_CLS(); ucKeyValue = App2_Page2Func();break;
				case 4:SYS_CLS(); ucKeyValue = App2_Page3Func();break;
				case 5:SYS_CLS(); ucKeyValue = App2_Page4Func();break;
				default: 
					break; 
			}
			
			if(ucKeyValue ==KEY_CANCEL)
			{
				App2_FirstMenu();
				if(0 == (EXIT_KEY_F1 - SYS_WaitKeyEvent(0, (uint)EXIT_KEY_ALL, 0)))
				{
					SYS_Reset();
				}
			}
		} 
	}
}  



PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  SYS_ComSendByte(ch);

  return ch;
}

//...............����....................  
