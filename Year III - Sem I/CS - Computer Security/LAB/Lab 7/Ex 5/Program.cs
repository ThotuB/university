using System;
using System.Security.Cryptography;
using System.Text;
using System.IO;
using System.Linq;

namespace Ex_5
{
    class Program
    {
        static byte[] StringToByteArray(string hex) {
            byte[] bytes = new byte[hex.Length / 2];
            for (int i = 0; i < hex.Length / 2; i++) {
                bytes[i] = Convert.ToByte(hex.Substring(i * 2, 2), 16);
            }
            return bytes;
        }

        static string ByteToHex(byte[] bytes, int blockSize) {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < bytes.Length; i++) {
                sb.Append(bytes[i].ToString("X2"));
                if (i % blockSize == blockSize - 1) {
                    sb.Append("\n");
                }
            }
            sb.Length--;
            return sb.ToString();
        }

        static void Main(string[] args)
        {
            string seq1 = "6DEBCDA70865BD399657B843BCC53F9C6527ABCF6F1201B6B5B8FC5A6BAAB04535F502E2A081D5D17FB787D1D3F47EB0104F35DAA17035FD5840C56A35FB4638154F91384A6BA7C226099E5E64213017";
            string seq2 = "658593078356EEEBF06E0536A4BE56E4F9B0C2D59543273567A55C5225FA8FC05D09DAAAEAA1E94AEDF724A40EB3CBD8F067F4C3BFDC948E605187D8A13E42A71698C125F48C89006C7356921EB3FD54";
            string seq3 = "954D5CAD5BE5A1D36140192898567010D60E57D6C9A45955E0897527945AB66CF941C1ACC5DA3ECBA0CD14AB4CEC0D05E76AED3A123E951633F34D6CFCCDF729476E45EDE95FC2E0B22AB9EBEFA2B6B6";
            
            byte[] s = StringToByteArray(seq1);
            string key = "71074F465189549BFC1DA059877CEAD8496A3814DA7D65DCA298C6D428463B8F";
            byte[] k = StringToByteArray(key);
            
            Console.WriteLine("Sequence:\n" + ByteToHex(s, 40));
            Console.WriteLine("\nKey: " + ByteToHex(k, 256) + "\n");

            byte[] c = new byte[32];
            byte[] iv = new byte[16];
            byte[] t = new byte[32];

            Array.Copy(s, 0, c, 0, 32);
            Array.Copy(s, 32, iv, 0, 16);
            Array.Copy(s, 48, t, 0, 32);

            Console.WriteLine("C  : " + ByteToHex(c, 48));
            Console.WriteLine("IV : " + ByteToHex(iv, 16));
            Console.WriteLine("T  : " + ByteToHex(t, 48));

            byte[] c_iv = new byte[48];
            Array.Copy(c, 0, c_iv, 0, 32);
            Array.Copy(iv, 0, c_iv, 32, 16);

            byte[] t_validate = new HMACSHA256(k).ComputeHash(c_iv);

            Console.WriteLine("\nT? : " + ByteToHex(t_validate, 48));

            Aes aes = Aes.Create();
            aes.Key = k;
            aes.IV = iv;
            aes.Mode = CipherMode.CBC;
            aes.Padding = PaddingMode.PKCS7;

            byte[] m = aes.CreateDecryptor().TransformFinalBlock(c, 0, c.Length);

            Console.WriteLine("\nMessage: " + Encoding.UTF8.GetString(m));
        }
    }
}
