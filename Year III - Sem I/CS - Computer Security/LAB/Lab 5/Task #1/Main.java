import System;
import System.Numerics;

class Program
{
    // static (BigInteger, BigInteger) ProductSumRoots(BigInteger sum, BigInteger product)
    // {
    //     BigInteger delta = BigInteger.Pow(sum, 2) - 4 * product;
    //     BigInteger sqrt_delta = BigInteger.Pow(delta, 1.0 / 2);

    //     Console.WriteLine(sqrt_delta);

    //     BigInteger root1 = (sum + BigInteger.Pow(delta, 1/2)) / 2;
    //     BigInteger root2 = (sum - BigInteger.Pow(delta, 1/2)) / 2;

    //     return (root1, root2);
    // }

    static void Main(String[] args)
    {
        BigInteger n = new BigInteger(837210799);
        BigInteger e = new BigInteger(7);
        BigInteger d = new BigInteger(478341751);

        BigInteger k = (d * e - 1) / n;
        BigInteger rem = (d * e - 1) % n;
        k += rem.IsZero ? 1 : 0;
        
        BigInteger S = (k * (n + 1) + 1 - d * e) / k;
        BigInteger P = n;

        (BigInteger x1, BigInteger x2) = ProductSumRoots(S, P);

        Console.WriteLine($"x1 = {x1}");
        Console.WriteLine($"x2 = {x2}");
    }
}
