import java.math.BigInteger;

class RSAFactorization {
    public interface IFactorize {
        BigInteger[] factorize(BigInteger n, BigInteger e, BigInteger d);
    }

    public interface ICurriedFactorize {
        IFactorize run(BigInteger x);
    }

    public static IFactorize factorize1 = (n, e, d) -> {
        BigInteger temp = e.multiply(d).subtract(BigInteger.ONE);
        BigInteger k = temp.divide(n).add( (!(temp.mod(n).equals(BigInteger.ZERO)) ? BigInteger.ONE : BigInteger.ZERO) );

        System.out.println(String.format("k = %s", k));

        BigInteger sum = k.multiply(n.add(BigInteger.ONE)).subtract(temp).divide(k);
        BigInteger prod = n;

        System.out.println(String.format("sum = %s\nprod = %s", sum, prod));

        BigInteger delta = sum.pow(2).subtract(prod.multiply(BigInteger.valueOf(4)));
        BigInteger sqrtDelta = delta.sqrt();

        System.out.println(String.format("delta = %s\nsqrtDelta = %s", delta, sqrtDelta));
        
        BigInteger x1 = sum.add(sqrtDelta).divide(BigInteger.TWO);
        BigInteger x2 = sum.subtract(sqrtDelta).divide(BigInteger.TWO);

        return new BigInteger[] {x1, x2};
    };

    public static ICurriedFactorize factorize2 = (x) -> {
        IFactorize factorize = (n, e, d) -> {
            BigInteger temp = e.multiply(d).subtract(BigInteger.ONE);
    
            BigInteger power = temp.divide(BigInteger.TWO);
            BigInteger result;
    
            do {
                result = x.modPow(power, n);
                power = power.divide(BigInteger.TWO);
            }while (result.equals(BigInteger.ONE) );
            
            System.out.println(String.format("result = %s", result));
    
            BigInteger p = n.gcd(result.add(BigInteger.ONE));
            BigInteger q = n.gcd(result.subtract(BigInteger.ONE));
    
            return new BigInteger[] {p, q};
        };

        return factorize;
    };

    public static BigInteger calcPrivateExponent(BigInteger p, BigInteger q, BigInteger e) {
        BigInteger phi = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));

        return e.modInverse(phi);
    }
}

public class Main {
    public static BigInteger solution(BigInteger n, BigInteger e1, BigInteger d1, BigInteger e2, RSAFactorization.IFactorize factorize) {
        BigInteger[] factors = factorize.factorize(n, e1, d1);
    
        BigInteger p = factors[0];
        BigInteger q = factors[1];

        System.out.println(String.format("p = %s\nq = %s", p, q));

        return RSAFactorization.calcPrivateExponent(p, q, e2);
    }

    public static void main(String[] args) {
        BigInteger n = new BigInteger("837210799");

        BigInteger e1 = new BigInteger("7");
        BigInteger d1 = new BigInteger("478341751");
        BigInteger e2 = new BigInteger("17");
        System.out.println("SOLUTION 1");
        BigInteger d2 = solution(n, e1, d1, e2, RSAFactorization.factorize1);

        System.out.println(String.format("d2 = %s", d2));

        System.out.println("\nSOLUTION 2");
        BigInteger x = new BigInteger("10");
        d2 = solution(n, e1, d1, e2, RSAFactorization.factorize2.run(x));

        System.out.println(String.format("d2 = %s", d2));
    }
}