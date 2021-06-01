import java.util.*;

abstract class Teacher {
    protected String name;
    protected double salary;

    public Teacher(String name){
        this.name = name;
        this.salary = getSalary();
    }

    public abstract double getSalary();

    public String toString(){
        return "\nName: " + name + "\nSalary: " + salary;
    }

    public boolean equals(Object o){
        if(o instanceof Teacher){
            return((Teacher)o).name.equals(name);
        }
        return false;
    }
}

class HourlyTeacher extends Teacher{
    private static int workedHours = 20;

    public HourlyTeacher(String name){
        super(name);
    }

    public double getSalary(){
        return workedHours * 60;
    }

    public int getWorkedHours(){
        return workedHours;
    }
}

class PermanentTeacher extends Teacher{
    public PermanentTeacher(String name){
        super(name);
    }

    public double getSalary(){
        return 3200.5;
    }
}

class University{
    private String name;
    private ArrayList<Teacher> teachers;
 
    public University(String name){
        this.name = name;
        teachers = new ArrayList<>(12);
    }
 
    public void addTeacher(Teacher teacher) throws AlreadyAddedException{
        if(!teachers.contains(teacher))
            teachers.add(teacher);
        else
            throw new AlreadyAddedException(teacher.name);
    }
    public String toString(){
        return name + " " + teachers;
    }
}

class TeacherAlreadyAddedException extends AlreadyAddedException{
    public TeacherAlreadyAddedException(String name){
        super("Teacher" + name);
    }
}

class AlreadyAddedException extends RuntimeException{
    public AlreadyAddedException(String entity){
        super(entity + " already added!");
    }
}

class Test1{
    public static void main(String[] args){
        Teacher t1 = new PermanentTeacher("Mike");
        Teacher t2 = new PermanentTeacher("Joe");
        Teacher t3 = new HourlyTeacher("Raphael");
        Teacher t4 = new HourlyTeacher("Johnny");
        Teacher t5 = new HourlyTeacher("Mike");

        University university = new University("upt");

        try{
            university.addTeacher(t1);
            university.addTeacher(t2);
            university.addTeacher(t3);
            university.addTeacher(t4);
            university.addTeacher(t5);
        }catch (Exception e){
            System.out.println(e);
        }

        System.out.println(university);
        System.out.println(university);
        System.out.println(university);
        System.out.println(university);
        System.out.println(university);
    }
}