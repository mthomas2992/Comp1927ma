#!/bin/bash

for num2 in {0..70}
do
  for num1 in {0..70}
  do
  var="$(./conn2 "$num2" "$num1")"
  if [ -n "$var" ]; then
	echo "$(./conn2 "$num2" "$num1")"
  fi


done
done  
