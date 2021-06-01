class L1 extends Exception {
    public String toString() { 
        return "L1"; 
    }
}

class L2 extends Exception {
    public String toString() { 
        return "L2"; 
    }
}
   
class Prob8_3 {
    public static void main(String[] args) {
        for (int i = 0 ; i < 4 ; i++) {
            try {
                if (i==0){
                    throw new L1();
                }
                else {
                    throw new L2();
                } 
            }
            catch (Exception e) {
                System.out.println(e);
            }
        }
    } 
}