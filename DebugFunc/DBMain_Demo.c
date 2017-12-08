/****************************************************************************
*
*�ļ�(File):         Main.h
*
*�޸�(Modify):       2012-11-29 10:33:36
*
*����(Author):       ��֪��
*
*����(Compile):     Keil4
*
*����(Description):
*1..BIOS����ϵͳ�������ļ�
*2..
*
----------------------------------------------------------------------------
|
| Version | Datetime             |   Author    | Description
| --------+----------------------+-------------+----------------------------
|
| V1.00    2012-11-29 10:33:36     ��֪��      
----------------------------------------------------------------------------
****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "com.h"
#include "AppIF.h"
#include "APIINC.h"
#include "DB.h"
#include "AppIFExt.h"
#include "systick.h"

		/*���ݿ����*/
//		printf("\r\n���ʼ��\r\n");
//		DBMain_Init();
//		printf("\r\nAdd...\r\n");
//		uiTick = SYS_GetTickCount();
//		for(i=0; i< 10000; i ++)
//		DBMain_Add_One_Record(i);
//		printf("\r\ntime:%dS\r\n",(SYS_GetTickCount() - uiTick)/100);
////		i = 9999;
////		for(i = 0; i < 9999; i++)
//		DBMain_Display_Record(9999);
//		uiTick = SYS_GetTickCount();
//		DBMain_Find_One_Record();
//		printf("\r\ntime:%dmS\r\n",(SYS_GetTickCount() - uiTick)*10);
//		while(1)
//		{
//			DBMain_Demo();
//		}

//The demo struct for data table 1!
typedef __packed struct
{
	uchar aucName[16];
	uchar aucNo[16];
}TYP_USER_INFO;

#define OUR_DATA_TABLE_NUM	2 //����Ϊ2����

//data table block number
 ushort g_ausRecordBlockNum[OUR_DATA_TABLE_NUM] =  {10,4};	 //��С64*4

//data table record size
 ushort g_ausRecordSize[OUR_DATA_TABLE_NUM] = {sizeof(TYP_USER_INFO),64}; //ÿһ����¼�ĳ���

 uchar	m_uname[20];

 void	 DBMain_Demo(void);
 int	 DBMain_Init(void);
 void	 DBMain_Add_One_Record(uint);
 void	 DBMain_Del_One_Record(void);
 void	 DBMain_Find_One_Record(void);
 void	 DBMain_Check_One_Record(void);
 void	 DBMain_Check_Capacity(void);
 void	 DBMain_Del_All_Record(void);
 void	 DBMain_Check_Count(void);
 void	 DBMain_Display_Record(uint);
 short Input_Charnum(ushort minnum,ushort maxnum,uchar *retbuf);
 short Input_Num(    ushort minnum,ushort maxnum,uchar *retbuf);
 short		 Table_Match(void *rec);

extern void SendToPC(uchar *buff,uchar ucRow, uchar ucCol, uint uiDispType);
void DBMain_DemoMenu(void)
{
    SYS_CLS();
   	SYS_DisplayCE("1.Add a record  ",1,0,DISP_POSITION|DISP_6x8);
   	SYS_DisplayCE("2.Del a record  ",3,0,DISP_POSITION|DISP_6x8);
   	SYS_DisplayCE("3.Find a record ",5,0,DISP_POSITION|DISP_6x8);
   	SYS_DisplayCE("4.Clear table   ",7,0,DISP_POSITION|DISP_6x8);
   	SYS_DisplayCE("5.Check a record",9,0,DISP_POSITION|DISP_6x8);
   	SYS_DisplayCE("6.Check capacity",11,0,DISP_POSITION|DISP_6x8);
   	SYS_DisplayCE("7.Record count  ",13,0,DISP_POSITION|DISP_6x8);
   	SYS_DisplayCE("8.SYS_Display record",15,0,DISP_POSITION|DISP_6x8);

}

 void	DBMain_Demo(void)
{
	int	    i;
	int	    siNeedInit = 0;
	char	ascDispBuff[40];
	short	retshort;
	long	retlong;
	int     iKey = 0; 

	//������ݿ�
	if( DB_CreateDataBase(0) != OUR_DATA_TABLE_NUM )
	{
		SYS_Display("���",1,1);	
		siNeedInit = 1;		
	}
	else
	{
		//������ݱ��ʽ
		for(i=0; i<OUR_DATA_TABLE_NUM; i++)
		{
			retshort = DB_TableCheck(i, g_ausRecordBlockNum[i], g_ausRecordSize[i]);
			if(retshort)
			{
				sprintf(ascDispBuff,"��%d ��:%d",i,retshort);
				SYS_Display((uchar*)ascDispBuff,1,1);
		        siNeedInit = 1;
		        break;		        	
		    }
		}
	}  
	if(siNeedInit)
	{		
        SYS_CLS();
        SYS_DisplayCE("����Ҫ��ʼ��"  ,1,0,DISP_CENTER);
		SYS_Display("ȷ�� - ��ʼ��",3,1);
		SYS_Display("���� - ȡ��"  ,5,1);

		retlong = SYS_WaitKeyEvent(0, EXIT_KEY_ALL, 0);
		retlong = EXIT_KEY_RETURN;
		if(retlong == EXIT_KEY_RETURN)
		{		   
			//���ó�ʼ������
			if( DBMain_Init() )
			{
				return;
			}
		}
		else
		{
			return;
		}		
	} 
Again:    	
	SYS_CLS();
    DBMain_DemoMenu(); //..<<>>
	iKey = 0;
	while(1)
	{
//	    iKey = SYS_ReadKey();	
		
		iKey = 1;		
		switch( iKey )
		{
			case KEY_1:
				DBMain_Add_One_Record(1);
				goto Again;
                			
			case KEY_2:
				DBMain_Del_One_Record();			
				goto Again;
							
			case KEY_3:
				DBMain_Find_One_Record();
				goto Again;
				
			case KEY_4:
				DBMain_Del_All_Record();
				goto Again;
			
			case KEY_5:
				DBMain_Check_One_Record();
				goto Again;
				
			case KEY_6:
				DBMain_Check_Capacity();
				goto Again;
				
			case KEY_7:
				DBMain_Check_Count();
				goto Again;			
			case KEY_8:
				DBMain_Display_Record(17);
				goto Again;				
			case KEY_F1:
				SYS_Reset();
				goto Again;			
		}
	}
}

 int	DBMain_Init(void)
{
	char	ascDispBuff[40];
	short	ssReturn;
	int	i;
	
 	SYS_OpenPortExt(1,1000,115200,2);
    Uart_SetSysDebug(1);
	printf("���ݿ��ʼ��\r\n");
	printf("��Ҫ�Ƚϳ�ʱ��\r\n");
	printf("�Ե�......\r\n");
	
	
	DB_DeleteDataBase();

	
	for(i=0; i<OUR_DATA_TABLE_NUM; i++)
	{
		ssReturn = DB_CreateTable(i, g_ausRecordBlockNum[i], g_ausRecordSize[i]);
		if(ssReturn)
		{
			sprintf(ascDispBuff,"�������:%d",ssReturn);
			printf("�������\r\n");
//			printf(ascDispBuff,7,0,DISP_POSITION|DISP_CLRLINE);			
			ssReturn = -1;
			goto end;
			
		}
	}
	
	//..check the whole system
	ssReturn = DB_CreateDataBase(0x200000);
	if(ssReturn != OUR_DATA_TABLE_NUM) 
	{
		printf("���ݿ����\r\n");		
		ssReturn = -2;
		goto end;
	}
	else
	{
		for(i=0; i<OUR_DATA_TABLE_NUM; i++)
		{
			ssReturn = DB_TableCheck(i,g_ausRecordBlockNum[i],g_ausRecordSize[i]);
			if(ssReturn)
			{
//				sprintf(ascDispBuff,"���TID %d E:%d",i,ssReturn);
//				SYS_DisplayCE(ascDispBuff,7,0,DISP_POSITION|DISP_CLRLINE);
		        goto end;		        			        	
		    }
		} 
		SendToPC((uchar *)"��ʼ���ɹ�OK", 1, 2 , DISP_POSITION | DISP_CLRSCR); 		
//		SYS_DisplayCE("��ʼ���ɹ�OK",4,0,DISP_CENTER|DISP_CLRSCR);		
		ssReturn = 0;
		goto end;
	}    
end:
//	SYS_WaitKeyEvent(0,EXIT_KEY_ALL,0);
	return ssReturn;	
}   

 void	DBMain_Add_One_Record(uint a)
{
	char		    ascDispBuff[40];
	long	retlong;
	TYP_USER_INFO	stUser={"XP","34"};
	
	uint b = 10000000;
	uint C = 0;
	memset((char *)stUser.aucName,0,16);
	memset((char *)stUser.aucNo,0,16);


	sprintf(ascDispBuff,"D%09d", b + a);
	memcpy(stUser.aucName,ascDispBuff,10);
	

	Uart_SetSysDebug(1);
	
	sprintf(ascDispBuff,"F%09d", C + a);
	memcpy(stUser.aucNo,ascDispBuff,24);
	
//	Uart1_DumpData("\r\nstUser:\r\n",(uchar*)&stUser,32);
	retlong = DB_InsertRecord(0, (void *)(&stUser));
	
	
	if(retlong)
	{
		if(9999 == a)printf("\r\n%d...Add OK\r\n",a);
		if(11999 == a)printf("\r\n%d...Add OK\r\n",a);
		if(21999 == a)printf("\r\n%d...Add OK\r\n",a);
		if(29999 == a)
		{
			printf("\r\n%d...Add OK\r\n",a);	
		}			
	}
	else
	{
		printf("\r\nAdd ERROR\r\n");

	}
	

}


 void	DBMain_Del_One_Record(void)
{
	uint	uiRecordIdex;
	char		ascIdxBuff[20];

		
	memset(ascIdxBuff,0,sizeof(ascIdxBuff));
	
	SYS_DisplayCE("Input Idx:",1,0,DISP_CENTER|DISP_CLRSCR);
	if( Input_Num(1,8,(uchar *)ascIdxBuff) )
	{
		return ;
	}
	
	uiRecordIdex = atoi(ascIdxBuff); 
	DB_DeleteRecord(0,uiRecordIdex);
	
	SYS_DisplayCE("ɾ���ɹ�",4,0,DISP_CENTER|DISP_CLRSCR);
			
	SYS_WaitKeyEvent(0,EXIT_KEY_ALL,0);
}

 void	DBMain_Del_All_Record(void)
{
    short  ssTemp;
    
	ssTemp = DB_DeleteTable(0);
    if(ssTemp == 0)
    {
        SYS_DisplayCE("������¼�ɹ�",4,0,DISP_POSITION|DISP_CLRSCR);
	}
    else
    {
        SYS_DisplayCE("������¼ʧ��",4,0,DISP_POSITION|DISP_CLRSCR);
    }
	SYS_WaitKeyEvent(0,EXIT_KEY_ALL,0);
} 

 void	DBMain_Display_Record(uint b)
{
	uint	        uiRecordIdex;   
	char		    ascIdxBuff[20];
	char           ascDispBuff[40];
	char		    scRecordFlag;	
	char	    	*pstRecord;
	TYP_USER_INFO	*pstRecordInfo;
		
	memset(ascIdxBuff, 0, sizeof(ascIdxBuff));
	

	Uart_SetSysDebug(1);
	uiRecordIdex = atoi(ascIdxBuff); //���ڼ���
	uiRecordIdex = 1;
	pstRecord = (char *)DB_MoveToRecord(0, b, &scRecordFlag);
	if(scRecordFlag == 1)
	{
		printf("\r\nNull record\r\n");
//		SYS_DisplayCE("�ռ�¼",1,0,DISP_CENTER|DISP_CLRSCR);
	}
	else if(scRecordFlag == 2)
	{
		printf("\r\nDeleted\r\n");
//		SYS_DisplayCE("��¼ɾ��",1,0,DISP_CENTER|DISP_CLRSCR);
	}
	else
	{
		printf("\r\nQuery record successful��\r\n");
		pstRecordInfo = (TYP_USER_INFO *)pstRecord;
		memcpy(ascDispBuff, (char *)(pstRecordInfo->aucName), 16);
//		SYS_DisplayCE("Name:",1,0,DISP_POSITION|DISP_CLRSCR);
//		SYS_DisplayCE(ascDispBuff,3,0,DISP_POSITION);
		
		Uart1_DumpData("\r\nID:\r\n",(uchar*)pstRecordInfo,16);
		Uart1_DumpData("\r\nsecret key:\r\n",((uchar*)pstRecordInfo + 16),16);
//		memcpy(ascDispBuff, (char *)(pstRecordInfo->aucNo), 16);
//		SYS_DisplayCE("No:",5,0,DISP_POSITION);
//		SYS_DisplayCE(ascDispBuff,7,0,DISP_POSITION);
	}
	
//	SYS_WaitKeyEvent(0,EXIT_KEY_ALL,0);
}


short	Table_Match(void *rec)
{
	return (!strncmp( (char *)rec, (char *)m_uname, 32));
}

//======================================================================
// Name��DBMain_Find_One_Record
// Function��Find record demo
// Parameters��	
// Return��
//======================================================================
 void	DBMain_Find_One_Record(void)
{
	short	retshort;
	char	ascDispBuff[40];
	uint b = 123456789;
//	sprintf(ascDispBuff,"%d", b + 1);
	memset(m_uname,0,sizeof(m_uname));
	
	
//	memcpy(m_uname,ascDispBuff, 9);
	
	
	
//	SYS_DisplayCE("Input name:",1,0,DISP_CENTER|DISP_CLRSCR);
//	if( Input_Charnum(1,16,m_uname) )
//	{
//		return ;
//	}
	memcpy(m_uname,"D010009999",10);
	retshort = DB_FindRecordFirs(0,Table_Match);
	if(retshort>=0)	
	{
		printf("\r\nQuery OK\r\n");
		printf("\r\nIndex:%d\r\n",retshort);
//		SYS_DisplayCE("��ѯ�ɹ�!",1,0,DISP_CENTER|DISP_CLRSCR);
		
//		sprintf(ascDispBuff,"Index:%d",retshort);	
//		SYS_DisplayCE(ascDispBuff,3,0,DISP_CENTER);			        			        	
	}
	else
	{
//		SYS_DisplayCE("��ѯʧ��",1,0,DISP_CENTER|DISP_CLRSCR);	
		printf("\r\nERROR\r\n");
	}
	
//	SYS_WaitKeyEvent(0,EXIT_KEY_ALL,0);
}

 void	DBMain_Check_One_Record(void)
{
	uint	uiRecordIdex;
	char		ascIdxBuff[20];

		
	memset(ascIdxBuff,0,sizeof(ascIdxBuff));
	
	SYS_DisplayCE("Input Idx:",1,0,DISP_CENTER|DISP_CLRSCR);
	if( Input_Num(1,8,(uchar *)ascIdxBuff) )
	{
		return ;
	}
	
	uiRecordIdex = atoi(ascIdxBuff); 
	if( DB_RecordCheck(0,uiRecordIdex) )
	{
		SYS_DisplayCE("��¼���ɹ�",4,0,DISP_CENTER|DISP_CLRSCR);
	}
	else
	{
		SYS_DisplayCE("��¼���ʧ��",4,0,DISP_CENTER|DISP_CLRSCR);
	}
			
	SYS_WaitKeyEvent(0,EXIT_KEY_ALL,0);
}

 void	DBMain_Check_Capacity(void)
{
	long	db_cap;
	char		ascDispBuff[40];
	
	db_cap = DB_GetTableSize(0);
	SYS_DisplayCE("��0�ռ�:",1,0,DISP_CENTER|DISP_CLRSCR);
	sprintf((char*)ascDispBuff,"%ld",db_cap);
	SYS_DisplayCE(ascDispBuff,3,0,DISP_CENTER);
	
	db_cap = DB_GetTableSize(1);
	SYS_DisplayCE("��1�ռ�:",5,0,DISP_CENTER);
	sprintf((char*)ascDispBuff,"%ld",db_cap);
	SYS_DisplayCE(ascDispBuff,7,0,DISP_CENTER);
	
	SYS_WaitKeyEvent(0,EXIT_KEY_ALL,0);	
}


 void	DBMain_Check_Count(void)
{
	long	uiRecordNum;
	char	ascDispBuff[40];
			
	uiRecordNum = DB_GetRecordNumber(0);
	SYS_DisplayCE("��0��¼:",1,0,DISP_CENTER|DISP_CLRSCR);
	sprintf((char*)ascDispBuff,"%ld",uiRecordNum);
	SYS_DisplayCE(ascDispBuff,3,0,DISP_CENTER);
	
	uiRecordNum = DB_GetRecordNumber(1);
	SYS_DisplayCE("��1��¼:",5,0,DISP_CENTER);
	sprintf((char*)ascDispBuff,"%ld",uiRecordNum);
	SYS_DisplayCE(ascDispBuff,7,0,DISP_CENTER);
	
	SYS_WaitKeyEvent(0,EXIT_KEY_ALL,0);	
}

 short Input_Charnum(ushort minnum,ushort maxnum,uchar *retbuf)
{
	INPUTMETHODEXT_STTypePara 	im;
	
	im.siCol        = 0;
	im.siRow        = 4;
	im.scFont       = 0;
	im.scAlpha      = 4;
	im.scCsrChar    = '_';
	im.pscStr       = (char *)retbuf;
	im.siCharCntMax     = maxnum;
	im.siRetNum         = 0;
	im.slQuitEvent      = EXIT_KEY_CANCEL;
	if ( !SYS_InputMethodExt(&im) )
	{		
		return 0;
	}  	
	return -1;
}


 short Input_Num(ushort minnum,ushort maxnum,uchar *retbuf)
{
	INPUTMETHODEXT_STTypePara 	im;
	
	im.siCol        = 0;
	im.siRow        = 3;
	im.scFont       = 0;
	im.scAlpha      = 0;
	im.scCsrChar    = '_';
	im.pscStr       = (char *)retbuf;
	im.siCharCntMax     = maxnum;
	im.siRetNum         = 0;
	im.slQuitEvent      = EXIT_KEY_CANCEL;
	if ( !SYS_InputMethodExt(&im) )
	{		
		return 0;
	}
	return -1;
}

