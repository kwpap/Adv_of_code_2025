#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("Error");
        return 1;
    }

    // Current position of the dial (0-99)
    int current_pos = 50;
    
    // Answers for the two parts
    int part1_count = 0;
    long long part2_count = 0; // Use long long just in case numbers are huge

    char direction;
    int amount;

    // Read the file line by line: e.g., "R45" or "L10"
    // The space before %c skips any leftover newlines
    while (fscanf(fp, " %c%d", &direction, &amount) == 2) {
        
        // 1. Handle the "Full Circles" immediately
        // Every 100 steps, we are guaranteed to touch 0 exactly once.
        part2_count += amount / 100;

        // 2. Handle the "Remainder" by stepping one by one
        // We only need to simulate the leftover steps (0 to 99 steps max)
        int remainder = amount % 100;

        for (int i = 0; i < remainder; i++) {
            if (direction == 'R') {
                current_pos++;
                if (current_pos > 99) {
                    current_pos = 0;
                }
            } else { // Direction is 'L'
                current_pos--;
                if (current_pos < 0) {
                    current_pos = 99;
                }
            }

            // If we touch 0 during the remainder simulation, count it
            if (current_pos == 0) {
                part2_count++;
            }
        }

        // 3. Check for Part 1
        // Part 1 only cares if we land on 0 at the very end of the line
        if (current_pos == 0) {
            part1_count++;
        }
    }

    fclose(fp);

    printf("Part 1 Password: %d\n", part1_count);
    printf("Part 2 Password: %lld\n", part2_count);

    return 0;
}
