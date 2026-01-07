#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

int find_number_of_line_digits(char * a) {
    int count = 0;
    // Safety fix: Stop at newline OR null terminator
    while (a[count] != '\n' && a[count] != '\0') {
        if (isdigit(a[count])) count++; // Only count actual digits
        else break; // Stop counting if we hit whitespace/garbage
    }
    return count;
}

long long power(long long base, int exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

typedef struct Node {
    char data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
    int size; 
} LinkedList;

LinkedList* create_list() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void free_list(LinkedList* list) {
    Node* current = list->head;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(list);
}

void prepend(LinkedList* list, char value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;
    if (list->tail == NULL) {
        list->tail = newNode;
    }
    list->size++;
}

void remove_head(LinkedList* list) {
    if (list->head == NULL) return;
    Node* temp = list->head;
    list->head = list->head->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }
    free(temp);
    list->size--;
}

int main(void) {
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Error opening input.txt");
        return 1;
    }
    
    int line_digits = 0;
    int digits_in_question = 12; 
    long long sum = 0;
    LinkedList* best_number = create_list();
    long long final_number = 0;

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        // Calculate total digits available in this line
        line_digits = 0;
        for(int k=0; line[k] != '\0'; k++) {
            if(isdigit(line[k])) line_digits++;
        }

        // Clean newline
        line[strcspn(line, "\n")] = 0;
        
        // Track how many digits we have processed to calculate 'remaining' correctly
        int digits_processed = 0;

        for (int i=0; line[i] != '\0'; i++) {
            if (!isdigit(line[i])) continue; // Skip garbage

            int digit = line[i] - '0';
            int remaining_digits = line_digits - 1 - digits_processed;

            // FIX: Changed '>' to '>='
            while (best_number->head != NULL && 
                   best_number->head->data < digit && 
                   (best_number->size + remaining_digits >= digits_in_question)) {
                remove_head(best_number);
            }

            if (best_number->size < digits_in_question) {
                prepend(best_number, digit);
            }
            digits_processed++;
        }
        
        Node* current = best_number->head;
        for (int i = 0; i < digits_in_question; i++) {
            if (current != NULL) {
                final_number += (current->data) * power(10, i);
                current = current->next;
            }
        }
        
        printf("%s has %d digits best number :%lld \n", line, line_digits, final_number);
        
        free_list(best_number);
        best_number = create_list();
        sum += final_number;
        final_number = 0;
    }
    
    fclose(fp);
    
    printf("Part 1: %lld\n", sum);

    return 0;
}