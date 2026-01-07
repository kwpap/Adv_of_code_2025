#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

//define a simple linked 

int main(void) {
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    
    // Open input file
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Error opening input.txt");
        return 1;
    }
    
    // Read and process input
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;
        
        // TODO: Process each line
        printf("%s\n", line);
    }
    
    fclose(fp);
    
    // TODO: Implement solution
    printf("Part 1: %d\n", 0);
    printf("Part 2: %d\n", 0);
    
    return 0;
}
