#!/bin/bash

# Ensure an argument was provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <path>"
    echo "       where <path> is the file or root of the tree you want to summarize."
    exit 1
fi

path="$1"

# Count directories and regular files
num_dirs=$(find "$path" -type d | wc -l)
num_regular=$(find "$path" -type f | wc -l)

printf "There were %d directories.\n" "$num_dirs"
printf "There were %d regular files.\n" "$num_regular"
