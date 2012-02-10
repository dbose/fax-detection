//**********************************************************
//
// Author: dbose
// Creation date: 25/02/2007
// Description: This file declares the core of Goertzel computation
//				for DTMF/Fax detection
// Completion time: -
//
// Modification history: 
//		[Author]		[Date]			[Modification Log]
//
//*********************************************************
#pragma once

#define  MAX_DTMF_DIGITS      128
#define  SAMPLING_RATE       8000

/* Basic DTMF specs:
*
* Minimum tone on = 40ms
* Minimum tone off = 50ms
* Maximum digit rate = 10 per second
* Normal twist <= 8dB accepted
* Reverse twist <= 4dB accepted
* S/N >= 15dB will detect OK
* Attenuation <= 26dB will detect OK
* Frequency tolerance +- 1.5% will detect, +-3.5% will reject
*/

#define DTMF_THRESHOLD     8.0e7
#define FAX_THRESHOLD      8.0e7
#define FAX_2ND_HARMONIC   2.0     /* 4dB */

#define DTMF_TO_TOTAL_ENERGY	21.0	//42.0(earlier)

/*
   In high level iterative statements, Goertzel can be described as follows

   coeff = 2*cos(2*PI*normalized_frequency);
	for each sample, x[n],
	  s = x[n] + coeff*s_prev - s_prev2;
	  s_prev2 = s_prev;
	  s_prev = s;
	end

	power = s_prev2*s_prev2 + s_prev*s_prev - coeff*s_prev2*s_prev;

	s_prev(s[n-1]) , s_prev2(s[n-2]) and the coeff is pushed to a type called
	goertzel_state_t described below.
*/
typedef struct {
	float v2;
    float v3;
    float fac;
    int samples;
} goertzel_state_t;

//This type summerizes the calculative attributes of a typical
//Goertzel computation for DTMF/Fax detection
typedef struct
{
	goertzel_state_t fax_tone;
    goertzel_state_t fax_tone2nd;  

	float energy;
	int current_sample;
   
	int fax_hits;
} dtmf_detect_state_t;

//Fax frequency(s)
#define FAX_FREQ_CNG 1100.0
#define FAX_FREQ_ANS 2100.0

//Detects std. DTMF and fax
class CGoertzelDTMFFax
{
//Fax Detection Routines
public:
	CGoertzelDTMFFax();
	~CGoertzelDTMFFax();
	int fax_detect(double amp[], int samples);
	static float sampling_rate;
private:
	dtmf_detect_state_t* state;
	static float init();
	static void goertzel_sample(goertzel_state_t *s, short sample);
	static void goertzel_update(goertzel_state_t *s, short *samps, int count);
	static float goertzel_result(goertzel_state_t *s);
	static void goertzel_init(goertzel_state_t *s, float freq, int samples);
	static void goertzel_reset(goertzel_state_t *s);

};
