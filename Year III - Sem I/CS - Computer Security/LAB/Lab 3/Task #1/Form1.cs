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
	public partial class MACForm : Form
	{
		HMAC hash = new HMACSHA256();

		public MACForm()
		{
			InitializeComponent();
		}

		#region Helper Methods
		private void HashType(string type)
		{
			switch ( type )
			{
				case "SHA-1":
					hash = new HMACSHA1();
					break;
				case "SHA-256":
					hash = new HMACSHA256();
					break;
				case "SHA-384":
					hash = new HMACSHA384();
					break;
				case "SHA-512":
					hash = new HMACSHA512();
					break;
				case "MD5":
					hash = new HMACMD5();
					break;
				case "RIPEMD":
					hash = new HMACRIPEMD160();
					break;
			}
		}

		public bool VerifyMacHelper(byte[] text, byte[] mac, byte[] key)
		{
			hash.Key = key;

			byte[] computed_mac = hash.ComputeHash(text);

			return ( Enumerable.SequenceEqual(computed_mac, mac) );
		}

		public byte[] ComputeMacHelper(byte[] text, byte[] key)
		{
			hash.Key = key;

			return hash.ComputeHash(text);
		}

		public (string, string) ComputeMac(string text, string key)
		{
			byte[] text_bytes = Conversion.StringToByteArray(text);
			byte[] key_bytes = Conversion.StringToByteArray(key);

			byte[] mac_bytes = ComputeMacHelper(text_bytes, key_bytes);

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
			string key = this.keyTextBox.Text;

			(string mac_text, string mac_hex) = ComputeMac(text, key);

			this.macAsciiTextBox.Text = mac_text;
			this.macHexTextBox.Text = mac_hex;
		}

		private void Verify_Click(object sender, EventArgs e)
		{
			string text = this.plainTextBox.Text;
			string key = this.keyTextBox.Text;
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
		#endregion
	}
}
