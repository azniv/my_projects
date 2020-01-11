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

namespace arduinoControl
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

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

       

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            if (!isConnected)
            {
                isConnected = true;
                string selectedPort = cBSelectPorts.SelectedValue.ToString();
                port = new SerialPort(selectedPort, 9600, Parity.None, 8, StopBits.One);
                port.Open();
                state.Fill = Brushes.Green;
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            cBSelectPorts.Items.Clear();
            string[] portnames = SerialPort.GetPortNames();
            if (portnames.Length == 0)
            {
                MessageBox.Show("COM PORT not found");
            }
            foreach (string s in portnames)
            {
                cBSelectPorts.Items.Add(s);
            }
        }

        private void btnDisconnect_Click(object sender, RoutedEventArgs e)
        {
            if (isConnected)
            {
                isConnected = false;
                port.Close();
                state.Fill = Brushes.Red;
            }
        }

        private void btnLedOn_Click(object sender, RoutedEventArgs e)
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

        private void btnLedOff_Click(object sender, RoutedEventArgs e)
        {
            try
            {

                port.Write("#w|");   // включаем светодиод 
            }
            catch (Exception)
            {
                MessageBox.Show("Please to connect!", "Not connect");
            }
        }
    }
}
