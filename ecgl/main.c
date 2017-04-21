
#include "main.h"
#include "AlgInterface.h"
#include <stdlib.h>

#include "android/log.h"
static const char *TAG="serial_port";
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)

JNIEXPORT void JNICALL Java_com_example_test_ecgl12_InitProcFunc
  (JNIEnv *env, jobject obj)
{
	InitProcFunc();
}

/*
 * Class:     com_example_test_ecgl12
 * Method:    UsartDataProc
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_example_test_ecgl12_UsartDataProc
  (JNIEnv *env, jobject obj, jbyteArray dataarr,jint len)
{
	//unsigned char b = data;
	//UsartDataProc(b);
	int i = 0;
	unsigned char *jbarray = (unsigned char *)malloc(len * sizeof(unsigned char));
	(*env)->GetByteArrayRegion(env,dataarr,0,len,jbarray);
	//LOGD("Opening serial port -->%d",size);
	unsigned char *data = (unsigned char *)jbarray;
	for(i=0;i<len;i++)
	{
		UsartDataProc(data[i]);
		//LOGD("data serial port :%d-->%d",i,data[i]);
	}
	free(jbarray);
}

/*
 * Class:     com_example_test_ecgl12
 * Method:    GetResult
 * Signature: ([I)[I
 */
JNIEXPORT jintArray JNICALL Java_com_example_test_ecgl12_GetResult
  (JNIEnv *env, jobject obj, jintArray arr)
{
	int *a;
	jint *carr = (*env)->GetIntArrayElements(env,arr,false);
	jintArray arrtem = (*env)->NewIntArray(env,3060);
	a = GetResult(carr);
	(*env)->SetIntArrayRegion(env,arrtem,0,3060,a);
	(*env)->SetIntArrayRegion(env,arr,0,48,carr);
	(*env)->ReleaseIntArrayElements(env,arr,carr,0);
	return arrtem;
}

/*
 * Class:     com_example_test_ecgl12
 * Method:    WitleafRcvCmd1
 * Signature: ()C
 */
JNIEXPORT jboolean JNICALL Java_com_example_test_ecgl12_WitleafRcvCmd1
  (JNIEnv *env, jobject obj)
{
	unsigned char ret = WitleafRcvCmd1();
	return ret;
}

/*
 * Class:     com_example_test_ecgl12
 * Method:    SatrtEcgAnalysisFlag
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_example_test_ecgl12_SatrtEcgAnalysisFlag
  (JNIEnv *env, jobject obj, jboolean flag)
{
	unsigned char f = flag;
	SatrtEcgAnalysisFlag(f);
}

/*
 * Class:     com_example_test_ecgl12
 * Method:    GetFinishEcgAnalysisFlag
 * Signature: ()C
 */
JNIEXPORT jboolean JNICALL Java_com_example_test_ecgl12_GetFinishEcgAnalysisFlag
  (JNIEnv *env, jobject obj)
{
	jboolean f = GetFinishEcgAnalysisFlag();
	return f;
}

/*
 * Class:     com_example_test_ecgl12
 * Method:    ClearEcgAnalysisFlag
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_test_ecgl12_ClearEcgAnalysisFlag
  (JNIEnv *env, jobject obj)
{
	ClearEcgAnalysisFlag();
}

/*
 * Class:     com_example_test_ecgl12
 * Method:    DiagnosisAnalysis
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_test_ecgl12_DiagnosisAnalysis
  (JNIEnv *env, jobject obj)
{
	DiagnosisAnalysis();
}


JNIEXPORT jchar JNICALL Java_com_example_test_ecgl12_GetWitleafPacket
  (JNIEnv *env, jobject obj)
{
		return gtWitleafDataPacket.iheartRate ;
}

JNIEXPORT jintArray JNICALL Java_com_example_test_ecgl12_GetWitleafDataPacket
  (JNIEnv *env, jobject obj)
{
	int i;
	jint *carr = (jint *)malloc(sizeof(jint)*17);
	jintArray arrtem = (*env)->NewIntArray(env,17);
	//实时心率 1S 刷新一次，心率范围为 0-300
	carr[0] = gtWitleafDataPacket.iheartRate;
	// Pace 检测标志，在检测到 Pace 信号后上传， 为 1 表示检测到 Pace 信号。
	carr[1] = gtWitleafDataPacket.iPaceFlag & 0xff;
	// 心电通道过载标志为，1S 刷新一次
	carr[2] = gtWitleafDataPacket.iOverLoadSttus & 0xff;
	//导联脱落检测标志，1S 刷新 1 次
	carr[3] = gtWitleafDataPacket.iRalallOffFlag&0xff;
	carr[4] = gtWitleafDataPacket.iVxOffFlag & 0xff;

	//分别表示 I，II，V1—V6 这 8 个通道的 心电信号，以 500HZ 频率上传，
	//数值范围为 0-4096，基线值为 2048, 1mV 对应幅值约 为 300 左右。

	carr[5] = gtWitleafDataPacket.i16EcgData[0];
	carr[6] = gtWitleafDataPacket.i16EcgData[1];
	carr[7] = gtWitleafDataPacket.i16EcgData[1] - gtWitleafDataPacket.i16EcgData[0]; //III
	carr[8] = -0.5*(gtWitleafDataPacket.i16EcgData[1]+gtWitleafDataPacket.i16EcgData[0]); //avR
	carr[9] = gtWitleafDataPacket.i16EcgData[0] - 0.5*gtWitleafDataPacket.i16EcgData[1]; //avL
	carr[10] = gtWitleafDataPacket.i16EcgData[1] - 0.5*gtWitleafDataPacket.i16EcgData[0]; //avF
	for(i=11;i<17;i++)
	{
		carr[i] = gtWitleafDataPacket.i16EcgData[i-9];
	}
	(*env)->SetIntArrayRegion(env,arrtem,0,17,carr);
	free(carr);
	return arrtem;
}
