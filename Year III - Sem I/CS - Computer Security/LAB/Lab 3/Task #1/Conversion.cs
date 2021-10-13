using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_1
{
	static class Conversion
	{
		public static byte[] CharArrayToByteArray(char[] arr){
			return Encoding.ASCII.GetBytes(arr, 0, arr.Length); 
		}

		public static byte[] StringToByteArray(string str){
			return CharArrayToByteArray(str.ToCharArray());
		}

		public static string ByteArrayToString(byte[] arr){
			return Encoding.ASCII.GetString(arr);
		}

		public static string ByteArrayToHexString(byte[] arr){
			string output = "";
			for (int i = 0; i < arr.Length; i++)
			{
				byte nibble1 = (byte) ((arr[i] >> 4) & 0x0F);
				byte nibble2 = (byte) (arr[i] & 0x0F);

				output += nibble1.ToString("X") + nibble2.ToString("X");
			}

			return output;
		}

		private static byte HexCharToNibble(char c){
			if (c >= '0' && c <= '9'){
				return (byte) (c - '0');
			}
			if (c >= 'A' && c <= 'F'){
				return (byte) (c - 'A' + 10);
			}
			return 0x00;
		}

		public static byte[] HexStringToByteArray(string str){
			byte[] output = new byte[str.Length / 2];
			char[] chars = str.ToCharArray();

			for (int i = 0; i < output.Length ; i++)
			{
				char nibble1 = chars[i * 2];
				char nibble2 = chars[i * 2 + 1];

				byte hex1 = (byte) ((HexCharToNibble(nibble1) << 4) & 0xF0);
				byte hex2 = (byte) (HexCharToNibble(nibble2) & 0x0F);

				output[i] = (byte) (hex1 | hex2);
			}

			return output;
		}

	}
}
