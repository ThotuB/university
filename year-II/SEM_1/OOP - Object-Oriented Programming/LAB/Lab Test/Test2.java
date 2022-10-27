import java.util.*;

abstract class Student{
    protected String name;
    protected double grade;
    protected int year;

    public Student(String n,double g,int y){
        this.name = n;
        this.grade = g;
        this.year = y;
    }

    public abstract double getGrade();

    public String toString(){
        return "Name:"+ name +"Grade:" + grade + "year:" + year;
    }

    public boolean equals(Object o){
        if(o instanceof Student){
            return ((Student)o).name.equals(name) && ((Student)o).year == year;
        }
        return false;
    }

    public String getName(){
        return name;
    }
}

class ErasmusStudent extends Student{
    public ErasmusStudent(String n, double g,int y){
        super(n,g,y);
    }

    public double getGrade(){
        return grade*10;
    }
}
class RegularStudent extends Student{
    public RegularStudent(String n,double g,int y){
        super(n,g,y);
    }

    public double getGrade(){
        return grade;
    }
}

class Uni{
    private String name;
    private List<Student> students;
    
    public Uni(String name){
        this.name = name;
        this.students = new ArrayList<>(5);
    }

    public void addStudent(Student student) throws StudentAlreadyExistsExcption{
        if(!students.contains(student)){
            students.add(student);
        }
        else {
            throw new StudentAlreadyExistsExcption(student.getName());
        }
    }

    public String toString(){
        return "University" + name + "has students"+ students;
    }
}

class StudentAlreadyExistsExcption extends RuntimeException{
    public StudentAlreadyExistsExcption(String studentName){
        super("Student " + studentName + " already in university");
    }
}

class Test2{
    public static void main(String[] args){
        Uni university = new Uni("UPT");
        for(int i=0;i<10;i++){
            if(i%2==0)
                university.addStudent(new ErasmusStudent("Student",i+1,i));
            else 
                university.addStudent(new RegularStudent("Student",i+1,i-1));
        }
    
        System.out.println(university);
    }
    
}

