namespace FDTest
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.btnStart = new System.Windows.Forms.Button();
            this.btnStop = new System.Windows.Forms.Button();
            this.axAMSFaxDetection1 = new AxAMSFaxDetectionLib.AxAMSFaxDetection();
            ((System.ComponentModel.ISupportInitialize)(this.axAMSFaxDetection1)).BeginInit();
            this.SuspendLayout();
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(139, 21);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(136, 23);
            this.btnStart.TabIndex = 1;
            this.btnStart.Text = "Start Fax Detection";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // btnStop
            // 
            this.btnStop.Location = new System.Drawing.Point(139, 50);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(136, 23);
            this.btnStop.TabIndex = 2;
            this.btnStop.Text = "Stop Fax Detection";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // axAMSFaxDetection1
            // 
            this.axAMSFaxDetection1.Enabled = true;
            this.axAMSFaxDetection1.Location = new System.Drawing.Point(12, 21);
            this.axAMSFaxDetection1.Name = "axAMSFaxDetection1";
            this.axAMSFaxDetection1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axAMSFaxDetection1.OcxState")));
            this.axAMSFaxDetection1.Size = new System.Drawing.Size(100, 50);
            this.axAMSFaxDetection1.TabIndex = 3;
            this.axAMSFaxDetection1.FaxToneDetected += new System.EventHandler(this.axFaxDetection1_FaxToneDetected);
            this.axAMSFaxDetection1.AnsweringMachineDetected += new System.EventHandler(this.axFaxDetection1_AnsweringMachineDetected);
            this.axAMSFaxDetection1.HumanDetected += new System.EventHandler(this.axFaxDetection1_HumanDetected);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(296, 208);
            this.Controls.Add(this.axAMSFaxDetection1);
            this.Controls.Add(this.btnStop);
            this.Controls.Add(this.btnStart);
            this.Name = "Form1";
            this.Text = "Fax Detection TestHarness";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.axAMSFaxDetection1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Button btnStop;
        private AxAMSFaxDetectionLib.AxAMSFaxDetection axAMSFaxDetection1;


    }
}

