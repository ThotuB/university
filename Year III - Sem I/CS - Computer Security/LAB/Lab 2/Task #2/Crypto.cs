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
            alg.KeySize = 128;
            alg.GenerateKey();

            return alg;
        }

        private static byte[] EncryptProcess(SymmetricAlgorithm alg, byte[] plaintext_bytes) { 
            MemoryStream ms = new MemoryStream();
            CryptoStream cs = new CryptoStream(ms, alg.CreateEncryptor(), CryptoStreamMode.Write);

            cs.Write(plaintext_bytes, 0, plaintext_bytes.Length);
            cs.Close();

            byte[] ciphertext_bytes = ms.ToArray();
            ms.Close();

            return ciphertext_bytes;
        }
        
        public static byte[] Encrypt(byte[] plaintext_bytes) {
            SymmetricAlgorithm alg = EncryptSetup();
            byte[] ciphertext_bytes = EncryptProcess(alg, plaintext_bytes);

            return ciphertext_bytes;
        }
	}
}
