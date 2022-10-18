using System;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;

namespace Ex_5
{
    class Program
    {
        static byte[] HexStringToByteArray(string hex)
        {
            return Enumerable.Range(0, hex.Length)
                             .Where(x => x % 2 == 0)
                             .Select(x => Convert.ToByte(hex.Substring(x, 2), 16))
                             .ToArray();
        }

        static string ByteArrayToHexString(byte[] bytes, int blockSize)
        {
            return BitConverter.ToString(bytes).Replace("-", string.Empty);
        }

        static void Main(string[] args)
        {
            string[] seqs = {
                "6DEBCDA70865BD399657B843BCC53F9C6527ABCF6F1201B6B5B8FC5A6BAAB04535F502E2A081D5D17FB787D1D3F47EB0104F35DAA17035FD5840C56A35FB4638154F91384A6BA7C226099E5E64213017",
                "658593078356EEEBF06E0536A4BE56E4F9B0C2D59543273567A55C5225FA8FC05D09DAAAEAA1E94AEDF724A40EB3CBD8F067F4C3BFDC948E605187D8A13E42A71698C125F48C89006C7356921EB3FD54",
                "954D5CAD5BE5A1D36140192898567010D60E57D6C9A45955E0897527945AB66CF941C1ACC5DA3ECBA0CD14AB4CEC0D05E76AED3A123E951633F34D6CFCCDF729476E45EDE95FC2E0B22AB9EBEFA2B6B8"
            };

            foreach (string seq in seqs)
            {
                byte[] s = HexStringToByteArray(seq);
                string key = "71074F465189549BFC1DA059877CEAD8496A3814DA7D65DCA298C6D428463B8F";
                byte[] k = HexStringToByteArray(key);

                Console.WriteLine("Sequence:\n" + ByteArrayToHexString(s, 40));
                Console.WriteLine("\nKey: " + ByteArrayToHexString(k, 256) + "\n");

                byte[] c = new byte[32];
                byte[] iv = new byte[16];
                byte[] t = new byte[32];

                Array.Copy(s, 0, c, 0, 32);
                Array.Copy(s, 32, iv, 0, 16);
                Array.Copy(s, 48, t, 0, 32);

                Console.WriteLine("C  : " + ByteArrayToHexString(c, 48));
                Console.WriteLine("IV : " + ByteArrayToHexString(iv, 16));
                Console.WriteLine("T  : " + ByteArrayToHexString(t, 48));

                byte[] c_iv = new byte[48];
                Array.Copy(c, 0, c_iv, 0, 32);
                Array.Copy(iv, 0, c_iv, 32, 16);

                byte[] t_validate = new HMACSHA256(k).ComputeHash(c_iv);

                Console.WriteLine("\nT? : " + ByteArrayToHexString(t_validate, 48));

                if (!t.SequenceEqual(t_validate))
                {
                    Console.WriteLine("\nInvalid!");
                    continue;
                }

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
}
