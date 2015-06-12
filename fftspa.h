#ifndef _FFT_SPA_H_
#define _FFT_SPA_H_
#define ONEWAY

//#include <ap_cint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "ap_fixed.h"
#include "ap_int.h"
extern "C" float sqrtf(float);
extern "C" float cosf(float);
extern "C" float logf(float);
#include <iostream>
#include <string>
#include <fstream>
using namespace std;




#ifndef FX_POINT
typedef float llr;
typedef float hadamard_llr;
#else
typedef ap_fixed< 8, 1, AP_RND_INF, SC_SAT > llr;
typedef ap_fixed<16, 3, AP_RND_INF, SC_SAT > hadamard_llr;
#endif


#define WORDS 4
#define SQR(A) ((A)*(A))
#define PI 3.1415926536
#define BPSK(x) (1.0f-2.0f*(x))

//--------------------------------------------------
// channel
//--------------------------------------------------
//#define BEC
#define AWGN
//#define BSC
//--------------------------------------------------
// Galois Field
//--------------------------------------------------
// #define LOG_GF   1
// #define LOG_GF   2
// #define LOG_GF   3
// #define LOG_GF   4
// #define LOG_GF   5
// #define LOG_GF   6
// #define LOG_GF   7
#define LOG_GF   2
#define GF  (1<<(LOG_GF))
//--------------------------------------------------


#define SO stdout
#define MAX(a,b) ( ((a)>(b) ) ? (a) : (b) )
#define MIN(a,b) ( ((a)<(b) ) ? (a) : (b) )

//#define TOTAL_EDGE	10240/LOG_GF*2*3
//#define TOTAL_EDGE	1024/LOG_GF*2*3
//#define TOTAL_EDGE	512/LOG_GF*2*3
//#define TOTAL_EDGE	384/LOG_GF*2*3
//#define TOTAL_EDGE	192/LOG_GF*2*3

#define TOTAL_EDGE      768

#define VARIABLE_WEIGHT		2
#define CHECK_WEIGHT		3
#define VARIABLE_NUM		TOTAL_EDGE / VARIABLE_WEIGHT
#define CHECK_NUM		TOTAL_EDGE / CHECK_WEIGHT


#define VLEN 256
#define VLLEN 8
#define JOBS TOTAL_EDGE

/*
   TPB - Threads per block
   BPG - Blocks per grid
*/
#define TPB 128
#define BPG 300

//For fft's
typedef struct {
  float* x;
} Vector;


const float RATE = (((float)(CHECK_WEIGHT-VARIABLE_WEIGHT))/CHECK_WEIGHT);

void FFTSPA_Simulator(llr *messages,int *decision,int *word,
		int errorSymbols[1],  int errorWords[1], int avgIterations[1], int maxIterations[1],float SNR[1],
		int error_counter[1]);
void InitEncoding(int interleaver[TOTAL_EDGE],int MatValue[TOTAL_EDGE],int M,int N,int ADDGF[GF*GF],int MULGF[GF*GF],int DIVGF[GF*GF],int G[(VARIABLE_NUM-CHECK_NUM)*VARIABLE_NUM]);
void Encoding(int K,int N,int G[(VARIABLE_NUM-CHECK_NUM)*VARIABLE_NUM],int Symbol[VARIABLE_NUM],int ADDGF[GF*GF],int MULGF[GF*GF],int zero_cw);
void initialize_message(float d_input[GF*VARIABLE_NUM], int d_BINGF[GF*LOG_GF],int d_Symbol[VARIABLE_NUM], float d_Rand1[VARIABLE_NUM*LOG_GF], float d_Rand2[VARIABLE_NUM*LOG_GF],float d_ch[1],float d_rw[LOG_GF*VARIABLE_NUM],int d_Bit[VARIABLE_NUM*LOG_GF],int n);
void init_mcv(float *mcv,int i);
/*void fftspa(float input[GF*VARIABLE_NUM],float mvc[GF*TOTAL_EDGE], float mcv[GF*TOTAL_EDGE],
		int decisionB[LOG_GF*VARIABLE_NUM],int decisionS[VARIABLE_NUM],int syndromeS[CHECK_NUM],
		int h_Symbol[VARIABLE_NUM],int cnt_error[1],int ir[1],int NIter);
*/

void fftspa(volatile int*,volatile llr*);
void fftspa(volatile int*,volatile llr



#endif
