using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO.Ports;

namespace ArduionoControl
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        bool isConnected = false;
        SerialPort port;
        public MainWindow()
        {
            InitializeComponent();
        }
       
        private void btnUpdateCOMList_Click(object sender, RoutedEventArgs e)
        {
            comboBoxSelectPorts.Items.Clear();
            string[] portnames = SerialPort.GetPortNames();
            if (portnames.Length == 0)
            {
                MessageBox.Show("COM PORT not found");
            }
            foreach (string s in portnames)
            {
                comboBoxSelectPorts.Items.Add(s);
            }
        }
        private void connectToArduino()
        {
            isConnected = true;
            string selectedPort = comboBoxSelectPorts.SelectedValue.ToString();
            port = new SerialPort(selectedPort, 9600, Parity.None, 8, StopBits.One);
            port.Open();
            stateEl.Fill = Brushes.Green;
          //  labelStateOfConnection.Content = "State of connection: connect";
            
        }

        private void disconnectFromArduino()
        {
           
            isConnected = false;
            port.Close();
            stateEl.Fill = Brushes.Red;
            //   labelStateOfConnection.Content = "State of connection: disconnect";
           
        }

        private void btnConnect_Click(object sender, RoutedEventArgs e)
        {
            if (!isConnected)
            {
                connectToArduino();
            }
           

        }
        private void btnDisconnect_Click(object sender, RoutedEventArgs e)
        {
            if(isConnected)
            {
                disconnectFromArduino();
            }
        }
        private void btnLEDOn_Click(object sender, RoutedEventArgs e)
        {
            try
            {
             
                port.Write("#x|");   // включаем светодиод 
            }
            catch (Exception)
            {
                MessageBox.Show("Please to connect!", "Not connect");
            }

        }

        private void btnLEDOff_Click(object sender, RoutedEventArgs e)
        {
            try
            {
              
                port.Write("#w|");  // выключаем светодиод 
            }
            catch (Exception)
            {
                MessageBox.Show("Please to connect!", "Not connect");
            }
        }

       
    }
}
