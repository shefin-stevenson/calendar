to test yor files first cp the entire contents of this directroy to somewhere in your personal directory. eg:

cp * ~/project3/tests/

the first arguments "*" means "everything in this directory,the second arguments should be wherever you put your proj.c file.
After that simply call ./run_tests.sh and you should see all the diffs your program makes with the tests. Feel free to modify 
the script to only go through certain tests, if your program is not complete yet. You can also run the tests manually.  
