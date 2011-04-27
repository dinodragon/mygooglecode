namespace CallShellCmd
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.textBox_window = new System.Windows.Forms.TextBox();
            this.button_Run = new System.Windows.Forms.Button();
            this.textBox_cmd = new System.Windows.Forms.TextBox();
            this.textBox_parameter = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button_clean = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox_window
            // 
            this.textBox_window.Location = new System.Drawing.Point(12, 12);
            this.textBox_window.Multiline = true;
            this.textBox_window.Name = "textBox_window";
            this.textBox_window.Size = new System.Drawing.Size(914, 385);
            this.textBox_window.TabIndex = 0;
            // 
            // button_Run
            // 
            this.button_Run.Location = new System.Drawing.Point(745, 404);
            this.button_Run.Name = "button_Run";
            this.button_Run.Size = new System.Drawing.Size(75, 23);
            this.button_Run.TabIndex = 1;
            this.button_Run.Text = "运行";
            this.button_Run.UseVisualStyleBackColor = true;
            this.button_Run.Click += new System.EventHandler(this.button_Run_Click);
            // 
            // textBox_cmd
            // 
            this.textBox_cmd.Location = new System.Drawing.Point(59, 404);
            this.textBox_cmd.Name = "textBox_cmd";
            this.textBox_cmd.Size = new System.Drawing.Size(100, 20);
            this.textBox_cmd.TabIndex = 2;
            this.textBox_cmd.Text = "ping";
            // 
            // textBox_parameter
            // 
            this.textBox_parameter.Location = new System.Drawing.Point(234, 404);
            this.textBox_parameter.Name = "textBox_parameter";
            this.textBox_parameter.Size = new System.Drawing.Size(495, 20);
            this.textBox_parameter.TabIndex = 3;
            this.textBox_parameter.Text = "localhost";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(10, 408);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(43, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "命令：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(185, 408);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(43, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "参数：";
            // 
            // button_clean
            // 
            this.button_clean.Location = new System.Drawing.Point(851, 404);
            this.button_clean.Name = "button_clean";
            this.button_clean.Size = new System.Drawing.Size(75, 23);
            this.button_clean.TabIndex = 5;
            this.button_clean.Text = "清空";
            this.button_clean.UseVisualStyleBackColor = true;
            this.button_clean.Click += new System.EventHandler(this.button_clean_Click);
            // 
            // Form1
            // 
            this.AcceptButton = this.button_Run;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(938, 436);
            this.Controls.Add(this.button_clean);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox_parameter);
            this.Controls.Add(this.textBox_cmd);
            this.Controls.Add(this.button_Run);
            this.Controls.Add(this.textBox_window);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_window;
        private System.Windows.Forms.Button button_Run;
        private System.Windows.Forms.TextBox textBox_cmd;
        private System.Windows.Forms.TextBox textBox_parameter;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button_clean;
    }
}

