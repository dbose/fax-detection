using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace FDTest
{
    [StructLayoutAttribute(LayoutKind.Sequential)]
    public struct AmdActiveXParmData
    {
        //    Parms used for control
        public float fMaxAnalysisTime;
        public float fMaxInitialSilence;
        public int iMaxNumberWords;
        public float fMaxSilenceAfterGreeting;
        public int iMaxRemoteRecordingTimeSec;
        //    WAV format control
        public int nChannels;
        public int nSamplesPerSec;
        public int wBitsPerSample;
    }

    public partial class Form1 : Form
    {
        private AmdActiveXParmData m_amdControlData = new AmdActiveXParmData();
        
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            IntPtr m_amdCdPtr = IntPtr.Zero;
            m_amdCdPtr = Marshal.AllocHGlobal(Marshal.SizeOf(m_amdControlData));
            m_amdControlData.fMaxAnalysisTime = 6.0f;
            m_amdControlData.fMaxInitialSilence = 2.5f;
            m_amdControlData.fMaxSilenceAfterGreeting = 0.80f;
            m_amdControlData.iMaxNumberWords = 3;
            m_amdControlData.iMaxRemoteRecordingTimeSec = 120;
            m_amdControlData.nChannels = 1;
            m_amdControlData.nSamplesPerSec = 8000;
            m_amdControlData.wBitsPerSample = 16;
            Marshal.StructureToPtr(m_amdControlData, m_amdCdPtr, true);
            axAMSFaxDetection1.SetControlParameters(m_amdCdPtr.ToInt32());

            //Implicit Open()..
            axAMSFaxDetection1.SetWaveID(0);

            

        }

        private void axFaxDetection1_DetectionStarted(object sender, EventArgs e)
        {
            MessageBox.Show("Fax Detection Started");
        }

        private void axFaxDetection1_FaxToneDetected(object sender, EventArgs e)
        {
            MessageBox.Show("Fax Tone Detected !!!");
        }

        private void axFaxDetection1_DetectionStopped(object sender, EventArgs e)
        {
            MessageBox.Show("Fax Detection Stopped");
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            try
            {
                axAMSFaxDetection1.StartFaxDetection();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            axAMSFaxDetection1.StopFaxDetection();
        }

        private void axFaxDetection1_AnsweringMachineDetected(object sender, EventArgs e)
        {
            MessageBox.Show("AMS Detected !!!");
        }

        private void axFaxDetection1_HumanDetected(object sender, EventArgs e)
        {
            MessageBox.Show("Human Detected !!!");
        }
    }
}