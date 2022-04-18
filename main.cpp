#include "userHeader.h"
#include "userDefineHeader.h"

/*-----------------------------------------------
			   Parameters
-------------------------------------------------*/

/************* DAQ ****************/
TaskHandle TaskAI;
TaskHandle TaskAI_ACC;

/************** Time *******************/
#define MRESAMPLINGTIME (double)(0.0005) 
#define ACCSAMPLINGTIME (double)(0.0005)
#define CONTROLTIME		(double)(0.5120) // data num = 1024
#define FINISHTIME		(double)(300)

/************** freq *******************/
#define MREDATANUM  (int) (FINISHTIME/MRESAMPLINGTIME)
#define ACCDATANUM  (int) (FINISHTIME/ACCSAMPLINGTIME)
#define TICKNUM     (int) int(FINISHTIME/CONTROLTIME)

#define MRECONTNUM  (int) (CONTROLTIME/MRESAMPLINGTIME)
#define ACCCONTNUM  (int) (CONTROLTIME/ACCSAMPLINGTIME)

/*****************Idle*******************/
double intialTime = 0.0;
double startTime = 0.0;
double endTime = 0.0;
double finishTime = 0.0;
double deltTime = 0.010;
double currentTime = 0.0;
int32       read;

int MREsamplingFreq = 1 / MRESAMPLINGTIME;
int ACCsamplingFreq = 1 / ACCSAMPLINGTIME;

/*************array initial****************/
double Tmre[MREDATANUM] = { 0.0 };
double Tacc[MREDATANUM] = { 0.0 };
double Vmre[MREDATANUM] = { 0.0 };
double FFTmre[MREDATANUM] = { 0.0 };

double Vacc_in[ACCDATANUM] = { 0.0 };
double Vacc_out[ACCDATANUM] = { 0.0 };

/*************buffer initial****************/
double buf_Vmre[MRECONTNUM] = { 0.0 };
double buf_Vmre_im[MRECONTNUM] = { 0.0 };

double buf_FFTmre[MRECONTNUM] = { 0.0 };
double buf_FFTmre_im[MRECONTNUM] = { 0.0 };
double buf_FFTmre_mag[MRECONTNUM] = { 0.0 };

double buf_Vacc_in[ACCCONTNUM] = { 0.0 };
double buf_Vacc_out[ACCCONTNUM*2] = { 0.0 };

/************* addtional parameter ****************/
char name1[100] = "nonControl_time_Vmre_Vfft_";
char name2[100] = "nonControl_time_freq_step_";
char name3[100] = "nonControl_time_Vaccin_Vaccout_";

//char name1[100] = "Control_time_Vmre_Vfft_";
//char name2[100] = "Control_time_freq_step_";
//char name3[100] = "Control_time_Vaccin_Vaccout_";

//char name1[100] = "retune_time_Vmre_Vfft_";
//char name2[100] = "retune_time_freq_step_";
//char name3[100] = "retune_time_Vaccin_Vaccout_";

//char name1[100] = "MINControl_time_Vmre_Vfft_";
//char name2[100] = "MINControl_time_freq_step_";
//char name3[100] = "MINControl_time_Vaccin_Vaccout_";

//char name1[100] = "MAXControl_time_Vmre_Vfft_";
//char name2[100] = "MAXControl_time_freq_step_";
//char name3[100] = "MAXControl_time_Vaccin_Vaccout_";

//char name1[100] = "retune_time_Vmre_Vfft_";
//char name2[100] = "retune_time_freq_step_";
//char name3[100] = "retune_time_Vaccin_Vaccout_";

int num = 4;

/************* Serial ****************/
Serial* SP = new Serial("COM4");
int dataLength = 1;
bool writeResult = false;

/************* zero crossing ****************/
double freq[TICKNUM] = { 0.0 };
double zctime[TICKNUM] = { 0.0 };
double totalTime[TICKNUM] = { 0.0 };

int dataset = 0;
double freqtime = 0.0;

/************* motor commend ****************/
double Step[TICKNUM] = { 0 };

char step = 'a';
int pastStep = 0;
int presentStep = 0;
int direction = 1;

int Bflag = 0;

/*----------------------------------------------
				     Main
------------------------------------------------*/

void main() {

	DAQmxCreateTask("", &TaskAI);
	DAQmxCreateTask("", &TaskAI_ACC);

	CREATE_AI_CH(TaskAI, "Dev5/ai2");
	CREATE_AI_ACC_CH(TaskAI_ACC, "Dev9/ai2");
	CREATE_AI_ACC_CH(TaskAI_ACC, "Dev9/ai3");
	
	SAMPLECONFIG_AI(TaskAI, MREsamplingFreq, MRECONTNUM);
	SAMPLECONFIG_AI_ACC(TaskAI_ACC, ACCsamplingFreq, ACCCONTNUM);

	if (SP->IsConnected()) {
		printf("We're connected\n");
	}

	if (((step > 65 && step <= 73) || (step > 97 && step <= 105))) {

		writeResult = SP->WriteData(&step, dataLength);
		printf("%c-->", step);
		printf(writeResult ? "true" : "false");
		printf("\n");

	}
	printf("start\n");
	Sleep(3000);

	startTime = checkWindowsTime() * 0.001;

	do {

		intialTime = checkWindowsTime() * 0.001;

		DAQmxStartTask(TaskAI);
		DAQmxStartTask(TaskAI_ACC);

		/*----------------------------------------------
					  data read from daq
		-----------------------------------------------*/

		DAQmxReadAnalogF64(TaskAI, MRECONTNUM, 10.0, DAQmx_Val_GroupByChannel, buf_Vmre, MRECONTNUM, &read, NULL);
		DAQmxReadAnalogF64(TaskAI_ACC, ACCCONTNUM, 10.0, DAQmx_Val_GroupByChannel, buf_Vacc_out, ACCCONTNUM*2, &read, NULL);

		/*----------------------------------------------
					frequency calculate
		-----------------------------------------------*/

		//bandPassFilter(buf_Vmre, MRECONTNUM, buf_Vmref);
		//freq[dataset] = zeroCrossing(buf_Vmre, MRECONTNUM, CONTROLTIME, dataset);
		freq[dataset] = mre_freq(buf_Vmre, buf_Vmre_im, buf_FFTmre, buf_FFTmre_im, buf_FFTmre_mag);
		step = motorRotation(freq[dataset], &pastStep, &presentStep, &direction);
		Step[dataset] = presentStep;

		printf("freq=%lf[Hz]\n", freq[dataset]);
		printf("Vacc_in=%lf[V]\n", buf_Vacc_out[2047]);
		printf("Vacc_out=%lf[V]\n\n", buf_Vacc_out[50]);

		/*----------------------------------------------
					 Serial Communication
		------------------------------------------------*/

		//if (totalTime[dataset] >= 70 && Bflag==0) {
		//	Bflag = 1;
		//	step = 'H';

			if (((step > 65 && step <= 73) || (step > 97 && step <= 105))) {

				//writeResult = SP->WriteData(&step, dataLength);
				printf("%c-->", step);
				printf(writeResult ? "true" : "false");
				printf("\n");

			}

		//}


		

		/*----------------------------------------------
					   Buffer data save
		------------------------------------------------*/

		for (int i = 0; i < MRECONTNUM; i++) {
			Tmre[i + dataset * MRECONTNUM] = totalTime[dataset] + MRESAMPLINGTIME * i;
			FFTmre[i + dataset * MRECONTNUM] = buf_FFTmre[i];
			Vmre[i + dataset * MRECONTNUM] = buf_Vmre[i];
		}

		for (int i = 0; i < ACCCONTNUM; i++) {
			Tacc[i + dataset * ACCCONTNUM] = totalTime[dataset] + ACCSAMPLINGTIME * i;
			Vacc_in[i + dataset * ACCCONTNUM] = buf_Vacc_out[i+1024];
			Vacc_out[i + dataset * ACCCONTNUM] = buf_Vacc_out[i];
		}

		
		/*----------------------------------------------
						Idle Time
		------------------------------------------------*/
	
		while (1) {
			endTime = checkWindowsTime() * 0.001 - intialTime;

			if (endTime >= CONTROLTIME) {
				break;
			}
		}

		DAQmxStopTask(TaskAI);
		DAQmxStopTask(TaskAI_ACC);
		dataset++;

		//printf("samplingtime=%lf[sec]\n", endTime);
		//printf("time=%lf\n\n", totalTime[dataset-1]);

		totalTime[dataset] = checkWindowsTime() * 0.001 - startTime;

	} while (totalTime[dataset] < FINISHTIME);

	DAQmxClearTask(TaskAI);
	DAQmxClearTask(TaskAI_ACC);

	/*---------------------------------------------------
			     solving the data(in PC)
	-----------------------------------------------------*/

	writeTextFile(name1, num, MREDATANUM, Tmre, Vmre, FFTmre);
	writeTextFile(name2, num, TICKNUM, totalTime, freq, Step);
	writeTextFile(name3, num, ACCDATANUM, Tacc, Vacc_in, Vacc_out);

}
#pragma once