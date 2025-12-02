# Advent of Code 2025 - Makefile
CC = gcc
CFLAGS = -Wall -Wextra -O2

# All days
DAYS = Day01 Day02 Day03 Day04 Day05 Day06 Day07 Day08 Day09 Day10 \
       Day11 Day12 Day13 Day14 Day15 Day16 Day17 Day18 Day19 Day20 \
       Day21 Day22 Day23 Day24 Day25

.PHONY: all clean $(DAYS)

# Build all days
all: $(DAYS)

# Build a specific day
$(DAYS):
	@if [ -f $@/solution.c ]; then \
		echo "Building $@..."; \
		$(CC) $(CFLAGS) -o $@/solution $@/solution.c; \
	fi

# Clean all compiled binaries
clean:
	@for day in $(DAYS); do \
		rm -f $$day/solution; \
	done
	@echo "Cleaned all binaries"

# Run a specific day (usage: make run DAY=Day01)
run:
	@if [ -z "$(DAY)" ]; then \
		echo "Usage: make run DAY=Day01"; \
	elif [ -f $(DAY)/solution ]; then \
		cd $(DAY) && ./solution; \
	else \
		echo "Binary not found. Run 'make $(DAY)' first."; \
	fi

# Run TCL solution for a specific day (usage: make run-tcl DAY=Day01)
run-tcl:
	@if [ -z "$(DAY)" ]; then \
		echo "Usage: make run-tcl DAY=Day01"; \
	elif [ -f $(DAY)/solution.tcl ]; then \
		cd $(DAY) && tclsh solution.tcl; \
	else \
		echo "TCL solution not found for $(DAY)"; \
	fi
