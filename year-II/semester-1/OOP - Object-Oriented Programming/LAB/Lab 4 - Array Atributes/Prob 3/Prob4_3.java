class Acronyms{
    private String[] word = new String[20];
    private String[] acronym = new String[20];
    private int size = 0;

    public boolean addWordNAcronym(String newWord, String newAcro){
        if ( size == 20 ){
            return false;
        }

        for (int i = 0 ; i < size ; i++){
            if ( this.acronym[i].equals(newAcro) ){
                this.word[i] = newWord;
                return true;
            }
        }

        this.acronym[size] = newAcro;
        this.word[size] = newWord;
        size++;
        return true;
    }

    public String getWord(String acroToFind){
        for (int i = 0 ; i < size ; i++){
            if ( this.acronym[i].equals(acroToFind) ){
                return this.word[i] + "\n";
            }
        }
        return "XXXX\n";
    }

    public String toString(){
        String printString = "";
        for (int i = 0 ; i < size ; i++){
            printString += "Acronym: " + this.acronym[i] + "\nWords: "+ this.word[i] + "\n\n";
        }
        return printString;
    }
}

public class Prob4_3 {
    public static void main(String[] args){
        Acronyms a = new Acronyms();

        a.addWordNAcronym("jfksdjk sdfwe asfsa", "JSA");
        a.addWordNAcronym("colegiul mihai viteazu", "CMV");
        a.addWordNAcronym("colaj manele vechi", "CMV");

        System.out.print(a);

        System.out.print( a.getWord("CMV") );
        System.out.print( a.getWord("RNG") );
    }
}
