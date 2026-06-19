import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;

/**
 * StudentCourseSystem.java
 * 
 * Mini Project: Student Course Registration System
 * 
 * Features:
 * - Add students and courses
 * - Register students to courses
 * - View all students and their registered courses
 * 
 * Author: TAN ZHI MING , LEE YIN SHEN
 * Date: 20 June 2025
 */

public class StudentCourseSystem {

    // === CLASS RELATIONSHIPS ===
    static abstract class Person {
        protected String name;
        protected int id;

        public Person(String name, int id) {
            this.name = name;
            this.id = id;
        }

        public abstract void displayRole();
    }

    static class Student extends Person {
        private ArrayList<Course> registeredCourses;

        public Student(String name, int id) {
            super(name, id);
            this.registeredCourses = new ArrayList<>();
        }

        public void registerCourse(Course course) {
            registeredCourses.add(course);
        }

        public ArrayList<Course> getCourses() {
            return registeredCourses;
        }

        @Override
        public void displayRole() {
            System.out.println("Student: " + name + " (ID: " + id + ")");
        }
    }

    static class Course {
        private String courseName;

        public Course(String courseName) {
            this.courseName = courseName;
        }

        public String getCourseName() {
            return courseName;
        }

        @Override
        public String toString() {
            return courseName;
        }
    }

    public static void main(String[] args) {
        ArrayList<Student> students = new ArrayList<>();
        ArrayList<Course> courses = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        int choice = -1;

        while (choice != 5) {
            System.out.println("\n=== Student Course Registration System ===");
            System.out.println("1. Add Student");
            System.out.println("2. Add Course");
            System.out.println("3. Register Student to Course");
            System.out.println("4. View Students and Courses");
            System.out.println("5. Exit");
            System.out.print("Enter choice: ");

            try {
                choice = Integer.parseInt(scanner.nextLine());

                switch (choice) {
                    case 1:
                        System.out.print("Enter student name: ");
                        String name = scanner.nextLine();
                        System.out.print("Enter student ID (integer): ");
                        int id = Integer.parseInt(scanner.nextLine());
                        students.add(new Student(name, id));
                        System.out.println("Student added.");
                        break;

                    case 2:
                        System.out.print("Enter course name: ");
                        String courseName = scanner.nextLine();
                        courses.add(new Course(courseName));
                        System.out.println("Course added.");
                        break;

                    case 3:
                        if (students.isEmpty() || courses.isEmpty()) {
                            System.out.println("Please add both students and courses first.");
                            break;
                        }
                        System.out.println("Select Student:");
                        for (int i = 0; i < students.size(); i++) {
                            System.out.println(i + ". " + students.get(i).name);
                        }
                        System.out.print("Enter student number: ");
                        int stuIndex = Integer.parseInt(scanner.nextLine());

                        System.out.println("Select Course:");
                        for (int i = 0; i < courses.size(); i++) {
                            System.out.println(i + ". " + courses.get(i).getCourseName());
                        }
                        System.out.print("Enter course number: ");
                        int courseIndex = Integer.parseInt(scanner.nextLine());

                        students.get(stuIndex).registerCourse(courses.get(courseIndex));
                        System.out.println("Registered successfully.");
                        break;

                    case 4:
                        if (students.isEmpty()) {
                            System.out.println("No students to display.");
                            break;
                        }
                        for (Student stu : students) {
                            stu.displayRole();
                            ArrayList<Course> regCourses = stu.getCourses();
                            if (regCourses.isEmpty()) {
                                System.out.println("No courses registered.");
                            } else {
                                for (Course c : regCourses) {
                                    System.out.println("  - " + c.getCourseName());
                                }
                            }
                        }
                        break;

                    case 5:
                        System.out.println("Exiting system...");
                        break;

                    default:
                        System.out.println("Invalid choice. Try again.");
                }

            } catch (NumberFormatException e) {
                System.out.println("❗ Invalid number input. Please try again.");
            } catch (IndexOutOfBoundsException e) {
                System.out.println("❗ Invalid index selected. Please try again.");
            }
        }

        scanner.close();
    }
}
