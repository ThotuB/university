using System.Diagnostics;
using System.Security.Cryptography;

namespace Task_2
{
	class Timer
	{
		const int COUNT = 1000;
		static Stopwatch stopwatch = new Stopwatch();

		private static float TimeFunction(){
			return stopwatch.ElapsedTicks / (float)COUNT;
		}

		public static (DSACryptoServiceProvider, float) TimeKeyGenerate(int keySize)
		{
			DSACryptoServiceProvider dsa = new DSACryptoServiceProvider();
			stopwatch.Start();
			for (int i = 0; i < COUNT; i++)
			{
				dsa = new DSACryptoServiceProvider(keySize);
			}
			stopwatch.Stop();
			float time = TimeFunction();
			stopwatch.Reset();

			return (dsa, time);
		}

		public static(byte[], float) TimeSign(DSACryptoServiceProvider dsa, byte[] data)
		{
			byte[] signature = new byte[0];
			stopwatch.Start();
			for (int i = 0; i < COUNT; i++)
			{
				signature = dsa.SignData(data);
			}
			stopwatch.Stop();
			float time = TimeFunction();
			stopwatch.Reset();

			return (signature, time);
		}

		public static(bool, float) TimeVerify(DSACryptoServiceProvider dsa, byte[] data, byte[] signature)
		{
			bool result = false;
			stopwatch.Start();
			for (int i = 0; i < COUNT; i++)
			{
				result = dsa.VerifyData(data, signature);
			}
			stopwatch.Stop();
			float time = TimeFunction();
			stopwatch.Reset();

			return (result, time);
		}
	}
}
