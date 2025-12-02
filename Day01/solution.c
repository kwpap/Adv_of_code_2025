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
    // Read and process input
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;
        
        //split the first character and cast the rest to integer
        char direction = line[0];
        int value = atoi(&line[1]);
        if (direction == 'R') {

            while (remeinder + value >= 100) {
                count_of_second_task++;
                value -= 100;
            }
            remeinder = (remeinder + value) % 100;

        } else {
            while (remeinder - value < 0) {
                count_of_second_task++;
                value -= 100;
            }
            remeinder = (remeinder - value + 100) % 100;
        }
        if (remeinder == 0) {
            count++;
            count_of_second_task ++;
        }
    }

    fclose(fp);

    printf("Part 1: %d\n", count);
    printf("Part 2: %d\n", count_of_second_task);

    
    return 0;
}
