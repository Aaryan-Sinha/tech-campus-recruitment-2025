1)Functionality:
The program reads a large log file line by line.
It checks whether a line starts with the specified date (using line.rfind(date, 0) == 0 for efficiency).
If the condition is met, the line is written to an output file in the output directory.
2)Efficiency:
The file is processed line by line to minimize memory usage.
No unnecessary data structures are used, keeping the memory footprint low.
The program leverages standard library functions for file handling and string operations, ensuring portability and reliability.
3)Error Handling:
Checks are added for file opening and directory creation.
Informative error messages guide the user in case of issues.

This is the brute-force approach which looks line by line into the logs and if the date matches it returns the result. In this code no use of data-structures keeps the use of memory low and
I have use C++ for faster execution which saves time .Error handling is also kept for a smoother User experience.

Another line of thought which I was thinking was about using Binary search for the dates which would take down the current complexity from O(n) to O(logn)
But given the time constraint i was able to come up with this solution.
