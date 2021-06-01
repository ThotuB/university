import java.util.ArrayList;

interface Type {
    public String getType();

    public String toString();

    public boolean equals(Object o);
}

class IntegerType implements Type{
    private int data;

    public IntegerType(int data){
        this.data = data;
    }

    public int getData(){
        return this.data;
    }

    public String getType(){
        return "Type: IntegerType";
    }

    public String toString(){
        return "" + this.data;
    }

    public boolean equals(Object o){
        if ( o instanceof IntegerType ){
            if ( this.data == ((IntegerType)o).getData() ){
                return true;
            }
        }
        return false;
    }
}

class StringType implements Type{
    private String data;

    public StringType(String data){
        this.data = data;
    }

    public String getData(){
        return this.data;
    }

    public String getType(){
        return "Type: StringType";
    }

    public String toString(){
        return this.data;
    }

    public boolean equals(Object o){
        if ( o instanceof StringType ){
            if ( this.data.equals( ((StringType)o).getData() ) ){
                return true;
            }
        }
        return false;
    }
}

class CollectionType implements Type{
    private ArrayList<Type> data = new ArrayList<Type>();

    public CollectionType(Type ... data){
        for (Type type: data){
            this.add(type);
        }
    }

    public Type get(int index){
        return data.get(index);
    }

    public int size(){
        return this.data.size();
    }

    public String getType(){
        String printString = "Type: CollectionType( ";

        for (Type type: data){
            printString += type.getType() + ", ";
        }
        printString += " )";

        return printString;
    }

    public void add(Type newType){
        data.add(newType);
    }

    public String toString(){
        String printString = "( ";

        for (Type type: data){
            printString += type.toString() + ", ";
        }
        printString = printString.substring(0, printString.length() - 2);
        printString += " )";

        return printString;
    }

    public boolean equals(Object o){
        if ( o instanceof CollectionType ){
            if ( this.size() == ((CollectionType)o).size() ){
                for (int index = 0 ; index < this.size() ; index++){
                    if ( !this.get(index).equals( ((CollectionType)o).get(index) ) ){
                        return false;
                    }
                }
                return true;
            }
        }
        return false;
    }
}

public class Prob7_2 {
    public static void main(String[] args){
        // I
        CollectionType c1 = new CollectionType(new IntegerType(7), new IntegerType(4), new StringType("Eu"), new IntegerType(12));

        System.out.println(c1);

        // II
        CollectionType c2 = new CollectionType(new IntegerType(2), new IntegerType(8));

        c1.add(c2);
        System.out.println(c2);
        System.out.println(c1);

        // III
        System.out.println("c1 == c1: " + c1.equals(c1));
        System.out.println("c1 == c2: " + c1.equals(c2));
        System.out.println("c2 == c2: " + c2.equals(c2));

    }
}
