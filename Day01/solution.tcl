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
    set num_lines [llength $lines]
    set part1 0
    set clock 50
    set part2 0

    foreach line $lines {
        # puts $line
        # find the first letter and convert the rest to a number
        set direction [string index $line 0]
        set rest [string range $line 1 end]
        if { $direction == "R"} {
            if { [expr $rest + $clock >= 100]} {
                # puts "Adding to part2, where going R clock=$clock and rest=$rest the value [expr ($rest + $clock)/100], and ending clock will be [expr {($rest + $clock) % 100}]"
                set part2 [expr $part2 + (($rest + $clock))/100 ]
                if {$clock == 0} {
                    # puts "Special case where clock is 0, removing the extra 1"
                    set part2 [expr $part2 - 1]
                }
            }
            set clock [expr {($rest + $clock) % 100}]
        } elseif { $direction == "L"} {

            if { [expr (100 - $clock) + $rest >= 100]} {
                # puts "Adding to part2, where going L clock=$clock and rest=$rest the value [expr (100 + $rest - $clock)/100], and ending clock will be [expr {($clock - $rest) % 100}]"
                set part2 [expr $part2 + ((100 + $rest - $clock))/100]
                if {$clock == 0} {
                    # puts "Special case where clock is 0, removing the extra 1"
                    set part2 [expr $part2 - 1]
                }
            }
            set clock [expr {($clock - $rest) % 100}]
        }
        if { $clock == 0 } {
            set part1 [expr {$part1 + 1}]

            
        }
    }
    
    
    
    puts "Part 1: $part1"
    puts "Part 2: $part2"
}

# Run the solution
solve
