import java.util.Stack;

class MyStack {
    private int MAX_ELEMENTS;
    private int currentElements = 0;
    private Stack<Object> elements = new Stack<Object>();

    public MyStack(int max) throws RuntimeException{
        if ( max >= 5000 ){
            throw new RuntimeException("Too Many Elements");
        }

        this.MAX_ELEMENTS = max;
    }

    public void push(Object o){
        try {
            if ( this.currentElements == this.MAX_ELEMENTS ){
                throw new Exception("Stack Full");
            }
            
            this.elements.push(o);
            this.currentElements++;
        }
        catch (Exception e){
            System.out.println(e);
        }
    }

    public Object pop(){
        try {
            if ( this.currentElements == 0 ){
                throw new Exception("Stack Empty");
            }
            
            Object o = this.elements.pop();
            this.currentElements--;

            return o;
        }
        catch (Exception e){
            System.out.println(e);
        }
        
        return null;
    }

    public String toString(){
        String printString = "Stack: ";

        for (Object o: this.elements){
            printString  += o + " ";
        }

        return printString;
    }
}

public class Prob8_5 {
    public static void main(String[] args){
            MyStack st = new MyStack(24324123);

            st.push(1);
            System.out.println(st);
            st.push(2);
            System.out.println(st);
            st.push(3);
            System.out.println(st);
            st.pop();
            System.out.println(st);
            st.push(4);
            System.out.println(st);
            st.push(5);
            System.out.println(st);
            st.pop();
            System.out.println(st);
            st.pop();
            System.out.println(st);
            st.pop();
            System.out.println(st);
            st.pop();
            System.out.println(st);
    }
}
