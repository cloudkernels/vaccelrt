#!/bin/bash

TESTDIR="../build_test/test/out/"
SHARED_OBJECT="../reqs/lib/libvaccel-noop.so"
OUTPUT_DIR="./valgrind_output"

# declare -a ARGUMENTS=(
#     "valgrind --leak-check=full --track-origins=yes --verbose"
# )

declare -a ARGUMENTS=(
    "valgrind --leak-check=full"
)

total_files=$(find "$TESTDIR" -maxdepth 1 -type f -executable | wc -l)
current_file=0

mkdir -p "$OUTPUT_DIR"

for file in "$TESTDIR"*.out; do
    if [ -x "$file" ]; then

        test_name=$(basename "$file")
        
        for args in "${ARGUMENTS[@]}"; do
            current_file=$((current_file + 1))
            output_file="$OUTPUT_DIR/valgrind_output_${test_name}.txt"
            export VACCEL_BACKENDS="$SHARED_OBJECT"
            $args "$file" > "$output_file" 2>&1
            progress=$((current_file * 100 / total_files))
            printf "Progress: [%-50s] %d%%\r" $(printf "#%.0s" {1..50}) "$progress"
        done
    fi
done

echo  