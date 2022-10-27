class Square {
    private int side;

    public Square(){
        side = 15;
    }

    public Square(int s){
        side = s;
    }

    // public void print(){
    //     System.out.println("Square: " + side);
    //     System.out.println("Area: " + side * side + "\n");
    // }

    public String toString(){
        return "Square: " + side + "\nArea: " + side * side + "\n\n";
    }
}

public class Prob3_2 {
    public static void main(String[] args){
        Square s1 = new Square();
        System.out.print(s1);

        s1 = new Square(6);
        System.out.print(s1);
    }
}