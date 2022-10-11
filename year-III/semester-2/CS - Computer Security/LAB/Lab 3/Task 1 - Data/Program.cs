using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace Task_1___Data
{
	class Program
	{
		static void Main(string[] args)
		{
			// Create file streams
			FileStream in_fs = new FileStream(Path.GetFullPath(@"..\\Bogdan_Tatu.rar"), FileMode.Open, FileAccess.Read);
			FileStream out_fs = new FileStream(Path.GetFullPath(@"resources\\output.txt"), FileMode.Create, FileAccess.Write);

			if ( in_fs == null || out_fs == null ){
				Console.WriteLine("Error opening files");
				return;
			}

			// Create key
			string key = "L3Assignment";
			byte[] key_bytes = Encoding.ASCII.GetBytes(key);

			// Create HMAC
			HMACSHA256 hmac = new HMACSHA256(key_bytes);

			// Compute MAC
			byte[] mac = hmac.ComputeHash(in_fs);

			// Convert MAC to string
			string mac_ASCII = BitConverter.ToString(mac).Replace("-", "");
			Console.WriteLine("MAC: " + mac_ASCII);
			byte[] mac_ASCII_bytes = Encoding.ASCII.GetBytes(mac_ASCII);

			// Write MAC to output file
			out_fs.Write(mac_ASCII_bytes, 0, mac_ASCII_bytes.Length);

			// Close file streams
			in_fs.Close();
			out_fs.Close();
		}
	}
}
