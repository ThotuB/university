using System;
using System.Security.Cryptography;
using System.IO;
using System.Text;
using System.Linq;

namespace Ex_3
{
    class RSA {
        RSACryptoServiceProvider rsa = new RSACryptoServiceProvider();

        public RSA(int keySize) {
            rsa = new RSACryptoServiceProvider(keySize);
        }

        public byte[] Encrypt(byte[] data) {
            return rsa.Encrypt(data, true);
        }

        public byte[] Decrypt(byte[] data) {
            return rsa.Decrypt(data, true);
        }

        public byte[] Sign(byte[] data, HashAlgorithm hashAlgorithm) {
            return rsa.SignData(data, hashAlgorithm);
        }

        public bool Verify(byte[] data, byte[] signature, HashAlgorithm hashAlgorithm) {
            return rsa.VerifyData(data, hashAlgorithm, signature);
        }
    }

    class Program
    {
        static string ToHex(byte[] data) {
            string hex = "";
            foreach (byte b in data){
                hex += b.ToString("X2");
            }
            return hex;
        }

        static void Main(string[] args)
        {
            string message = "Hello World!";
            byte[] data = Encoding.UTF8.GetBytes(message);

            var rsa = new RSA(2048);

            var encrypted = rsa.Encrypt(data);

            Console.WriteLine("Original message: " + message);
            Console.WriteLine("Encrypted message: " + ToHex(encrypted));
        }
    }
}
