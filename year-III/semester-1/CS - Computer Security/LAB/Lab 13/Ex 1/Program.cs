using System;
using System.Security.Cryptography;
using System.Text;
using System.Linq;

namespace Ex_1
{
    class Program
    {
        static byte[] StringToByteArray(string hex)
        {
            byte[] bytes = new byte[hex.Length / 2];
            for (int i = 0; i < hex.Length / 2; i++)
            {
                bytes[i] = Convert.ToByte(hex.Substring(i * 2, 2), 16);
            }
            return bytes;
        }

        static string ByteToHexString(byte[] bytes, int blockSize)
        {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < bytes.Length; i++)
            {
                sb.Append(bytes[i].ToString("X2"));
                if (i % blockSize == blockSize - 1)
                {
                    sb.Append("\n");
                }
            }
            sb.Length--;
            return sb.ToString();
        }

        static void Main(string[] args)
        {
            string message = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
            byte[] m = Encoding.ASCII.GetBytes(message);
            byte[] key = StringToByteArray("71074F465189549BFC1DA059877CEAD8496A3814DA7D65DCA298C6D428463B8F");

            Aes aes = Aes.Create();
            aes.KeySize = 256;
            aes.Key = key;
            aes.Mode = CipherMode.ECB;

            byte[] enc = aes.CreateEncryptor().TransformFinalBlock(m, 0, m.Length);

            Console.WriteLine("Message:\n" + ByteToHexString(m, 16));
            Console.WriteLine("\nEncrypted Message:\n" + ByteToHexString(enc, 16) + "\n");
        }
    }
}
