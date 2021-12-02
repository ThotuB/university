using System;
using System.Diagnostics;
using System.Security.Cryptography;
using System.Linq;
using System.IO;

namespace Task_1
{
	class Program
	{
		static string ToCSV(float[,] times, string[] cols, string[] rows)
		{
			string csv = ",";
			// Header
			for (int i = 0; i < cols.Length; i++){
				csv += cols[i] + " bit,";
			}
			csv += "\n";
			// Data
			for (int i = 0; i < times.GetLength(0); i++){
				csv += rows[i] + ',';
				for (int j = 0; j < times.GetLength(1); j++){
					csv += times[i, j] + " ms,";
				}
				csv += "\n";
			}
			
			return csv;
		}

		static void WriteToFile(string data, string path){
			using (StreamWriter writer = new StreamWriter(Path.GetFullPath(path))){
				writer.Write(data);
			}
		}

		static void Main(string[] args)
		{
			string path = @"resources\\times.csv";
			int[] keySizes = { 1024, 2048, 3072, 4096 };

			string[] rows = { "Key Generation", "Encryption", "Decryption", "Signing", "Verification" };
			string[] cols = keySizes.Select(x => x.ToString()).ToArray();
			float[,] times = new float[rows.Length, cols.Length];

			RSACryptoServiceProvider rsa;
			byte[] plain_bytes = new byte[20];
			byte[] cipher_bytes;
			byte[] signature;
			bool verified;

			for (int i = 0; i < keySizes.Length; i++)
			{
				int keySize = keySizes[i];

				Console.WriteLine($"Size: {keySize}");
				(rsa, times[0, i]) = Timer.TimeKeyGenerate(keySize);
				(cipher_bytes, times[1, i]) = Timer.TimeEncrypt(rsa, plain_bytes);
				(plain_bytes, times[2, i]) = Timer.TimeDecrypt(rsa, cipher_bytes);
				(signature, times[3, i]) = Timer.TimeSign(rsa, plain_bytes);
				(verified, times[4, i]) = Timer.TimeVerify(rsa, plain_bytes, signature);
			}


			string csv = ToCSV(times, cols, rows);
			WriteToFile(csv, path);
		}
	}
}
