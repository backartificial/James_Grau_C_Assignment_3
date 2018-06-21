/* 
 * 
 * File:   main.c/main.txt
 * Author: James Grau
 *
 * Created on June 21, 2018
 * 
 */

// Include needed headers
#include <stdio.h>
#include <stdlib.h>

// Define program constants
#define FLUSH stdin = freopen(NULL, "r", stdin)

// Define student structure
typedef struct node {
    char name[30];
    float gpa;
    struct node *next;
} student_t;

// Define method
student_t *createList();
student_t *createNode();
void displayList(student_t*);
void insertNode(student_t**, student_t*);


/*
 * 
 * This method is used to run the main application
 * 
 */
int main() {
    // Print first 
    printf("Creating List of students:\n\n");

    // Call create a head pointer that is set the the returning value of createList()
    student_t *head = createList();
    
    // Display the list of students
    displayList(head);
    
    // Return 0 on run success
    return 0;
}

/**
 * 
 * This method is used to create a list of structures of students
 * 
 * @return a pointer to the header of the students list
 */
student_t* createList(){
    // Create the needed method variables
    student_t *new_node = NULL, *current = NULL, *head = NULL;

    // Loop through and initialize the list of student_t nodes
    while ((new_node = createNode()) != NULL) {
        // Check to see if the current student pointer is NULL
        if(current == NULL) {
            // Set the head to the created new node
            head = new_node;
            
            // Set the current to new node
            current = new_node;
        }else{
            // Set the current student pointers next pointer to the new_node address
            current->next = new_node;
            
            // Set the current student pointer to the new_node
            current = new_node;
        }
    };
    
    // Return the pointer to the head of the students link list
    return head;
}

/**
 * 
 * This method is used to create a new student node
 * 
 * @return the pointer the the created node
 * 
 */
student_t* createNode(){
    // Create the needed method variables
    student_t* new_node = (student_t*)malloc(1 * sizeof(student_t));
 
    // Check to see if the new_node could be initialized on the heap
    if (new_node == NULL) {
        // Display error message
        printf("Memory cannot be allocated.\n");
        
        // Exit the application on error
        exit(-1);
    } 

    // Prompt user to enter students name
    printf("Please Enter Students Name: ");
    
    // Get the input from stdin and store it into the new_node name
    fgets(new_node->name, sizeof(new_node->name), stdin);
    
    // Remove '\n' from the input and set it to a NULL terminating character
    new_node->name[strcspn(new_node->name, "\n")] = '\0';
    
    // Check to see if the string length of the students name is less then 1
    if (strlen(new_node->name) < 1) {
        // Free the new_node from the stack
        free(new_node);
        
        // Set the new_node to NULL
        new_node = NULL;
    }else{        
        // Perform a loop to get the students GPA
        do {
            // Prompt the user to enter the GPA
            printf("Please Enter Students GPA: ");
            
            // Get the GPA input and store it to the new_node
            scanf("%f", &new_node->gpa);
            
            // Flush Input buffer
            FLUSH;
            
            // Check to make sure that the GPA is between 0 & 100
            if (new_node->gpa < 0 || new_node->gpa > 100) {
                // Print an error for incorrect input
                printf("\nOops... That is an invalid GPA value.  PLease enter a number between 0 & 100.\n");
                
                // Set the GPA to 0 to allow loop to loop again and ask for correct input
                new_node->gpa = 0;
            }
        } while (new_node->gpa == 0); // Loop while the GPA is 0

        // Set the new_node next structure to NULL
        new_node->next = NULL;
    }

    // Print a blank new line
    printf("\n");

    // Return the pointer to the new node
    return new_node;
}

/**
 * 
 * This method is used to take the pointer to head and then display the list of student information
 * 
 * @param head: is the starting pointing to the start of the link list of students
 * 
 */
void displayList(student_t* head) {
    // Create and assign needed method variables
    student_t *current = head; // Store the passed in pointer to a structure and store it into a local variable
    register int i = 1; // Store the iteration counter into the register
    
    // Display table header
    printf("-------------------------------------------");
    printf("%3s. %9s %s\n", "No.", "GPA", "Student Name");
    printf("-------------------------------------------");
    
    // Loop while the current student pointer is not NULL
    while(current != NULL) {
        // Print out the list with the student information
        printf("%3d. %6.2f %s\n", i++, current->gpa, current->name);
        
        // Move the current pointer to the next student
        current = current->next;
    }
}

