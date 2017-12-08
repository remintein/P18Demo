#include <stdio.h>
#include <string.h>
#include "com.h"
#include "libAlgo.h"
///todo include files..........................................

/*rsa PLU KEY*/
unsigned char aucModule[] =//256
{
    0xc9,0xf2,0xc9,0x11,0x75,0xe7,0xc4,0x69,0x02,0xd4,0x1a,0x63,0xe3,0x6c,0xf8,0xc0,
    0x6f,0x1e,0xd7,0x9e,0x85,0x8d,0x14,0xdd,0x07,0xeb,0x8d,0x22,0x0a,0x18,0x2d,0x59,
    0xf0,0x2f,0x7d,0x9d,0x7b,0x60,0x4a,0x1f,0xf9,0xb0,0x9f,0x01,0x19,0x15,0xd6,0x42,
    0xcf,0xe9,0x4a,0x94,0x93,0x45,0xd2,0x9c,0x66,0x98,0x88,0x81,0x34,0x28,0x6e,0xec,
    0xd2,0x9b,0x40,0x3a,0xe4,0x42,0x4c,0x1f,0x9f,0x68,0x07,0xb6,0x4a,0xcc,0xc4,0x74,
    0x9b,0x63,0x39,0x01,0xc4,0x0d,0x75,0x2a,0x28,0x84,0xd1,0xb6,0x23,0x1c,0xa8,0xc5,
    0x14,0x5a,0x77,0x11,0xb6,0x68,0xb4,0xf2,0x02,0x5b,0x95,0x27,0x41,0x9f,0x7c,0x33,
    0x9a,0xca,0xf3,0x9c,0x93,0xa6,0x2c,0xc3,0x9e,0x9d,0xe9,0x0c,0x1e,0x89,0xd1,0x34,
    0x17,0xa3,0xa2,0xe2,0x51,0x11,0x6c,0xe2,0x2e,0x4e,0x0e,0x53,0x39,0xa0,0x40,0xfd,
    0x5c,0xdc,0xfc,0x32,0x55,0x2d,0xf9,0x98,0x28,0x48,0x80,0x40,0xb1,0x32,0x76,0x8c,
    0x56,0x84,0x36,0x42,0xb3,0x64,0x16,0xbe,0x32,0x39,0xfe,0x2e,0xe7,0xad,0x23,0xb4,
    0x66,0xd6,0x4c,0xff,0x22,0x5a,0xe8,0x37,0xcf,0x93,0x7c,0x85,0x4a,0x99,0xbb,0x3a,
    0x90,0x5f,0xbe,0x88,0xfd,0xa2,0xd7,0xf4,0x1f,0xc1,0x86,0x35,0xd4,0xaa,0xb2,0x8e,
    0xca,0xa9,0x00,0x16,0x20,0x83,0x46,0xf0,0x56,0xba,0x15,0xf0,0x8d,0xd0,0xcc,0x58,
    0x13,0x47,0x71,0xeb,0xb7,0x43,0xd9,0x4e,0x5a,0x3a,0xfc,0x54,0xda,0x85,0x2d,0x16,
    0xf4,0x23,0x97,0xb0,0x5e,0x2c,0xad,0x32,0x9d,0xe7,0xce,0xae,0xd5,0x89,0x32,0xcd
};

unsigned char aucPub[] =
{
	0x01,0x00,0x01
};
unsigned char pucKey[16]=
{
	0x00,0x01,0x02,0x03,0x00,0x01,0x02,0x03,0x00,0x01,0x02,0x03,0x00,0x01,0x02,0x03
};
unsigned char aucPri[]=//256
{
	0x98,0xd3,0xbf,0x0e,0x13,0xa8,0x3d,0x9f,0x2a,0xa0,0xd1,0x07,0xde,0xc8,0x4c,0xc7,
	0x74,0x50,0x66,0xe4,0x74,0x34,0xfc,0x20,0xf9,0x29,0x6d,0x38,0xe1,0x62,0xc2,0x8f,
	0x59,0x90,0xd7,0x03,0x22,0xa7,0x0f,0xf1,0x7a,0xc8,0x0a,0xcc,0x8d,0xeb,0x54,0xa6,
	0x63,0x29,0x2d,0x63,0x9a,0xc0,0x30,0x4e,0x63,0xe5,0xf3,0x07,0xb4,0x2d,0x15,0x24,
	0xeb,0x8c,0xc9,0xe2,0xc7,0x72,0xd4,0xa0,0xe9,0xc5,0x94,0x70,0x83,0xd2,0xca,0xa9,
	0x64,0x1e,0x86,0xb9,0xab,0x60,0x73,0xd6,0x5f,0xab,0x83,0xf8,0xce,0x41,0x96,0x06,
	0xef,0x0c,0x37,0x27,0x94,0x5f,0x50,0xf0,0x04,0x90,0xc2,0x23,0x5f,0x2a,0x0e,0x98,
	0x0f,0x00,0x9f,0xb3,0x52,0x99,0x63,0x2e,0x44,0x6d,0xf2,0xfa,0x56,0x26,0xcd,0xac,
	0x9d,0x43,0x37,0xb7,0x7e,0x29,0x64,0x05,0x37,0xe0,0xc6,0xa2,0xed,0xd6,0x65,0x37,
	0x2d,0x67,0x32,0x23,0x6e,0x41,0x22,0x4d,0x30,0x0c,0x99,0x31,0x06,0x1e,0x7a,0xce,
	0x5f,0x3d,0xde,0x3f,0x46,0x04,0xb1,0x42,0x7d,0xef,0xb1,0x09,0x82,0x1b,0x20,0x15,
	0x16,0x91,0xb9,0x3b,0x4a,0x24,0xcf,0x79,0x1b,0xe5,0xfd,0x4c,0x85,0x9a,0xf4,0xae,
	0xf8,0x6c,0x2e,0x92,0xd6,0xd0,0x7b,0xcb,0x58,0x55,0xd5,0x4b,0xf6,0x6d,0x7a,0x65,
	0xb2,0xe4,0x63,0x68,0x99,0xa5,0xbb,0x3e,0x86,0xb2,0x8f,0x77,0x0a,0xe6,0xa3,0x45,
	0x47,0x49,0xb2,0xbc,0xeb,0xac,0xaf,0x10,0xa6,0xed,0x6b,0x58,0xc5,0x46,0x71,0x76,
	0x71,0x36,0x73,0xa7,0xf8,0xf6,0x87,0xc6,0x0d,0xdf,0xe0,0xaa,0xa3,0x91,0xe5,0x11
};

#define RSA_2048_KEYLEN 256

void *CONV_HexAsc(unsigned char *pucDest,unsigned char *pucSrc,unsigned int uiLen)
{
	unsigned int uiI;
	unsigned char *pucPtr;

    pucPtr = pucDest ;
    if ( uiLen % 2 )
        *pucDest++ = (*pucSrc++ & 0x0F) + 0x30 ;
    for ( uiI = 0 ; uiI < (uiLen / 2) ; uiI++)
    {
        *pucDest++ = ( (*pucSrc & 0xF0) >> 4 ) + 0x30 ;
        *pucDest++ = (*pucSrc++ & 0x0F) + 0x30 ;
    }
    while (pucPtr != pucDest)
    {
        if (*pucPtr >= 0x3A)
            *pucPtr += 7 ;
        pucPtr++;
    }
	return((unsigned char*)pucDest);
}

void test_algo(void)
{
    unsigned char aucInput[RSA_2048_KEYLEN],aucRsaOut[RSA_2048_KEYLEN] = "\0";
    unsigned char aucPrnBuf[RSA_2048_KEYLEN*2];
	int i;
	
    aucInput[0] = 0x00;
    aucInput[1] = 0x01;
    for(i = 2;i < RSA_2048_KEYLEN;i++)
    aucInput[i] = i+0x10; 

    SHA1_Compute(aucInput,sizeof(aucInput),aucRsaOut);//20
	CONV_HexAsc(aucPrnBuf,aucRsaOut,RSA_2048_KEYLEN);
	COM1_SendNBytes (RSA_2048_KEYLEN*2,aucPrnBuf);
	COM1_SendNBytes(2,"\r\n");

    memset((void*)aucRsaOut,0,sizeof(aucRsaOut));
    RSA_PublicDecrypt(aucModule,RSA_2048_KEYLEN,aucPri,sizeof(aucPri),aucInput,RSA_2048_KEYLEN,aucRsaOut);//256
	CONV_HexAsc(aucPrnBuf,aucRsaOut,RSA_2048_KEYLEN*2);
	COM1_SendNBytes (RSA_2048_KEYLEN*2,aucPrnBuf);
	COM1_SendNBytes(2,"\r\n");
    
    memset((void*)aucInput,0,sizeof(aucInput));
    RSA_PublicDecrypt(aucModule,RSA_2048_KEYLEN,aucPub,3,aucRsaOut,RSA_2048_KEYLEN,aucInput);//256
	CONV_HexAsc(aucPrnBuf,aucInput,RSA_2048_KEYLEN*2);
	COM1_SendNBytes (RSA_2048_KEYLEN*2,aucPrnBuf);
	COM1_SendNBytes(2,"\r\n");

    memset((void*)aucInput,0x45,sizeof(aucInput));	
	Des_Encrypt(aucInput, aucRsaOut, pucKey);
    Des_Decrypt(aucRsaOut, aucInput, pucKey);
	CONV_HexAsc(aucPrnBuf,aucInput,8*2);
	COM1_SendNBytes (16,aucPrnBuf);
	COM1_SendNBytes(2,"\r\n");
	
	memset((void*)aucInput,0x23,sizeof(aucInput));
	TDes_Encrypt(aucInput, aucRsaOut, pucKey);
    TDes_Decrypt(aucRsaOut, aucInput, pucKey);
	CONV_HexAsc(aucPrnBuf,aucInput,8*2);
	COM1_SendNBytes (16,aucPrnBuf);
	COM1_SendNBytes(2,"\r\n");
}
