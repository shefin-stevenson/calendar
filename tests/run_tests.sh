#!/bin/bash

gcc proj.c

for i in "1" 
do
    ./a.out mycal$i.cal < test$i.in > my$i.out
    echo test$i console output diff=============================
    diff my$i.out test$i.out
    echo test$i output calander diff============================
    diff mycal$i.cal output$i.cal
    
done

#echo
#echo
#echo let\'s put in some weird arguments=====================
#./a.out > my9.out
#echo no argument test ======================================
#diff my9.out test9.out
#./a.out mycal1.cal mycal1.cal mycal1.cal > my10.out
#echo wrong argument test ===================================
#diff my10.out test10.out
#echo
#echo
