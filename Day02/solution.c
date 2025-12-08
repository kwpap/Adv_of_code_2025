#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 4096

long long power(long long base, int exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

// 1. The Node (The individual link)
typedef struct Node {
    long long data;
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
void append(LinkedList* list, long long value) {
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
        printf("%lld -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
// Print the list (just to verify)
void print_list_with_limit(LinkedList* list, int limit) {
    Node* current = list->head;
    int count = 0;
    while (current != NULL && count < limit) {
        printf("%lld -> ", current->data);
        current = current->next;
        count++;
    }
    printf("NULL\n");
}

// Sort the list using Bubble Sort (inefficient but simple)
void sort_list(LinkedList* list) {
    if (list->head == NULL) return; // Empty list

    int swapped;
    do {
        swapped = 0;
        Node* current = list->head;
        while (current->next != NULL) {
            if (current->data > current->next->data) {
                // Swap data
                long long temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

void remove_doublicates_and_sort(LinkedList* list) {
    // First, sort the list
    sort_list(list);

    // Then, remove duplicates
    Node* current = list->head;
    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            // Duplicate found; remove it
            Node* temp = current->next;
            current->next = current->next->next;
            free(temp);
            if (current->next == NULL) {
                list->tail = current; // Update tail if we removed the last element
            }
        } else {
            current = current->next; // Move to next node only if no deletion
        }
    }
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

long long number_sequence_repeater(long long number, int times) {
    long long result = 0;
    int digits = find_digits(number);
    for (int i = 0; i < times; i++) {
        result = result * power(10, digits) + number;
    }
    return result;
}

int main(void) {
    FILE *fp;
    
    // Open input file
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Error opening input.txt");
        return 1;
    }

    long long max = 0;
    char c;
    int index = 0;
    LinkedList* lower_bounds = create_list();
    LinkedList* upper_bounds = create_list();
    long long current_number = 0;

    // Loop through every single character in the file
    while ((c = fgetc(fp)) != EOF) {

        
        // If it is a number, print it (or store it in a buffer)
        if (isdigit(c)) {
            current_number = current_number * 10 + (c - '0');
        } 
        // If it is a separator, print a newline to show we finished that number
        else if (c == ',' || c == '-' || c == '\n') {
            if (index % 2 == 1) {
                append(upper_bounds, current_number);
            } else {
                append(lower_bounds, current_number);
            }
            max = current_number > max ? current_number : max;
            index++;
            current_number = 0;
        }
    }
    sort_list(lower_bounds);
    sort_list(upper_bounds);
    // printf("the lower bound numbers are:\n");
    // print_list(lower_bounds);
    // printf("the upper bound numbers are:\n");
    //print_list(upper_bounds);


    // Let's generate the invalid ids.

    LinkedList* invalid_ids = create_list();
    // find the number of digits of max
    int digits = find_digits(max);
    long long  max_number_to_check =  max / power(10, digits/2);
    //printf("Max number to check: %lld\n", max_number_to_check);
    for (long long i = 1 ; i <= max_number_to_check; i++) {
        append(invalid_ids, i+ i * power(10, find_digits(i)));
    }

    long long final_solution = 0;
    int multiplier = 0;
    Node* current_invalid = invalid_ids->head;
    Node* current_lower = lower_bounds->head;
    Node* current_upper = upper_bounds->head;

    while (current_invalid != NULL) {
        //printf("Checking invalid id %lld\n", current_invalid->data);
        while (current_lower != NULL && current_invalid->data >= current_lower-> data ){
            current_lower = current_lower->next;
            multiplier++;
            //printf("Incrementing lower bound pointer to %lld, multiplier is now %d\n", current_lower != NULL ? current_lower->data : -1, multiplier);
        }
        while (current_upper != NULL && current_invalid->data > current_upper->data) {
            current_upper = current_upper->next;
            multiplier--;
            //printf("Incrementing upper bound pointer to %lld and multiplier become %d\n",  current_upper != NULL ? current_upper->data : -1, multiplier);
        }
        final_solution += multiplier*current_invalid->data;
        if (multiplier > 0) {
        //printf("Adding %lld * %d to final solution, now %lld\n", current_invalid->data, multiplier, final_solution);

        }
               current_invalid = current_invalid->next;
       }
    printf("Part 1: %lld\n", final_solution);

    //Let's expand the invalid list id to include any number occuring by concatinating a number with itself 2 or more times.
       LinkedList* expanded_invalid_ids = create_list();

    int max_digits = find_digits(max);
    for (int i = 1; i< max_number_to_check; i++) {
        //printf("Expanding invalid id %d\n", i);
        for (int repeat = 2; repeat * find_digits(i) <= max_digits; repeat++) {
            long long new_invalid = number_sequence_repeater(i, repeat);
            if (new_invalid > max) {
                break;
            }
            append(expanded_invalid_ids, new_invalid);
            //printf("Adding expanded invalid id %lld\n", new_invalid);
        }
    }
    remove_doublicates_and_sort(expanded_invalid_ids);
    //printf("The expanded invalid ids are:\n");
    //print_list_with_limit(expanded_invalid_ids, 20);
    
    long long final_solution_2 = 0;
    multiplier = 0;
    current_invalid = expanded_invalid_ids->head;
    current_lower = lower_bounds->head;
    current_upper = upper_bounds->head;

    while (current_invalid != NULL) {
        //printf("Checking invalid id %lld\n", current_invalid->data);
        while (current_lower != NULL && current_invalid->data >= current_lower-> data ){
            current_lower = current_lower->next;
            multiplier++;
            //printf("Incrementing lower bound pointer to %lld, multiplier is now %d\n", current_lower != NULL ? current_lower->data : -1, multiplier);
        }
        while (current_upper != NULL && current_invalid->data > current_upper->data) {
            current_upper = current_upper->next;
            multiplier--;
            //printf("Incrementing upper bound pointer to %lld and multiplier become %d\n",  current_upper != NULL ? current_upper->data : -1, multiplier);
        }
        final_solution_2 += multiplier*current_invalid->data;
        if (multiplier > 0) {
        printf("Adding %lld * %d to final solution, now %lld\n", current_invalid->data, multiplier, final_solution_2);

        }
               current_invalid = current_invalid->next;
       }
    printf("Part 2: %lld\n", final_solution_2);




    
    fclose(fp);
    //printf("Part 1: %d\n", 0);
    
    return 0;
}



