//**********************************************************
//
// Author: dbose
// Creation date: 27/02/2007
// Description: This file implements the core of Goertzel computation
//				for DTMF/Fax detection
// Completion time: -
//
// Modification history: 
//		[Author]		[Date]			[Modification Log]
//
//*********************************************************

#include "StdAfx.h"
#include "GoertzelDTMFFax.h"

#ifndef _USE_MATH_DEFINES
	#define	_USE_MATH_DEFINES
#endif
#include <math.h>

CGoertzelDTMFFax::CGoertzelDTMFFax()
{
	int i;
 
	//Allocate the dtmf_detect_state_t
	state = (dtmf_detect_state_t *)malloc(sizeof(dtmf_detect_state_t));
	memset(state, 0, sizeof(state));

    state->energy = 0.0;
	
    /* Same for the fax dector */
	CGoertzelDTMFFax::goertzel_init(&state->fax_tone, FAX_FREQ_ANS, 102);
 
	/* Same for the fax dector 2nd harmonic */
	CGoertzelDTMFFax::goertzel_init(&state->fax_tone2nd, FAX_FREQ_ANS * 2.0, 102);

	state->fax_hits = 0;
    state->current_sample = 0;
}

CGoertzelDTMFFax::~CGoertzelDTMFFax()
{
	if(state)
	{
		free(state);
		state = NULL;
	}
	return;

}

float CGoertzelDTMFFax::init()
{
	return SAMPLING_RATE;
}

float CGoertzelDTMFFax::sampling_rate = CGoertzelDTMFFax::init();

/*
 * Initialization for Goertzel computation
 *
 * coef = 2.0 * cos( (2.0 * PI * target_freq) / SAMPLING_RATE );
 */
void CGoertzelDTMFFax::goertzel_init(goertzel_state_t *s, float freq, int samples)
{
    s->v2 = s->v3 = 0.0;
    s->fac = 2.0 * cos(2.0 * M_PI * (freq / CGoertzelDTMFFax::sampling_rate));
    s->samples = samples;
}

//One iterative step of the computation
void CGoertzelDTMFFax::goertzel_sample(goertzel_state_t* s, short sample)
{
	float v1;
	float fsamp  = sample;
    
    v1 = s->v2;
    s->v2 = s->v3;
    s->v3 = s->fac * s->v2 - v1 + fsamp;
}

//For all samples, update the goertzel_state_t variable
void CGoertzelDTMFFax::goertzel_update(goertzel_state_t* s, short* samps, int count)
{
    int i;

    for (i=0;i<count;i++) 
		goertzel_sample(s, samps[i]);
}

//Power calculation:
//
//	power = s_prev2*s_prev2 + s_prev*s_prev - coeff*s_prev2*s_prev;
//
float CGoertzelDTMFFax::goertzel_result(goertzel_state_t *s)
{
    return s->v3 * s->v3 + s->v2 * s->v2 - s->v2 * s->v3 * s->fac;
}

void CGoertzelDTMFFax::goertzel_reset(goertzel_state_t *s)
{
    s->v2 = s->v3 = 0.0;
}

int CGoertzelDTMFFax::fax_detect
(
	double					amp[], 
	int						samples
)
{
	double fax_energy;
	double fax_energy_2nd;
    double famp;
    float v1;
    int i;
    int j;
    int sample;
    int hit;
    int limit;
 
    hit = 0;
    for (sample = 0;  sample < samples;  sample = limit) 
	{
       /* 102 is optimised to meet the DTMF specs. */
       if ((samples - sample) >= (102 - state->current_sample))
          limit = sample + (102 - state->current_sample);
       else
          limit = samples;

       for (j=sample;j<limit;j++) 
	   {
          famp = amp[j];
          state->energy += famp*famp;

		  //goertzel_sample(&(state->fax_tone), famp);
          v1 = state->fax_tone.v2;
          state->fax_tone.v2 = state->fax_tone.v3;
          state->fax_tone.v3 = state->fax_tone.fac*state->fax_tone.v2 - v1 + famp;

		  //goertzel_sample(&(state->fax_tone2nd), famp);
          v1 = state->fax_tone.v2;
          state->fax_tone2nd.v2 = state->fax_tone2nd.v3;
          state->fax_tone2nd.v3 = state->fax_tone2nd.fac*state->fax_tone2nd.v2 - v1 + famp;

       }

	   state->current_sample += (limit - sample);
         
       /* Detect the fax energy */
       fax_energy = goertzel_result(&state->fax_tone);
	   
	   hit = 0;

       if ((fax_energy >= FAX_THRESHOLD) && 
          (fax_energy >= DTMF_TO_TOTAL_ENERGY*state->energy)) 
	   {               
		    
		    //Bug here...
		    //Test the 2nd harmonic too
		    
			/*fax_energy_2nd = goertzel_result(&state->fax_tone2nd);
			if (fax_energy_2nd * FAX_2ND_HARMONIC < fax_energy)
			{
			
			  Probably need better checking than just this the energy
			}*/
			
			hit = 'f';
			state->fax_hits++;

			//Enough of it...
			if (state->fax_hits > 5) 
			{
				break;
			}
       }

       goertzel_reset (&state->fax_tone);
       goertzel_reset (&state->fax_tone2nd);

       state->energy = 0.0;
       state->current_sample = 0;
    }

    return (hit);
}










