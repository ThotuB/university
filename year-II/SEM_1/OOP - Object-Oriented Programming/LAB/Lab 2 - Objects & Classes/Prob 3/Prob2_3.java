class Complex {
  private double re;
  private double im;
  private static int counter = 0;

  public Complex(double r, double i){
    re = r;
    im = i;
  }

  public double returnModule(){
    return Math.sqrt(re*re + im*im);
  }

  public void printNumber(){
    System.out.println("Number: " + re + " + i*" + im);
    counter++;
  }

  public static Complex sum(Complex nr1, Complex nr2){
    Complex sum = new Complex(nr1.re +  nr2.re, nr1.im + nr2.im);
    return sum;
  }

  public static int returnCounter(){
    return counter;
  }
}

public class Prob2_3 {
  public static void main(String[] args){
    Complex c1, c2;
    c1 = new Complex(3, 5);
    System.out.println("Module: " + c1.returnModule());
    c1.printNumber();
    System.out.println("Counter: " + Complex.returnCounter() + "\n");

    c2 = new Complex(3, 4);
    System.out.println("Module: " + c2.returnModule());
    c2.printNumber();
    System.out.println("Counter: " + Complex.returnCounter() + "\n");

    Complex c3 = Complex.sum(c1, c2);
    System.out.println("Module: " + c3.returnModule());
    c3.printNumber();
    System.out.println("Counter: " + Complex.returnCounter() + "\n");
  }
}
