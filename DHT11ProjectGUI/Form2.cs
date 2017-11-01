using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using sf;

namespace sf
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();

            CommPort com = CommPort.Instance;

            int found = 0;
            string[] portList = com.GetAvailablePorts();
            for (int i=0; i<portList.Length; ++i)
            {
                string name = portList[i];
                comboBox1.Items.Add(name);
                if (name == Settings.Port.PortName)
                    found = i;
            }
            if (portList.Length > 0)
                comboBox1.SelectedIndex = found;

            Int32[] baudRates = {
                100,300,600,1200,2400,4800,9600,14400,19200,
                38400,56000,57600,115200,128000,256000,0
            };
            found = 0;
            for (int i=0; baudRates[i] != 0; ++i)
            {
                comboBox2.Items.Add(baudRates[i].ToString());
                if (baudRates[i] == Settings.Port.BaudRate)
                    found = i;
            }
            comboBox2.SelectedIndex = found;



            foreach (string s in Enum.GetNames(typeof(Parity)))
            {
               
            }
          
            foreach (string s in Enum.GetNames(typeof(StopBits)))
            {
          
            }
         
            foreach (string s in Enum.GetNames(typeof(Handshake)))
            {
             
            }
          
		}

		
		private void button1_Click(object sender, EventArgs e)
		{
			Settings.Port.PortName = comboBox1.Text;
			Settings.Port.BaudRate = Int32.Parse(comboBox2.Text);
			

		
			CommPort com = CommPort.Instance;
			com.Open();

			Settings.Write();

			Close();
		}

		
        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }

		private void button3_Click(object sender, EventArgs e)
        {
            Settings.Option.LogFileName = "";

            SaveFileDialog fileDialog1 = new SaveFileDialog();

            fileDialog1.Title = "Save Log As";
            fileDialog1.Filter = "Log files (*.log)|*.log|All files (*.*)|*.*";
            fileDialog1.FilterIndex = 2;
            fileDialog1.RestoreDirectory = true;
			fileDialog1.FileName = Settings.Option.LogFileName;

            if (fileDialog1.ShowDialog() == DialogResult.OK)
            {
				
			}
            else
            {
				
            }
        }
    }
}