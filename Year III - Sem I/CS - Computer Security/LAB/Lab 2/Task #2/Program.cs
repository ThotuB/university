using System;
using System.Text;
using System.IO;

namespace Task_2
{
	class Program
	{
		static byte[] ImageToByteArray(String path)
		{
			byte[] imageBytes;
			using (var br = new BinaryReader(File.Open(path, FileMode.Open)))
			{
				imageBytes = br.ReadBytes((int)br.BaseStream.Length);
			}
			return imageBytes;
		}

		static Image ByteArrayToImage(byte[] byteArrayIn)
		{
			using (var ms = new MemoryStream(byteArrayIn))
			{
				return Image.FromStream(ms);
			}
		}

		static String StringifyBytes(byte[] bytes)
		{
			String output = "";
			foreach (byte b in bytes)
			{
				output += b.ToString("x2") + " ";
			}
			output += "\n";
			return output;
		}

		static void Main(String[] args)
		{
			string path = @"resources\\sample_image.png";
			Console.WriteLine("Image file path: " + path);

			byte[] imageBytes = ImageToByteArray(path);
			// Console.WriteLine("Length: " + imageBytes.Length); 
		}
	}
}
			// byte[] plaintext_bytes = Encoding.ASCII.GetBytes(plaintext);
			// byte[] ciphertext_bytes = Crypto.Encrypt(plaintext_bytes);

			// Console.WriteLine("Plaintext: " + plaintext);
			// Console.Write("Plaintext bytes: " + StringifyBytes(plaintext_bytes));
			// Console.WriteLine();
			// Console.Write("Ciphertext bytes: " + StringifyBytes(ciphertext_bytes));
			// Console.Write("Ciphertext: " + Encoding.ASCII.GetString(ciphertext_bytes));
// 		}
// 	}
// }