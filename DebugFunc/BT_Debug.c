#include <stdio.h>	
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h" 
#include "system.h"
#include "bluetooth.h"
#include "com.h"
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern uchar TCP_SetCallBackFlag(uchar);
//extern uchar BT_Icon(uchar);
extern uchar LANGUAGE;
/********************************************************************************************************
** �������ܣ���BT��������
** ��    ����pucBuffer���跢����������
        	 uiSize��   ���ݳ���
** ��    �أ���
*********************************************************************************************************/
void BT_SendNBytes_(uchar *pucBuffer, uint uiSize)
{
//    SYS_OpenPortExt(5,1000,115200,2);
//    COM5_AuxioSelect(2);
    SYS_PortSend(5 , pucBuffer , uiSize);
}
/********************************************************************************************************
** �������ܣ�������len�ֽ�EEPROM����
** ��    ���� ucLen		��ȡ���ݳ���
              usAddr	Ҫ��ȡ����ʼEEPROM��ַ
			  pucPara	���Σ���ȡ������
** ��    �أ�0          ��ȷ
			 1          ����
** ˵    ��: 
*********************************************************************************************************/
uchar BT_ReadNbyteE2PROM_(uchar ucLen, ushort usAddr, uchar *pucPara)
{
	uchar ucTmpPara;
	uchar ucTmpRecieveLen;
	uchar ucErrorFlag = 0;
	uchar aucTmpBuff[100];
	uint  uiLen;
	uchar ucDataBuf[2048];

	uiLen = 0;
	memcpy(&ucDataBuf[uiLen],"\x01\x29\xFC\x03",4);
	uiLen += 4;
	ucDataBuf[uiLen] = (uchar)((usAddr>>8)&0xff);
	uiLen += 1;
	ucDataBuf[uiLen] = (uchar)((usAddr>>0)&0xff);
	uiLen += 1;
	ucDataBuf[uiLen] = ucLen;
	uiLen += 1;
	BT_SendNBytes_(ucDataBuf,uiLen);

	if(Uart5_GetData_DMA(&uiLen,aucTmpBuff,100))
		return 1;
	
	ucTmpPara = memcmp(aucTmpBuff,"\x04\x0e",2);		  // 04 0e  len 01 29 fc
	if(ucTmpPara)
	{
		return 1;
	}
	ucTmpPara = memcmp(&aucTmpBuff[3],"\x01\x29\xfc",3);		  //  01 29 fc
	if(ucTmpPara)
	{
		return 1;
	}
	
	ucErrorFlag     = aucTmpBuff[6];
	ucTmpRecieveLen = aucTmpBuff[9];
	memcpy(pucPara,&aucTmpBuff[10],ucTmpRecieveLen);
	if(ucErrorFlag)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/********************************************************************************************************
** �������ܣ�����дlen�ֽ�EEPROM����
** ��    ���� ucLen		д�����ݳ���
              usAddr	Ҫд�����ʼEEPROM��ַ
			  pucPara	Ҫд�������
** ��    �أ�0          ��ȷ
			 1          ����
** ˵    ��: 
*********************************************************************************************************/
uchar BT_WriteNbyteE2PROM_(uchar ucLen, ushort usAddr, uchar *pucPara)
{
	uchar ucTmpPara;
	uchar aucTmpBuff[100] = {0};
	uint  uiLen;
	uchar ucDataBuf[2048];

	uiLen = 0;
	memcpy(&ucDataBuf[uiLen],"\x01\x27\xfc",3);
	uiLen += 3;
	ucDataBuf[uiLen] = ucLen+3;
	uiLen += 1;
	ucDataBuf[uiLen] = (uchar)((usAddr>>8)&0xff);
	uiLen += 1;
	ucDataBuf[uiLen] = (uchar)((usAddr>>0)&0xff);
	uiLen += 1;
	ucDataBuf[uiLen] = ucLen;
	uiLen += 1;
	if(uiLen+ucLen > 2048)
		return 1;
	memcpy(&ucDataBuf[uiLen],pucPara,ucLen);
	uiLen += ucLen;
	BT_SendNBytes_(ucDataBuf,uiLen);
	
	if(Uart5_GetData_DMA(&uiLen,aucTmpBuff,1000))
		return 1;

	ucTmpPara = memcmp(aucTmpBuff,"\x04\x0e\x04\x01\x27\xfc",6);		  //04 0e 04 01 27 fc
	if(ucTmpPara)
	{
		return 1;
	}
	return 	aucTmpBuff[6];	  // TmpBuff[6] is the sign of sucess or fail
}
/********************************************************************************************************
** �������ܣ���ȡ��������BM57����ģ������
** ��    ����ucGetOrSet ��   GET_BT_ADDR
                             SET_BT_ADDR
			 pucModuleName :  16�ֽڣ�ASCII��
** ��    �أ�0:	�ɹ�
             1: ��������
			 2����������   
** ˵    ��:    ��ַ0x0b,16�ֽڣ���EEPROM�д�˱���
*********************************************************************************************************/
uchar BT_ModuleName_(uchar ucGetOrSet,uchar *pucModuleName)
{
	uchar ucTmpPara;
	uchar ucTmp[100]={0};
	
	if (ucGetOrSet == BT_GET_VALUE)
	{
		ucTmpPara = BT_ReadNbyteE2PROM_(16, 0x0B, pucModuleName);
		
		if(ucTmpPara)
		{
			return 2;
		}
		return 0;
	}
	else if (ucGetOrSet == BT_SET_VALUE)
	{	
		ucTmpPara = BT_WriteNbyteE2PROM_(16, 0x0B, pucModuleName);
		BT_ReadNbyteE2PROM_(16, 0x0B, ucTmp);
		if(memcmp(ucTmp,pucModuleName,16))
		{
			ucTmpPara = BT_WriteNbyteE2PROM_(16, 0x0B, pucModuleName);
		}	
		if(ucTmpPara)
		{
			return 2;
		}
		BT_WriteNbyteE2PROM_(16, 0x3a1, pucModuleName);
		return 0;	
	}
	else
	{
		return 1;
	}
}
extern uchar  COM1_ReceiveData(uchar *pRecBuff , uint *uiRecLen , uint TimeOutMs);


void BT_Debug(void)
{
	uchar ucKeyValue = KEY_NONE;
    uint  uiLen; 
	uchar ucBack;
//	uchar ucShowFlag = 0; 
	uchar aucReadBuff[100];	
	uchar aucReadBuff1[100];
	
	/*����ר��*/
	uchar acRecBuff[1000], acRecBuff1[1000];
	uint puiRecLen;
	
	if(0 == LANGUAGE)
	{  	
		SendToPC((uchar*)"��������", 1,0,DISP_CENTER|DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar*)"BT      TEST ", 1,0,DISP_CENTER|DISP_CLRSCR);
	}
	Uart_BTDebug(1);
//	BT_Icon(0);  //��ʾͼ��
	BT_Power(BT_POWER_ON);
	printf("\r\n�ϵ����\r\n");
//	BT_Reset();
	BT_SetMode(BT_MODE);
	printf("\r\nBT_MODE���\r\n");
	SYSTICK_DelayMs(200);
	BT_SetMode(UART_MODE);
	printf("\r\nUART_MODE���\r\n");
	SYSTICK_DelayMs(2000);
//	SYS_OpenPortExt(1,1000,115200,2);
//    SYS_OpenPortExt(5,1000,115200,2);
//    COM5_AuxioSelect(2);
//	Uart_SetSysDebug(1);
//	while(1)
//	{
///*����ר��*/		
//			COM1_ReceiveData(acRecBuff , &puiRecLen , 100);
//			if(puiRecLen != 0)
//			{
//				Uart1_DumpData("\r\nSend<-",acRecBuff,puiRecLen);
////				Uart_Printf("\r\nSend(%d):%s\r\n",puiRecLen,acRecBuff);
//				SYS_PortSend(5,(uchar*)acRecBuff, puiRecLen);
//				memset(acRecBuff,0,100);
//				puiRecLen = 0;
//			}
//			Uart5_GetData_DMA(&puiRecLen, acRecBuff1, 50);
//			if(puiRecLen != 0)
//			{
//				Uart1_DumpData("\r\nRend<-",acRecBuff1,puiRecLen);
////				Uart_Printf("\r\nRend(%d):%s\r\n",puiRecLen,acRecBuff1);
//				memset(acRecBuff1,0,1000);
//				puiRecLen = 0;
//			}
//		
//	}
    ucBack = BT_ModuleName(BT_GET_VALUE, aucReadBuff);
	if(!ucBack)
	{
		if(memcmp(aucReadBuff," DECARD.P18.SPP2 ",16))		 //���ֲ�Ϊ" DECARD.T80.SPP "����������
		{
    		ucBack = BT_ModuleName(BT_SET_VALUE, (uchar*)" DECARD.P18.SPP2 ");
			if(!ucBack)
			{
				SYSTICK_DelayMs(50);
				ucBack = BT_ModuleName(BT_GET_VALUE, aucReadBuff);
			}
		}
	}
	if(!ucBack)
	{
		aucReadBuff[16] = 0;
		SendToPC((uchar*)"Name:", 1,0,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)aucReadBuff,3,0,DISP_POSITION | DISP_CLRLINE);
	}
	else
	{
		SYS_CLS();
		SendToPC((uchar*)"GetPinCode Fail!",3,0,DISP_POSITION | DISP_CLRLINE);
		SYSTICK_DelayMs(1000);
		goto  BT_END;
	}
	SYSTICK_DelayMs(1000);
	ucBack = BT_PinCode(BT_GET_VALUE,aucReadBuff);
	if(!ucBack)
	{
		aucReadBuff[4] = 0;
		SendToPC((uchar*)"PinCode:",1 , 0,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)aucReadBuff,3 , 0,DISP_POSITION | DISP_CLRLINE);
			
	}
	else
	{
		SYS_CLS();
		SendToPC( (uchar*)"GetPinCode Fail!",3 ,0 ,DISP_POSITION | DISP_CLRLINE);
		SYSTICK_DelayMs(1000);
		goto  BT_END;
	}
	SYSTICK_DelayMs(1000);
	ucBack = BT_BtAddr(BT_GET_VALUE,aucReadBuff1);	  
	if(!ucBack)
	{
		sprintf((char*)aucReadBuff1,
		"%02X.%02X.%02X.%02X.%02X.%02X",
		aucReadBuff1[0],aucReadBuff1[1],aucReadBuff1[2],aucReadBuff1[3],aucReadBuff1[4],aucReadBuff1[5]);
		SendToPC((uchar*)"BtAddr:",3,0,DISP_POSITION | DISP_CLRLINE);
		SendToPC((uchar*)aucReadBuff1,5,0,DISP_POSITION | DISP_CLRLINE);
	}
	else
	{
		SYS_CLS();
		SendToPC( (uchar*)"GetAddr Fail!",3,0,DISP_POSITION | DISP_CLRLINE);
		SYSTICK_DelayMs(1000);
	    goto  BT_END;
	}
	SYSTICK_DelayMs(1000);
	ucBack = BT_UartBaut(BT_GET_VALUE,aucReadBuff);
	if(!ucBack)
	{
		SendToPC((uchar*)"Baut:",1,0,DISP_POSITION | DISP_CLRLINE);
        switch(aucReadBuff[0])
        {
            case 0:  SendToPC((uchar*) "921600",3,0,DISP_POSITION | DISP_CLRLINE);  break;
            case 1:  SendToPC((uchar*) "460800",3,0,DISP_POSITION | DISP_CLRLINE);  break;
            case 2:  SendToPC((uchar*) "230400",3,0,DISP_POSITION | DISP_CLRLINE);  break;
            case 3:  SendToPC((uchar*) "115200",3,0,DISP_POSITION | DISP_CLRLINE);  break;
            case 4:  SendToPC((uchar*) "57600",3,0,DISP_POSITION | DISP_CLRLINE);   break;
            case 5:  SendToPC((uchar*) "38400",3,0,DISP_POSITION | DISP_CLRLINE);   break;
            case 6:  SendToPC((uchar*) "28800",3,0,DISP_POSITION | DISP_CLRLINE);   break;
            case 7:  SendToPC((uchar*) "19200",3,0,DISP_POSITION | DISP_CLRLINE);   break;
            case 8:  SendToPC((uchar*) "14400",3,0,DISP_POSITION | DISP_CLRLINE);   break;
            case 9:  SendToPC((uchar*) "9600",3,0,DISP_POSITION | DISP_CLRLINE);    break;
            case 10: SendToPC((uchar*) "4800",3,0,DISP_POSITION | DISP_CLRLINE);    break;
            case 11: SendToPC((uchar*) "2400",3,0,DISP_POSITION | DISP_CLRLINE);    break;
            default: SendToPC((uchar*) "Invalid",3,0,DISP_POSITION | DISP_CLRLINE);  break;
        }
	}
	else
	{
		SYS_CLS();
		SendToPC((uchar*)"GetBaut Fail!",3,0,DISP_POSITION | DISP_CLRLINE);
		SYSTICK_DelayMs(1000);
		return ;
	}
	SYSTICK_DelayMs(1000);
	SYS_CLS();
	BT_SetMode(BT_MODE);
	SendToPC((uchar*)"Connectting...",3,0,DISP_CENTER | DISP_CLRLINE);

	uiLen = 0;
//		
	if(0 == LANGUAGE)
	{  
		SendToPC((uchar*)"��1����",1,0,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"��2����",3,0,DISP_POSITION | DISP_CLRLINE);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar*)"KEY_1  Send",1,0,DISP_POSITION | DISP_CLRSCR);
		SendToPC((uchar*)"KEY_2  Recv",3,0,DISP_POSITION | DISP_CLRLINE);
	}
	SendToPC((uchar*)aucReadBuff1,7,0,DISP_POSITION | DISP_CLRLINE);
	while(1)
    {	
		ucKeyValue = SYS_ReadKey();
		switch(ucKeyValue)
		{
			case KEY_1:	
				if(0 == LANGUAGE)
				{ 				
					SendToPC((uchar*)"���ͣ�1234567890+-*/?<",1,0,DISP_POSITION | DISP_CLRLINE);		
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar*)"Send��1234567890+-*/?<",1,0,DISP_POSITION | DISP_CLRLINE);
				}
				BT_SendData((uchar*)"1234567890+-*/?<",strlen("1234567890+-*/?<"));
				break;
			case KEY_2:
				if(0 == LANGUAGE)
				{ 
					SendToPC((uchar*)"���գ�",1,0,DISP_POSITION | DISP_CLRLINE);
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar*)"Recv��",1,0,DISP_POSITION | DISP_CLRLINE);
				}
				if(!BT_RecData(aucReadBuff,&uiLen,100))
				{ 			
					SendToPC((uchar*)aucReadBuff,7,0,DISP_POSITION | DISP_CLRLINE);
					memset(aucReadBuff,0,sizeof(aucReadBuff));	
				}
				else
				{
					if(0 == LANGUAGE)
					{ 
						SendToPC((uchar*)"���ճ�ʱ",7,0,DISP_POSITION | DISP_CLRLINE);
					}
					else if(1 == LANGUAGE)
					{
						SendToPC((uchar*)"Receive overtime",7,0,DISP_POSITION | DISP_CLRLINE);
					}
				}
				break ;
			case KEY_CANCEL:
			BT_END:			
				BT_Power(BT_POWER_OFF);
//				BT_Icon(1);  //��ͼ����ʾ
				if(0 == LANGUAGE)
				{
					SendToPC((uchar*)"�˳�����",1,0,DISP_POSITION | DISP_CLRLINE);
				}
				else if(1 == LANGUAGE)
				{
					SendToPC((uchar*)"Exit test",1,0,DISP_POSITION | DISP_CLRLINE);
				}
				return ;
			default: break;
		}						   
	}
}
