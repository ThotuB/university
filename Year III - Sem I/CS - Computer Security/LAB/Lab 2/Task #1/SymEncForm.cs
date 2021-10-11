using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Security.Cryptography;
using System.IO;

namespace Task_1
{
	public partial class SymEncForm : Form
	{
		SymmetricAlgorithm alg = DES.Create();

		public SymEncForm()
		{
			InitializeComponent();
		}

		#region Helper Methods
		private void EncryptionType(string type)
		{
			switch ( type )
			{
				case "DES":
					alg = DES.Create();
					break;
				case "3DES":
					alg = TripleDES.Create();
					break;
				case "RC2":
					alg = RC2.Create();
					break;
				case "Rijndael":
					alg = Rijndael.Create();
					break;
				case "AES":
					alg = Aes.Create();
					break;
			}
		}

		private (string, string) Generate() {
			alg.GenerateIV();
			alg.GenerateKey();

			string key = Conversion.ByteArrayToHexString(alg.Key);
			string iv = Conversion.ByteArrayToHexString(alg.IV);

			return (key, iv);
		}

		private byte[] EncryptHelper(byte[] plain_bytes) {
			MemoryStream ms = new MemoryStream();
			CryptoStream cs = new CryptoStream(ms, alg.CreateEncryptor(), CryptoStreamMode.Write);

			cs.Write(plain_bytes, 0, plain_bytes.Length);
			cs.Close();

			byte[] cipher_bytes = ms.ToArray();

			ms.Close();

			return cipher_bytes;
		}

		private (string, string) Encrypt(string plain_text)
		{
			byte[] plain_bytes = Conversion.StringToByteArray(plain_text);

			byte[] cipher_bytes = EncryptHelper(plain_bytes);

			string cipher_text = Conversion.ByteArrayToString(cipher_bytes);
			string cipher_hex = Conversion.ByteArrayToHexString(cipher_bytes);

			return (cipher_text, cipher_hex);
		}

		private byte[] DecryptHelper(byte[] cipher_bytes) {
			MemoryStream ms = new MemoryStream(cipher_bytes);
			CryptoStream cs = new CryptoStream(ms, alg.CreateDecryptor(), CryptoStreamMode.Read);

			byte[] plain_bytes = new byte[cipher_bytes.Length];

			cs.Read(plain_bytes, 0, plain_bytes.Length);
			cs.Close();

			return plain_bytes;
		}

		private string Decrypt(string cipher_hex)
		{
			byte[] cipher_bytes = Conversion.HexStringToByteArray(cipher_hex);

			byte[] plain_bytes = DecryptHelper(cipher_bytes);

			return Conversion.ByteArrayToString(plain_bytes);
		}

		private string EncryptTime()
		{
			(string key, string iv) = Generate();

			this.keyTextBox.Text = key;
			this.ivTextBox.Text = iv;

			MemoryStream ms = new MemoryStream();
			CryptoStream cs = new CryptoStream(ms, alg.CreateEncryptor(), CryptoStreamMode.Write);

			byte[] plain_bytes = new byte[8];
			long start_time = DateTime.Now.Ticks;

			uint count = 10_000_000;
			for (int i = 0; i < count; i++)
			{
				cs.Write(plain_bytes, 0, plain_bytes.Length);
			}
			cs.Close();
			ms.Close();

			long stop_time = DateTime.Now.Ticks;

			double operation_time = ((double)(stop_time - start_time)) / (10 * count);

			return operation_time.ToString() + " us";
		}

		private string DecryptTime()
		{
			(string key, string iv) = Generate();

			this.keyTextBox.Text = key;
			this.ivTextBox.Text = iv;

			byte[] plain_bytes = new byte[8];
			byte[] cipher_bytes = EncryptHelper(new byte[7]);

			MemoryStream ms = new MemoryStream(cipher_bytes);
			CryptoStream cs = new CryptoStream(ms, alg.CreateDecryptor(), CryptoStreamMode.Read);

			long start_time = DateTime.Now.Ticks;

			uint count = 10_000_000;

			for (int i = 0; i < count; i++)
			{
				cs.Read(plain_bytes, 0, cipher_bytes.Length);
			}
			cs.Close();
			ms.Close();

			long stop_time = DateTime.Now.Ticks;

			double operation_time = ((double)(stop_time - start_time)) / (10 * count);

			return operation_time.ToString() + " us";
		}
		#endregion

		#region Form Even Handlers
		private void Form1_Load(object sender, EventArgs e)
		{

		}

		private void Encrypt_Click(object sender, EventArgs e)
		{
			string plain_text = this.plainAsciiTextBox.Text;

			(string cipher_text, string cipher_hex) = Encrypt(plain_text);

			this.cipherAsciiTextBox.Text = cipher_text;
			this.cipherHexTextBox.Text = cipher_hex;
		}

		private void Decrypt_Click(object sender, EventArgs e)
		{
			string cipher_text = this.cipherHexTextBox.Text;

			string plain_text = Decrypt(cipher_text);

			this.plainAsciiTextBox.Text = plain_text;
		}

		private void Generate_Click(object sender, EventArgs e)
		{
			(string key, string iv) = Generate();

			this.keyTextBox.Text = key;
			this.ivTextBox.Text = iv;
		}

		private void PlainText_Changed(object sender, EventArgs e)
		{
			string plain_text = this.plainAsciiTextBox.Text;
			byte[] plain_bytes = Conversion.StringToByteArray(plain_text);
			string plain_hex = Conversion.ByteArrayToHexString(plain_bytes);

			this.plainHexTextBox.Text = plain_hex;
		}

		private void EncryptionType_SelectedIndexChanged(object sender, EventArgs e) {
			string type = this.encyptionTypeComboBox.Text;

			EncryptionType(type);
		}

		private void EncTime_Click(object sender, EventArgs e)
		{
			string encTime = EncryptTime();

			this.encTimeLabel.Text = encTime;
		}

		private void DecTime_Click(object sender, EventArgs e)
		{
			string decTime = DecryptTime();

			this.decTimeLabel.Text = decTime;
		}
		#endregion
	}
}
