using System.IO;
using System.Security.Cryptography;

namespace Task_2
{
	class Crypto
	{
        private static SymmetricAlgorithm EncryptSetup()
        {
            SymmetricAlgorithm alg = AesManaged.Create();

            alg.Mode = CipherMode.ECB;
            alg.GenerateKey();

            return alg;
        }

        private static byte[] EncryptProcess(SymmetricAlgorithm alg, byte[] plaintext_bytes) { 
            MemoryStream memory_stream = new MemoryStream();
            CryptoStream crypto_stream = new CryptoStream(memory_stream, alg.CreateEncryptor(), CryptoStreamMode.Write);

            crypto_stream.Write(plaintext_bytes, 0, plaintext_bytes.Length);
            crypto_stream.Close();

            byte[] ciphertext_bytes = memory_stream.ToArray();
            memory_stream.Close();

            return ciphertext_bytes;
        }
        
        public static byte[] Encrypt(byte[] plaintext_bytes) {
            SymmetricAlgorithm alg = EncryptSetup();
            byte[] ciphertext_bytes = EncryptProcess(alg, plaintext_bytes);

            return ciphertext_bytes;
        }
	}
}
