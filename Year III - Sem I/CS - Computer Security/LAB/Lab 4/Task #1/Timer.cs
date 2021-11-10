using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Security.Cryptography;
using System.Text;

namespace Task_1
{
	class Timer
	{
		const int COUNT = 100;
		static readonly Stopwatch stopwatch = new Stopwatch();

		private static float TimeFunction(){
			return stopwatch.ElapsedTicks / (COUNT * 10.0f);
		}

		public static (RSACryptoServiceProvider, float) TimeKeyGenerate(int keySize)
		{
			RSACryptoServiceProvider rsa = new RSACryptoServiceProvider();
			stopwatch.Start();
			for (int i = 0; i < COUNT; i++)
			{
				rsa = new RSACryptoServiceProvider(keySize);
			}
			stopwatch.Stop();
			float time = TimeFunction();
			stopwatch.Reset();

			return (rsa, time);
		}

		public static (byte[], float) TimeEncrypt(RSACryptoServiceProvider rsa, byte[] plain_bytes)
		{
			byte[] cipher_bytes = new byte[plain_bytes.Length];

			stopwatch.Start();
			for (int i = 0; i < COUNT; i++)
			{
				cipher_bytes = rsa.Encrypt(plain_bytes, true);
			}
			stopwatch.Stop();
			float time = TimeFunction();
			stopwatch.Reset();

			return (cipher_bytes, time);
		}

		public static (byte[], float) TimeDecrypt(RSACryptoServiceProvider rsa, byte[] cipher_bytes)
		{
			byte[] plain_bytes = new byte[cipher_bytes.Length];

			stopwatch.Start();
			for (int i = 0; i < COUNT; i++)
			{
				plain_bytes = rsa.Decrypt(cipher_bytes, true);
			}
			stopwatch.Stop();
			float time = TimeFunction();
			stopwatch.Reset();

			return (plain_bytes, time);
		}

		public static (byte[], float) TimeSign(RSACryptoServiceProvider rsa, byte[] plain_bytes)
		{
			byte[] signature = new byte[0];

			stopwatch.Start();
			for (int i = 0; i < COUNT; i++)
			{
				signature = rsa.SignData(plain_bytes, new SHA256Managed());
			}
			stopwatch.Stop();
			float time = TimeFunction();
			stopwatch.Reset();

			return (signature, time);
		}

		public static (bool, float) TimeVerify(RSACryptoServiceProvider rsa, byte[] plain_bytes, byte[] signature)
		{
			bool verified = false;

			stopwatch.Start();
			for (int i = 0; i < COUNT; i++)
			{
				verified = rsa.VerifyData(plain_bytes, new SHA256Managed(), signature);
			}
			stopwatch.Stop();
			float time = TimeFunction();
			stopwatch.Reset();

			return (verified, time);
		}
	}
}
