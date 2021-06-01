class Prob8_4 {
    public static void main(String[] args) {
        try {
            for(int i = 0; i < 100; i++) {
                throw new Exception("FOR " + i);
            }
        }
        catch(Exception e) {
            System.out.println(e.getMessage());
        }
    }
} 