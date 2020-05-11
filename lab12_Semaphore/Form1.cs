using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SP12_Semaphore
{
    public partial class Form1 : Form
    {
        Semaphore semaphore = new Semaphore(1, 1);
        public Form1()
        {
            InitializeComponent();
            Task.Run(() =>
            {
                while (true)
                {
                    ChangeBG(Color.Yellow);
                    Thread.Sleep(new TimeSpan(0, 0, 1));
                }
            });
            Task.Run(() =>
            {
                while (true)
                {
                    ChangeBG(Color.Blue);
                    Thread.Sleep(new TimeSpan(0, 0, 1));
                }

            });
            Task.Run(() =>
            {
                while (true)
                {
                    ChangeBG(Color.Black);
                    Thread.Sleep(new TimeSpan(0, 0, 1));
                }
            });
        }
        void ChangeBG(Color color)
        {
            semaphore.WaitOne();
            this.BackColor = color;
            Thread.Sleep(1000);
            semaphore.Release();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
