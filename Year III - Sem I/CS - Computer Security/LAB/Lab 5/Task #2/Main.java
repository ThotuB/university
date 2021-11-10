import java.math.BigInteger;

class RSAFactorization {
    public static BigInteger[] factorize(BigInteger n, BigInteger e, BigInteger d) {
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
    }
}

public class Main {
    public static void main(String[] args) {
        BigInteger n = new BigInteger("5076313634899413540120536350051034312987619378778911504647420938544746517711031490115528420427319479274407389058253897498557110913160302801741874277608327");
        BigInteger e = new BigInteger("3");
        BigInteger d = new BigInteger("3384209089932942360080357566700689541991746252519274336431613959029831011807259226655786125050887727921274719751986104162037800807641522348207376583379547");
        
        BigInteger[] factors = RSAFactorization.factorize(n, e, d);
    
        BigInteger p = factors[0];
        BigInteger q = factors[1];

        System.out.println(String.format("p = %s\nq = %s", p, q));

        BigInteger res = p.multiply(q);

        if (res.equals(n)) {
            System.out.println("Success!");
        } else {
            System.out.println("Failure!");
        }
    }
}