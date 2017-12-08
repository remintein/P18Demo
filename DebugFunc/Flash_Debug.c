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
** 函数功能：铁电测试
** 参    数：无
** 返    回：0成功，否则失败
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
		SendToPC((uchar *)"铁电测试", 1, 0,DISP_CENTER|DISP_CLRSCR);
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
			SendToPC((uchar*)"读出成功",5,0,DISP_CENTER|DISP_CLRLINE);
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
			SendToPC((uchar*)"写入成功",5,0,DISP_CENTER|DISP_CLRLINE);
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
			SendToPC((uchar*)"读出成功",5,0,DISP_CENTER|DISP_CLRLINE);
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
		SendToPC("SPI存储测试", 1, 0 ,DISP_CENTER|DISP_CLRSCR);
		printf("SPI存储容量：%d M\r\n",MXFLASH_GetSize());
	}
	else if(1 == LANGUAGE)
	{
		SendToPC("SPI FLASH TEST", 1, 0 ,DISP_CENTER|DISP_CLRSCR);
		printf("capacity：%d M\r\n",MXFLASH_GetSize());
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
			SendToPC("SPI存储1读取成功", 3, 0 ,DISP_CENTER);
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
			SendToPC("SPI存储1读取失败", 3, 0 ,DISP_CENTER);
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
			SendToPC("SPI存储2读取成功", 3, 0 ,DISP_CENTER);
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
			SendToPC("SPI存储2读取失败", 3, 0 ,DISP_CENTER);
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
** 函数功能：填充缓存数组。
** 参    数：pBuffer 数据指针
             BufferLenght 数据长度
             data 填充的值
** 返    回：无
*********************************************************************************************************/
void Fill_Buffer_8(uint8_t *pBuffer, uint16_t BufferLenght, uint8_t data)
{
    uint16_t IndexTmp = 0;

    /* 填充*/
    for (IndexTmp = 0; IndexTmp < BufferLenght; IndexTmp++ )
    {
        pBuffer[IndexTmp] = data;
    }
}

/********************************************************************************************************
** 函数功能 比较3组数值  （只写中间一段，比较头、中间、尾三段）
** 参    数：uint8_t *A,  数据A  读出的
			uint8_t *B,  数据B   写入的（只写中间一段，比较头、中间、尾三段）
			uint8_t *B,  数据C   读出的
			uint32_t len1 第一段长度
			uint32_t len2 第二段长度
			uint32_t len3 第三段长度
** 返    回：无
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
	4M = 1024个扇区
	**/
	  /*****************初始化变量*******************************/
	uint8_t TxBuffer[0x1100] = {0};
	uint8_t RxBuffer[0x1100] = {0};;
	uint8_t RxBuffer1[0x1100] = {0};
	char sprntfBUFF[50] = {0};
	/********循环变量*********/
    uint  i = 0; 
	Uart_SetSysDebug(1);
	SYS_CLS();
	
	if(0 == LANGUAGE)
	{			
		SendToPC((uchar *)"存储模块", 1, 0 ,DISP_CENTER  | DISP_CLRSCR);
		SendToPC((uchar *)"正在做读写测试...", 3, 0 ,DISP_CENTER  | DISP_CLRSCR);
		SendToPC((uchar *)"铁电测试", 5, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"Memory module", 1, 0 ,DISP_CENTER  | DISP_CLRSCR);
		SendToPC((uchar *)"Read-write test...", 3, 0 ,DISP_CENTER  | DISP_CLRSCR);
		SendToPC((uchar *)"EEPROM TEST", 5, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}
	

	Fram_Debug();  //铁电测试。
	
	if(0 == LANGUAGE)
	{			
		SendToPC((uchar *)"SPI存储测试", 5, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"SPI FLASH TEST", 5, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}
	
	MxFlash_Debug();
	if(0 == LANGUAGE)
	{			
		SendToPC((uchar *)"NORFlash测试", 5, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"NORFlash TEST", 5, 0 ,DISP_CENTER  | DISP_CLRSCR);
	}
	
	/*************************/
	for(i = 0; i <= 0x400/100; i++  )   //只测试 1/100
	{
		if(0 == LANGUAGE)
		{			
			sprintf(sprntfBUFF, "第%d块...", i);
		}
		else if(1 == LANGUAGE)
		{
			sprintf(sprntfBUFF, "%d area...", i);
		}
		
		SendToPC((uchar *)sprntfBUFF, 1, 0 , DISP_POSITION | DISP_CLRLINE); 
		Flash_UserRead((0x1000 * i - 0x50) , 0x1000 + 0x100, RxBuffer);  //读0x1100字节
		Fill_Buffer_8(TxBuffer, 0x1000, 0x55);  //填充缓存区
		Flash_UserWrite(0x1000 * i, 0x1000, TxBuffer);  //写0x1000字节
		Flash_UserRead((0x1000 * i - 0x50) , 0x1000 + 0x100, RxBuffer1);  //读0x1100字节
		if(0 != ABC_memcmp(RxBuffer, TxBuffer, RxBuffer1, 0x50, 0x1000, 0x50))
		{
			if(0 == LANGUAGE)
			{			
				SendToPC((uchar *)"测试失败！", 1, 0 , DISP_POSITION | DISP_CLRSCR); 
				SendToPC((uchar *)"退出测试...", 3, 0 , DISP_POSITION | DISP_CLRSCR);
			}
			else if(1 == LANGUAGE)
			{
				SendToPC((uchar *)"Test failed！", 1, 0 , DISP_POSITION | DISP_CLRSCR); 
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
		SendToPC((uchar *)"测试成功！", 1, 0 , DISP_POSITION | DISP_CLRSCR); 
		SendToPC((uchar *)"退出测试...", 3, 0 , DISP_POSITION | DISP_CLRSCR); 
	}
	else if(1 == LANGUAGE)
	{
		SendToPC((uchar *)"Successful test！", 1, 0 , DISP_POSITION | DISP_CLRSCR); 
		SendToPC((uchar *)"Exit test...", 3, 0 , DISP_POSITION | DISP_CLRSCR); 
	}

	Uart_SetSysDebug(0);	
	SYSTICK_DelayMs(1000);
	SYS_CLS();
	return; 		

}
