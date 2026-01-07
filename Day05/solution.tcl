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

    set ranges {}
    set ids {}
    set parsing_ranges 1

    set lines [read_input "input.txt"]
    

# --- Step 1: Bulletproof Parsing ---
    foreach line $lines {
        set line [string trim $line]
        if {$line eq ""} continue

        # Check 1: Is it a Range? (Look for two numbers separated by junk)
        if {[regexp {^(\d+)\D+(\d+)$} $line -> start end]} {
            lappend ranges [list $start $end]

        # Check 2: Is it an ID? (Look for a pure string of digits)
        # We use regex here because 'string is integer' can fail on massive numbers.
        } elseif {[regexp {^\d+$} $line]} {
            lappend ids $line

        } else {
             puts "WARNING: Skipped line: '$line'"
        }
    }
    
    # DEBUG: Inspect the ranges to prove the big one is clean
    puts "--- DEBUG RANGES ---"
    foreach r $ranges {
        # puts "Range: Start=[lindex $r 0] End=[lindex $r 1]" 
    }
    foreach id $ids {
        # puts "ID: $id"
    }
    puts "--------------------"


    # --- Step 2: Sort Ranges ---
# We sort the list of lists by the first element (index 0) numerically (-integer)
# This transforms the messy input into a linear timeline.
set sorted_ranges [lsort -integer -index 0 $ranges]
set part2 0
# --- Step 3: Merge Overlapping Ranges ---
# This is much faster than checking every raw range later.
set merged_ranges {}
if {[llength $sorted_ranges] > 0} {
    # Initialize with the first range
    lassign [lindex $sorted_ranges 0] current_start current_end

    foreach range [lrange $sorted_ranges 1 end] {
        lassign $range next_start next_end
        
        if {$next_start <= $current_end + 1} {
            # Overlap or adjacent: Extend the current range if needed
            if {$next_end > $current_end} {
                set current_end $next_end
            }
        } else {
            # No overlap: Save current range and start a new one
            lappend merged_ranges [list $current_start $current_end]
            set part2 [expr $part2 + $current_end - $current_start + 1]
            set current_start $next_start
            set current_end $next_end
            
        }
    }
    # Don't forget the last range
    lappend merged_ranges [list $current_start $current_end]
    set part2 [expr $part2 + $current_end - $current_start + 1]
}

# --- Step 4: Count Fresh Ingredients ---
    set fresh_count 0

    foreach id $ids {
        # Validating with regex to allow big numbers
        if {![regexp {^\d+$} $id]} continue

        set is_fresh 0
        foreach range $merged_ranges {
            lassign $range start end
            
            # --- THE FIX IS HERE ---
            # We add '+ 0' to every variable. 
            # This forces Tcl to treat them as Numbers (Math), not Strings (Text).
            
            # 1. The Optimization (Safe now because we forced math)
            if {$id + 0 < $start + 0} { break }

            # 2. The Check
            if {$id + 0 >= $start + 0 && $id + 0 <= $end + 0} {
                set is_fresh 1
                break 
            }
        }
        
        if {$is_fresh} {
            incr fresh_count
        }
    }

    puts "Total fresh ingredients: $fresh_count"
    puts "Part 2 $part2"

}

# Run the solution
solve
