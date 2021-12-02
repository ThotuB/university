using System;
using System.Security.Cryptography;
using System.Linq;
using System.IO;

namespace Task_2
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
			for (int i = 0; i < times.GetLength(0); i++)
			{
				csv += rows[i] + ',';
				for (int j = 0; j < times.GetLength(1); j++)
				{
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
			int[] keySizes = { 512, 640, 768, 1024 };

			string[] rows = { "Key Generation", "Signing", "Verification" };
			string[] cols = keySizes.Select(x => x.ToString()).ToArray();
			float[,] times = new float[rows.Length, cols.Length];

			DSACryptoServiceProvider dsa;
			byte[] data = new byte[20];
			byte[] signature;
			bool verified;

			for (int i = 0; i < keySizes.Length ; i++)
			{
				int keySize = keySizes[i];

				Console.WriteLine($"Size {keySize}");
				(dsa, times[0, i]) = Timer.TimeKeyGenerate(keySize);
				(signature, times[1, i]) = Timer.TimeSign(dsa, data);
				(verified, times[2, i]) = Timer.TimeVerify(dsa, data, signature);
			}

			string csv = ToCSV(times, cols, rows);
			WriteToFile(csv, path);
		}
	}
}
