using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using LibUsbDotNet;
using LibUsbDotNet.Info;
using LibUsbDotNet.Main;



namespace VUSBProba
{
    public partial class Form1 : Form
    {
        public static UsbDevice MyUsbDevice;
        public static UsbDeviceFinder MyUsbFinder = new UsbDeviceFinder(0xffd2, 0x01aa);
        System.Windows.Forms.Timer   timer = new System.Windows.Forms.Timer();
        

        public Form1()
        {
            InitializeComponent();
            timer.Interval = 1000;  //интервал между срабатываниями 1000 миллисекунд
            timer.Tick += new EventHandler(timer_Tick);
            timer.Start();
        }

        void timer_Tick(object sender, EventArgs e)
        {
            MyUsbDevice = UsbDevice.OpenUsbDevice(MyUsbFinder);


            //выводим надпись о состоянии подключения 
            if (MyUsbDevice != null)
            {
                label2.Text = " Подключено !";
            }
            else label2.Text = " Не найдено !";


            int countIn;
            //получаем данные от МК
            UsbSetupPacket packet = new UsbSetupPacket((byte)(UsbCtrlFlags.RequestType_Vendor |
            UsbCtrlFlags.Recipient_Device | UsbCtrlFlags.Direction_In), 2, (short)0, (short)0, (short)0);
            byte[] buffer = new byte[1024];

            try
            {

                if (MyUsbDevice.ControlTransfer(ref packet, buffer, 1024, out countIn))
                {

                    //преобразование значений буффера в текст      
                    string temp = System.Text.Encoding.UTF8.GetString(buffer, 0, 6);
                    //выводим результат измерений 
                    label4.Text = temp;
                    String rom = System.Text.Encoding.UTF8.GetString(buffer, 7, 8);
                    label5.Text = rom;

                }

            }
            catch (NullReferenceException)
            {
                label4.Text = "Подкючите устройство!";
                label5.Text = "Подкючите устройство!";
            }
        }

       
       
           

        }
    
        
 }



    
      


        
    
