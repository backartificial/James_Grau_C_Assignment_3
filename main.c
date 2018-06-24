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
#include <string.h>

// Define program constants
#define FLUSH stdin = freopen(NULL, "r", stdin)

// Define student structure
typedef struct node {
    char name[30];
    float gpa;
    struct node *next;
} student_t;

// Initialize function Prototypes
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
 * 
 */
student_t* createList(){
    // Create the needed method variables
    student_t *new_node = NULL, *current = NULL, *head = NULL;

    // Loop through and initialize the list of student_t nodes
    while((new_node = createNode()) != NULL) {
        // Check to see if the current student pointer is NULL
        if(current == NULL) {
            // Set the head to the created new node
            head = new_node;
            
            // Set the current to new node
            current = new_node;
        }else{
            // Set the current student pointer the the head pointer
            current = head;
            
            // Check if the new_node GPA is greater then the 
            if(new_node->gpa > current->gpa) {                
                // Set the new_node next pointer to point to the head
                new_node->next = head;
                
                // Set the head to the new_node
                head = new_node;
            }else{
                // Loop through the linked list and check where the new_node GPA is less than the current GPA
                while((new_node->gpa < current->gpa) && current->next != NULL) {
                    // Point to the next item in the linked list
                    current = current->next;
                }

                // Check if the current next pointer is not NULL
                if(current->next != NULL) {
                    // Set the new_node next pointer to point to the current next pointer
                    new_node->next = current->next;
                    
                    // Set the current next pointer to the new_node
                    current->next = new_node;
                }else{
                    // Set the current student pointers next pointer to the new_node address
                    current->next = new_node;
                }                
            }
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
    printf("Please Enter Student's Name: ");
    
    // Get the input from stdin and store it into the new_node name
    fgets(new_node->name, sizeof(new_node->name), stdin);
    
    // Flush the input buffer
    FLUSH;
    
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
            printf("Please Enter Student's GPA (0-100): ");
            
            // Get the GPA input and store it to the new_node
            scanf("%f", &new_node->gpa);
            
            // Flush Input buffer
            FLUSH;
            
            // Check to make sure that the GPA is between 0 & 100
            if (new_node->gpa < 0 || new_node->gpa > 100) {
                // Print an error for incorrect input
                printf("\nOops... Thats is an invalid GPA number.  Please enter a number between 0 & 100.\n");
                
                // Set the GPA to -1 to allow loop to loop again and ask for correct input
                new_node->gpa = -1;
            }
        } while (new_node->gpa == -1); // Loop while the GPA is 0

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
    printf("================= List of Students: =================\n");
    printf("-------------------------------------------\n");
    printf("%3s. %-6s %s\n", "No", "GPA", "Student Name");
    printf("-------------------------------------------\n");
    
    // Check if the head pointer is NULL
    if(head == NULL) {
        // Print a message display that the list of students is empty
        printf("List of students is empty.\n");
    }else{
        // Loop while the current student pointer is not NULL
        while(current != NULL) {
            // Print out the list with the student information
            printf("%3d. %6.2f %s\n", i++, current->gpa, current->name);

            // Move the current pointer to the next student
            current = current->next;
        }
    }
}