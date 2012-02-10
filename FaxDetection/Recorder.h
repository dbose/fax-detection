// Recorder.h: interface for the CRecorder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECORDER_H__0ADF01BB_785C_4FA5_B241_3E9D26B90EC9__INCLUDED_)
#define AFX_RECORDER_H__0ADF01BB_785C_4FA5_B241_3E9D26B90EC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

enum FaxDetectionMessageID
{
	FAX_DETECTION_MSG_TONE_DETECTED = 0
};

enum AMSDetectionMessageID
{
	AMS_DETECTION_MSG_INITIALIZE =							10,
	AMS_DETECTION_MSG_DETECTION_STARTED =					100,
	AMS_DETECTION_MSG_WAVID_OPENED =						200,
	AMS_DETECTION_MSG_RECORDING_STARTED = 					220,
	AMS_DETECTION_MSG_RECORDING_STOPPED = 					230,
	AMS_DETECTION_MSG_WAVID_CLOSED = 						400,

	AMS_DETECTION_MSG_AMS_DETECTED_INIT_SIL = 				501,		//	Intidates ANS detected due to long initial silence
	AMS_DETECTION_MSG_AMS_DETECTED_MAX_WORDS =				502,		//	Intidates ANS detected based on too many words 
	AMS_DETECTION_MSG_AMS_DETECTED_MAX_INITIAL_SPEECH =		503,		//	Intidates ANS detected based on too many words 
	AMS_DETECTION_MSG_AMS_NOT_DETECTED_MAX_SIL_AFT_GRTN =	600,		//	Intidates ANS NOT detected due to long silence after initial words completed
	AMS_DETECTION_MSG_AMS_NOT_DETECTED_MAX_ANAL_TIME =		601,		//	Intidates ANS NOT detected due to no key events by termination time
	AMS_DETECTION_MSG_AMS_DETECTED_RECORDING_BEGAN =		700,		//	Indicates ANS detected and remote end recording
	AMS_DETECTION_MSG_AMS_DETECTED_RECORDING_ENDED =		710,		//	Indicates ANS detected and remote end recording ended
	AMS_DETECTION_MSG_MAX_TIME_REACHED =					1000
};

//Aggregated message IDs
enum MachineDetectionMessageID
{
	HUMAN_DETECTED = 0,
	FAX_MACHINE_DETECTED = 1,
	ANSWERING_MACHINE_DETECTED = 2
};

//	ANS Machine States
#define SOUND_STATE_SILENCE			1
#define SOUND_STATE_SPEAKING		2


typedef struct _PCMFORMAT
{
	WORD    wBitsPerSample;//no.of bits per sample for Recording 
	WORD	wChannels;//no.of channels for Recording
	DWORD	dwSampleRate;//Sampling rate for Recording
}PCMFORMAT, *LPPCMFORMAT;

typedef struct _ActiveXParmData
{
	//	Parms used for control
	float	fMaxAnalysisTime; 
	float	fMaxInitialSilence; 
	int		iMaxNumberWords;
	float	fMaxSilenceAfterGreetingMSec;
	int		iMaxRemoteRecordingTimeSec;

	//	WAV format control
	int		nChannels;
	int		nSamplesPerSec;
	int		wBitsPerSample;

} ActiveXParmData, FAR *PActiveXParmData;


struct WAVECLASS
{
	HWAVE hWave;
	void* lpData;
};

typedef struct tagWavInProcData
{
	BOOL		iMonitoredWavDataReceived;
	int			iTotalWavBytesRecorded;
	int			iBuffersOutstanding;

	int			iMaxRecordedSec;
	int			iMaxRecordedBytes;

	BOOL		iStopRequested;

	HWAVEIN		hWave;
	int			iWavBufSize;
	int			iWavInBuffers;

	LPWAVEHDR	lpLastHdr;

} WavInProcData, FAR *PWavInProcData;

#define MAXNUMOFBUFFER 16

typedef BOOL (*ProcessBuffer)(LPWAVEHDR pwh);

class Recorder
{

public:
	void Initialize();
	Recorder(int nBufferLength=1024);
	Recorder(PCMFORMAT pcm,int nBufferLength=1024);
	Recorder(WORD wBitsPerSample,WORD wChannels,DWORD dwSampleRate,int nBufferLength=1024);
	virtual ~Recorder();
	BOOL Open(MCIDEVICEID wMCIDeviceID=WAVE_MAPPER,DWORD dwCallBack=NULL,DWORD dwCallbackType=CALLBACK_FUNCTION);
	void SetDeviceID(MCIDEVICEID waveID);
	void Close();
	void Start();
	void Stop();
	void ProcessNextBuffer(LPWAVEHDR pwh);
	void SetFormat(LPPCMFORMAT lpPcmFormat);
	void SetFormat(WORD wBitsPerSample,WORD wChannels,DWORD dwSampleRate);
	BOOL IsRecording();
	BOOL IsDeviceOpen();
	void SetBufferFunction(ProcessBuffer fnProcess) { fnProcessBuffer = fnProcess; }
	DWORD GetPosition();
	BOOL Pause();
	BOOL Continue();
	BOOL IsFormatSupported(WAVEFORMATEX wfEx, UINT nDev=WAVE_MAPPER);
	
	HANDLE m_hEvent;
	LPWAVEHDR m_lpWaveHdr;

protected:
	//void* m_lpData;
	HANDLE			m_hThread;
	ProcessBuffer	fnProcessBuffer;
	WAVECLASS		m_waveClass;
	GLOBALHANDLE	m_hWaveInHdr[MAXNUMOFBUFFER];
	LPWAVEHDR		m_lpWaveInHdr[MAXNUMOFBUFFER];
	GLOBALHANDLE	m_hInBuffer[MAXNUMOFBUFFER];
	LPBYTE			m_lpInBuffer [MAXNUMOFBUFFER];
	PCMFORMAT		m_PcmFormat;
	WAVEFORMATEX	m_WaveFormat;
	HWAVEIN			m_hWaveIn;
	BOOL			m_bRecording;
	BOOL			m_bDeviceOpen;
	DWORD			m_dwBufferSize;
	CWnd*			m_pWindow;
	int				m_messageID;
	MCIDEVICEID		m_waveID;
	int				m_nBufferLength;
	bool			bThrottleNotification;


	WavInProcData	m_wpWavInProData;
	int				m_iMaxDurationSec;
	int				m_iMaxDurationPad;
	BOOL			m_iMaxDurationReached;

	//Silence variables
	BOOL			m_iSilenceDetectionEnabled;
	BOOL			m_iSilenceDetected;
	int				m_iSilencePercentage;
	int				m_iSilencePeriodSec;

	DWORD			m_dwStartTime;
	int				m_iBufMax;
	float			m_fLastMaxTime;

	//For the ActiveX
	BOOL			m_iEnableAmsDetection;
	BOOL			m_iAmsDetected;
	BOOL			m_iHumanDetected;
	BOOL			m_iMaxTimeReached;
	BOOL			m_iMaxAnalysisTimeReached;

	BOOL			m_iFaxDetected;

	BOOL			m_iRemoteRecordingBegun;
	BOOL			m_iRemoteRecordingEnded;
	float			m_fTimeRemoteRecordingBegan;
	int				m_iMaxRemoteRecordingTimeSec;

	//Intermediary control variables
	float			m_fLastSoundTime;
	float			m_fLastSoundStartTime;
	float			m_fLastSoundStopTime;
	int				m_iNumberWords;
	int				m_iSoundState;

	//Constants used in eval
	float			m_fMaxTotalAnalysisTime;
	float			m_fMaxInitialSilenceMSec;
	float			m_fMaxSilenceAfterGreetingMSec;
	float			m_fMaxInitialSpeechMSec;
	int				m_iMaxNumberWords;
	float			m_fSilenceBetweenWords;
	float			m_fMinWordDuration;
	float			m_fMaxSilenceAfterANSForRecording;

	float GetRecordedDuration();
	void PostAnsResult(int iCode);

	//Realtime processing functions
	void ProcessForFaxDetection(LPWAVEHDR pwh);
	void ProcessForAMSDetection(LPWAVEHDR pwh);
	
public:

	// Sets the details of the window to which custom messages will be posted
	void SetMessageWindow(CWnd* pWindow, int messageID);

	//Set control parameters(PCM details mostly)
	void SetSamplingDetails(LPVOID samplingDetails);
};

#endif // !defined(AFX_RECORDER_H__0ADF01BB_785C_4FA5_B241_3E9D26B90EC9__INCLUDED_)
