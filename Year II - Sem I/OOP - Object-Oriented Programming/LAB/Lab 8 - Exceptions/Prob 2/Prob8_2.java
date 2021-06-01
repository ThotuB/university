class Operation {
    public static void performDivision(int number, int divisor) throws DivisionByZeroException{
        if ( divisor == 0 ){
            throw new DivisionByZeroException();
        }
        System.out.println((float)number/divisor);
    }
}

class DivisionByZeroException extends RuntimeException {
    public DivisionByZeroException(){
        super("Division by 0");
    }
}

public class Prob8_2 {
    public static void main(String[] args){
        Operation.performDivision(4, 3);
        try {
            Operation.performDivision(4, 0);
        }
        catch ( Exception e ){
            System.out.println(e);
        }

        System.out.println("plm");

        // int[] c = new int[3];
        // System.out.println(c[5]);
    }
}
