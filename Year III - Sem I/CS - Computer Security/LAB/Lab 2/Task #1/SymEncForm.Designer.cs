
namespace Task_1
{
	partial class SymEncForm
	{
		private System.ComponentModel.IContainer components = null;

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
			this.plainHexTextBox = new System.Windows.Forms.TextBox();
			this.encyptionTypeComboBox = new System.Windows.Forms.ComboBox();
			this.plainAsciiTextBox = new System.Windows.Forms.TextBox();
			this.encryptButton = new System.Windows.Forms.Button();
			this.cipherAsciiTextBox = new System.Windows.Forms.TextBox();
			this.cipherHexTextBox = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.decryptButton = new System.Windows.Forms.Button();
			this.keyTextBox = new System.Windows.Forms.TextBox();
			this.ivTextBox = new System.Windows.Forms.TextBox();
			this.generateButton = new System.Windows.Forms.Button();
			this.label5 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.label7 = new System.Windows.Forms.Label();
			this.label8 = new System.Windows.Forms.Label();
			this.encTimeLabel = new System.Windows.Forms.Label();
			this.decTimeLabel = new System.Windows.Forms.Label();
			this.label11 = new System.Windows.Forms.Label();
			this.label12 = new System.Windows.Forms.Label();
			this.encTimeButton = new System.Windows.Forms.Button();
			this.decTimeButton = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// plainHexTextBox
			// 
			this.plainHexTextBox.Enabled = false;
			this.plainHexTextBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.plainHexTextBox.Location = new System.Drawing.Point(12, 300);
			this.plainHexTextBox.Multiline = true;
			this.plainHexTextBox.Name = "plainHexTextBox";
			this.plainHexTextBox.Size = new System.Drawing.Size(552, 50);
			this.plainHexTextBox.TabIndex = 1;
			// 
			// encyptionTypeComboBox
			// 
			this.encyptionTypeComboBox.Font = new System.Drawing.Font("Calibri", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.encyptionTypeComboBox.FormattingEnabled = true;
			this.encyptionTypeComboBox.Items.AddRange(new object[] {
            "DES",
            "3DES",
            "RC2",
            "Rijndael",
            "AES"});
			this.encyptionTypeComboBox.Location = new System.Drawing.Point(709, 173);
			this.encyptionTypeComboBox.Name = "encyptionTypeComboBox";
			this.encyptionTypeComboBox.Size = new System.Drawing.Size(271, 47);
			this.encyptionTypeComboBox.TabIndex = 3;
			this.encyptionTypeComboBox.Text = "DES";
			this.encyptionTypeComboBox.SelectedIndexChanged += new System.EventHandler(this.EncryptionType_SelectedIndexChanged);
			// 
			// plainAsciiTextBox
			// 
			this.plainAsciiTextBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.plainAsciiTextBox.Location = new System.Drawing.Point(12, 244);
			this.plainAsciiTextBox.Multiline = true;
			this.plainAsciiTextBox.Name = "plainAsciiTextBox";
			this.plainAsciiTextBox.Size = new System.Drawing.Size(552, 50);
			this.plainAsciiTextBox.TabIndex = 4;
			this.plainAsciiTextBox.TextChanged += new System.EventHandler(this.PlainText_Changed);
			// 
			// encryptButton
			// 
			this.encryptButton.BackColor = System.Drawing.Color.White;
			this.encryptButton.Cursor = System.Windows.Forms.Cursors.Hand;
			this.encryptButton.Font = new System.Drawing.Font("Calibri", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.encryptButton.ForeColor = System.Drawing.Color.Black;
			this.encryptButton.Location = new System.Drawing.Point(293, 173);
			this.encryptButton.Margin = new System.Windows.Forms.Padding(0);
			this.encryptButton.Name = "encryptButton";
			this.encryptButton.Size = new System.Drawing.Size(271, 50);
			this.encryptButton.TabIndex = 0;
			this.encryptButton.Text = "ENCRYPT";
			this.encryptButton.UseVisualStyleBackColor = false;
			this.encryptButton.Click += new System.EventHandler(this.Encrypt_Click);
			// 
			// cipherAsciiTextBox
			// 
			this.cipherAsciiTextBox.Enabled = false;
			this.cipherAsciiTextBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cipherAsciiTextBox.Location = new System.Drawing.Point(1117, 244);
			this.cipherAsciiTextBox.Multiline = true;
			this.cipherAsciiTextBox.Name = "cipherAsciiTextBox";
			this.cipherAsciiTextBox.Size = new System.Drawing.Size(552, 50);
			this.cipherAsciiTextBox.TabIndex = 5;
			// 
			// cipherHexTextBox
			// 
			this.cipherHexTextBox.Enabled = false;
			this.cipherHexTextBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.cipherHexTextBox.Location = new System.Drawing.Point(1117, 300);
			this.cipherHexTextBox.Multiline = true;
			this.cipherHexTextBox.Name = "cipherHexTextBox";
			this.cipherHexTextBox.Size = new System.Drawing.Size(552, 50);
			this.cipherHexTextBox.TabIndex = 6;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.BackColor = System.Drawing.Color.Transparent;
			this.label1.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.ForeColor = System.Drawing.Color.White;
			this.label1.Location = new System.Drawing.Point(570, 303);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(71, 37);
			this.label1.TabIndex = 7;
			this.label1.Text = "HEX";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.BackColor = System.Drawing.Color.Transparent;
			this.label2.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label2.ForeColor = System.Drawing.Color.White;
			this.label2.Location = new System.Drawing.Point(570, 247);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(107, 37);
			this.label2.TabIndex = 8;
			this.label2.Text = "ASCII";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.BackColor = System.Drawing.Color.Transparent;
			this.label3.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label3.ForeColor = System.Drawing.Color.White;
			this.label3.Location = new System.Drawing.Point(1004, 247);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(107, 37);
			this.label3.TabIndex = 9;
			this.label3.Text = "ASCII";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.BackColor = System.Drawing.Color.Transparent;
			this.label4.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label4.ForeColor = System.Drawing.Color.White;
			this.label4.Location = new System.Drawing.Point(1040, 303);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(71, 37);
			this.label4.TabIndex = 10;
			this.label4.Text = "HEX";
			// 
			// decryptButton
			// 
			this.decryptButton.BackColor = System.Drawing.Color.White;
			this.decryptButton.Cursor = System.Windows.Forms.Cursors.Hand;
			this.decryptButton.Font = new System.Drawing.Font("Calibri", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.decryptButton.ForeColor = System.Drawing.Color.Black;
			this.decryptButton.Location = new System.Drawing.Point(1117, 173);
			this.decryptButton.Margin = new System.Windows.Forms.Padding(0);
			this.decryptButton.Name = "decryptButton";
			this.decryptButton.Size = new System.Drawing.Size(271, 50);
			this.decryptButton.TabIndex = 11;
			this.decryptButton.Text = "DECRYPT";
			this.decryptButton.UseVisualStyleBackColor = false;
			this.decryptButton.Click += new System.EventHandler(this.Decrypt_Click);
			// 
			// keyTextBox
			// 
			this.keyTextBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.keyTextBox.Location = new System.Drawing.Point(12, 12);
			this.keyTextBox.Multiline = true;
			this.keyTextBox.Name = "keyTextBox";
			this.keyTextBox.Size = new System.Drawing.Size(552, 50);
			this.keyTextBox.TabIndex = 12;
			// 
			// ivTextBox
			// 
			this.ivTextBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.ivTextBox.Location = new System.Drawing.Point(1117, 12);
			this.ivTextBox.Multiline = true;
			this.ivTextBox.Name = "ivTextBox";
			this.ivTextBox.Size = new System.Drawing.Size(552, 50);
			this.ivTextBox.TabIndex = 13;
			// 
			// generateButton
			// 
			this.generateButton.BackColor = System.Drawing.Color.White;
			this.generateButton.Cursor = System.Windows.Forms.Cursors.Hand;
			this.generateButton.Font = new System.Drawing.Font("Calibri", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.generateButton.ForeColor = System.Drawing.Color.Black;
			this.generateButton.Location = new System.Drawing.Point(709, 12);
			this.generateButton.Margin = new System.Windows.Forms.Padding(0);
			this.generateButton.Name = "generateButton";
			this.generateButton.Size = new System.Drawing.Size(271, 50);
			this.generateButton.TabIndex = 14;
			this.generateButton.Text = "GENERATE";
			this.generateButton.UseVisualStyleBackColor = false;
			this.generateButton.Click += new System.EventHandler(this.Generate_Click);
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.BackColor = System.Drawing.Color.Transparent;
			this.label5.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label5.ForeColor = System.Drawing.Color.White;
			this.label5.Location = new System.Drawing.Point(570, 15);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(71, 37);
			this.label5.TabIndex = 15;
			this.label5.Text = "KEY";
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.BackColor = System.Drawing.Color.Transparent;
			this.label6.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label6.ForeColor = System.Drawing.Color.White;
			this.label6.Location = new System.Drawing.Point(1058, 15);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(53, 37);
			this.label6.TabIndex = 16;
			this.label6.Text = "IV";
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.BackColor = System.Drawing.Color.Transparent;
			this.label7.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label7.ForeColor = System.Drawing.Color.White;
			this.label7.Location = new System.Drawing.Point(168, 368);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(125, 37);
			this.label7.TabIndex = 17;
			this.label7.Text = "Time: ";
			// 
			// label8
			// 
			this.label8.AutoSize = true;
			this.label8.BackColor = System.Drawing.Color.Transparent;
			this.label8.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label8.ForeColor = System.Drawing.Color.White;
			this.label8.Location = new System.Drawing.Point(1273, 368);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(125, 37);
			this.label8.TabIndex = 18;
			this.label8.Text = "Time: ";
			// 
			// encTimeLabel
			// 
			this.encTimeLabel.AutoSize = true;
			this.encTimeLabel.BackColor = System.Drawing.Color.Transparent;
			this.encTimeLabel.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.encTimeLabel.ForeColor = System.Drawing.Color.White;
			this.encTimeLabel.Location = new System.Drawing.Point(299, 368);
			this.encTimeLabel.Name = "encTimeLabel";
			this.encTimeLabel.Size = new System.Drawing.Size(71, 37);
			this.encTimeLabel.TabIndex = 19;
			this.encTimeLabel.Text = "---";
			// 
			// decTimeLabel
			// 
			this.decTimeLabel.AutoSize = true;
			this.decTimeLabel.BackColor = System.Drawing.Color.Transparent;
			this.decTimeLabel.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.decTimeLabel.ForeColor = System.Drawing.Color.White;
			this.decTimeLabel.Location = new System.Drawing.Point(1404, 368);
			this.decTimeLabel.Name = "decTimeLabel";
			this.decTimeLabel.Size = new System.Drawing.Size(71, 37);
			this.decTimeLabel.TabIndex = 20;
			this.decTimeLabel.Text = "---";
			// 
			// label11
			// 
			this.label11.AutoSize = true;
			this.label11.BackColor = System.Drawing.Color.Transparent;
			this.label11.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label11.ForeColor = System.Drawing.Color.White;
			this.label11.Location = new System.Drawing.Point(12, 186);
			this.label11.Name = "label11";
			this.label11.Size = new System.Drawing.Size(197, 37);
			this.label11.TabIndex = 21;
			this.label11.Text = "Plain Text";
			// 
			// label12
			// 
			this.label12.AutoSize = true;
			this.label12.BackColor = System.Drawing.Color.Transparent;
			this.label12.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label12.ForeColor = System.Drawing.Color.White;
			this.label12.Location = new System.Drawing.Point(1454, 186);
			this.label12.Name = "label12";
			this.label12.Size = new System.Drawing.Size(215, 37);
			this.label12.TabIndex = 22;
			this.label12.Text = "Cypher Text";
			// 
			// encTimeButton
			// 
			this.encTimeButton.BackColor = System.Drawing.Color.White;
			this.encTimeButton.Cursor = System.Windows.Forms.Cursors.Hand;
			this.encTimeButton.Font = new System.Drawing.Font("Calibri", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.encTimeButton.ForeColor = System.Drawing.Color.Black;
			this.encTimeButton.Location = new System.Drawing.Point(9, 361);
			this.encTimeButton.Margin = new System.Windows.Forms.Padding(0);
			this.encTimeButton.Name = "encTimeButton";
			this.encTimeButton.Size = new System.Drawing.Size(153, 50);
			this.encTimeButton.TabIndex = 23;
			this.encTimeButton.Text = "TIME";
			this.encTimeButton.UseVisualStyleBackColor = false;
			this.encTimeButton.Click += new System.EventHandler(this.EncTime_Click);
			// 
			// decTimeButton
			// 
			this.decTimeButton.BackColor = System.Drawing.Color.White;
			this.decTimeButton.Cursor = System.Windows.Forms.Cursors.Hand;
			this.decTimeButton.Font = new System.Drawing.Font("Calibri", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.decTimeButton.ForeColor = System.Drawing.Color.Black;
			this.decTimeButton.Location = new System.Drawing.Point(1117, 361);
			this.decTimeButton.Margin = new System.Windows.Forms.Padding(0);
			this.decTimeButton.Name = "decTimeButton";
			this.decTimeButton.Size = new System.Drawing.Size(153, 50);
			this.decTimeButton.TabIndex = 24;
			this.decTimeButton.Text = "TIME";
			this.decTimeButton.UseVisualStyleBackColor = false;
			this.decTimeButton.Click += new System.EventHandler(this.DecTime_Click);
			// 
			// SymEncForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(33)))), ((int)(((byte)(36)))));
			this.ClientSize = new System.Drawing.Size(1681, 420);
			this.Controls.Add(this.decTimeButton);
			this.Controls.Add(this.encTimeButton);
			this.Controls.Add(this.label12);
			this.Controls.Add(this.label11);
			this.Controls.Add(this.decTimeLabel);
			this.Controls.Add(this.encTimeLabel);
			this.Controls.Add(this.label8);
			this.Controls.Add(this.label7);
			this.Controls.Add(this.label6);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.generateButton);
			this.Controls.Add(this.ivTextBox);
			this.Controls.Add(this.keyTextBox);
			this.Controls.Add(this.decryptButton);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.plainHexTextBox);
			this.Controls.Add(this.encryptButton);
			this.Controls.Add(this.cipherHexTextBox);
			this.Controls.Add(this.cipherAsciiTextBox);
			this.Controls.Add(this.encyptionTypeComboBox);
			this.Controls.Add(this.plainAsciiTextBox);
			this.ForeColor = System.Drawing.Color.White;
			this.Name = "SymEncForm";
			this.Text = "Encrypt";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox plainHexTextBox;
		private System.Windows.Forms.TextBox plainAsciiTextBox;
		private System.Windows.Forms.TextBox cipherAsciiTextBox;
		private System.Windows.Forms.TextBox cipherHexTextBox;
		private System.Windows.Forms.TextBox keyTextBox;
		private System.Windows.Forms.TextBox ivTextBox;

		private System.Windows.Forms.ComboBox encyptionTypeComboBox;

		private System.Windows.Forms.Button encryptButton;
		private System.Windows.Forms.Button decryptButton;
		private System.Windows.Forms.Button generateButton;
		private System.Windows.Forms.Button encTimeButton;
		private System.Windows.Forms.Button decTimeButton;

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.Label encTimeLabel;
		private System.Windows.Forms.Label decTimeLabel;
		private System.Windows.Forms.Label label11;
		private System.Windows.Forms.Label label12;
	}
}

