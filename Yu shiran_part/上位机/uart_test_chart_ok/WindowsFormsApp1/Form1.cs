using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;//头文件
using System.Windows.Forms.DataVisualization.Charting;
using System.Threading;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);
            serialPort1.Encoding = Encoding.GetEncoding("GB2312");
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;

            chart1.Series.Add("line1");//折线图创建图线
            chart1.Series["line1"].Color = Color.Red;
            this.chart1.ChartAreas[0].AxisY.Minimum = 0;
            this.chart1.ChartAreas[0].AxisY.Maximum = 10;
            this.chart1.ChartAreas[0].AxisX.Minimum = 0;
            this.chart1.ChartAreas[0].AxisX.Maximum = 90;
            chart1.Series["line1"].ChartType = SeriesChartType.Line ;


        }
        /////////////////////////////////////////////////////////////////图表区
        void chart_display()
        {
            Draw();
        }
        delegate void my_delegate();//创建一个代理,图表刷新需要在主线程，所以需要加委托
        Queue<double> Q1 = new Queue<double>();
        public void Draw()
        {
            if (!chart1.InvokeRequired)
            {
                this.chart1.Series["line1"].Points.Clear();
                for (int i = 0; i < FFF_chart.Length; i++)
                {
                    chart1.Series["line1"].Points.AddXY(i, FFF_chart[i]);
                }
            }
            else
            {
                my_delegate delegate_FFF = new my_delegate(Draw);
                Invoke(delegate_FFF, new object[] { });//执行唤醒操作
            }
        }

       
        private void Form1_Load(object sender, EventArgs e)
        {
            FFF_chart = new double[90];
        }
        /// /////////////////////////////////////////////////////////////////////////数据接收部分
        byte[] buf; ////缓冲数组
        public double[] FFF_chart;
        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)//接收函数  SerialDataReceivedEventArgs写错，导致错误，谨记
        {
            Thread chart_display_th = new Thread(new ThreadStart(chart_display));////////数值显示线程
            chart_display_th.Start();
            try
            {
                string recive_data;
                //recive_data = serialPort1.ReadExisting();
                //textBox1.AppendText(recive_data);
                //textBox1.AppendText("\r\n");
                buf = new byte[serialPort1.BytesToRead];//定义缓冲数组
                serialPort1.Read(buf, 0, buf.Length);
                if (buf.Length >= 3 && buf[0] == 65 && buf[1] == 65 && buf[2] == 65)// && buf[29] == 122 && buf[30] == 122 && buf[31] == 122
                {
                    for (int count_i = 0; count_i < 89; count_i++)
                    { FFF_chart[count_i] = FFF_chart[count_i + 1]; }
                    FFF_chart[89] = buf[3]-48;
                }

            }
            catch { }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
       


        /// //////////////////////////////////////////////////////////////////////搜索串口部分
        private void button1_Click(object sender, EventArgs e)
        {
            SearchAnAddSerialToComboBox(serialPort1, comboBox1);
        }
        private void SearchAnAddSerialToComboBox(SerialPort MyPort, ComboBox MyBox)//搜索串口函数
        { //将可用的串口号添加到ComboBox
            string[] NmberOfport = new string[20];//最多容纳20个，太多会卡，影响效率
            string MidString1;//中间数组，用于缓存
            MyBox.Items.Clear();//清空combobox的内容
            for (int i = 1; i < 20; i++)
            {
                try //核心是靠try和catch 完成遍历
                {
                    MidString1 = "COM" + i.ToString();  //把串口名字赋给MidString1
                    MyPort.PortName = MidString1;       //把MidString1赋给 MyPort.PortName 
                    MyPort.Open();                      //如果失败，后面代码不执行？？
                    NmberOfport[i - 1] = MidString1;    //依次把MidString1的字符赋给NmberOfport
                    MyBox.Items.Add(MidString1);        //打开成功，添加到下列列表
                    MyPort.Close();                     //关闭
                    MyBox.Text = NmberOfport[i - 1];    //显示最后扫描成功那个串口
                }
                catch { };
            }
        }
  
        /// ////////////////////////////////////////////////////////////////////////////////打开串口部分
        private void button2_Click(object sender, EventArgs e)
        {
            if (button2.Text == "打开串口")//为0时，表示关闭，此时可以进行打开操作
            {
                try
                {
                    serialPort1.PortName = comboBox1.Text;//获取端口号
                    serialPort1.BaudRate = Convert.ToInt32(comboBox2.Text);//设置波特率
                    serialPort1.Open();//打开串口
                    button2.Text = " 关闭串口";
                }
                catch
                {
                    MessageBox.Show("串口打开错误");
                }
            }
            else  //为1时，表示开启，此时可以进行关闭操作
            {
                try
                {
                    serialPort1.Close();//关闭串口
                    button2.Text = "打开串口";//置位为0，表示状态为关闭
                }
                catch { }
            }
        }
        /// <summary>
        /// /////////////////////////////////////////////////////////////清空显示部分
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button3_Click(object sender, EventArgs e)
        {
            textBox1.Clear();
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
