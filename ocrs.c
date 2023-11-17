#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Course {
    int courseId;
    char courseName[50];
    char instructor[50];
} Course;

typedef struct User {
    char username[50];
    char password[50];
    int userType;
    Course registeredCourses[100]; // List of registered courses
    int courseCount; // Number of registered courses
} User;

// Function to register a course for a student
void registerCourse(User *student, Course course) {
    student->registeredCourses[student->courseCount] = course;
    student->courseCount++;
    printf("Course registered successfully!\n");
}

// Function to display the courses registered by a student
void displayRegisteredCourses(User student) {
    int i;
    
    if (student.courseCount == 0) {
        printf("No courses registered!\n");
        return;
    }
    
    printf("Registered Courses:\n");
    for (i = 0; i < student.courseCount; i++) {
        printf("Course ID: %d\n", student.registeredCourses[i].courseId);
        printf("Course Name: %s\n", student.registeredCourses[i].courseName);
        printf("Instructor: %s\n", student.registeredCourses[i].instructor);
        printf("--------------------\n");
    }
}

void displayMenu(int userType) {
    if (userType == 1) {
        printf("Teacher Mode\n");
        printf("1. Add Course\n");
        printf("2. Display All Courses\n");
        printf("3. Exit\n");
    } else if (userType == 2) {
        printf("Student Mode\n");
        printf("1. Search Course\n");
        printf("2. Display All Courses\n");
        printf("3. Register for a Course\n"); 
        printf("4. Display Registered Courses\n"); 
        printf("5. Exit\n");
    } else {
        printf("Invalid user type!\n");
    }
}

void addCourse(Course courses[], int *count) {
    Course newCourse;
    
    printf("Enter the Course ID: ");
    scanf("%d", &newCourse.courseId);
    
    printf("Enter the Course Name: ");
    scanf(" %[^\n]s", newCourse.courseName);
    
    printf("Enter the Instructor Name: ");
    scanf(" %[^\n]s", newCourse.instructor);
    
    courses[*count] = newCourse;
    (*count)++;
    
    printf("Course added successfully!\n");
}

void searchCourse(Course courses[], int count) {
    int searchId, i;
    printf("Enter the Course ID to search: ");
    scanf("%d", &searchId);
    
    for (i = 0; i < count; i++) {
        if (courses[i].courseId == searchId) {
            printf("Course ID: %d\n", courses[i].courseId);
            printf("Course Name: %s\n", courses[i].courseName);
            printf("Instructor: %s\n", courses[i].instructor);
            return;
        }
    }
    
    printf("Course not found!\n");
}

void displayCourses(Course courses[], int count) {
    int i;
    
    if (count == 0) {
        printf("No courses found!\n");
        return;
    }
    
    printf("Course List:\n");
    for (i = 0; i < count; i++) {
        printf("Course ID: %d\n", courses[i].courseId);
        printf("Course Name: %s\n", courses[i].courseName);
        printf("Instructor: %s\n", courses[i].instructor);
        printf("--------------------\n");
    }
}

int login(User users[], int userCount, char username[], char password[]) {
    int i;
    for (i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return users[i].userType;
        }
    }
    return -1; // Invalid credentials
}

int main() {
    Course courses[100];
    User users[2]; // Assuming 2 users for demonstration purposes
    int choice, count = 0;
    int userType;
    
    // Predefined user credentials
    strcpy(users[0].username, "teacher");
    strcpy(users[0].password, "password");
    users[0].userType = 1; // Teacher
    
    strcpy(users[1].username, "student");
    strcpy(users[1].password, "password");
    users[1].userType = 2; // Student
    
    char username[50];
    char password[50];
    
    again:
    printf("Select user type:\n");
    printf("1. Teacher\n");
    printf("2. Student\n");
    printf("Enter your choice: ");
    scanf("%d", &userType);
    
    printf("Enter your username: ");
    scanf("%s", username);
    
    printf("Enter your password: ");
    scanf("%s", password);
    
    int loggedInUserType = login(users, 2, username, password);
    
    if (loggedInUserType == -1) {
        printf("Invalid username or password!\n");
        goto again;
    }
    
    do {
        displayMenu(loggedInUserType);
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (loggedInUserType) {
            case 1: // Teacher mode
                switch (choice) {
                    case 1:
                        addCourse(courses, &count);
                        break;
                    case 2:
                        displayCourses(courses, count);
                        break;
                    case 3:
                        printf("Exiting...\n");
                        goto again;
                        exit(0);
                    default:
                        printf("Invalid choice! Please try again.\n");
                }
                break;
            case 2: // Student mode
                switch (choice) {
                    case 1:
                        searchCourse(courses, count);
                        break;
                    case 2:
                        displayCourses(courses, count);
                        break;
                    case 5:
                        printf("Exiting...\n");
                        goto again;
                        exit(0);
                    case 3:
                        registerCourse(&users[i], courses[choice - 1]);
                        break;
                    case 4:
                        displayRegisteredCourses(users[i]);
                        break;
                    default:
                        printf("Invalid choice! Please try again.\n");
                }
                break;
            default:
                printf("Invalid user type!\n");
                exit(1);
        }
    } while (1);
    
    return 0;
}
