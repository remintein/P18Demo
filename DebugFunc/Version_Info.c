#include <stdio.h>
#include "systick.h"
#include "AppIF.h"
#include "APIINC.h"
#include "system.h"

void Version_Info()
{
	SendToPC("�汾��Ϣ", 1, 0 ,DISP_CENTER|DISP_CLRSCR);
	
	
	SendToPC("�ͺ�:T80", 3, 0 ,DISP_POSITION);
	SendToPC("�汾:16012501", 5, 0 ,DISP_POSITION);
	while(1)
	{
		if(KEY_CANCEL == SYS_ReadKey())
		{
			return ;
		}
	}
}