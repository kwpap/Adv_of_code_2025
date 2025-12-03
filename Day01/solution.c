#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(void) {
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    
    // Open input file
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Error opening input.txt");
        return 1;
    }
    int count = 0;
    int count_of_second_task = 0;
    int remeinder = 50;
    int last_count = 0;
    // Read and process input
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL ) {
        last_count = count_of_second_task;
        // Remove newline character
        line[strcspn(line, "\n")] = 0;
        
        //split the first character and cast the rest to integer
        char direction = line[0];
        int value = atoi(&line[1]);
        if (direction == 'R') {
            if (remeinder + value >= 100) {
                count_of_second_task++;
            }
            remeinder = (remeinder + value) %100;

        } else {
            if (remeinder - value <= 0) {
                count_of_second_task++;
            }
            remeinder = (remeinder - value ) % 100;
        }
        if (remeinder == 0) {
            count++;
        }
        // if (last_count - count_of_second_task > 1) {

        //     printf("Direction: %c, Value: %d, Remeinder: %d, Count: %d, Count of second task: %d\n", direction, value, remeinder, count, count_of_second_task);

        // }
        //printf("Direction: %c, Value: %d, Remeinder: %d, Count: %d, Count of second task: %d\n", direction, value, remeinder, count, count_of_second_task);
    }

    fclose(fp);

    printf("Part 1: %d\n", count);
    printf("Part 2: %d\n", count_of_second_task);

    
    return 0;
}
