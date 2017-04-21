#ifndef _ECGTYPE_H_
#define _ECGTYPE_H_

#define bool int
#define true  1
#define false 0

#ifndef NULL
#define NULL	0
#endif

#define NONE_WAVE 0

#define ECG_AMP_RATIO 300//500  //

#define ECG_ANA_TOTAL_SECOND	3
#define ECG_ANA_SAMPLE_RATE	250      //采样频率
#define ECG_ANA_BUFFER_LEN	(ECG_ANA_SAMPLE_RATE * ECG_ANA_TOTAL_SECOND)

#define MWIN_WIDTH	36

#define MIN_PEAK_WIDTH	10 //原为4

#define PEAKNUM	8

#define TC	0.1875

#define MIN_THRESHOLD	10

#define FILTER_DELAY	24

#define HIGHPASS_DELAY	16

#define SEARCH_WIDTH	30

#define BACKED_WIDTH	25

#define MAX_PEAK2END	50

#define EDGE_SEARCH_WIDTH	30

#define MIN_SLOPE	7

#define EDGE_MAX_WIDTH	25

#define WIDTH_SEARCHED	6

#define MAX_QRS_NUM	60

#define CHECKED_WIDTH	100

#define MIN_PVC_WIDTH	20 // 原16

#define STFILTER_DELAY  2

#define RPOS_DELAY      4

#define FILTER_DIVIDE   5

#define _100MS				(ECG_ANA_SAMPLE_RATE / 10)
#define _200MS				(ECG_ANA_SAMPLE_RATE / 5)
#define _250MS				(ECG_ANA_SAMPLE_RATE>>2)
#define _300MS				(_100MS * 3)
#define _600MS				(_200MS * 3)
#define _500MS				(ECG_ANA_SAMPLE_RATE / 2)
#define _1000MS				ECG_ANA_SAMPLE_RATE
#define _2000MS				(_1000MS << 1)

typedef enum
{
	ECG_EXT_CHANNEL_I,
	ECG_EXT_CHANNEL_II,
	ECG_EXT_CHANNEL_V1,
	ECG_EXT_CHANNEL_V2,
	ECG_EXT_CHANNEL_V3,
	ECG_EXT_CHANNEL_V4,
	ECG_EXT_CHANNEL_V5,
	ECG_EXT_CHANNEL_V6,
	ECG_EXT_CHANNEL_III,
	ECG_EXT_CHANNEL_AVR,
	ECG_EXT_CHANNEL_AVL,
	ECG_EXT_CHANNEL_AVF,

	ECG_EXT_CHANNEL_MAX

} ECG_EXT_CHANNEL_LIST;

typedef enum
{
	ECG_ANA_CHANNEL_I,
	ECG_ANA_CHANNEL_II,
	ECG_ANA_CHANNEL_V1,
	ECG_ANA_CHANNEL_V2,
	ECG_ANA_CHANNEL_V3,
	ECG_ANA_CHANNEL_V4,
	ECG_ANA_CHANNEL_V5,
	ECG_ANA_CHANNEL_V6,

	ECG_ANA_CHANNEL_MAX

} ECG_ANA_CHANNEL_LIST;

typedef enum 
{
	ECG_ANA_QRS_TYPE_DOMINANT = 0,						
	ECG_ANA_QRS_TYPE_ABNORMAL,							
	ECG_ANA_QRS_TYPE_UNCLASSIFIED,						
	ECG_ANA_QRS_TYPE_LEARN,								

} ECG_ANA_QRS_TYPE_LIST;

typedef struct
{
	int iAveWidth;

	int iAveRAmp;

	int iAveSAmp;

	int iAveQRSAmp;

	int iAveNetQRSAmp;

}ECG_ANA_QRS_AVEVAL;

typedef struct
{
	bool bIsPeak;   

	short i16RAmp;

	short i16SAmp;

	short i16QrsAmp;

	short i16MaxChangeAmp80Ms;

	short i16ISOlevel;

	short i16ISOnoise;

	short i16BaselineShift;

} ECG_ANA_QRS_SHAPE_INFO;

typedef struct
{
	int iOnsetPos;
	int iOnsetHeight;								
	int iPeakPos;
	int iPeakHeight;								

} ECG_ANA_PEAK;

typedef struct
{
	int iNormal;							
	int iBacked;							

} ECG_ANA_THRESHOLD;

typedef struct
{
	int iLeft;   
	int iRight;  

} ECG_ANA_RSQUARE;

typedef struct
{
	int i32OnsetPos;
	int i32Time;										
	int i32Pos;
	int i32Height;									
	int i32BufPos;
	int i32Pages;										
	int i32Searched;									

} ECG_ANA_PEAK_INFO;

typedef struct
{
	int i32PeakPos;									

	int i32Rri;										

	int i32Onset;										

	int i32Width;										

	int i32Fiducial;									

	int i32Coef;										

	int i32OnRri;										

	int i32Morph;										

	char i8Updated;										

	ECG_ANA_QRS_TYPE_LIST tType;						

	char i8Matched;										

	int i32Noise;										

	int i32Peak2End;									

	int i32Threshold;									

	bool bIsPeak;										

	ECG_ANA_QRS_SHAPE_INFO tQrsShapeInfo;							

	short i16MaxQrsSlope;													

	int u32QrsId;															

	ECG_ANA_QRS_TYPE_LIST tOrgType;												

} ECG_ANA_QRS_COMPLEX;	

typedef struct
{
	ECG_ANA_PEAK_INFO ptBeatDetQueRec[8];					

	ECG_ANA_PEAK_INFO ptBeatNoiseHeigh[8];					

	int i32BeatDetQueNum;									

	int i32LastPeakPos;									

	bool pbNoisePeak[8];									

} ECG_ANA_DETECT_BEAT_QUE;

typedef struct
{
	int i32QrsDetected;								

	int i32QrsPtr;									

	int i32QrsClassified;								

	int i32ClassifiedQrsPtr;							

	int i32QrsCountInHr;								

	int i32LastRPos;					             //last R wave position

	int i32LastOnset;									

	int i32AveRri;									

	int i32Rrml;										

	int i32LastSlope;									

	int i32AveSlope;									

	int i32TimePast;									

	int i32InitLength;								

	int i32Initialized;								

	int i32Counter;								 //use in MorphClassify, save the number of continued PVCs

	int i32ResetPeakDetect;							

	int i32ValidRri;									

	int i32MaxSlope;									

	int i32MaxUserSlope;								

	int i32AveQrsAmp;												

	int i32TallTPosable;										

	unsigned int u32QrsId;													

	int i32Irregularity;										

} ECG_ANA_QRS_GLOBALS;

typedef struct
{
	int PVal;

	int PastRi;

	int NextRi;

	int RPos;

	int QPos;

	int QRSBgn;

	int JPos;

}ECG_WAVE_PARAM;

typedef struct
{
	int iType;

	int iRr;

}ECG_RHYTHM_TYPE;

typedef struct
{
	int QDur;
	int QAmp;
	int RDur;
	int RAmp;
	int SDur;
	int SAmp;
	int RrDur;
	int RrAmp;
	int PDur;
	int PAmp;
	int VAT;
	int STJ;
	int STM;
	int STE;
	int TAmpM;
	int TAmp;
	int Tup;

	int QRSDur;

	bool bDeltaWave;

	int QRSarea;
	int QRSRatio;

}ECG_PARAM_DETAIL;

typedef struct  
{
	int MinnecodeF;

	int MinnecodeS;

	int MinnecodeT;

}ECG_MINNESOTA_CODE;

typedef struct _DIG_CODE_MAP
{
	int No;//N
	char strCode[8];//digcode
	char strChinName[80];
	char strEngName[255];
	char strMapCode[26]; //if map multi code,use comma as divider
	//==2005-06-01为了MD12SL代码评测功能,追加的有关定义
	char degree;	//0/'A'-definite;1/'B'-probable;2/'C'-posiible;
	unsigned int type;		//类型,0-结构性;1-节律性;2-描述性;3-结论性
	unsigned int gruop1;		//按1分组的类别进行评测
	unsigned int gruop2;		//按2分组的类别进行评测
	unsigned int gruop3;		//按3分组的类别进行评测
	char gp1_abbr[7];//类别的缩写
	//--2005-06-01为了MD12SL代码评测功能,追加的有关定义
} DIG_CODE_MAP;

typedef struct
{
	int iheartRate;
	unsigned char iRalallOffFlag;
	unsigned char iVxOffFlag;
	unsigned char iOverLoadSttus;
	unsigned char iPaceFlag;
	int i16EcgData[8];
}ECG_WITLEAF_DATA_TYPE;

#endif
