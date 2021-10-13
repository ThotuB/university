
namespace Task_1
{
	partial class MACForm
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
			this.plainTextBox = new System.Windows.Forms.TextBox();
			this.hashTypeComboBox = new System.Windows.Forms.ComboBox();
			this.keyTextBox = new System.Windows.Forms.TextBox();
			this.computeButton = new System.Windows.Forms.Button();
			this.macAsciiTextBox = new System.Windows.Forms.TextBox();
			this.macHexTextBox = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.verifyButton = new System.Windows.Forms.Button();
			this.label11 = new System.Windows.Forms.Label();
			this.label12 = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// plainTextBox
			// 
			this.plainTextBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.plainTextBox.Location = new System.Drawing.Point(12, 161);
			this.plainTextBox.Multiline = true;
			this.plainTextBox.Name = "plainTextBox";
			this.plainTextBox.Size = new System.Drawing.Size(552, 50);
			this.plainTextBox.TabIndex = 1;
			// 
			// hashTypeComboBox
			// 
			this.hashTypeComboBox.Font = new System.Drawing.Font("Calibri", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.hashTypeComboBox.FormattingEnabled = true;
			this.hashTypeComboBox.Items.AddRange(new object[] {
            "SHA-1",
            "SHA-256",
            "SHA-384",
            "SHA-512",
            "MD5",
            "RIPEMD"});
			this.hashTypeComboBox.Location = new System.Drawing.Point(683, 48);
			this.hashTypeComboBox.Name = "hashTypeComboBox";
			this.hashTypeComboBox.Size = new System.Drawing.Size(281, 47);
			this.hashTypeComboBox.TabIndex = 3;
			this.hashTypeComboBox.Text = "SHA-256";
			this.hashTypeComboBox.SelectedIndexChanged += new System.EventHandler(this.HashType_SelectedIndexChanged);
			// 
			// keyTextBox
			// 
			this.keyTextBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.keyTextBox.Location = new System.Drawing.Point(12, 49);
			this.keyTextBox.Multiline = true;
			this.keyTextBox.Name = "keyTextBox";
			this.keyTextBox.Size = new System.Drawing.Size(552, 50);
			this.keyTextBox.TabIndex = 4;
			// 
			// computeButton
			// 
			this.computeButton.BackColor = System.Drawing.Color.White;
			this.computeButton.Cursor = System.Windows.Forms.Cursors.Hand;
			this.computeButton.Font = new System.Drawing.Font("Calibri", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.computeButton.ForeColor = System.Drawing.Color.Black;
			this.computeButton.Location = new System.Drawing.Point(683, 105);
			this.computeButton.Margin = new System.Windows.Forms.Padding(0);
			this.computeButton.Name = "computeButton";
			this.computeButton.Size = new System.Drawing.Size(281, 50);
			this.computeButton.TabIndex = 0;
			this.computeButton.Text = "COMPUTE";
			this.computeButton.UseVisualStyleBackColor = false;
			this.computeButton.Click += new System.EventHandler(this.Compute_Click);
			// 
			// macAsciiTextBox
			// 
			this.macAsciiTextBox.Enabled = false;
			this.macAsciiTextBox.Font = new System.Drawing.Font("Consolas", 14F);
			this.macAsciiTextBox.Location = new System.Drawing.Point(1083, 48);
			this.macAsciiTextBox.Multiline = true;
			this.macAsciiTextBox.Name = "macAsciiTextBox";
			this.macAsciiTextBox.Size = new System.Drawing.Size(586, 50);
			this.macAsciiTextBox.TabIndex = 5;
			// 
			// macHexTextBox
			// 
			this.macHexTextBox.AllowDrop = true;
			this.macHexTextBox.Enabled = false;
			this.macHexTextBox.Font = new System.Drawing.Font("Consolas", 18F);
			this.macHexTextBox.Location = new System.Drawing.Point(1083, 105);
			this.macHexTextBox.Multiline = true;
			this.macHexTextBox.Name = "macHexTextBox";
			this.macHexTextBox.Size = new System.Drawing.Size(586, 96);
			this.macHexTextBox.TabIndex = 6;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.BackColor = System.Drawing.Color.Transparent;
			this.label2.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label2.ForeColor = System.Drawing.Color.White;
			this.label2.Location = new System.Drawing.Point(570, 52);
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
			this.label3.Location = new System.Drawing.Point(970, 52);
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
			this.label4.Location = new System.Drawing.Point(1006, 164);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(71, 37);
			this.label4.TabIndex = 10;
			this.label4.Text = "HEX";
			// 
			// verifyButton
			// 
			this.verifyButton.BackColor = System.Drawing.Color.White;
			this.verifyButton.Cursor = System.Windows.Forms.Cursors.Hand;
			this.verifyButton.Font = new System.Drawing.Font("Calibri", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.verifyButton.ForeColor = System.Drawing.Color.Black;
			this.verifyButton.Location = new System.Drawing.Point(683, 161);
			this.verifyButton.Margin = new System.Windows.Forms.Padding(0);
			this.verifyButton.Name = "verifyButton";
			this.verifyButton.Size = new System.Drawing.Size(281, 50);
			this.verifyButton.TabIndex = 11;
			this.verifyButton.Text = "VERIFY";
			this.verifyButton.UseVisualStyleBackColor = false;
			this.verifyButton.Click += new System.EventHandler(this.Verify_Click);
			// 
			// label11
			// 
			this.label11.AutoSize = true;
			this.label11.BackColor = System.Drawing.Color.Transparent;
			this.label11.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label11.ForeColor = System.Drawing.Color.White;
			this.label11.Location = new System.Drawing.Point(12, 121);
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
			this.label12.Location = new System.Drawing.Point(1598, 9);
			this.label12.Name = "label12";
			this.label12.Size = new System.Drawing.Size(71, 37);
			this.label12.TabIndex = 22;
			this.label12.Text = "MAC";
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.BackColor = System.Drawing.Color.Transparent;
			this.label5.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label5.ForeColor = System.Drawing.Color.White;
			this.label5.Location = new System.Drawing.Point(12, 9);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(71, 37);
			this.label5.TabIndex = 25;
			this.label5.Text = "Key";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.BackColor = System.Drawing.Color.Transparent;
			this.label1.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.ForeColor = System.Drawing.Color.White;
			this.label1.Location = new System.Drawing.Point(570, 164);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(107, 37);
			this.label1.TabIndex = 26;
			this.label1.Text = "ASCII";
			// 
			// MACForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(33)))), ((int)(((byte)(36)))));
			this.ClientSize = new System.Drawing.Size(1681, 236);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.label12);
			this.Controls.Add(this.label11);
			this.Controls.Add(this.verifyButton);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.plainTextBox);
			this.Controls.Add(this.computeButton);
			this.Controls.Add(this.macHexTextBox);
			this.Controls.Add(this.macAsciiTextBox);
			this.Controls.Add(this.hashTypeComboBox);
			this.Controls.Add(this.keyTextBox);
			this.ForeColor = System.Drawing.Color.White;
			this.Name = "MACForm";
			this.Text = "Encrypt";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox plainTextBox;
		private System.Windows.Forms.TextBox keyTextBox;
		private System.Windows.Forms.TextBox macAsciiTextBox;
		private System.Windows.Forms.TextBox macHexTextBox;

		private System.Windows.Forms.ComboBox hashTypeComboBox;

		private System.Windows.Forms.Button computeButton;
		private System.Windows.Forms.Button verifyButton;

		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label11;
		private System.Windows.Forms.Label label12;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label1;
	}
}

