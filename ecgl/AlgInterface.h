#ifndef _ALGINTERFACE_H
#define _ALGINTERFACE_H

#include "EcgType.h"
typedef struct _WITLEAF_PACKET
{
	unsigned char u8Len;
	unsigned char u8ParaType;
	unsigned char u8Type;
	unsigned char u8Id;
	int u32No;
	unsigned char pu8Data[22];
	unsigned char u8Checksum;
} WITLEAF_PACKET;
extern ECG_WITLEAF_DATA_TYPE gtWitleafDataPacket;
extern WITLEAF_PACKET gtWitleafPacket;;
extern void InitProcFunc(void);
extern int * GetResult(int *ResultBuff);

unsigned char WitleafRcvCmd1(void);
void UsartDataProc(unsigned char data);
void SatrtEcgAnalysisFlag(unsigned char flag);
unsigned char GetFinishEcgAnalysisFlag(void);
void ClearEcgAnalysisFlag(void);
void DiagnosisAnalysis(void);
#endif