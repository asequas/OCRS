#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for Course and Student
struct Course {
    int course_id;
    char course_name[50];
    char instructor[50];
    char schedule[20];
    int capacity;
    int student_count;
    struct Student** students; // Use a double pointer to dynamically allocate memory
};

struct Student {
    int student_id;
    char student_name[50];
    int course_count;
    struct Course** courses; // Use a double pointer to dynamically allocate memory
};

// Function to enroll a student in a course
void enroll_student(struct Course* course, struct Student* student) {
    if (course->student_count < course->capacity) {
        course->students[course->student_count] = student;
        course->student_count++;
        student->courses[student->course_count] = course;
        student->course_count++;
    } else {
        printf("Course %s is full. Cannot enroll %s.\n", course->course_name, student->student_name);
    }
}

// Function to display a student's schedule
void display_schedule(struct Student* student) {
    printf("%s's Schedule:\n", student->student_name);
    for (int i = 0; i < student->course_count; i++) {
        printf("%s with %s at %s\n", student->courses[i]->course_name, student->courses[i]->instructor, student->courses[i]->schedule);
    }
}

int main() {
    // Create courses
    struct Course course1 = {1, "Introduction to Programming", "Dr.A", "MWF 10:00 AM", 2, 0, NULL};
    struct Course course2 = {2, "Data Structures", "Prof.ABC", "TTH 2:00 PM", 2, 0, NULL};

    // Create students
    struct Student student1 = {101, "Alice", 0, NULL};
    struct Student student2 = {102, "Bob", 0, NULL};

    // Dynamically allocate memory for student arrays
    course1.students = (struct Student**)malloc(course1.capacity * sizeof(struct Student*));
    course2.students = (struct Student**)malloc(course2.capacity * sizeof(struct Student*));

    student1.courses = (struct Course**)malloc(course1.capacity * sizeof(struct Course*));
    student2.courses = (struct Course**)malloc(course2.capacity * sizeof(struct Course*));

    // Enroll students in courses
    enroll_student(&course1, &student1);
    enroll_student(&course1, &student2);
    enroll_student(&course2, &student1);

    // Display student schedules
    display_schedule(&student1);
    display_schedule(&student2);

    // Free allocated memory
    free(course1.students);
    free(course2.students);
    free(student1.courses);
    free(student2.courses);

    return 0;
}
