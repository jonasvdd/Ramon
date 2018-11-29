namespace SerialCommunication
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
            this.components = new System.ComponentModel.Container();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.qtableRandomInit_Checkbox = new System.Windows.Forms.CheckBox();
            this.Button_Receive = new System.Windows.Forms.Button();
            this.Button_Connect = new System.Windows.Forms.Button();
            this.Button_Disconnect = new System.Windows.Forms.Button();
            this.ComboBox_AvailableSerialPorts = new System.Windows.Forms.ComboBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.Action1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.action2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Action3 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.action4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.textBox_freq = new System.Windows.Forms.TextBox();
            this.TopTextbox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.Numberofmoves_Label = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.qtableRandomInit_Checkbox);
            this.groupBox1.Controls.Add(this.Button_Receive);
            this.groupBox1.Controls.Add(this.Button_Connect);
            this.groupBox1.Controls.Add(this.Button_Disconnect);
            this.groupBox1.Controls.Add(this.ComboBox_AvailableSerialPorts);
            this.groupBox1.Location = new System.Drawing.Point(30, 29);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(1834, 261);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "USART Communication";
            // 
            // qtableRandomInit_Checkbox
            // 
            this.qtableRandomInit_Checkbox.AutoSize = true;
            this.qtableRandomInit_Checkbox.Location = new System.Drawing.Point(23, 213);
            this.qtableRandomInit_Checkbox.Name = "qtableRandomInit_Checkbox";
            this.qtableRandomInit_Checkbox.Size = new System.Drawing.Size(320, 33);
            this.qtableRandomInit_Checkbox.TabIndex = 4;
            this.qtableRandomInit_Checkbox.Text = "Q-table random initialized";
            this.qtableRandomInit_Checkbox.UseVisualStyleBackColor = true;
            // 
            // Button_Receive
            // 
            this.Button_Receive.Location = new System.Drawing.Point(868, 100);
            this.Button_Receive.Name = "Button_Receive";
            this.Button_Receive.Size = new System.Drawing.Size(138, 63);
            this.Button_Receive.TabIndex = 3;
            this.Button_Receive.Text = "receive";
            this.Button_Receive.UseVisualStyleBackColor = true;
            this.Button_Receive.Click += new System.EventHandler(this.Button_Receive_Click);
            // 
            // Button_Connect
            // 
            this.Button_Connect.Location = new System.Drawing.Point(1447, 100);
            this.Button_Connect.Name = "Button_Connect";
            this.Button_Connect.Size = new System.Drawing.Size(299, 63);
            this.Button_Connect.TabIndex = 2;
            this.Button_Connect.Text = "Connect";
            this.Button_Connect.UseVisualStyleBackColor = true;
            this.Button_Connect.Click += new System.EventHandler(this.Button_Connect_Click);
            // 
            // Button_Disconnect
            // 
            this.Button_Disconnect.Location = new System.Drawing.Point(1117, 100);
            this.Button_Disconnect.Name = "Button_Disconnect";
            this.Button_Disconnect.Size = new System.Drawing.Size(299, 63);
            this.Button_Disconnect.TabIndex = 1;
            this.Button_Disconnect.Text = "Disconnect";
            this.Button_Disconnect.UseVisualStyleBackColor = true;
            this.Button_Disconnect.Click += new System.EventHandler(this.Button_Disconnect_Click);
            // 
            // ComboBox_AvailableSerialPorts
            // 
            this.ComboBox_AvailableSerialPorts.FormattingEnabled = true;
            this.ComboBox_AvailableSerialPorts.Location = new System.Drawing.Point(226, 114);
            this.ComboBox_AvailableSerialPorts.Name = "ComboBox_AvailableSerialPorts";
            this.ComboBox_AvailableSerialPorts.Size = new System.Drawing.Size(425, 37);
            this.ComboBox_AvailableSerialPorts.TabIndex = 0;
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // dataGridView1
            // 
            this.dataGridView1.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Action1,
            this.action2,
            this.Action3,
            this.action4});
            this.dataGridView1.Location = new System.Drawing.Point(648, 365);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 37;
            this.dataGridView1.Size = new System.Drawing.Size(1216, 772);
            this.dataGridView1.TabIndex = 2;
            // 
            // Action1
            // 
            this.Action1.HeaderText = "Action 1";
            this.Action1.Name = "Action1";
            // 
            // action2
            // 
            this.action2.HeaderText = "Action 2";
            this.action2.Name = "action2";
            // 
            // Action3
            // 
            this.Action3.HeaderText = "Action 3";
            this.Action3.Name = "Action3";
            // 
            // action4
            // 
            this.action4.HeaderText = "Action 4";
            this.action4.Name = "action4";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.SkyBlue;
            this.label1.Location = new System.Drawing.Point(1197, 314);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(103, 29);
            this.label1.TabIndex = 3;
            this.label1.Text = "Q-Table";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(30, 365);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(194, 61);
            this.button1.TabIndex = 4;
            this.button1.Text = "Clear";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(30, 458);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(194, 83);
            this.button2.TabIndex = 5;
            this.button2.Text = "Show most used Actions";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // textBox_freq
            // 
            this.textBox_freq.Location = new System.Drawing.Point(30, 579);
            this.textBox_freq.Multiline = true;
            this.textBox_freq.Name = "textBox_freq";
            this.textBox_freq.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox_freq.Size = new System.Drawing.Size(577, 558);
            this.textBox_freq.TabIndex = 6;
            // 
            // TopTextbox
            // 
            this.TopTextbox.Location = new System.Drawing.Point(282, 365);
            this.TopTextbox.Multiline = true;
            this.TopTextbox.Name = "TopTextbox";
            this.TopTextbox.Size = new System.Drawing.Size(325, 135);
            this.TopTextbox.TabIndex = 7;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.SkyBlue;
            this.label2.Location = new System.Drawing.Point(306, 314);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(275, 29);
            this.label2.TabIndex = 8;
            this.label2.Text = "Top 4 most used actions";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.SkyBlue;
            this.label3.Location = new System.Drawing.Point(282, 512);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(209, 29);
            this.label3.TabIndex = 9;
            this.label3.Text = "Number of moves:";
            // 
            // Numberofmoves_Label
            // 
            this.Numberofmoves_Label.AutoSize = true;
            this.Numberofmoves_Label.BackColor = System.Drawing.Color.SkyBlue;
            this.Numberofmoves_Label.Location = new System.Drawing.Point(528, 512);
            this.Numberofmoves_Label.Name = "Numberofmoves_Label";
            this.Numberofmoves_Label.Size = new System.Drawing.Size(26, 29);
            this.Numberofmoves_Label.TabIndex = 10;
            this.Numberofmoves_Label.Text = "0";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(14F, 29F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.BackColor = System.Drawing.Color.SlateGray;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(1871, 1143);
            this.Controls.Add(this.Numberofmoves_Label);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.TopTextbox);
            this.Controls.Add(this.textBox_freq);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button Button_Connect;
        private System.Windows.Forms.Button Button_Disconnect;
        private System.Windows.Forms.ComboBox ComboBox_AvailableSerialPorts;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button Button_Receive;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Action1;
        private System.Windows.Forms.DataGridViewTextBoxColumn action2;
        private System.Windows.Forms.DataGridViewTextBoxColumn Action3;
        private System.Windows.Forms.DataGridViewTextBoxColumn action4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox textBox_freq;
        private System.Windows.Forms.TextBox TopTextbox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label Numberofmoves_Label;
        private System.Windows.Forms.CheckBox qtableRandomInit_Checkbox;
    }
}

