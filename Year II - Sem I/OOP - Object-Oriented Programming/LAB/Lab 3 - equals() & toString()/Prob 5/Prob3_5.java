class Book {
    private String author;
    private String title;

    public Book(String a, String t){
        author = a;
        title = t;
    }

    public String toString(){
        return "Title: " + this.title + "\nAuthor: " + this.author + "\n\n";
    }

    public boolean equals(Object o){
        return (o instanceof Book) && ((Book)o).author == author && ((Book)o).title == title;
    }
}

class Set {
    private Book[] bookArr;
    private int size = 0;
    private int MAX_SIZE;

    public Set(int max){
        MAX_SIZE = max;
        bookArr = new Book[MAX_SIZE];
    }

    private boolean check(Book b){
        if ( size < MAX_SIZE ){
            for (int i = 0; i < this.size ; i++){
                if ( b.equals(this.bookArr[i]) ){
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    public void push(Book b){
        if ( this.check(b) ){
            bookArr[size] = b;
            size++;
        }
    }

    public static Set union(Set s1, Set s2){
        Set s = new Set(s1.MAX_SIZE + s2.MAX_SIZE);

        for (int i = 0 ; i < s1.size; i++){
            s.push(s1.bookArr[i]);
        }
        for (int i = 0 ; i < s2.size; i++){
            s.push(s2.bookArr[i]);
        }

        return s;
    }

    public String toString(){
        String s = "";

        for (int i = 0 ; i < this.size ; i++){
            s += this.bookArr[i];
        }

        return s;
    }
}

public class Prob3_5 {
    public static void main(String[] args){
        Book b1 = new Book("1", "111");
        Book b2 = new Book("2", "222");
        Book b3 = new Book("3", "333");
        Book b4 = new Book("4", "444");
        Book b5 = new Book("5", "555");
        
        Set s1 = new Set(3);
        s1.push(b1);
        s1.push(b1);
        s1.push(b2);
        s1.push(b3);
        s1.push(b4);

        System.out.print("Set 1 contains:\n" + s1);

        Set s2 = new Set(3);
        s2.push(b5);
        s2.push(b4);
        s2.push(b3);

        System.out.print("Set 2 contains:\n" + s2);
        
        System.out.print("Union Set contains:\n" + Set.union(s1, s2));
    }
}