using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace SerialCommunication
{
    public partial class Form1 : Form
    {
        private Queue<byte[]> dataQueue = new Queue<byte[]>();
        private int[,] Q_table = new int[16, 4];
        private int indexpointer = int.MaxValue;
        private byte[] comArr = new byte[3];

        bool possent = false;
        bool qSent = false;
        private int row;
        private int column;
        private short Q_value;
        private int[,] FreqTable = new int[16, 4];

        private int prevRow = 0;
        private int prevColumn = 0;

        private int iPerm;
        private int jPerm;

        private int[] iPERM = new int[4];
        private int[] jPERM = new int[4];

        private int Iterations = 0;

        public Form1()
        {
            InitializeComponent();                          

            dataGridView1.AllowUserToAddRows = true;
            dataGridView1.RowCount = 16;
            dataGridView1.RowHeadersWidth = 119;
            dataGridView1.Height = 343;

            timer1.Interval = 100;

            Numberofmoves_Label.Visible = false;

            for (int i = 1; i <= 16; i++)
            {
                int perm = i;
                string name = "state " + perm;
                dataGridView1.Rows[perm - 1].HeaderCell.Value = name;
            }

            //datagridview initialiseren
            for (int i = 0; i < 16; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    dataGridView1.Rows[i].Cells[j].Value = (short)0;
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            foreach (string s in SerialPort.GetPortNames())
            {
                ComboBox_AvailableSerialPorts.Items.Add(s);
            }

            ComboBox_AvailableSerialPorts.Text = "Available Serial Ports";

            serialPort1.ReadTimeout = 2000;

            Button_Connect.Visible = true;
            Button_Disconnect.Visible = false;
            Button_Receive.Visible = false;
        }

        private void Button_Connect_Click(object sender, EventArgs e)
        {
            serialPort1.BaudRate = 9600;
            serialPort1.StopBits = StopBits.Two;
            serialPort1.DataBits = 8;
            serialPort1.Handshake = Handshake.None;
            serialPort1.Parity = Parity.None;
            serialPort1.PortName = ComboBox_AvailableSerialPorts.SelectedItem.ToString();

            Button_Connect.Visible = false;
            Button_Disconnect.Visible = true;
            Button_Receive.Visible = true;

            timer1.Start();

            if (qtableRandomInit_Checkbox.Checked == true)
            {
                Iterations = Iterations - 64;
            }

            qtableRandomInit_Checkbox.Visible = false;

            if (serialPort1.IsOpen == false)
            {
                serialPort1.Open();
                serialPort1.DiscardOutBuffer();
                serialPort1.DiscardInBuffer();
            }
        }

        private void Button_Disconnect_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen == true)
            {
                serialPort1.Close();
            }

            Button_Connect.Visible = true;
            Button_Disconnect.Visible = false;
            Button_Receive.Visible = false;

            timer1.Stop();
        }

        private void Button_Receive_Click(object sender, EventArgs e)
        {
            serialPort1.DiscardOutBuffer();
            serialPort1.DiscardInBuffer();
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            Console.WriteLine("data received");
            if (serialPort1.IsOpen == true)
            {
                byte[] data = new byte[serialPort1.BytesToRead];
                Console.WriteLine("numb bytes:\t{0}", data.Length);
                serialPort1.Read(data, 0, data.Length);
                for (int i = 0; i < data.Length; i++)
                {
                    byte[] temp = new byte[1];
                    temp[0] = data[i];
                    if (indexpointer == int.MaxValue && System.Text.Encoding.ASCII.GetString(temp) == Convert.ToString(Protocol.startChar))
                    {
                        indexpointer = 0;
                        Console.WriteLine("char: {0}", System.Text.Encoding.ASCII.GetString(temp));
                        Console.WriteLine("startChar sent");
                    }
                    else if (indexpointer == 3 && System.Text.Encoding.ASCII.GetString(temp) == Convert.ToString(Protocol.endchar))
                    {
                        Console.WriteLine("char: {0}", System.Text.Encoding.ASCII.GetString(temp));
                        Console.WriteLine("endChar sent\n");
                        indexpointer = int.MaxValue;
                        dataQueue.Enqueue(comArr);
                        CompleteQ_table();                        

                    }
                    else if (indexpointer != int.MaxValue)
                    {
                        if (indexpointer <= 2)
                        {
                            Console.WriteLine("data {0}:\t{1}", indexpointer, temp[0]);
                            comArr[indexpointer] = temp[0];
                        }
                        else
                        {
                            Console.WriteLine("error no end char");
                        }
                        indexpointer++;
                    }                   
                }
            }           
        }

        private void CheckTopMoves()
        {
            TopTextbox.Clear();

            int[,] temp = new int[16, 4];
            
            for(int i = 0; i < 16; i ++)
            {
                for(int j = 0; j < 4; j ++)
                {
                    temp[i, j] = FreqTable[i, j];
                }
            }

            int[] topMoves = new int[4];
            int CurrMax = 0;
            int aantal = 0;           

            while(aantal < 4)
            {
                CurrMax = 0;
                for (int i = 0; i < 16; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (temp[i, j] >= CurrMax)
                        {
                            CurrMax = temp[i, j];
                            iPerm = i;
                            jPerm = j;                         
                        }
                    }
                }

                topMoves[aantal] = CurrMax;
                iPERM[aantal] = iPerm;
                jPERM[aantal] = jPerm;
                temp[iPerm, jPerm] = 0;
                aantal++;
            }

            
            for(int i = 0; i < 4; i ++)
            {
                TopTextbox.Text += ("state: " + (iPERM[i] + 1) + ", action: " + (jPERM[i] + 1) + " = " + topMoves[i] + Environment.NewLine);
            }
           
        }

        private void CompleteQ_table()
        {
            char character = Convert.ToChar(comArr[0]);   
            
            switch(character)
            {
                case 'p':
                    prevColumn = column;
                    prevRow = row;
                    row = Convert.ToInt32(comArr[1]);
                    column = Convert.ToInt32(comArr[2]);
                    possent = true;
                    break;
                case 'q':
                    Q_value = comArr[1];
                    Q_value |= (short)(comArr[2] << 8);
                    qSent = true;
                    break;
                case 't':
                    break;
                default:
                    break;

            }         
                            
            if (possent && qSent)
            {               
                dataGridView1.Rows[row].Cells[column].Value = Q_value;
                FreqTable[row, column]++;

                Iterations++;

                ChangeColors();    
      
                Q_table[row, column] = Q_value;
                possent = false;
                qSent = false;
            }
                   
        }

        private void ChangeColors()
        {
            if((short)dataGridView1.Rows[prevRow].Cells[prevColumn].Value >= 50)
            {
                dataGridView1.Rows[row].Cells[column].Style.BackColor = Color.LightYellow;
                dataGridView1.Rows[prevRow].Cells[prevColumn].Style.BackColor = Color.ForestGreen;
            }
            else if ((short)dataGridView1.Rows[prevRow].Cells[prevColumn].Value >= 25)
            {
                dataGridView1.Rows[row].Cells[column].Style.BackColor = Color.LightYellow;
                dataGridView1.Rows[prevRow].Cells[prevColumn].Style.BackColor = Color.LightGreen;
            }
            else if ((short)dataGridView1.Rows[prevRow].Cells[prevColumn].Value >= 0)
            {
                dataGridView1.Rows[row].Cells[column].Style.BackColor = Color.LightYellow;
                dataGridView1.Rows[prevRow].Cells[prevColumn].Style.BackColor = Color.Moccasin;
            }
            else if ((short)dataGridView1.Rows[prevRow].Cells[prevColumn].Value >= -50)
            {
                dataGridView1.Rows[row].Cells[column].Style.BackColor = Color.LightYellow;
                dataGridView1.Rows[prevRow].Cells[prevColumn].Style.BackColor = Color.Orange;
            }
            else
            {
                dataGridView1.Rows[row].Cells[column].Style.BackColor = Color.LightYellow;
                dataGridView1.Rows[prevRow].Cells[prevColumn].Style.BackColor = Color.Red;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            for(int i = 0; i < 16; i++)
            {
                for(int j = 0; j < 4; j++)
                {
                    dataGridView1.Rows[i].Cells[j].Style.BackColor = Color.White;
                    dataGridView1.Rows[i].Cells[j].Value = " ";
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox_freq.Clear();

            for(int i = 0; i < 16; i ++)
            {
                for(int j = 0; j < 4; j++)
                {
                    int permi = i;
                    int permj = j;
                    textBox_freq.Text += "state " + (permi + 1) + ", action " + (permj + 1) + ":" + FreqTable[i, j] + Environment.NewLine;
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if(Iterations >= 0)
            {
                Numberofmoves_Label.Visible = true;
            }
            Numberofmoves_Label.Text = Convert.ToString(Iterations);

            CheckTopMoves();
        }
    }
}
