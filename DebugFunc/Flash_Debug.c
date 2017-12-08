#include <stdio.h>
#include <string.h>
#include "system.h"
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h"
#include "Flash.h"
#include "com.h"
#include "mxflash.h"
extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
extern void Uart_SetSysDebug(uchar);
//extern uchar rand(void);
extern uchar LANGUAGE;
/********************************************************************************************************
** �������ܣ��������
** ��    ������
** ��    �أ�0�ɹ�������ʧ��
*********************************************************************************************************/
void Fram_Debug()	
{
	ushort  i;
	uchar  temp;
	uchar FramWriteBuff[64] = {0};
	uchar FramReadBuff[64] = {0};
	SYSTEM_I2CPortInitExt();
	if(0 == LANGUAGE)
	{			
		SendToPC((uchar *)"�������", 1, 0,DISP_CENTER|DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"EEPROM TEST", 1, 0,DISP_CENTER|DISP_CLRSCR);
	}
	

	temp = SYSTEM_I2CRead24CExt(1024, FramReadBuff,32);
	if(!temp)
	{
		Uart1_DumpData("\r\nReadOut:",FramReadBuff,32);
		if(0 == LANGUAGE)
		{			
			SendToPC((uchar*)"�����ɹ�",5,0,DISP_CENTER|DISP_CLRLINE);
		}
		else if(1 == LANGUAGE)
		{
			SendToPC((uchar*)"Read successfully",5,0,DISP_CENTER|DISP_CLRLINE);
		}
		
		SYSTICK_DelayMs(1000);
	}
	for(i = 0;i < 32; i ++)
	{
		FramWriteBuff[i] = i;
	}

	temp = SYSTEM_I2CWrite24CExt(1024, FramWriteBuff,32);

	if(!temp)
	{
		Uart1_DumpData("\r\nWriteIn:",FramWriteBuff,32);
		if(0 == LANGUAGE)
		{			
			SendToPC((uchar*)"д��ɹ�",5,0,DISP_CENTER|DISP_CLRLINE);
		}
		else if(1 == LANGUAGE)
		{
			SendToPC((uchar*)"Write successfully",3,0,DISP_CENTER|DISP_CLRLINE);
		}
		SYSTICK_DelayMs(1000);
	}
	temp = SYSTEM_I2CRead24CExt(1024, FramReadBuff,32);
	if(!temp)
	{
		Uart1_DumpData("\r\nReadOut:",FramReadBuff,32);
		if(0 == LANGUAGE)
		{			
			SendToPC((uchar*)"�����ɹ�",5,0,DISP_CENTER|DISP_CLRLINE);
		}
		else if(1 == LANGUAGE)
		{
			SendToPC((uchar*)"Read successfully",5,0,DISP_CENTER|DISP_CLRLINE);
		}
		SYSTICK_DelayMs(1000);
	}
}

void MxFlash_Debug()
{
	uchar Mx_Buff[1024] = {0};

	
	MXFLASH_Init();
	if(0 == LANGUAGE)
	{			
		SendToPC("SPI�洢����", 1, 0 ,DISP_CENTER|DISP_CLRSCR);
		printf("SPI�洢������%d M\r\n",MXFLASH_GetSize());
	}
	else if(1 == LANGUAGE)
	{
		SendToPC("SPI FLASH TEST", 1, 0 ,DISP_CENTER|DISP_CLRSCR);
		printf("capacity��%d M\r\n",MXFLASH_GetSize());
	}

	
	MXFLASH_Select(0);
	MXFLASH_Write(0, 5, "kkkkk");

	MXFLASH_Select(1);
	MXFLASH_Write(0, 5, "nnnnn");
	
	MXFLASH_Select(0);
	if(!MXFLASH_Read(0, 5, Mx_Buff))
	{
		Uart1_DumpData("MXFLASH_Read",Mx_Buff,5);
		if(0 == LANGUAGE)
		{			
			SendToPC("SPI�洢1��ȡ�ɹ�", 3, 0 ,DISP_CENTER);
		}
		else if(1 == LANGUAGE)
		{
			SendToPC("1_ Successful test", 3, 0 ,DISP_CENTER);
		}
		
	}
	else
	{
		if(0 == LANGUAGE)
		{			
			SendToPC("SPI�洢1��ȡʧ��", 3, 0 ,DISP_CENTER);
		}
		else if(1 == LANGUAGE)
		{
			SendToPC("1_ Test failed", 3, 0 ,DISP_CENTER);
		}
		
	}
	MXFLASH_Select(1);
	
	if(!MXFLASH_Read(0, 5, Mx_Buff))
	{
		Uart1_DumpData("MXFLASH_Read",Mx_Buff,5);
		if(0 == LANGUAGE)
		{			
			SendToPC("SPI�洢2��ȡ�ɹ�", 3, 0 ,DISP_CENTER);
		}
		else if(1 == LANGUAGE)
		{
			SendToPC("2_ Successful test", 3, 0 ,DISP_CENTER);
		}		
	}
	else
	{
		if(0 == LANGUAGE)
		{			
			SendToPC("SPI�洢2��ȡʧ��", 3, 0 ,DISP_CENTER);
		}
		else if(1 == LANGUAGE)
		{
			SendToPC("2_ Test failed", 3, 0 ,DISP_CENTER);
		}
	}
	SYSTICK_DelayMs(1000);	
	
	return ;
}
/********************************************************************************************************
** �������ܣ���仺�����顣
** ��    ����pBuffer ����ָ��
             BufferLenght ���ݳ���
             data ����ֵ
** ��    �أ���
*********************************************************************************************************/
void Fill_Buffer_8(uint8_t *pBuffer, uint16_t BufferLenght, uint8_t data)
{
    uint16_t IndexTmp = 0;

    /* ���*/
    for (IndexTmp = 0; IndexTmp < BufferLenght; IndexTmp++ )
    {
        pBuffer[IndexTmp] = data;
    }
}

/********************************************************************************************************
** �������� �Ƚ�3����ֵ  ��ֻд�м�һ�Σ��Ƚ�ͷ���м䡢β���Σ�
** ��    ����uint8_t *A,  ����A  ������
			uint8_t *B,  ����B   д��ģ�ֻд�м�һ�Σ��Ƚ�ͷ���м䡢β���Σ�
			uint8_t *B,  ����C   ������
			uint32_t len1 ��һ�γ���
			uint32_t len2 �ڶ��γ���
			uint32_t len3 �����γ���
** ��    �أ���
*********************************************************************************************************/
uchar ABC_memcmp(uint8_t *A, uint8_t *B, uint8_t *C, uint32_t len1, uint32_t len2, uint32_t len3)
{
	uint i = 0;
//	printf("\r\n%d,%d,%d\r\n",len1,len2,len3);
//	Uart1_DumpData("\r\nFlash_UserRead<-",A, 0x1000+0x100);
//	Uart1_DumpData("\r\nFlash_UserRead<-",C, 0x1000+0x100);
	for(i = 0; i < len1; i++)
	{
		if (A[i] != C[i]) 
		{
			printf("\r\n1\r\n");
			return 1;
		}
	
	}
	for(i = 0; i < len2; i++)
	{
		if (B[i] != C[i + len1])
		{
			printf("\r\n2\r\n");
			return 2;
		}
	}
	for(i = 0; i < len3; i++)
	{
		if (A[i + len1 + len2] != C[i + len1 + len2]) 
		{
			printf("\r\n3\r\n");
			return 3;
		}
	}
	return 0;
}

void  Flash_Debug()
{
	/**
	4M = 4 * 1024 * 1024 = 0X400 000 
	4M = 1024������
	**/
	  /*****************��ʼ������*******************************/
	uint8_t TxBuffer[0x1100] = {0};
	uint8_t RxBuffer[0x1100] = {0};;
	uint8_t RxBuffer1[0x1100] = {0};
	char sprntfBUFF[50] = {0};
	/********ѭ������*********/
    uint  i = 0; 
	Uart_SetSysDebug(1);
	SYS_CLS();
	
	if(0 == LANGUAGE)
	{			
		SendToPC((uchar *)"�洢ģ��", 1, 0 ,DISP_CENTER  | DISP_CLRSCR);
		SendToPC((uchar *)"��������д����...", 3, 0 ,DISP_CENTER  | DISP_CLRSCR);
		SendToPC((uchar *)"�������", 5, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"Memory module", 1, 0 ,DISP_CENTER  | DISP_CLRSCR);
		SendToPC((uchar *)"Read-write test...", 3, 0 ,DISP_CENTER  | DISP_CLRSCR);
		SendToPC((uchar *)"EEPROM TEST", 5, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}
	

	Fram_Debug();  //������ԡ�
	
	if(0 == LANGUAGE)
	{			
		SendToPC((uchar *)"SPI�洢����", 5, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"SPI FLASH TEST", 5, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}
	
	MxFlash_Debug();
	if(0 == LANGUAGE)
	{			
		SendToPC((uchar *)"NORFlash����", 5, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"NORFlash TEST", 5, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}
	
	/*************************/
	for(i = 0; i <= 0x400/100; i++  )   //ֻ���� 1/100
	{
		if(0 == LANGUAGE)
		{			
			sprintf(sprntfBUFF, "��%d��...", i);
		}
		else if(1 == LANGUAGE)
		{
			sprintf(sprntfBUFF, "%d area...", i);
		}
		
		SendToPC((uchar *)sprntfBUFF, 1, 0 , DISP_POSITION | DISP_CLRLINE); 
		Flash_UserRead((0x1000 * i - 0x50) , 0x1000 + 0x100, RxBuffer);  //��0x1100�ֽ�
		Fill_Buffer_8(TxBuffer, 0x1000, 0x55);  //��仺����
		Flash_UserWrite(0x1000 * i, 0x1000, TxBuffer);  //д0x1000�ֽ�
		Flash_UserRead((0x1000 * i - 0x50) , 0x1000 + 0x100, RxBuffer1);  //��0x1100�ֽ�
		if(0 != ABC_memcmp(RxBuffer, TxBuffer, RxBuffer1, 0x50, 0x1000, 0x50))
		{
			if(0 == LANGUAGE)
			{			
				SendToPC((uchar *)"����ʧ�ܣ�", 1, 0 , DISP_POSITION | DISP_CLRSCR); 
				SendToPC((uchar *)"�˳�����...", 3, 0 , DISP_POSITION | DISP_CLRSCR);
			}
			else if(1 == LANGUAGE)
			{
				SendToPC((uchar *)"Test failed��", 1, 0 , DISP_POSITION | DISP_CLRSCR); 
				SendToPC((uchar *)"Exit test...", 3, 0 , DISP_POSITION | DISP_CLRSCR);
			}
			
			Uart_SetSysDebug(0);			
			SYSTICK_DelayMs(1000);
			SYS_CLS();
			return; 
		}
		SYSTICK_DelayMs(500);
		
	}
	if(0 == LANGUAGE)
	{			
		SendToPC((uchar *)"���Գɹ���", 1, 0 , DISP_POSITION | DISP_CLRSCR); 
		SendToPC((uchar *)"�˳�����...", 3, 0 , DISP_POSITION | DISP_CLRSCR); 
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"Successful test��", 1, 0 , DISP_POSITION | DISP_CLRSCR); 
		SendToPC((uchar *)"Exit test...", 3, 0 , DISP_POSITION | DISP_CLRSCR); 
	}

	Uart_SetSysDebug(0);	
	SYSTICK_DelayMs(1000);
	SYS_CLS();
	return; 		

}
