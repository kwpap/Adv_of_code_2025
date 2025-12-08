# Advent of Code 2025 - Makefile
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Source discovery
SOURCES_C := $(wildcard Day*/solution.c)
SOURCES_TCL := $(wildcard Day*/solution.tcl)
SOURCES := $(SOURCES_C) $(SOURCES_TCL)

# Most recently modified source (C or TCL)
LATEST_SRC := $(shell ls -t $(SOURCES) 2>/dev/null | head -n1)

.DEFAULT_GOAL := auto

# All days
DAYS = Day01 Day02 Day03 Day04 Day05 Day06 Day07 Day08 Day09 Day10 \
       Day11 Day12 Day13 Day14 Day15 Day16 Day17 Day18 Day19 Day20 \
       Day21 Day22 Day23 Day24 Day25

.PHONY: all clean $(DAYS) auto build-updated run-latest

# Build all days
all: $(DAYS)

# Build a specific day
$(DAYS):
	@if [ -f $@/solution.c ]; then \
		echo "Building $@..."; \
		$(CC) $(CFLAGS) -o $@/solution $@/solution.c; \
	fi

# Build any C solutions that are newer than their binaries (or missing binaries)
build-updated:
	@if [ -z "$(SOURCES_C)" ]; then \
		echo "No C sources found"; \
	else \
		for src in $(SOURCES_C); do \
			day=$$(basename $$(dirname "$$src")); \
			bin="$$day/solution"; \
			if [ ! -f "$$bin" ] || [ "$$src" -nt "$$bin" ]; then \
				echo "Building $$bin (updated from $$src)..."; \
				$(CC) $(CFLAGS) -o "$$bin" "$$src"; \
			fi; \
		done; \
	fi

# Run the most recently modified source (C binary or TCL script)
run-latest:
	@if [ -z "$(LATEST_SRC)" ]; then \
		echo "No source files found"; \
		exit 1; \
	fi; \
	day=$$(basename $$(dirname "$(LATEST_SRC)")); \
	case "$(LATEST_SRC)" in \
		*.c) \
			echo "Running $$day/solution (from $(LATEST_SRC))"; \
			cd "$$day" && ./solution; \
			;; \
		*.tcl) \
			echo "Running $(LATEST_SRC)"; \
			cd "$$day" && tclsh solution.tcl; \
			;; \
		*) \
			echo "Unknown latest source: $(LATEST_SRC)"; \
			exit 1; \
			;; \
	esac

# Default target: build any updated C sources, then run the latest changed source
auto: build-updated run-latest

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
