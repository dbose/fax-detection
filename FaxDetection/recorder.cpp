//**********************************************************
//
// Author: dbose
// Creation date: 25/02/2007
// Description: This file implements the real-time waveIn audio processing
//				hooking the Goertzel computation.
// Completion time: -
//
// Modification history: 
//		[Author]		[Date]			[Modification Log]
//		dbose			01/03/2007		Integration of Answering Machine Detection
//
//*********************************************************

// Recorder.cpp: implementation of the CRecorder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Recorder.h"
#include "GoertzelDTMFFax.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//The process hook function
void Recorder::ProcessForFaxDetection(LPWAVEHDR pwh)
{

	//Realtime FFT/DFT/Goertzel happens here...

	int iBytesPerSample = m_PcmFormat.wBitsPerSample/8;
	int iBytesRecorded = pwh->dwBytesRecorded;

	//Number of samples captured
	int iSamples = iBytesRecorded/iBytesPerSample;

	double* leftChannel = new double[iSamples];

	//For the last block/chunk processing, the buffer will not be full
	//So number of samples recorded at that block takes precedence over the
	//Goertzel sample size
	//int limit = (iSamples > GSAMP_SIZE_NA ? GSAMP_SIZE : iSamples);

	int iVal, iIndex;
	for (DWORD sample = 0; sample < iSamples; sample++)
	{
		//	Get value for each sample
		if (iBytesPerSample == 1)
		{
			iVal = pwh->lpData[sample];
		}
		else
		{
			iIndex = sample*2;
			iVal = pwh->lpData[iIndex];
			iVal += 255*pwh->lpData[iIndex+1];
		}

		//copy audio signal to fft real component for left channel
		leftChannel[sample] = (double)iVal;
		//dw+=2;	//Channel number = 2
	}

	int fDetect;
	//Call the Goertzel engine for computation
	TRY
	{
		CGoertzelDTMFFax faxDetector;
		fDetect = faxDetector.fax_detect(leftChannel, iSamples);
	}
	CATCH_ALL(e)
	{
	}
	END_CATCH_ALL

	delete[] leftChannel;

	if ((bThrottleNotification == false) && (fDetect == 'f'))
	{
		bThrottleNotification = true;

		m_iFaxDetected = true;
	}
}



float Recorder::GetRecordedDuration()
{
	float fRecordedDuration = 0.0;

	fRecordedDuration = ((float)m_wpWavInProData.iTotalWavBytesRecorded)/((float) m_WaveFormat.nAvgBytesPerSec);

	return fRecordedDuration;
}


void Recorder::ProcessForAMSDetection(LPWAVEHDR pWaveHeader)
{
	//Quit on bad header
	if (!pWaveHeader)
		return;

	//Any data on the buffer? If no, no need to progress further
	int iBytesRecorded = pWaveHeader->dwBytesRecorded;
	if (iBytesRecorded <= 0)
		return;

	PWavInProcData pWavData = (PWavInProcData)(pWaveHeader->dwUser);
	if (!pWavData)
		return;

	//Update Total WAV bytes recorder so far
	int iBytesRec = pWaveHeader->dwBytesRecorded;
	if (pWavData->iTotalWavBytesRecorded + iBytesRec >= pWavData->iMaxRecordedBytes)
	{
		iBytesRec = max(0, pWavData->iMaxRecordedBytes - pWavData->iTotalWavBytesRecorded);
	}
	pWavData->iTotalWavBytesRecorded += iBytesRec;

	if (m_iMaxDurationReached)
	{		
		PostAnsResult(AMS_DETECTION_MSG_MAX_TIME_REACHED);
		return;
	}

	//Skip if silence not enabled
	if (!m_iSilenceDetectionEnabled)
		return;

	float fDataTime = GetRecordedDuration();
	float fBufferDuration = ((float) iBytesRecorded)/((float) m_WaveFormat.nAvgBytesPerSec);

	int		iVal, iIndex, iMinData, iMaxData, iBufTotal, iBufAverage, iBufMinAbs;
	float	fBufMaxPercentage;
	char	szText[512];
	float	fSpeakingDuration;

	iMinData = 3200000;
	iMaxData = -3200000;
	iBufMinAbs = 3200000;
	iBufAverage = 0;
	iBufTotal = 0;

	int iBytesPerSample = m_WaveFormat.wBitsPerSample/8;
	int iRead = iBytesRecorded;
	int iSamples = iRead/iBytesPerSample;

	//Analyze this set of samples
	for (int i = 0; i < iSamples; i++)
	{
		//Get value for each sample
		if (iBytesPerSample == 1)
		{
			iVal = pWaveHeader->lpData[i];
		}
		else
		{
			iIndex = i*2;
			iVal = pWaveHeader->lpData[iIndex];
			iVal += 255*pWaveHeader->lpData[iIndex+1];
		}

		//	Update total and min/max
		iBufTotal += iVal;
		iBufMinAbs = min(iBufMinAbs, abs(iVal));

		iMinData = min(iMinData, iVal);
		iMaxData = max(iMaxData, iVal);
	}

	//	Get average and overall max
	iBufTotal = iBufTotal + abs(iMinData*iRead);
	iBufAverage = iBufTotal/iRead;
	m_iBufMax = max(m_iBufMax, iBufAverage);

	int iTargetThreshold = m_iBufMax * m_iSilencePercentage/100;

	if (iBufAverage > iTargetThreshold)
		m_fLastMaxTime = fDataTime;

	fBufMaxPercentage = ((float) iBufAverage)/( (float) m_iBufMax);

	//	Check for silence
	if (m_iSilenceDetectionEnabled)
	{
		if (fDataTime - m_fLastMaxTime > m_iSilencePeriodSec)
		{
			m_iSilenceDetected = TRUE;
		}
	}

	//	Check for AMS detection
	if (m_iEnableAmsDetection && 
		!m_iMaxTimeReached)
	{
		//	If max time, quit now
		if (fDataTime >= m_fMaxTotalAnalysisTime 
			&& !m_iMaxTimeReached && 
			!m_iHumanDetected && 
			!m_iMaxAnalysisTimeReached)
		{

			m_iHumanDetected = TRUE;
			m_iMaxAnalysisTimeReached = TRUE;

			PostAnsResult(AMS_DETECTION_MSG_AMS_NOT_DETECTED_MAX_ANAL_TIME);

			return;
		}

		//	Check for sound level that indicates activity
		//		if (iBufAverage >= 0.1*m_iBufMax)
		if (iBufAverage >= 1000)
		{
		//
		//	Indicates speach is present and talking is occurring
		//
		//
		//	If current state was silence, check for speech starting
			if (m_iSoundState == SOUND_STATE_SILENCE)
			{
				//See if this is a new start time
				if (m_fLastSoundStartTime < 0)
					m_fLastSoundStartTime = fDataTime - fBufferDuration;

				//In a speaking period
				fSpeakingDuration = fDataTime - m_fLastSoundStartTime;

				//If duration greater than threashold and previous state silence, 
				//we are now speaking
				if (fSpeakingDuration >= m_fMinWordDuration)
				{	
					m_iSoundState = SOUND_STATE_SPEAKING;
					m_fLastSoundStopTime = fDataTime;
				}
			}
			else
			{
			//	In a speaking period
				fSpeakingDuration = fDataTime - m_fLastSoundStartTime;

			//	If too long speech, ANS is likely
				if (fSpeakingDuration > m_fMaxInitialSpeechMSec && !m_iAmsDetected)
				{
					m_iAmsDetected = TRUE;
					PostAnsResult(AMS_DETECTION_MSG_AMS_DETECTED_MAX_INITIAL_SPEECH);
				}

				m_fLastSoundStopTime = fDataTime;
			}

		//	Speaking
			m_fLastSoundTime = fDataTime;
		}
		else
		{
		//	In a silence period
			float fSilenceDuration = fDataTime - m_fLastSoundStopTime;

		//	If no words yet and max initial silence, a machine
			if (m_iNumberWords == 0 && 
				fSilenceDuration >= m_fMaxInitialSilenceMSec && 
				!m_iAmsDetected)
			{
				m_iAmsDetected = TRUE;
				PostAnsResult(AMS_DETECTION_MSG_AMS_DETECTED_INIT_SIL);
			}

		//	If just one work and long silence, ANS not likely.  Most likely human who said hell0.
			if (m_iNumberWords == 1 && 
				fSilenceDuration >= m_fMaxSilenceAfterGreetingMSec && 
				!m_iHumanDetected)
			{
				m_iHumanDetected = TRUE;
				PostAnsResult(AMS_DETECTION_MSG_AMS_NOT_DETECTED_MAX_SIL_AFT_GRTN);
			}

		//	If silence greater than word sep and previous state was speaking
			if (fSilenceDuration >= m_fSilenceBetweenWords && 
				m_iSoundState == SOUND_STATE_SPEAKING)
			{
		
			//	Now in silence state
				m_iSoundState = SOUND_STATE_SILENCE;

			//	Increement word count
				m_iNumberWords++;

			//	If too many words, ANS likely
				if (m_iNumberWords >= m_iMaxNumberWords && !m_iAmsDetected)
				{
					m_iAmsDetected = TRUE;
					PostAnsResult(AMS_DETECTION_MSG_AMS_DETECTED_MAX_WORDS);
				}
			}

		//	Check for silence after ANS positive, which likely indicates recording a message
			if (fSilenceDuration >= m_fMaxSilenceAfterANSForRecording && 
				m_iAmsDetected && 
				m_iSoundState == SOUND_STATE_SILENCE && 
				!m_iRemoteRecordingBegun)
			{
				m_iRemoteRecordingBegun = TRUE;
				m_fTimeRemoteRecordingBegan = fDataTime;
				PostAnsResult(AMS_DETECTION_MSG_AMS_DETECTED_RECORDING_BEGAN);
			}

			//	Check for end of remote recording
			if (m_iRemoteRecordingBegun && !m_iRemoteRecordingEnded)
			{
				float fRecordingDuration = fDataTime - m_fTimeRemoteRecordingBegan;

				if (fRecordingDuration >= m_iMaxRemoteRecordingTimeSec)
				{
					m_iRemoteRecordingEnded = TRUE;
					PostAnsResult(AMS_DETECTION_MSG_AMS_DETECTED_RECORDING_ENDED);
				}
			}
		}
	}

}

void Recorder::PostAnsResult(int iCode)
{
	int iParm = 0;

	//Quit if no pointer
	if (!m_pWindow)
		return;

	switch(iCode)
	{
		//	ANS positive results
		case AMS_DETECTION_MSG_AMS_DETECTED_INIT_SIL:
		case AMS_DETECTION_MSG_AMS_DETECTED_MAX_WORDS:
		case AMS_DETECTION_MSG_AMS_DETECTED_MAX_INITIAL_SPEECH:

			//	Skip if Human already detected
			if (m_iHumanDetected)
			{
				return;
			}

			if (::IsWindow(m_pWindow->m_hWnd))
			{
				
				//Check if fax is detected too
				m_pWindow->PostMessage(m_messageID, 
									(m_iFaxDetected == TRUE) ? FAX_MACHINE_DETECTED : ANSWERING_MACHINE_DETECTED, 
									iParm);

			}

		break;

	//	ANS negative results
		case AMS_DETECTION_MSG_AMS_NOT_DETECTED_MAX_SIL_AFT_GRTN:
		case AMS_DETECTION_MSG_AMS_NOT_DETECTED_MAX_ANAL_TIME:

		//Skip if ANS already detected
			if (m_iAmsDetected)
				return;

			if (::IsWindow(m_pWindow->m_hWnd))
			{
				//Signal : Human Detected
				m_pWindow->PostMessage(m_messageID, HUMAN_DETECTED, iParm);
			}

		break;

	//	Other events
		case AMS_DETECTION_MSG_AMS_DETECTED_RECORDING_BEGAN:
			iParm = m_iMaxRemoteRecordingTimeSec;
		break;


		case AMS_DETECTION_MSG_MAX_TIME_REACHED:
			//No AMS, but could be a fax tone
			if (m_iFaxDetected)
			{
				if (::IsWindow(m_pWindow->m_hWnd))
				{
					m_pWindow->PostMessage(m_messageID, FAX_MACHINE_DETECTED, iParm);
				}
			}
			
		break;
	}

}




void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	Recorder* pRecorder = NULL;
	switch (uMsg)
	{
	case WIM_OPEN:
		break;
	case WIM_DATA:

		//if ((((LPWAVEHDR)dwParam1)->dwFlags) == WHDR_DONE)
		{
			pRecorder = (Recorder*)(dwInstance);
			pRecorder->m_lpWaveHdr = (LPWAVEHDR)dwParam1;
			SetEvent(pRecorder->m_hEvent);
		}
		break;
	case WIM_CLOSE:
		break;
	default:
		break;
	}
}
DWORD CALLBACK RecorderThreadFunc(LPVOID lpThreadData)
{
	Recorder* pRecorder = NULL;
	pRecorder = (Recorder*)lpThreadData;
	while (pRecorder->IsRecording())
	{
		WaitForSingleObject(pRecorder->m_hEvent,INFINITE);
		pRecorder->ProcessNextBuffer(pRecorder->m_lpWaveHdr);
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Common initialization routine
void Recorder::Initialize()
{
	bThrottleNotification = false;
	m_waveID = WAVE_MAPPER;
	m_bRecording = FALSE;
	m_bDeviceOpen = FALSE;

	fnProcessBuffer = NULL;
	m_lpWaveHdr = NULL;
	
	m_hEvent = NULL;
	m_hThread = NULL;
	for(int i=0; i<MAXNUMOFBUFFER; i++)
	{
		m_hWaveInHdr[i] = NULL;
		m_hInBuffer[i] = NULL;
	}

	//Initialization specific to Answring Machine Detection
	m_iMaxDurationSec = 0;
	m_iMaxDurationReached = FALSE;
	m_dwStartTime = 0;

	//Set data buffer
	memset(&m_wpWavInProData, 0, sizeof(WavInProcData));

	//Variables used in AMS ActiveX Control
	m_iNumberWords = 0;
	m_iAmsDetected = FALSE;
	m_iHumanDetected = FALSE;
	m_fLastSoundTime = -1.0;
	m_iMaxTimeReached = FALSE;
	m_iMaxAnalysisTimeReached = FALSE;

	m_iFaxDetected = FALSE;

	m_iRemoteRecordingBegun = FALSE;
	m_iRemoteRecordingEnded = FALSE;
	m_fTimeRemoteRecordingBegan = 0;

	m_iMaxRemoteRecordingTimeSec = 120;

	//Constants used in evaluation
	m_fMaxTotalAnalysisTime = 6.0;
	m_fMaxInitialSilenceMSec = 2.5;
	m_iMaxNumberWords = 3;
	m_fMaxSilenceAfterGreetingMSec = 0.80;

	m_iSoundState = SOUND_STATE_SILENCE;
	m_fSilenceBetweenWords = 0.05;
	m_fMinWordDuration = 0.100;
	m_fMaxInitialSpeechMSec = 3.0;
	m_fMaxSilenceAfterANSForRecording = 2.0;

	m_fLastSoundStartTime = -1.0;
	m_fLastSoundStopTime = 0.0;

	m_pWindow = NULL;
	m_messageID = 0;

	m_iEnableAmsDetection = TRUE;
	m_iMaxDurationPad = 300;

}




Recorder::Recorder(int nBufferLength)
{
	Initialize();

	m_nBufferLength = nBufferLength;
	m_PcmFormat.wBitsPerSample = 16;
	m_PcmFormat.wChannels = 1;
	m_PcmFormat.dwSampleRate = 8000;
	m_dwBufferSize = (m_nBufferLength * m_PcmFormat.wChannels * m_PcmFormat.wBitsPerSample / 8);

}

Recorder::Recorder(PCMFORMAT pcm,int nBufferLength)
{
	Initialize();

	m_nBufferLength = nBufferLength;
	m_PcmFormat.wBitsPerSample = pcm.wBitsPerSample;
	m_PcmFormat.wChannels = pcm.wChannels;
	m_PcmFormat.dwSampleRate = pcm.dwSampleRate;
	m_dwBufferSize = (m_nBufferLength * m_PcmFormat.wChannels * m_PcmFormat.wBitsPerSample / 8);
	
}
Recorder::Recorder(WORD wBitsPerSample,WORD wChannels,DWORD dwSampleRate,int nBufferLength)
{
	Initialize();

	m_nBufferLength = nBufferLength;
	m_PcmFormat.wBitsPerSample = wBitsPerSample;
	m_PcmFormat.wChannels = wChannels;
	m_PcmFormat.dwSampleRate = dwSampleRate;
	m_dwBufferSize = (m_nBufferLength * m_PcmFormat.wChannels * m_PcmFormat.wBitsPerSample / 8);
	
}

Recorder::~Recorder()
{
	if(m_bRecording)
		Stop();
	if(m_bDeviceOpen)
        Close();
	fnProcessBuffer = NULL;
}

void Recorder::SetDeviceID(MCIDEVICEID waveID)
{
	if (waveID != WAVE_MAPPER)
		m_waveID = waveID;

	//There is an inherent ordering in starting the detection engine
	//
	//	1. Set the Wave ID - SetDeviceID()
	//	2. Set control parameters  - SetSamplingDetails
	//
	//Probably, this two operations will be done some time before the actual
	//detection begins(ex. StartDetection() etc.). But if too much processing are 
	//done at that crucial time, detection engine will not perform optimally.
	//So we need to find a good place which is neither too early nor too late
	//to open up the Wave Device via waveInOpen() API. The intention is prepare buffers,
	//do N-number of initialization, allocation etc. but not to start the sample collection 
	//phase which is done by waveInStart() API
	//
	//This is the place we are talking for
	Open();

}

BOOL Recorder::Open(MCIDEVICEID wMCIDeviceID, DWORD dwCallBack, DWORD dwCallbackType)
{
	MMRESULT hResult = NULL;

	//Set the device ID
	//SetDeviceID(wMCIDeviceID);

    if(m_bDeviceOpen)
	{
		TRACE("Device Already Opened. Please Stop Recorder before attempting to Open\n");
		return FALSE;
	}
	if (dwCallBack == NULL)
		dwCallBack = (DWORD)waveInProc;

	for(int i=0; i<MAXNUMOFBUFFER; i++)
	{
		m_hWaveInHdr[i] = GlobalAlloc(GHND | GMEM_SHARE , sizeof(WAVEHDR));
		m_lpWaveInHdr[i] = (LPWAVEHDR)GlobalLock(m_hWaveInHdr[i]);
		m_hInBuffer[i] = GlobalAlloc(GHND | GMEM_SHARE , m_dwBufferSize);
		m_lpInBuffer[i] = (LPBYTE)GlobalLock(m_hInBuffer[i]);
		m_lpWaveInHdr[i]->lpData = (LPSTR)m_lpInBuffer[i];
		m_lpWaveInHdr[i]->dwBufferLength = m_dwBufferSize;
		m_lpWaveInHdr[i]->dwBytesRecorded = 0L;
		m_lpWaveInHdr[i]->dwUser = (DWORD)(void*)this;
		m_lpWaveInHdr[i]->dwFlags = 0L;
		m_lpWaveInHdr[i]->dwLoops = 1L;
		m_lpWaveInHdr[i]->lpNext = NULL;
		m_lpWaveInHdr[i]->reserved = 0L;
	}
	m_WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
	m_WaveFormat.nChannels = m_PcmFormat.wChannels;
	m_WaveFormat.wBitsPerSample = m_PcmFormat.wBitsPerSample;
	m_WaveFormat.nSamplesPerSec = m_PcmFormat.dwSampleRate;
	m_WaveFormat.nBlockAlign = m_WaveFormat.nChannels * m_WaveFormat.wBitsPerSample/8;
	m_WaveFormat.nAvgBytesPerSec = m_WaveFormat.nBlockAlign * m_WaveFormat.nSamplesPerSec;

	//Set callback-marshalled data structure
	m_wpWavInProData.iBuffersOutstanding = 0;
	m_wpWavInProData.iMonitoredWavDataReceived = FALSE;
	m_wpWavInProData.iTotalWavBytesRecorded = 0;
	m_wpWavInProData.iMaxRecordedSec = m_iMaxDurationSec;
	m_wpWavInProData.iMaxRecordedBytes = m_WaveFormat.nAvgBytesPerSec * (m_iMaxDurationSec + m_iMaxDurationPad);
	
	hResult = waveInOpen(&m_hWaveIn, 
						m_waveID, 
						&m_WaveFormat, 
						(DWORD)dwCallBack , 
						(DWORD)this, 
						dwCallbackType);

	if (hResult != MMSYSERR_NOERROR)
		return FALSE;

	m_hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
    m_bDeviceOpen=TRUE;

	if (m_pWindow)
	{
		if (::IsWindow(m_pWindow->m_hWnd))
		{
			m_pWindow->PostMessage(m_messageID, AMS_DETECTION_MSG_WAVID_OPENED, 0);
		}
	}

	for(int i=0; i<MAXNUMOFBUFFER; i++)
	{
		// Prepare wave in header
		if(waveInPrepareHeader(m_hWaveIn, m_lpWaveInHdr[i], sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
			return FALSE;

		// Add buffer into recording queue
		if(waveInAddBuffer(m_hWaveIn, m_lpWaveInHdr[i], sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
			return FALSE;
	}

	//Set the sampling frequency for the Goertzel engine
	CGoertzelDTMFFax::sampling_rate = m_PcmFormat.dwSampleRate;

	return TRUE;
}
void Recorder::Start()
{
	if(!m_bDeviceOpen)
	{
		TRACE("Device not Opened. Please open device before attempting to Start\n");
		return;
	}

	if (m_pWindow)
	{
		if (::IsWindow(m_pWindow->m_hWnd))
		{
			m_pWindow->PostMessage(m_messageID, AMS_DETECTION_MSG_RECORDING_STARTED, 0);
		}
	}

	/* Moved to Open()

	for(int i=0; i<MAXNUMOFBUFFER; i++)
	{
		// Prepare wave in header
		if(waveInPrepareHeader(m_hWaveIn, m_lpWaveInHdr[i], sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
			return;

		// Add buffer into recording queue
		if(waveInAddBuffer(m_hWaveIn, m_lpWaveInHdr[i], sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
			return;
	}

	//Set the sampling frequency for the Goertzel engine
	CGoertzelDTMFFax::sampling_rate = m_PcmFormat.dwSampleRate;

	*/

	// Begin sampling
	m_bRecording = TRUE;

	m_hThread = CreateThread(NULL,NULL,RecorderThreadFunc,this,NULL,NULL);
	waveInStart(m_hWaveIn);
	ASSERT(m_hThread!=NULL);

	SetPriorityClass(m_hThread,REALTIME_PRIORITY_CLASS);
	SetThreadPriority(m_hThread,THREAD_PRIORITY_HIGHEST);
	
}
void Recorder::Stop()
{
	if(!m_bDeviceOpen || !m_bRecording)
		return;
	if(waveInStop(m_hWaveIn) != MMSYSERR_NOERROR)
		return;
	else
		m_bRecording=FALSE;

	if (m_hThread != NULL)
		CloseHandle(m_hThread);

	bThrottleNotification = false;
	m_iHumanDetected = FALSE;
	m_iAmsDetected = FALSE;
	m_iFaxDetected = FALSE;

	if (m_pWindow)
	{
		if (::IsWindow(m_pWindow->m_hWnd))
		{
			m_pWindow->PostMessage(m_messageID, AMS_DETECTION_MSG_RECORDING_STOPPED, 0);
		}
	}
}
void Recorder::Close()
{
	if(m_bRecording)
        Stop();
	/*if (m_hThread != NULL)
		CloseHandle(m_hThread);*/
	if(m_bDeviceOpen)
		waveInClose(m_hWaveIn);
	for(int i=0; i<MAXNUMOFBUFFER; i++)
	{
		if (m_hWaveInHdr[i] != NULL)
		{
			if (GlobalUnlock(m_hWaveInHdr[i]))
				GlobalFree(m_hWaveInHdr[i]);
			if (GlobalUnlock(m_hInBuffer[i]))
				GlobalFree(m_hInBuffer[i]);
			m_hWaveInHdr[i] = NULL;
			m_hInBuffer[i] = NULL;
		}
	}
	m_bDeviceOpen=FALSE;
	m_bRecording = FALSE;
	m_hThread = NULL;

	if (m_pWindow)
	{
		if (::IsWindow(m_pWindow->m_hWnd))
		{
			m_pWindow->PostMessage(m_messageID, AMS_DETECTION_MSG_WAVID_CLOSED, 0);
		}
	}

}
void Recorder::SetFormat(LPPCMFORMAT lpPcmFormat)
{
	ASSERT(m_bDeviceOpen==false);
	m_PcmFormat.wBitsPerSample = lpPcmFormat->wBitsPerSample;
	m_PcmFormat.wChannels = lpPcmFormat->wChannels;
	m_PcmFormat.dwSampleRate = lpPcmFormat->dwSampleRate;

	m_dwBufferSize = (m_nBufferLength * m_PcmFormat.wChannels * m_PcmFormat.wBitsPerSample / 8);
}
void Recorder::SetFormat(WORD wBitsPerSample,WORD wChannels,DWORD dwSampleRate)
{
	ASSERT(m_bDeviceOpen==false);
	m_PcmFormat.wBitsPerSample = wBitsPerSample;
	m_PcmFormat.wChannels = wChannels;
	m_PcmFormat.dwSampleRate = dwSampleRate;

	m_dwBufferSize = (m_nBufferLength * m_PcmFormat.wChannels * m_PcmFormat.wBitsPerSample / 8);
}
BOOL Recorder::IsRecording()
{
	return m_bRecording;
}
BOOL Recorder::IsDeviceOpen()
{
	return m_bDeviceOpen;
}

void Recorder::ProcessNextBuffer(LPWAVEHDR pwh)
{
	//Altough looks sequential, we basically
	//deals with the identical buffer sample

	//Process for Fax ANS Tone Detection
	this->ProcessForFaxDetection(pwh);

	//Process for Answering Machine Detection
	pwh->dwUser = (DWORD)(&m_wpWavInProData);	//Probably not 64-bit safe
	this->ProcessForAMSDetection(pwh);

	waveInUnprepareHeader(m_hWaveIn, pwh, sizeof(WAVEHDR));
	waveInPrepareHeader (m_hWaveIn, pwh, sizeof(WAVEHDR));
	waveInAddBuffer(m_hWaveIn, pwh, sizeof(WAVEHDR));
}

DWORD Recorder::GetPosition()
{
	if (m_hWaveIn)
	{
		MMTIME mmtime;
		mmtime.wType = TIME_SAMPLES;
		if (waveInGetPosition(m_hWaveIn, &mmtime, sizeof(MMTIME)) != MMSYSERR_NOERROR)
			return -1;
		else
			return mmtime.u.sample;
	}
	return -1;
}

BOOL Recorder::Pause()
{
	if (m_hWaveIn)
	{
		if (waveInStop(m_hWaveIn) == MMSYSERR_NOERROR)
		{
			m_bRecording = FALSE;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL Recorder::Continue()
{
	if (m_hWaveIn)
	{
		if (waveInStart(m_hWaveIn) == MMSYSERR_NOERROR)
		{
			m_bRecording = FALSE;
			return TRUE;
		}
	}
	return FALSE;
}
BOOL Recorder::IsFormatSupported(WAVEFORMATEX wfEx, UINT nDev)
{
	MMRESULT mm = waveInOpen(0,nDev,&wfEx,0,0,WAVE_FORMAT_QUERY);
	return (BOOL)mm == MMSYSERR_NOERROR;		
}

// Sets the details of the window to which custom messages will be posted
void Recorder::SetMessageWindow(CWnd* pWindow, int messageID)
{
	m_pWindow = pWindow;
	m_messageID = messageID;
}

//Set the PCM details
void Recorder::SetSamplingDetails(LPVOID samplingDetails)
{
	//If null instance, fall back to default values
	if (samplingDetails)
	{
		//This memory pointer is passed from the client(C#/VB etc.)
		PActiveXParmData controlParameter = (PActiveXParmData)samplingDetails;

		//Set Wave formats
		SetFormat(controlParameter->wBitsPerSample, 
					controlParameter->nChannels, 
					controlParameter->nSamplesPerSec);

		//Set Answering Machine Parameters
		m_fMaxTotalAnalysisTime = controlParameter->fMaxAnalysisTime;
		m_fMaxInitialSilenceMSec = controlParameter->fMaxInitialSilence;
		m_iMaxNumberWords = controlParameter->iMaxNumberWords;
		m_fMaxSilenceAfterGreetingMSec = controlParameter->fMaxSilenceAfterGreetingMSec;
		m_iMaxRemoteRecordingTimeSec = controlParameter->iMaxRemoteRecordingTimeSec;
	}

	
}