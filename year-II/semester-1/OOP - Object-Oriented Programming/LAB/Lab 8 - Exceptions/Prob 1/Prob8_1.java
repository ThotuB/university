import java.util.ArrayList;

class Company8 {
    private ArrayList<Employee8> employeeList = new ArrayList<Employee8>();

    public boolean add(Employee8 newEmployee) throws EmployeeDuplicateException{
        if ( employeeList.contains(newEmployee) ){
            throw new EmployeeDuplicateException();
        }

        employeeList.add(newEmployee);
        return true;
    }

    public String toString(){
        String printString = "";

        for (Employee8 Employee8: employeeList){
            printString += Employee8.toString();
        }

        return printString;
    }
}

class EmployeeDuplicateException extends Exception {
    public EmployeeDuplicateException(){
        super("Duplicate Employee");
    }
}

abstract class Employee8 {
    private String name;
    private int personalID;

    protected Employee8(String name, int personalID){
        this.name = name;
        this.personalID = personalID;
    }

    public String getName(){
        return this.name;
    }
    
    abstract double getSalary();

    public boolean equals(Object o){
        if ( o instanceof Employee8 ){
            if ( ((Employee8)o).name.equals(this.name) && ((Employee8)o).personalID == (this.personalID) ) {
                return true;
            }
        }
        return false;
    }

    public String toString(){
        String printString = "";

        printString += "Name: " + this.name + "\n";
        printString += "Personal ID: " + this.personalID + "\n";
        printString += "Salary: " + this.getSalary() + "\n";

        return printString;
    }
}

class PermanentEmployee8 extends Employee8 {
    private double salary;

    public PermanentEmployee8(String name, int personalID, double salary){
        super(name, personalID);

        this.salary = salary;
    }

    public double getSalary(){
        return salary;
    }
}

class HourlyPaidEmployee8 extends Employee8 {
    private int workedHours;
    private double hourlyRate;

    public HourlyPaidEmployee8(String name, int personalID, double hourlyRate){
        super(name, personalID);

        this.hourlyRate = hourlyRate;
    }

    public void setWorkedHours(int workedHours){
        this.workedHours = workedHours;
    }

    public double getSalary(){
        return workedHours * hourlyRate;
    }
}

public class Prob8_1 {
    public static void main(String[] args){
        PermanentEmployee8 e1 = new PermanentEmployee8("Bob", 5255432, 3000);
        PermanentEmployee8 e2 = new PermanentEmployee8("Gion", 654645, 2500);
        HourlyPaidEmployee8 e3 = new HourlyPaidEmployee8("Inca cnv", 5436543, 50);
                            e3.setWorkedHours(20);

        Company8 c = new Company8();

        try {
            c.add(e1);
            c.add(e2);
            c.add(e3);
            c.add(e2);
        }
        catch (Exception e){
            System.out.println(e);
        }

        System.out.println(c);
    }
}
