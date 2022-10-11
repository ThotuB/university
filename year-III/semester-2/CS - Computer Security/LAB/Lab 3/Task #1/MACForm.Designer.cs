
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
			this.keyAsciiTextBox = new System.Windows.Forms.TextBox();
			this.computeButton = new System.Windows.Forms.Button();
			this.macAsciiTextBox = new System.Windows.Forms.TextBox();
			this.macHexTextBox = new System.Windows.Forms.TextBox();
			this.keyAsciiLabel = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.verifyButton = new System.Windows.Forms.Button();
			this.label11 = new System.Windows.Forms.Label();
			this.hashLabel = new System.Windows.Forms.Label();
			this.keyLabel = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.typeComboBox = new System.Windows.Forms.ComboBox();
			this.generateButton = new System.Windows.Forms.Button();
			this.keyHexTextBox = new System.Windows.Forms.TextBox();
			this.keyHexLabel = new System.Windows.Forms.Label();
			this.macLabel = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// plainTextBox
			// 
			this.plainTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.plainTextBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.plainTextBox.Location = new System.Drawing.Point(633, 66);
			this.plainTextBox.Multiline = true;
			this.plainTextBox.Name = "plainTextBox";
			this.plainTextBox.Size = new System.Drawing.Size(611, 50);
			this.plainTextBox.TabIndex = 1;
			// 
			// hashTypeComboBox
			// 
			this.hashTypeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.hashTypeComboBox.Font = new System.Drawing.Font("Calibri", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.hashTypeComboBox.FormattingEnabled = true;
			this.hashTypeComboBox.Items.AddRange(new object[] {
            "SHA-1",
            "SHA-256",
            "SHA-384",
            "SHA-512",
            "MD5",
            "RIPEMD"});
			this.hashTypeComboBox.Location = new System.Drawing.Point(12, 65);
			this.hashTypeComboBox.Name = "hashTypeComboBox";
			this.hashTypeComboBox.Size = new System.Drawing.Size(281, 47);
			this.hashTypeComboBox.TabIndex = 3;
			this.hashTypeComboBox.SelectedIndexChanged += new System.EventHandler(this.HashType_SelectedIndexChanged);
			// 
			// keyAsciiTextBox
			// 
			this.keyAsciiTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.keyAsciiTextBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.keyAsciiTextBox.Location = new System.Drawing.Point(633, 243);
			this.keyAsciiTextBox.Multiline = true;
			this.keyAsciiTextBox.Name = "keyAsciiTextBox";
			this.keyAsciiTextBox.Size = new System.Drawing.Size(611, 50);
			this.keyAsciiTextBox.TabIndex = 4;
			this.keyAsciiTextBox.Visible = false;
			// 
			// computeButton
			// 
			this.computeButton.BackColor = System.Drawing.Color.White;
			this.computeButton.Cursor = System.Windows.Forms.Cursors.Hand;
			this.computeButton.Font = new System.Drawing.Font("Calibri", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.computeButton.ForeColor = System.Drawing.Color.Black;
			this.computeButton.Location = new System.Drawing.Point(12, 239);
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
			this.macAsciiTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.macAsciiTextBox.Enabled = false;
			this.macAsciiTextBox.Font = new System.Drawing.Font("Consolas", 24F);
			this.macAsciiTextBox.Location = new System.Drawing.Point(12, 463);
			this.macAsciiTextBox.Multiline = true;
			this.macAsciiTextBox.Name = "macAsciiTextBox";
			this.macAsciiTextBox.Size = new System.Drawing.Size(611, 154);
			this.macAsciiTextBox.TabIndex = 5;
			// 
			// macHexTextBox
			// 
			this.macHexTextBox.AllowDrop = true;
			this.macHexTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.macHexTextBox.Enabled = false;
			this.macHexTextBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.macHexTextBox.Location = new System.Drawing.Point(633, 463);
			this.macHexTextBox.Multiline = true;
			this.macHexTextBox.Name = "macHexTextBox";
			this.macHexTextBox.Size = new System.Drawing.Size(611, 154);
			this.macHexTextBox.TabIndex = 6;
			// 
			// keyAsciiLabel
			// 
			this.keyAsciiLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.keyAsciiLabel.AutoSize = true;
			this.keyAsciiLabel.BackColor = System.Drawing.Color.Transparent;
			this.keyAsciiLabel.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.keyAsciiLabel.ForeColor = System.Drawing.Color.White;
			this.keyAsciiLabel.Location = new System.Drawing.Point(520, 246);
			this.keyAsciiLabel.Name = "keyAsciiLabel";
			this.keyAsciiLabel.Size = new System.Drawing.Size(107, 37);
			this.keyAsciiLabel.TabIndex = 8;
			this.keyAsciiLabel.Text = "ASCII";
			this.keyAsciiLabel.Visible = false;
			// 
			// label3
			// 
			this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.label3.AutoSize = true;
			this.label3.BackColor = System.Drawing.Color.Transparent;
			this.label3.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label3.ForeColor = System.Drawing.Color.White;
			this.label3.Location = new System.Drawing.Point(520, 69);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(107, 37);
			this.label3.TabIndex = 9;
			this.label3.Text = "ASCII";
			// 
			// label4
			// 
			this.label4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.label4.AutoSize = true;
			this.label4.BackColor = System.Drawing.Color.Transparent;
			this.label4.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label4.ForeColor = System.Drawing.Color.White;
			this.label4.Location = new System.Drawing.Point(1170, 423);
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
			this.verifyButton.Location = new System.Drawing.Point(12, 295);
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
			this.label11.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.label11.AutoSize = true;
			this.label11.BackColor = System.Drawing.Color.Transparent;
			this.label11.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label11.ForeColor = System.Drawing.Color.White;
			this.label11.Location = new System.Drawing.Point(626, 16);
			this.label11.Name = "label11";
			this.label11.Size = new System.Drawing.Size(197, 37);
			this.label11.TabIndex = 21;
			this.label11.Text = "Plain Text";
			// 
			// hashLabel
			// 
			this.hashLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.hashLabel.AutoSize = true;
			this.hashLabel.BackColor = System.Drawing.Color.Transparent;
			this.hashLabel.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.hashLabel.ForeColor = System.Drawing.Color.White;
			this.hashLabel.Location = new System.Drawing.Point(538, 423);
			this.hashLabel.Name = "hashLabel";
			this.hashLabel.Size = new System.Drawing.Size(89, 37);
			this.hashLabel.TabIndex = 22;
			this.hashLabel.Text = "HASH";
			// 
			// keyLabel
			// 
			this.keyLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.keyLabel.AutoSize = true;
			this.keyLabel.BackColor = System.Drawing.Color.Transparent;
			this.keyLabel.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.keyLabel.ForeColor = System.Drawing.Color.White;
			this.keyLabel.Location = new System.Drawing.Point(626, 196);
			this.keyLabel.Name = "keyLabel";
			this.keyLabel.Size = new System.Drawing.Size(71, 37);
			this.keyLabel.TabIndex = 25;
			this.keyLabel.Text = "Key";
			this.keyLabel.Visible = false;
			// 
			// label1
			// 
			this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.label1.AutoSize = true;
			this.label1.BackColor = System.Drawing.Color.Transparent;
			this.label1.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.ForeColor = System.Drawing.Color.White;
			this.label1.Location = new System.Drawing.Point(12, 423);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(107, 37);
			this.label1.TabIndex = 26;
			this.label1.Text = "ASCII";
			// 
			// typeComboBox
			// 
			this.typeComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.typeComboBox.Font = new System.Drawing.Font("Calibri", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.typeComboBox.FormattingEnabled = true;
			this.typeComboBox.Items.AddRange(new object[] {
            "HASH",
            "HMAC"});
			this.typeComboBox.Location = new System.Drawing.Point(12, 12);
			this.typeComboBox.Name = "typeComboBox";
			this.typeComboBox.Size = new System.Drawing.Size(281, 47);
			this.typeComboBox.TabIndex = 27;
			this.typeComboBox.SelectedIndexChanged += new System.EventHandler(this.Type_SelectedIndexChanged);
			// 
			// generateButton
			// 
			this.generateButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.generateButton.BackColor = System.Drawing.Color.White;
			this.generateButton.Cursor = System.Windows.Forms.Cursors.Hand;
			this.generateButton.Font = new System.Drawing.Font("Calibri", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.generateButton.ForeColor = System.Drawing.Color.Black;
			this.generateButton.Location = new System.Drawing.Point(963, 189);
			this.generateButton.Margin = new System.Windows.Forms.Padding(0);
			this.generateButton.Name = "generateButton";
			this.generateButton.Size = new System.Drawing.Size(281, 50);
			this.generateButton.TabIndex = 28;
			this.generateButton.Text = "GENERATE";
			this.generateButton.UseVisualStyleBackColor = false;
			this.generateButton.Visible = false;
			this.generateButton.Click += new System.EventHandler(this.Generate_Click);
			// 
			// keyHexTextBox
			// 
			this.keyHexTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.keyHexTextBox.Enabled = false;
			this.keyHexTextBox.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.keyHexTextBox.Location = new System.Drawing.Point(633, 299);
			this.keyHexTextBox.Multiline = true;
			this.keyHexTextBox.Name = "keyHexTextBox";
			this.keyHexTextBox.Size = new System.Drawing.Size(611, 50);
			this.keyHexTextBox.TabIndex = 29;
			this.keyHexTextBox.Visible = false;
			// 
			// keyHexLabel
			// 
			this.keyHexLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.keyHexLabel.AutoSize = true;
			this.keyHexLabel.BackColor = System.Drawing.Color.Transparent;
			this.keyHexLabel.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.keyHexLabel.ForeColor = System.Drawing.Color.White;
			this.keyHexLabel.Location = new System.Drawing.Point(556, 302);
			this.keyHexLabel.Name = "keyHexLabel";
			this.keyHexLabel.Size = new System.Drawing.Size(71, 37);
			this.keyHexLabel.TabIndex = 30;
			this.keyHexLabel.Text = "HEX";
			this.keyHexLabel.Visible = false;
			// 
			// macLabel
			// 
			this.macLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.macLabel.AutoSize = true;
			this.macLabel.BackColor = System.Drawing.Color.Transparent;
			this.macLabel.Font = new System.Drawing.Font("Consolas", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.macLabel.ForeColor = System.Drawing.Color.White;
			this.macLabel.Location = new System.Drawing.Point(626, 423);
			this.macLabel.Name = "macLabel";
			this.macLabel.Size = new System.Drawing.Size(71, 37);
			this.macLabel.TabIndex = 31;
			this.macLabel.Text = "MAC";
			// 
			// MACForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(32)))), ((int)(((byte)(33)))), ((int)(((byte)(36)))));
			this.ClientSize = new System.Drawing.Size(1253, 629);
			this.Controls.Add(this.macLabel);
			this.Controls.Add(this.keyHexLabel);
			this.Controls.Add(this.keyHexTextBox);
			this.Controls.Add(this.generateButton);
			this.Controls.Add(this.typeComboBox);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.keyLabel);
			this.Controls.Add(this.hashLabel);
			this.Controls.Add(this.label11);
			this.Controls.Add(this.verifyButton);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.keyAsciiLabel);
			this.Controls.Add(this.plainTextBox);
			this.Controls.Add(this.computeButton);
			this.Controls.Add(this.macHexTextBox);
			this.Controls.Add(this.macAsciiTextBox);
			this.Controls.Add(this.hashTypeComboBox);
			this.Controls.Add(this.keyAsciiTextBox);
			this.ForeColor = System.Drawing.Color.White;
			this.Name = "MACForm";
			this.Text = "Encrypt";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox plainTextBox;
		private System.Windows.Forms.TextBox keyAsciiTextBox;
		private System.Windows.Forms.TextBox macAsciiTextBox;
		private System.Windows.Forms.TextBox macHexTextBox;

		private System.Windows.Forms.ComboBox typeComboBox;
		private System.Windows.Forms.ComboBox hashTypeComboBox;

		private System.Windows.Forms.Button computeButton;
		private System.Windows.Forms.Button verifyButton;
		private System.Windows.Forms.Button generateButton;

		private System.Windows.Forms.Label keyAsciiLabel;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label11;
		private System.Windows.Forms.Label hashLabel;
		private System.Windows.Forms.Label keyLabel;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox keyHexTextBox;
		private System.Windows.Forms.Label keyHexLabel;
		private System.Windows.Forms.Label macLabel;
	}
}

