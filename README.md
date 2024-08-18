# Student-Information-System
The Student Management System program is a C-based application that manages student data using a linked list.

**1. Features of the System:**
The Student Management System is a C program designed to efficiently manage student information.

Key features include:

**Add a Student:** Prompts the user for new student details and adds them to the system.

**Display All Students:** Lists all stored student records.

**Search for a Student by ID:** Allows users to search for a student using their unique ID.

**Update Student Information:** Enables the update of student details (name, age, GPA) based on ID.

**Delete a Student:** Removes a student's record using their ID.

**Calculate Average GPA:** Computes and displays the average GPA of all students.

**Find Student with Highest GPA:** Identifies and shows the student with the highest GPA.

**Exit:** Terminates the program.

The system is implemented using fundamental programming concepts, such as conditions, loops, strings, structs, and pointers, and efficiently manages data using a linked list.


**2. Corner Cases Preventions:**

To ensure the integrity of data and prevent errors, the system includes the following corner case prevention mechanisms:


**Validations for Student Name:** The system prevents entering numbers or invalid characters in the student's name.

**ID Validations:** Checks if the student ID already exists before adding a new student, preventing duplicate entries.

**Valid Age and GPA:** Ensures that the age and GPA values entered are within a valid range. The GPA must be between 0 and 3.

**Memory Allocation:** If memory allocation for a new student fails, the system provides an error message and safely exits the operation.

These features and checks help maintain data consistency and prevent common user input errors.
