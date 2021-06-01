class File {
    private String name;
    private String information;

    public File(String nm, String info){
        this.name = nm;
        this.information = info;
    }

    public String getContent(){
        return this.information;
    }

    public boolean equals(Object o){
        return (o instanceof File) && ((File)o).name.equals(this.name);
    }
}

class Folder {
    private File[] entries;
    private int size = 0;

    public void addFile(File newFile){
        for (int i = 0 ; i < size ; i++){
            if ( this.entries[i].equals(newFile) ){
                return;
            }
        }
        File[] temp = new File[size+1];
        if ( size != 0 ){
            System.arraycopy(entries, 0, temp, 0, size);
        }
        temp[size] = newFile;
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

public class Prob4_1 {
    public static void main(String[] args){
        File f1 = new File("bani.txt", "Abi si Dani");
        File f2 = new File("Romeo Fantastik.mov", "Carolina Jambala");
        File f3 = new File("hatz.txt", "Gionule");

        Folder fol = new Folder();
        fol.addFile(f1);
        fol.addFile(f2);
        fol.addFile(f3);
        fol.addFile(f2);

        System.out.print(fol.getContent());
    }
}
