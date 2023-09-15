#!/bin/bash

# Compile the test code and CMocka source files
gcc simple_test.c ../src/plugin.c slog.c -I../src/ -I../src/include -o RUN_TESTS -lcmocka
# Run the tests
./RUN_TESTS

# if [ $? -eq 0 ]; then
#   rm RUN_TESTS
# else
#   echo "Tests failed. Files will not be deleted."
# fi
