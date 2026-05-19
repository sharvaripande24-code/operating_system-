#!/bin/bash
#Star Triangle
echo "Enter number of rows:"
read rows

for (( i=1; i<=rows; i++ ))
do
    for (( j=1; j<=i; j++ ))
    do
        echo -n "* "
    done

    echo
done


#!/bin/bash
#number triangle
echo "Enter number of rows:"
read rows

for (( i=1; i<=rows; i++ ))
do
    for (( j=1; j<=i; j++ ))
    do
        echo -n "$j "
    done

    echo
done


#!/bin/bash
#Reverse Star Pattern
echo "Enter number of rows:"
read rows

for (( i=rows; i>=1; i-- ))
do
    for (( j=1; j<=i; j++ ))
    do
        echo -n "* "
    done

    echo
done