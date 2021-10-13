using System;

namespace Task_3
{
	class Program
	{
		const Coin GUESS = Coin.HEADS;

		public static void PrintByteArray(byte[] array){
			foreach (byte b in array){
				Console.Write("{0:X2} ", b);
			}
			Console.WriteLine();
		}

		static void Normal(Bob bob, Alice alice){
			// Step 1: Bob flips a coin
			bob.FlipCoin();
			// Step 2: Alice generates a 384-bit key
			alice.GenerateKey();
			// Step 3: Bob generates a 128-bit key
			bob.GenerateKey();
			byte[] cipher = bob.Compute(alice.PublicKey);
			// Step 4: Alice guesses, Bob sends coin flip and cipher
			string outcome;
			try {
				bool res = alice.Guess(GUESS, bob.Coin, cipher, bob.Key);
				outcome = ( res ) ? "correct" : "incorrect";
			}
			catch (Exception) {
				outcome = "not accepted";
			}

			Console.WriteLine("Bob's coin: {0}", bob.Coin);
			Console.WriteLine("Alice's guess: {0}", Coin.HEADS);
			Console.WriteLine("Result: {0}", outcome);
		}

		static void Tampered(Bob bob, Alice alice){
			// Step 1: Bob flips a coin
			bob.FlipCoin();
			// Step 2: Alice generates a 384-bit key
			alice.GenerateKey();
			// Step 3: Bob generates a 128-bit key
			bob.GenerateKey();
			byte[] cipher = new byte[48];
			new Random().NextBytes(cipher); // tamper with cipher
			// Step 4: Alice guesses, Bob sends coin flip and cipher
			string outcome;
			try {
				bool res = alice.Guess(GUESS, bob.Coin, cipher, bob.Key);
				outcome = ( res ) ? "correct" : "incorrect";
			}
			catch (Exception) {
				outcome = "not accepted";
			}

			Console.WriteLine("Bob's coin: {0}", bob.Coin);
			Console.WriteLine("Alice's guess: {0}", Coin.HEADS);
			Console.WriteLine("Result: {0}", outcome);
		}

		static void Main(string[] args)
		{
			Bob bob = new Bob();
			Alice alice = new Alice();

			Normal(bob, alice);
			Tampered(bob, alice);
		}
	}
}
