using System;
using System.IO;
using System.Security.Cryptography;

namespace Task_3
{
	class Crypto
	{
        public static byte[] Encrypt(byte[] plain_bytes) {
            // Setup the AES algorithm with a given seed
            SymmetricAlgorithm EncryptSetup(int pass)
            {
                SymmetricAlgorithm alg = Aes.Create();

                alg.BlockSize = 128;
                byte[] key = new byte[16];
                new Random(pass).NextBytes(key);
                alg.Key = key;
                alg.IV = key;

                return alg;
            }

            // Encrypt the plain text bytes
            byte[] EncryptProcess(SymmetricAlgorithm alg, byte[] plaintext_bytes) { 
                MemoryStream ms = new MemoryStream();
                CryptoStream cs = new CryptoStream(ms, alg.CreateEncryptor(), CryptoStreamMode.Write);

                cs.Write(plaintext_bytes, 0, plaintext_bytes.Length);
                cs.Close();

                byte[] ciphertext_bytes = ms.ToArray();
                ms.Close();

                return ciphertext_bytes;
            }

            byte[] cipher_bytes = new byte[48];

            for (int pass = 0 ; pass < 3 ; pass++){
                SymmetricAlgorithm alg = EncryptSetup(pass);
                byte[] pass_bytes = EncryptProcess(alg, plain_bytes);

                Array.Copy(pass_bytes, 0, cipher_bytes, pass * 16, 16);
            }

            return cipher_bytes;
        }

        public static byte[] XOR(byte[] bytes1, byte[] bytes2) {
            byte[] xor_bytes = new byte[bytes1.Length];

            for (int i = 0 ; i < bytes1.Length ; i++) {
                xor_bytes[i] = (byte)(bytes1[i] ^ bytes2[i]);
            }

            return xor_bytes;
        }
	}
}
