#!/bin/bash

cp ../files/* .
c++ *.cpp -c &>compile_error.out
c++ *.o -o p4.exe &> link_error.out

rm zimmer*.cpp*

{ ./p4.exe>run.out; } 2>> run_error.out 


diff correct_tests.out tests.out>diff_tests.out
diff correct_run.out run.out>diff_run.out

#valgrind --leak-check=yes ./p4.exe 2> mem.out
ls -l *.out




