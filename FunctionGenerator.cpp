#ifndef SOURCE_USER_DEFINED_FUNCTIONGENERATOR
#define SOURCE_USER_DEFINED_FUNCTIONGENERATOR

//		

#include "userHeader.h"


	// �Լ� ������ main�� �����ؾ� �ϴ� ���� // 

	///********�ﰢ�� ����� �Ķ���͵� *********/
	//
	//int ct = 0;
	//double TRI_Frequency = 0.5;
	//double CurrentTime_tri = 0.0;
	//
	////double TRI_Frequency[20] = { 0 };
	////TRI_Frequency[k] = 0.1 + 0.1 * k;
	//
	//
	///*******������ ����� �Ķ���͵�*********/
	//
	//double sin_Frequency = 0.5;
	//
	////sin_Frequency[k] = 0.1 + 0.1 * k;
	////double sin_Frequency[20] = { 0 };
	//
	///*******�簢�� ����� �Ķ���͵�*********/
	//
	//double Pulse_Frequency = 0.5;
	//double direction = 1;
	//
	////double Pulse_Frequency[20] = { 0 };
	////Pulse_Frequency[k]= 0.1 + 0.1 * k;



	//* Vcmd ���� *//

	//Vcmd[i] = Lamp(i, Vcmd[i - 1]);
	//Vcmd[i] = TriangulerWave(2.5,  TRI_Frequency, CurrentTime_tri, ct);
	//Vcmd[i] = SinusoidialWave(0.7, sin_Frequency, Time);
	//Vcmd[i] = PulseWave((double)1, Pulse_Frequency[k],Time);




	/********************** ������ **************************/

double SinusoidialWave(double magnitude, double Frequency, double time) {

	double Vcmd = 0;

	Vcmd = magnitude * sin(2 * M_PI * Frequency * time);

	return (Vcmd);
};



/********************** �ﰢ�� **************************/

double TriangulerWave(double magnitude, double  TRI_Frequency, double CurrentTime_tri) {

	double Tri_out = 0;
	double Tri_time = 0;

	int ct = 0;

	Tri_time = 1 / TRI_Frequency;

	CurrentTime_tri = fmod(CurrentTime_tri, Tri_time);

	if (CurrentTime_tri > Tri_time * (ct + 1))
	{
		ct++;

	}
	//printf("CurrentTime_tri %f\n", CurrentTime_tri);

	if (CurrentTime_tri - Tri_time * ct < Tri_time * 0.25)
	{
		Tri_out = magnitude / (Tri_time * 0.25) * (CurrentTime_tri - Tri_time * ct);


	}

	else if (CurrentTime_tri - Tri_time * ct >= (Tri_time * 0.25) && CurrentTime_tri - Tri_time * ct < (Tri_time * 0.5))
	{
		Tri_out = -magnitude / (Tri_time * 0.25) * (CurrentTime_tri - Tri_time * 0.25 - Tri_time * ct) + magnitude;


	}

	else if (CurrentTime_tri - Tri_time * ct >= (Tri_time * 0.5) && CurrentTime_tri - Tri_time * ct < (Tri_time * 0.75))
	{
		Tri_out = -magnitude / (Tri_time * 0.25) * (CurrentTime_tri - Tri_time * 0.5 - Tri_time * ct);

	}

	else if (CurrentTime_tri - Tri_time * ct >= (Tri_time * 0.75) && CurrentTime_tri - Tri_time * ct <= (Tri_time))
	{
		Tri_out = magnitude / (Tri_time * 0.25) * (CurrentTime_tri - Tri_time * 0.75 - Tri_time * ct) - magnitude;


	}

	return (Tri_out);

}



/********************** �簢�� **************************/

double PulseWave(double magnitude, double Pulse_Frequency, double time) {

	double Vcmd = 0;
	double pluse_time;

	pluse_time = 1 / Pulse_Frequency;

	if (fmod(time, pluse_time) <= (pluse_time / 2)) {
		Vcmd = magnitude;
	}
	else {
		Vcmd = -magnitude;
	}
	return (Vcmd);
}


/********************** ����ȭ üũ  **************************/


double Lamp(double Vcmd) {

	double V = 0;

	V = Vcmd + 0.005;

	return  V;
}





double angularCheck(double Vcmd, double degree) {

	double V = 0;

	V = Vcmd + 0.1;

	if (degree > 60) {

		Vcmd = 0;

	}

	return V;

}

#endif