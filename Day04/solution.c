#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_ROWS 1024

int main(void) {
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    char map[MAX_ROWS][MAX_LINE_LENGTH];
    char next_map[MAX_ROWS][MAX_LINE_LENGTH];
    int rows = 0;
    int cols = 0;
    
    long long part1_removed = 0;
    long long total_removed = 0;
    int iteration_count = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Error opening input.txt");
        return 1;
    }

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        line[strcspn(line, "\n")] = 0;
        
        if (cols == 0) {
            int count = 0;
            while (line[count] != '\n' && line[count] != '\0') {
                count++;
            }
            cols = count;
        }

        strcpy(map[rows], line);
        rows++;
    }
    
    fclose(fp);

    int change_happened = 1;

    // Loop until no more rolls can be removed
    while (change_happened) {
        change_happened = 0;
        long long current_pass_removed = 0;
        
        // Initialize next_map with current state
        for (int i = 0; i < rows; i++) {
            strcpy(next_map[i], map[i]);
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (map[i][j] == '@') {
                    int neighbors = 0;
                    
                    // Check neighbors in the current map
                    for (int y = -1; y <= 1; y++) {
                        for (int x = -1; x <= 1; x++) {
                            if (y == 0 && x == 0) {
                                continue;
                            }

                            int check_r = i + y;
                            int check_c = j + x;

                            if (check_r < 0 || check_r >= rows) {
                                continue;
                            }
                            if (check_c < 0 || check_c >= cols) {
                                continue;
                            }

                            if (map[check_r][check_c] == '@') {
                                neighbors++;
                            }
                        }
                    }

                    if (neighbors < 4) {
                        next_map[i][j] = '.'; // Remove in next state
                        current_pass_removed++;
                        change_happened = 1;
                    }
                }
            }
        }

        // If this is the very first pass, that is the answer to Part 1
        if (iteration_count == 0) {
            part1_removed = current_pass_removed;
        }

        total_removed += current_pass_removed;
        iteration_count++;

        // Apply changes to the real map for the next iteration
        for (int i = 0; i < rows; i++) {
            strcpy(map[i], next_map[i]);
        }
    }

    printf("Part 1: %lld\n", part1_removed);
    printf("Part 2: %lld\n", total_removed);

    return 0;
}
