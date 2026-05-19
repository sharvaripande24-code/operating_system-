#!/bin/bash

# Prime and Non-Prime Numbers using Array

echo "Enter how many numbers you want to store:"
read n

# Array declaration
arr=()

# Taking array input
echo "Enter numbers:"

for (( i=0; i<n; i++ ))
do
    read arr[$i]
done

echo
echo "Array Elements are:"
echo "${arr[@]}"

prime_count=0

echo
echo "Result:"

# Checking numbers
for num in "${arr[@]}"
do
    flag=1

    if [ $num -le 1 ]
    then
        flag=0
    else
        for (( j=2; j<num; j++ ))
        do
            if [ $((num % j)) -eq 0 ]
            then
                flag=0
                break
            fi
        done
    fi

    # Directly printing result
    if [ $flag -eq 1 ]
    then
        echo "$num is Prime"
        prime_count=$((prime_count + 1))
    else
        echo "$num is Not Prime"
    fi

done

echo
echo "Total Prime Numbers = $prime_count"