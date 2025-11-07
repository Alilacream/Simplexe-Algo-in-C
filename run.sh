#!/bin/bash
# select the file you want
# -e: enables readline (so you get tab completion!)
# -p: shows a prompt (optional but user-friendly)
read -e -p "Enter the C file you wanna execute: " filename

#checks if the file exists or not
# -f is probably for type file
if [[ ! -f "$filename" ]]; then
  echo "File does not exist."
  exit 1
fi

#checking the type file of filename.
if [[ "$filename" == *.c ]]; then
  echo "the given file is a C file."
else
  echo "the given file IS NOT of type C."
  exit 1
fi

#runs the programe
while (true); do
  gcc "$filename" -o main && echo "Ran the programe, Succesfully." || echo "sadly, the programe failed."
  sleep 2 # wait 2 seconds to complete the execution
  ./main
  break
done
