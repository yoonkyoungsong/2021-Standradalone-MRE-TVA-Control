#ifndef HEADER_USER_DEFINED_USERDAQ
#define HEADER_USER_DEFINED_USERDAQ

#include "NIDAQmx.h"


/***************DAQ**************/

#define MAX_AI_VOLTAGE  (double)( 10.0) // NI6009
#define MIN_AI_VOLTAGE  (double)(-10.0) // NI6009
#define MAX_DI_VOLTAGE  (double)( 10.0) // NI6009

#define MAX_AO_VOLTAGE  (double)(  5.0) // NI6009
#define MIN_AO_VOLTAGE  (double)(  0.0) // NI6009
#define MAX_DO_VOLTAGE  (double)(  5.0) // NI6009

#define CREATE_AI_CH(Task, Chan)  DAQmxCreateAIVoltageChan(Task, Chan, "", DAQmx_Val_Diff, MIN_AI_VOLTAGE, MAX_AI_VOLTAGE, DAQmx_Val_Volts, NULL)   // creating an analog input channel
#define CREATE_AO_CH(Task, Chan)  DAQmxCreateAOVoltageChan(Task, Chan, "", MIN_AO_VOLTAGE, MAX_AO_VOLTAGE, DAQmx_Val_Volts, NULL)                     // creating an analog output channel
#define CREATE_DO_CH(Task, Chan) DAQmxCreateDOChan(Task, Chan, "", DAQmx_Val_ChanForAllLines)

#define SAMPLECONFIG_AI(Task, samplingTime, dataNum) DAQmxCfgSampClkTiming(Task, "", samplingTime, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, dataNum)

#define READ_AI(Task, dataNum, read) DAQmxReadAnalogF64(Task, dataNum, MAX_DO_VOLTAGE, DAQmx_Val_GroupByChannel, read, sizeof(float64) * 4, NULL, NULL) 

#define WRITE_AO(Task,Write) DAQmxWriteAnalogScalarF64(Task, "", MAX_AI_VOLTAGE, Write, NULL)  // 1번의 데이터값 출력
#define WRITE_DO(Task,Write) DAQmxWriteDigitalScalarU32(Task, "", MAX_DI_VOLTAGE , Write, NULL) //********* 전역변수



#define CREATE_AI_ACC_CH(Task, Chan) DAQmxCreateAIAccelChan(Task, Chan, "",DAQmx_Val_Cfg_Default, MIN_AI_VOLTAGE, MAX_AI_VOLTAGE, DAQmx_Val_AccelUnit_g, 100, DAQmx_Val_mVoltsPerG, DAQmx_Val_Internal, 0.0021, NULL)

#define SAMPLECONFIG_AI_ACC(Task, samplingTime, dataNum) DAQmxCfgSampClkTiming(Task, "", samplingTime, DAQmx_Val_Rising, DAQmx_Val_ContSamps, dataNum)



#pragma once
#endif
