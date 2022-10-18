using System;
using System.Linq;
using System.Windows.Forms;

using System.Security.Cryptography;

namespace Task_1
{
	public partial class MACForm : Form
	{
		HMAC hmac = new HMACSHA256();
		HashAlgorithm hash = new SHA256Managed();
		Func<byte[], byte[], byte[]> ComputeHelper;

		public MACForm()
		{
			InitializeComponent();
			this.typeComboBox.SelectedIndex = 0;
			this.hashTypeComboBox.SelectedIndex = 0;
		}

		#region Helper Methods

		private void SetKeyVisibility(bool visibility)
		{
			this.keyLabel.Visible = visibility;
			this.generateButton.Visible = visibility;
			this.keyAsciiLabel.Visible = visibility;
			this.keyAsciiTextBox.Visible = visibility;
			this.keyHexLabel.Visible = visibility;
			this.keyHexTextBox.Visible = visibility;
			this.hashLabel.Visible = !visibility;
			this.macLabel.Visible = visibility;
			this.verifyButton.Visible = visibility;
		}

		private void Type(string type)
		{
			switch ( type )
			{
				case "HASH":
					this.ComputeHelper = this.ComputeHashHelper;

					SetKeyVisibility(false);
					break;
				case "HMAC":
					this.ComputeHelper = this.ComputeMacHelper;

					SetKeyVisibility(true);
					break;
			}
		}

		private void HashType(string type)
		{
			switch ( type )
			{
				case "SHA-1":
					hmac = new HMACSHA1();
					hash = new SHA1Managed();
					break;
				case "SHA-256":
					hmac = new HMACSHA256();
					hash = new SHA256Managed();
					break;
				case "SHA-384":
					hmac = new HMACSHA384();
					hash = new SHA384Managed();
					break;
				case "SHA-512":
					hmac = new HMACSHA512();
					hash = new SHA512Managed();
					break;
				case "MD5":
					hmac = new HMACMD5();
					hash = new MD5CryptoServiceProvider();
					break;
				case "RIPEMD":
					hmac = new HMACRIPEMD160();
					hash = new RIPEMD160Managed();
					break;
			}
		}

		private (string, string) GenerateKey()
		{
			byte[] key_bytes = new byte[16];

			RandomNumberGenerator.Create().GetBytes(key_bytes);

			string key_text = Conversion.ByteArrayToString(key_bytes);
			string key_hex = Conversion.ByteArrayToHexString(key_bytes);

			return (key_text, key_hex);
		}

		private bool VerifyMacHelper(byte[] text, byte[] mac, byte[] key)
		{
			hmac.Key = key;

			byte[] computed_mac = hmac.ComputeHash(text);

			return ( Enumerable.SequenceEqual(computed_mac, mac) );
		}

		private byte[] ComputeHashHelper(byte[] text, byte[] key)
		{
			return hash.ComputeHash(text);
		}

		private byte[] ComputeMacHelper(byte[] text, byte[] key)
		{
			hmac.Key = key;

			return hmac.ComputeHash(text);
		}

		public (string, string) Compute(string text, string key)
		{
			byte[] text_bytes = Conversion.StringToByteArray(text);
			byte[] key_bytes = Conversion.StringToByteArray(key);

			Console.WriteLine(this.ComputeHelper);
			byte[] mac_bytes = this.ComputeHelper(text_bytes, key_bytes);

			string mac_text = Conversion.ByteArrayToString(mac_bytes);
			string mac_hex = Conversion.ByteArrayToHexString(mac_bytes);

			return (mac_text, mac_hex);
		}

		public bool VerifyMac(string text, string mac_hex, string key) 
		{
			byte[] text_bytes = Conversion.StringToByteArray(text);
			byte[] key_bytes = Conversion.StringToByteArray(key);
			byte[] mac_bytes = Conversion.HexStringToByteArray(mac_hex);

			return VerifyMacHelper(text_bytes, mac_bytes, key_bytes);
		}
		#endregion

		#region Form Even Handlers
		private void Compute_Click(object sender, EventArgs e)
		{
			string text = this.plainTextBox.Text;
			string key = this.keyAsciiTextBox.Text;

			(string mac_text, string mac_hex) = Compute(text, key);

			this.macAsciiTextBox.Text = mac_text;
			this.macHexTextBox.Text = mac_hex;
		}

		private void Verify_Click(object sender, EventArgs e)
		{
			string text = this.plainTextBox.Text;
			string key = this.keyAsciiTextBox.Text;
			string mac_hex = this.macHexTextBox.Text;

			bool verified = VerifyMac(text, mac_hex, key);

			if ( verified ) {
				MessageBox.Show("MAC verified!");
			}
			else {
				MessageBox.Show("MAC verification failed!");
			}
		}

		private void HashType_SelectedIndexChanged(object sender, EventArgs e)
		{
			string type = this.hashTypeComboBox.Text;

			HashType(type);
		}

		private void Generate_Click(object sender, EventArgs e)
		{
			(string key_text, string key_hex) = GenerateKey();

			this.keyAsciiTextBox.Text = key_text;
			this.keyHexTextBox.Text = key_hex;
		}

		private void Type_SelectedIndexChanged(object sender, EventArgs e)
		{
			string type = this.typeComboBox.Text;

			Type(type);
		}
		#endregion
	}
}
