#!/bin/bash
# Written by LLM on Feb 23, 2024

NUM_RUNS=100
SEG_FAULT_COUNT=0

for (( i=1; i<=NUM_RUNS; i++ )); do
    output=$(./worldpath <<< "done")

    # Check if "Segmentation fault" exists in the output
    if [[ "$output" == *"Segmentation fault"* ]]; then
        SEG_FAULT_COUNT=$((SEG_FAULT_COUNT + 1))
    fi
done
echo $(pwd)
echo "Segmentation faults encountered: $SEG_FAULT_COUNT/$NUM_RUNS" 
