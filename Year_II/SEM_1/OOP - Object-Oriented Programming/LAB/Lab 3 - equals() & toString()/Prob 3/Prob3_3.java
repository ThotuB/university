class Pyramid {
    public Pyramid(int n){
        for ( ; n > 0 ; n--){
            for (int i = 0 ; i < n ; i++){
                System.out.print(n + " ");
            }
            System.out.print("\n");
        }
    }
}

public class Prob3_3 {
    public static void main(String[] args){
        new Pyramid(6);
    }
}