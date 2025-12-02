#!/usr/bin/env tclsh

# Read input file
proc read_input {filename} {
    set fp [open $filename r]
    set data [read $fp]
    close $fp
    return [split [string trim $data] "\n"]
}

# Main solution
proc solve {} {
    set lines [read_input "input.txt"]
    
    # TODO: Process input
    foreach line $lines {
        puts $line
    }
    
    # TODO: Implement solution
    set part1 0
    set part2 0
    
    puts "Part 1: $part1"
    puts "Part 2: $part2"
}

# Run the solution
solve
