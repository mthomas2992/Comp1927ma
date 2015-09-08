#!/bin/bash

for num2 in {0..70}
do
  for num1 in {0..70}
  do
  echo "$(./conn "$num2" "$num1")"
  echo 
done
done  
