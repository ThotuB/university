using System;
using System.Text;
using System.IO;

namespace Task_2
{
	class Program
	{
		static String StringifyBytes(byte[] bytes){
			String output = "";
			int i = 0;
			for ( ; i < bytes.Length ; i++)
			{
				if (i % 16 == 0)
				{
					output += "\n";
				}
				output += bytes[i].ToString("x2") + " ";
			}
			while ( i % 16 != 0 )
			{
				output += "00 ";
				i++;
			}
			output += "\n";
			return output;
		}

		static void Main(String[] args)
		{
			string plain_text = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
			byte[] plaintext_bytes = Encoding.ASCII.GetBytes(plain_text);
			byte[] ciphertext_bytes = Crypto.Encrypt(plaintext_bytes);

			Console.WriteLine("Plaintext: " + plain_text);
			Console.WriteLine("Plaintext bytes: " + StringifyBytes(plaintext_bytes));
			Console.WriteLine("Ciphertext: " + Encoding.ASCII.GetString(ciphertext_bytes));
			Console.Write("Ciphertext bytes:\n" + StringifyBytes(ciphertext_bytes));
		}
	}
}