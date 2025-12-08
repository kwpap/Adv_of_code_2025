#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 4096

// 1. The Node (The individual link)
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 2. The List Manager (Keeps track of start and end)
typedef struct LinkedList {
    Node* head;
    Node* tail;
} LinkedList;

// --- Helper Functions ---

// Initialize a clean, empty list
// Returns a pointer to the manager struct
LinkedList* create_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Add to the back (The specific feature you asked for)
void append(LinkedList* list, int value) {
    // Create the new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    // Case 1: The list is empty
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode; // Head and Tail are the same
    } 
    // Case 2: The list has items
    else {
        list->tail->next = newNode; // Link old tail to new node
        list->tail = newNode;       // Update tail pointer to the new end
    }
}

// Print the list (just to verify)
void print_list(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}



// // Create the manager
//     LinkedList* myList = create_list();

//     // Add items (Fast insertion at back)
//     append(myList, 10);
//     append(myList, 20);
//     append(myList, 30);

//     // Accessing them
//     printf("First element: %d\n", myList->head->data);
//     printf("Last element:  %d\n", myList->tail->data); // Instant access!
    
//     print_list(myList);

int find_digits(long long number) {
    int digits = 0;
    while (number != 0) {
        number /= 10;
        digits++;
    }
    return digits;
}

int main(void) {
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    
    // Open input file
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Error opening input.txt");
        return 1;
    }
    long long ranges[100][2];
    ranges[0][0] = 0;
    long long max = 0;
    
char c;
int index = 0;

    // Loop through every single character in the file
    while ((c = fgetc(fp)) != EOF) {

        
        // If it is a number, print it (or store it in a buffer)
        if (isdigit(c)) {
            ranges[index / 2][index % 2] = ranges[index / 2][index % 2] * 10 + (c - '0');
            
        } 
        // If it is a separator, print a newline to show we finished that number
        else if (c == ',' || c == '-' || c == '\n') {
            if (index % 2 == 1) {
                max = (ranges[index / 2][1] > max) ? ranges[index / 2][1] : max;
            }
            index++;
            ranges[index / 2][index % 2] = 0;
        }
    }
    for (int i = 0; i < index / 2; i++) {
        printf("Range %d: %lld - %lld\n", i + 1, ranges[i][0], ranges[i][1]);
    }
    printf("Max value found: %lld\n", max);

    // Let's generate the invalid ids.

    LinkedList* invalid_ids = create_list();
    // find the number of digits of max
    int digits = find_digits(max);
    long long max_number_to_check = digits % 2 == 0 ? max / 10^digits : max / 10^(digits + 1);
    long long temp = 0;
    for (int i = 0 ; i <= max_number_to_check; i++) {
        
    }
    
    
    
    fclose(fp);
    printf("Part 1: %d\n", 0);
    
    return 0;
}



