abstract class Plane {
    private int planeID;
    private static int planeIDNext = 1;
    private int totalEnginePower;

    public Plane(int totalEnginePower){
        this.totalEnginePower = totalEnginePower;

        this.planeID = planeIDNext;
        planeIDNext++;
    }

    public String getPlaneID(){
        return "" + planeID;
    }

    public int getTotalEnginePower(){
        return totalEnginePower;
    }

    public void takeOff(){
        System.out.print("Plane " + this.getPlaneID() + " : ");
        System.out.println("Taking off!");
    }
    
    public void fly(){
        System.out.print("Plane " + this.getPlaneID() + " : ");
        System.out.println("Flying...");
    }

    public void land(){
        System.out.print("Plane " + this.getPlaneID() + " : ");
        System.out.println("Landing!");
    }
}

abstract class PassangerPlane extends Plane {
    private int maxPassangers;

    public PassangerPlane(int maxPassangers, int totalEnginePower){
        super(totalEnginePower);

        this.maxPassangers = maxPassangers;
    }

    public int getMaxPassangers(){
        return maxPassangers;
    }
}

class BoeingPassangerPlane extends PassangerPlane {
    public BoeingPassangerPlane(int maxPassangers, int totalEnginePower){
        super(maxPassangers, totalEnginePower);
    }
}

class ConcordePassangerPlane extends PassangerPlane {
    public ConcordePassangerPlane(int maxPassangers, int totalEnginePower){
        super(maxPassangers, totalEnginePower);
    }

    public void goSuperSonic(){
        System.out.print("Plane " + this.getPlaneID() + " : ");
        System.out.println("Supersonic mode activated!");
    }

    public void goSubSonic(){
        System.out.print("Plane " + this.getPlaneID() + " : ");
        System.out.println("Supersonic mode deactivated!");
    }
}

abstract class FighterPlane extends Plane {
    public FighterPlane(int totalEnginePower){
        super(totalEnginePower);
    }

    public void launchMissile(){
        System.out.print("Plane " + this.getPlaneID() + " : ");
        System.out.println("Launching rocket!");
    }
}

class MiGFighterPlane extends FighterPlane {
    public MiGFighterPlane(int totalEnginePower){
        super(totalEnginePower);
    }

    public void highSpeedGeometry(){
        System.out.print("Plane " + this.getPlaneID() + " : ");
        System.out.println("High Speed Geometry Selected.");
    }

    public void normalGeometry(){
        System.out.print("Plane " + this.getPlaneID() + " : ");
        System.out.println("Normal Geometry Selected.");
    }
}

class TomCatFighterPlane extends FighterPlane {
    public TomCatFighterPlane(int totalEnginePower){
        super(totalEnginePower);
    }

    public void refuel(){
        System.out.print("Plane " + this.getPlaneID() + " : ");
        System.out.println("TomCat - Refuelling");
    }
}

public class Prob5_1 {
    public static void main(String[] args){
        BoeingPassangerPlane p1 = new BoeingPassangerPlane(500, 95000);
        ConcordePassangerPlane p2 = new ConcordePassangerPlane(100, 30000);
        MiGFighterPlane p3 = new MiGFighterPlane(2500);
        TomCatFighterPlane p4 = new TomCatFighterPlane(2000);

        p1.takeOff();
        p1.fly();
        p1.land();

        p2.goSuperSonic();
        p2.goSubSonic();
        p2.takeOff();

        p3.highSpeedGeometry();
        p3.normalGeometry();

        p4.refuel();
        p4.launchMissile();
    }
}