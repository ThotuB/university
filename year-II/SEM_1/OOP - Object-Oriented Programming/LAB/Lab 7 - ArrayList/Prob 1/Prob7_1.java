import java.util.ArrayList;

class Company {
    private ArrayList<Employee> employeeList = new ArrayList<Employee>();

    public boolean add(Employee newEmployee){
        if ( employeeList.contains(newEmployee) ){
            return false;
        }

        employeeList.add(newEmployee);
        return true;
    }

    public boolean isInCompany(Strategy strategy){
        for (Employee employee: employeeList){
            if ( strategy.isCondition(employee) ){
                return true;
            }
        }
        return false;
    }

    public String toString(){
        String printString = "";

        for (Employee employee: employeeList){
            printString += employee.toString();
        }

        return printString;
    }
}

interface Strategy {
    public boolean isCondition(Employee employee);
}

class Strategy1 implements Strategy {
    String name;

    public Strategy1(String name){
        this.name = name;
    }

    public boolean isCondition(Employee employee){
        return this.name.equals(employee.getName());
    }
}

class Strategy2 implements Strategy {
    public boolean isCondition(Employee employee){
        return (employee.getSalary() == 1000) ;
    }
}

abstract class Employee {
    private String name;
    private int personalID;

    protected Employee(String name, int personalID){
        this.name = name;
        this.personalID = personalID;
    }

    public String getName(){
        return this.name;
    }
    
    abstract double getSalary();

    public boolean equals(Object o){
        if ( o instanceof Employee ){
            if ( ((Employee)o).name.equals(this.name) && ((Employee)o).personalID == (this.personalID) ) {
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

class PermanentEmployee extends Employee {
    private double salary;

    public PermanentEmployee(String name, int personalID, double salary){
        super(name, personalID);

        this.salary = salary;
    }

    public double getSalary(){
        return salary;
    }
}

class HourlyPaidEmployee extends Employee {
    private int workedHours;
    private double hourlyRate;

    public HourlyPaidEmployee(String name, int personalID, double hourlyRate){
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

public class Prob7_1 {
    public static void main(String[] args){
        PermanentEmployee e1 = new PermanentEmployee("Bob", 5255432, 3000);
        PermanentEmployee e2 = new PermanentEmployee("Gion", 654645, 2500);
        HourlyPaidEmployee e3 = new HourlyPaidEmployee("Inca cnv", 5436543, 50);
                            e3.setWorkedHours(20);

        Strategy1 s1 = new Strategy1("Gion");
        Strategy2 s2 = new Strategy2();

        Company c = new Company();

        c.add(e1);

        System.out.println(c.toString());
        System.out.println("Company has strategy1: " + c.isInCompany(s1));
        System.out.println("Company has strategy2: " + c.isInCompany(s2) + "\n");

        c.add(e2);

        System.out.println(c.toString());
        System.out.println("Company has strategy1: " + c.isInCompany(s1));
        System.out.println("Company has strategy2: " + c.isInCompany(s2) + "\n");

        c.add(e3);

        System.out.println(c.toString());
        System.out.println("Company has strategy1: " + c.isInCompany(s1));
        System.out.println("Company has strategy2: " + c.isInCompany(s2) + "\n");
    }
}
