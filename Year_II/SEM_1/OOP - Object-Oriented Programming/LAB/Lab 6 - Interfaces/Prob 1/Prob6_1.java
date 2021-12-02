interface Item {
    String getContent();
}

class File implements Item{
    private String information;

    public File(String information){
        this.information = information;
    }

    public String getContent(){
        return this.information;
    }
}

class Folder implements Item{
    private Item[] entries;
    private int size = 0;

    public void addItem(Item newItem){
        Item[] temp = new Item[size+1];
        if ( size != 0 ){
            System.arraycopy(entries, 0, temp, 0, size);
        }
        temp[size] = newItem;
        this.entries = temp;
        size++;
    }

    public String getContent(){
        String printString = "";

        for (int i = 0 ; i < size ; i++){
            printString += this.entries[i].getContent() + "\n";
        }
        
        return printString;
    }
}

public class Prob6_1 {
    public static void main(String[] args){
        File f1 = new File("file1.txt");
        File f2 = new File("file2.mov");
        File f3 = new File("file3.txt");

        Folder fol1 = new Folder();
        Folder fol2 = new Folder();
        fol1.addItem(f1);
        fol1.addItem(f2);
        fol2.addItem(f3);
        fol2.addItem(f2);
        fol1.addItem(fol2);

        System.out.print(fol1.getContent());
        System.out.print(fol2.getContent());
    }
}
