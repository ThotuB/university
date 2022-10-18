using System;
using System.Security.Cryptography;
using System.Text;
using System.Linq;

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

class DSA {
    DSACryptoServiceProvider dsa = new DSACryptoServiceProvider();

    public DSA(int keySize) {
        dsa = new DSACryptoServiceProvider(keySize);
    }

    public byte[] Sign(byte[] data) {
        return dsa.SignData(data);
    }

    public bool Verify(byte[] data, byte[] signature) {
        return dsa.VerifyData(data, signature);
    }
}

class AES {
    Aes aes;

    private AES(byte[] key, int keySize) {
        aes = Aes.Create();
        aes.KeySize = keySize;
        aes.Key = key;
    }

    public AES(byte[] key) 
        : this(key, 128)
    {
        aes.Mode = CipherMode.ECB;
    }

    public AES(byte[] key, byte[] iv) 
        : this(key, 128) 
    {
        aes.Mode = CipherMode.CBC;
        aes.IV = iv;
    }

    public byte[] Encrypt(byte[] data) {
        MemoryStream ms = new MemoryStream();
        CryptoStream cs = new CryptoStream(ms, aes.CreateEncryptor(), CryptoStreamMode.Write);

        cs.Write(data, 0, data.Length);
        cs.Close();

        byte[] cipher = ms.ToArray();
        ms.Close();

        return cipher;
    }

    public byte[] Decrypt(byte[] cipher) {
        MemoryStream ms = new MemoryStream(cipher);
        CryptoStream cs = new CryptoStream(ms, aes.CreateDecryptor(), CryptoStreamMode.Read);

        byte[] data = new byte[cipher.Length];
        cs.Read(data, 0, data.Length);
        cs.Close();

        ms.Close();

        return data;
    }

    public byte[] Sign(byte[] data, HashAlgorithm hashAlgorithm) {
        byte[] hash = hashAlgorithm.ComputeHash(data);

        return Encrypt(hash);
    }

    public bool Verify(byte[] data, byte[] signature, HashAlgorithm hashAlgorithm) {
        byte[] hash = hashAlgorithm.ComputeHash(data);

        return Decrypt(signature).SequenceEqual(hash);
    }
}

class Hash {
    HashAlgorithm hash;

    public Hash(string hashName) {
        hash = HashAlgorithm.Create(hashName);
    }

    public byte[] ComputeHash(byte[] data) {
        return hash.ComputeHash(data);
    }
}

class HMac {
    HMAC hmac;

    public HMac(string hashName, byte[] key) {
        hmac = HMAC.Create(hashName);
        hmac.Key = key;
    }

    public byte[] ComputeHash(byte[] data) {
        return hmac.ComputeHash(data);
    }

    public bool Verify(byte[] data, byte[] signature) {
        return hmac.ComputeHash(data) == signature;
    }
}

class Program {
    class Convert {
        public static string ToStr(byte[] data) {
            return Encoding.ASCII.GetString(data);
        }

        public static string ToHex(byte[] data, int block) {
            block /= 8;
            string hex = "";
            for (int i = 0; i < data.Length; i++) {
                hex += data[i].ToString("X2");
                if (i % block == block - 1) {
                    hex += "\n";
                }
            }
            return hex;
        }

        public static byte[] ToBytes(string text) {
            return Encoding.ASCII.GetBytes(text);
        }
    }

    public static void Main(string[] args) {
            string text = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
            byte[] data = Convert.ToBytes(text);
            
            Console.WriteLine($"Text:\n{text}\n");

            // RSA
            RSA rsa = new RSA(2048);

            byte[] rsa_encrypt = rsa.Encrypt(data);
            byte[] rsa_decrypt = rsa.Decrypt(rsa_encrypt);
            byte[] rsa_sign = rsa.Sign(data, new SHA256Managed());
            bool rsa_verify = rsa.Verify(data, rsa_sign, new SHA256Managed());

            Console.WriteLine("RSA");
            Console.WriteLine($"Encrypt:\n{Convert.ToHex(rsa_encrypt, 2048)}");
            Console.WriteLine($"Sign:\n{Convert.ToHex(rsa_sign, 256)}");
            Console.WriteLine($"Verify: {rsa_verify}\n");

            // DSA
            DSA dsa = new DSA(1024);

            byte[] dsa_sign = dsa.Sign(data);
            bool dsa_verify = dsa.Verify(data, dsa_sign);

            Console.WriteLine("DSA");
            Console.WriteLine($"Sign:\n{Convert.ToHex(dsa_sign, 320)}");
            Console.WriteLine($"Verify: {dsa_verify}\n");
            
            // AES
            byte[] key = Convert.ToBytes("1234567890123456");
            byte[] iv = Convert.ToBytes("1234567890123456");

            AES aes2 = new AES(key, iv);

            byte[] aes_encrypt = aes2.Encrypt(data);
            byte[] aes_decrypt = aes2.Decrypt(aes_encrypt);
            byte[] aes_sign = aes2.Sign(data, new SHA256Managed());
            bool aes_verify = aes2.Verify(data, aes_sign, new SHA256Managed());

            Console.WriteLine("AES - CBC");
            Console.WriteLine($"Encrypt:\n{Convert.ToHex(aes_encrypt, 128)}");
            Console.WriteLine($"Sign:\n{Convert.ToHex(aes_sign, 256)}\n");
            Console.WriteLine($"Verify: {aes_verify}\n");
    }
}

Program.Main(null);