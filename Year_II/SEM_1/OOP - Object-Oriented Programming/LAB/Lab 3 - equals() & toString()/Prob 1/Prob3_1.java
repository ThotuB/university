class Book {
    private int pages;

    public Book(int p){
        pages = p;
    }

    public Book(){
        pages = 5;
    }

    public void setPages(int p){
        pages = p;
    }

    public static int bookcmp(Book book1, Book book2){
        return book1.pages - book2.pages;
    }

    public boolean equals(Object o){
        return (o instanceof Book) && ((Book)o).pages == this.pages;
    }
}

public class Prob3_1 {
    public static void main(String[] args){
        Book b1 = new Book(31);
        Book b2 = new Book(21);

        int cmpres =  Book.bookcmp(b1, b2);

        if ( cmpres < 0 ){
            System.out.println("Book 1 < Book 2");
        }
        else if ( cmpres == 0 ){
            System.out.println("Book 1 == Book 2");
        }
        else {
            System.out.println("Book 1 > Book 2");
        }

        if ( b1.equals(b2) ){
            System.out.println("Book 1 == Book 2");
        }
        else {
            System.out.println("Book 1 != Book 2");
        }
    }
}