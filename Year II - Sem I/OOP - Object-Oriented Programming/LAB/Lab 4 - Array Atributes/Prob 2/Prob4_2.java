class Text {
    private String[] word;
    private int[] occurance;
    private int size = 0;

    public Text(){
        this.word = new String[20];
        this.occurance = new int[20];
    }

    public boolean addWord(String newWord){
        for (int i = 0 ; i < size ; i++){
            if ( this.word[i].equals(newWord) ){
                this.occurance[i]++;
                return true;
            }
        }
        if ( size == 20 ){
            return false;
        }
        this.word[size] = newWord;
        this.occurance[size] = 1;
        size++;
        return true;
    }

    public String toString(){
        String printString = "";
        
        for (int i = 0 ; i < size ; i++){
            printString += "Word: " + this.word[i] + "\nOccurance: " + this.occurance[i] + "\n\n";
        }

        return printString;
    }
}

public class Prob4_2 {
    public static void main(String[] args){
        Text t1 = new Text();
        t1.addWord("ceva");
        t1.addWord("ok");
        t1.addWord("ok");

        System.out.print(t1);
    }
}
