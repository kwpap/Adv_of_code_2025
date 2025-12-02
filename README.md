# Advent of Code 2025

My solutions for [Advent of Code 2025](https://adventofcode.com/2025) implemented in **C** and **TCL**.

## Project Structure

```
.
├── Day01/
│   ├── solution.c      # C solution
│   ├── solution.tcl    # TCL solution
│   └── input.txt       # Puzzle input
├── Day02/
│   └── ...
├── ...
├── Day25/
│   └── ...
├── Makefile
└── README.md
```

## Prerequisites

- **C Compiler**: GCC or any C99 compatible compiler
- **TCL**: tclsh (for running TCL solutions)

## Usage

### Building C Solutions

```bash
# Build all days
make all

# Build a specific day
make Day01

# Clean all compiled binaries
make clean
```

### Running Solutions

```bash
# Run C solution for a specific day
make run DAY=Day01

# Or run directly
cd Day01 && ./solution

# Run TCL solution for a specific day
make run-tcl DAY=Day01

# Or run directly
cd Day01 && tclsh solution.tcl
```

### Adding Your Puzzle Input

1. Navigate to the day's folder (e.g., `Day01/`)
2. Replace the content of `input.txt` with your puzzle input from the Advent of Code website

## Days Completed

- [ ] Day 01
- [ ] Day 02
- [ ] Day 03
- [ ] Day 04
- [ ] Day 05
- [ ] Day 06
- [ ] Day 07
- [ ] Day 08
- [ ] Day 09
- [ ] Day 10
- [ ] Day 11
- [ ] Day 12
- [ ] Day 13
- [ ] Day 14
- [ ] Day 15
- [ ] Day 16
- [ ] Day 17
- [ ] Day 18
- [ ] Day 19
- [ ] Day 20
- [ ] Day 21
- [ ] Day 22
- [ ] Day 23
- [ ] Day 24
- [ ] Day 25

## License

This project is for personal learning and practice.
