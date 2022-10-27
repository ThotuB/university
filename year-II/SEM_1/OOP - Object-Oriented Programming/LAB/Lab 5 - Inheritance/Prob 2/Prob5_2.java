abstract class Figure {
    private String color;
    protected double perimeter;

    public Figure(String color){
        this.color = color;
    }

    public void setColor(String color){
        this.color = color;
        Observer.notifyChange();
    }

    abstract public void computePerimeter();

    public String toString(){
        return color + " " + perimeter;
    }
}

class Circle extends Figure {
    private int radius;

    public Circle(String color, int radius){
        super(color);

        this.radius = radius;
        this.computePerimeter();
    }

    public void setRadius(int radius){
        this.radius = radius;
        this.computePerimeter();
        Observer.notifyChange();
    }

    public void computePerimeter(){
        super.perimeter = 2 * this.radius * Math.PI;
    }

    public boolean equals(Object o){
        if ( o instanceof Circle ){
            if ( perimeter == ((Circle)o).perimeter ){
                return true;
            }
        }
        return false;
    }

    public String toString(){
        return "Circle " + super.toString();
    }
}

class Square extends Figure {
    private int side;

    public Square(String color, int side){
        super(color);

        this.side = side;
        this.computePerimeter();
    }

    public void setSide(int side){
        this.side = side;
        this.computePerimeter();
        Observer.notifyChange();
    }

    public void computePerimeter(){
        super.perimeter = 4 * this.side;
    }

    public boolean equals(Object o){
        if ( o instanceof Square ){
            if ( perimeter == ((Square)o).perimeter ){
                return true;
            }
        }
        return false;
    }

    public String toString(){
        return "Square " + super.toString();
    }
}

class Triangle extends Figure {
    private int side1, side2, side3;

    public Triangle(String color, int side1, int side2, int side3){
        super(color);

        this.side1 = side1;
        this.side2 = side2;
        this.side3 = side3;
        this.computePerimeter();
    }

    public void setSides(int side1, int side2, int side3){
        this.side1 = side1;
        this.side2 = side2;
        this.side3 = side3;
        this.computePerimeter();
        Observer.notifyChange();
    }

    public void computePerimeter(){
        super.perimeter = this.side1 + this.side2 + this.side3;
    }

    public boolean equals(Object o){
        if ( o instanceof Triangle ){
            if ( perimeter == ((Triangle)o).perimeter ){
                return true;
            }
        }
        return false;
    }

    public String toString(){
        return "Triangle " + super.toString();
    }
}

class Observer {
    private Figure[] figureArray = new Figure[20];
    private int figureArraySize = 0;

    public void addFigure(Figure newFigure){
        if ( figureArraySize < 20 ){
            figureArray[figureArraySize] = newFigure;
            figureArraySize++;
        }
    }

    public static void notifyChange(){
        System.out.println("Figure Changed!");
    }

    public String toString(){
        String getString = "";

        for (int i = 0 ; i < figureArraySize ; i++){
            getString += figureArray[i] + "\n";
        }

        return getString;
    }
}

public class Prob5_2 {
    public static void main(String[] args){
        Circle c = new Circle("red", 5);
        Square s = new Square("blue", 2);
        Triangle t = new Triangle("green", 6, 2, 7);

        System.out.println(c);
        System.out.println(s);
        System.out.println(t);
    }
}
