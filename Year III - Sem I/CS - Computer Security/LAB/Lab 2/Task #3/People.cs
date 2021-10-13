using System;
using System.Linq;

namespace Task_3
{
    public enum Coin { HEADS, TAILS }

	class Bob
    {
        public Coin Coin { get; private set; } // b
        public byte[] Key { get; private set; } // s

        public Bob(){
            Key = new byte[16];
        }

        public void FlipCoin(){
            int coin = new Random().Next(2);

            Coin = (coin == 1) ? Coin.HEADS : Coin.TAILS;
        }

        public void GenerateKey(){
            new Random().NextBytes(Key);
        }

        public byte[] Compute(byte[] public_key) {
             // G(s)
            byte[] cipher = Crypto.Encrypt(Key);

            // Program.PrintByteArray(cipher);
            if ( Coin == Coin.TAILS ) {
                // G(s) XOR r -> tails
                cipher = Crypto.XOR(cipher, public_key); 
            }

            return cipher; // c
        }
    }

    class Alice
    {
        public byte[] PublicKey { get; private set; } // r

        public Alice(){
            PublicKey = new byte[48];
        }

        public void GenerateKey(){
            new Random().NextBytes(PublicKey);
        }

        public bool Guess(Coin guess, Coin coin, byte[] bob_cipher, byte[] key){
             // G(s)
            byte[] alice_cipher = Crypto.Encrypt(key);

            // Program.PrintByteArray(alice_cipher);
            if ( coin == Coin.TAILS ) {
                // G(s) XOR r -> tails
                alice_cipher = Crypto.XOR(alice_cipher, PublicKey); 
            }

            // check for tampering
            if ( Enumerable.SequenceEqual(alice_cipher, bob_cipher) ) {
                // return guess
                return guess == coin;
            }
            throw new Exception("Invalid cipher"); 
        }
    }
}
