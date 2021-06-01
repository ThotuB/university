class Train {
    private Carriage[] carriages = new Carriage[15];
    private int carriagesSize;

    public Train(Carriage ... carriages){
        this.carriagesSize = carriages.length;

        for (int i = 0 ; i < 15 && i < this.carriagesSize ; i++){
            this.carriages[i] = carriages[i];
        }
    }

    private int getPackageCapacity(){
        int packageCapacityTotal = 0;

        for (int i = 0 ; i < this.carriagesSize ; i++){
            packageCapacityTotal += this.carriages[i].getPackageCapacity();
        }

        return packageCapacityTotal;
    }

    public boolean equals(Object o){
        if ( o instanceof Train ){
            if ( this.getPackageCapacity() == ((Train)o).getPackageCapacity() ){
                return true;
            }
        }
        return false;
    }
}

interface Carriage {
    int getPackageCapacity();
}

class PassengersCarA_A implements Carriage {
    private int passagerCapacity = 40;
    private int packageCapacity = 300;
    
    public int getPassagerCapacity(){
        return this.passagerCapacity;
    }

    public int getPackageCapacity(){
        return this.packageCapacity;
    }

    public void openDoors(){
        System.out.println("Doors Open!");
    }
    
    public void closeDoors(){
        System.out.println("Doors Closed!");
    }
}

class PassengersCarB_A implements Carriage {
    private int passagerCapacity = 50;
    private int packageCapacity = 400;

    public int getPassagerCapacity(){
        return this.passagerCapacity;
    }
    
    public int getPackageCapacity(){
        return this.packageCapacity;
    }

    public void openDoors(){
        System.out.println("Doors Open!");
    }
    
    public void closeDoors(){
        System.out.println("Doors Closed!");
    }

    public void blockWindows(){
        System.out.println("Windows Blocked!");
    }
}

class LoadsCar_A implements Carriage {
    private int packageCapacity = 400;
    
    public int getPackageCapacity(){
        return this.packageCapacity;
    }
}

class PassengersCarA_B implements Carriage {
    public int getPackageCapacity(){
        return 300;
    }

    public void openDoors(){
        System.out.println("Doors Open!");
    }
    
    public void closeDoors(){
        System.out.println("Doors Closed!");
    }
}

class PassengersCarB_B implements Carriage {
    public int getPackageCapacity(){
        return 400;
    }

    public void openDoors(){
        System.out.println("Doors Open!");
    }
    
    public void closeDoors(){
        System.out.println("Doors Closed!");
    }

    public void blockWindows(){
        System.out.println("Windows Blocked!");
    }
}

class LoadsCar_B implements Carriage {
    public int getPackageCapacity(){
        return 400;
    }
}

public class Prob6_2 {
    public static void main(String[] args){
        Train t1 = new Train(new PassengersCarA_A(), new PassengersCarB_A());
        Train t2 = new Train(new LoadsCar_A(), new PassengersCarA_B());
        Train t3 = new Train(new PassengersCarA_B(), new PassengersCarB_B(), new LoadsCar_B());

        if ( t1.equals(t2) ){
            System.out.println("t1 == t2");
        }
        else {
            System.out.println("t1 != t2");
        }

        if ( t2.equals(t3) ){
            System.out.println("t2 == t3");
        }
        else {
            System.out.println("t2 != t3");
        }

        if ( t3.equals(t1) ){
            System.out.println("t3 == t1");
        }
        else {
            System.out.println("t3 != t1");
        }
    }
}
