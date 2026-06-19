public class Lab2 {
    public static void main(String[] args) {
  
        // Q1
        System.out.println("Q1");
        Employee e1 = new Employee();
        e1.setEmpNum(101);
        e1.setEmpName("Ali");
        System.out.println("Employee Number: " + e1.getEmpNum());
        System.out.println("Employee Name: " + e1.getEmpName());
        System.out.println();
  
        // Q2
        System.out.println("Q2") ;
        Car car = new Car() ;
        car.setBrand("BMW") ;
        System.out.println("Car brand: " + car.getBrand()) ;
        System.out.println("Car year: " + car.getYear()) ;
        System.out.println();

        // Q3
        System.out.println("Q3") ;
        Book b1 = new Book("Java 101", "John Doe");
        b1.display();
        System.out.println();

        // Q4
        System.out.println("Q4") ;
        Student student = new Student() ;
        student.setName("Lee") ;
        System.out.println("Student name: " + student.getName());
        System.out.println("Student age: " + student.getAge());
        System.out.println();

        // Q5
        System.out.println("Q5") ;
        Message message = new Message() ;
        message.display(); 
        message.display("Hello, my name is Lee!");
        System.out.println();

        // Q6
        System.out.println("Q6");
        new User();
        new User();
        System.out.println("Total Users: " + User.getUserCount());
        System.out.println();

        // Q7
        System.out.println("Q7");
        Employee2 e2 = new Employee2();
        e2.setSalary(5000);
        System.out.println("Salary: " + e2.getSalary());
  
    }
  }
  
  class Employee {
    // TODO: Add fields
    private int empNum ;
    private String empName ;
  
    // TODO: Add setter and getter methods
    public void setEmpNum(int eNum){
      empNum = eNum ; 
    }
  
    public int getEmpNum(){
      return empNum ;
    }
  
    public void setEmpName(String eName){
      empName = eName ;
    }
  
    public String getEmpName(){
      return empName ;
    }
  
  }
  
  
  //Q2: Instance Variables and Data Fields
  //Fill in the missing parts to declare instance variables properly and ensure encapsulation.
  class Car {
    // TODO: Declare two private instance variables (brand and year)
    private String brand ;
    private int year = 2025 ;
  
    // TODO: Create setter for brand
    public void setBrand(String b){
      brand = b ;
    }
  
    public String getBrand(){
      return brand ;
    }
  
    // TODO: Create getter for year
    public int getYear(){
      return year ;
    }
  
  }
  
  
  //Q3
  class Book {
    private String title;
    private String author;
  
    // TODO: Add a constructor
    public Book(String t, String a){
      title = t ;
      author = a ;
    }
  
    public void display() {
        System.out.println("Title: " + title);
        System.out.println("Author: " + author);
    }
  }
  
  
  //Q4: Getters and Setters
  //Complete the Student class by implementing proper getter and setter methods.
  class Student {
    private String name;
    private int age = 21 ;
  
    // TODO: Implement setter for name
    public void setName(String n){
      name = n ;
    }
  
    public String getName(){
      return name ;
    }
  
    // TODO: Implement getter for age
    public int getAge(){
      return age ;
    }
  
  }
  
  
  //Q5: Method Overloading
  //The following class should use method overloading to display a message with and without a parameter.
  class Message {
    // TODO: Write a method display() that prints "Hello!"
    public void display(){
      System.out.println("Hello!") ;
    }
  
    // TODO: Overload display(String msg) to print "Message: msg"
    public void display(String msg){
      System.out.println("Message: " + msg) ;
    }
  
  }
  
  
  //Q6: Static vc Non-Static
  //Fix the following code to keep track of how many objects of User have been created.
  class User {
    // TODO: Declare a static counter variable
    private static int count = 0 ;
  
    public User() {
      // TODO: Increment counter
      count++ ;
    }
  
    public static int getUserCount() {
      // TODO: Return counter
      return count ;
    }
  }
  
  
  //Q7: Access Modifiers
  //Fix the code below to ensure the salary field is private and accessible only through methods.
  class Employee2 {
    // TODO: Make salary private
    private float salary ;
  
    // TODO: Write setSalary() and getSalary() methods
    public void setSalary(float s){
      salary = s ;
    }
  
    public float getSalary(){
      return salary ;
    }
  
  
  }
  
  
  
  
  
  