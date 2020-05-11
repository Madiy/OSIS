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

namespace SP12
{
    public partial class Form1 : Form
    {
        Mutex mutexObj = new Mutex();
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
        public void ChangeBG(Color color)
        {
            mutexObj.WaitOne();
            this.BackColor = color;
            Thread.Sleep(new TimeSpan(0, 0, 1));

            mutexObj.ReleaseMutex();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
