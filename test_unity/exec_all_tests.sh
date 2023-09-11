#!/bin/bash

# Generate the test runner using Ruby script
ruby auto/generate_test_runner.rb test_plugins.c

# Compile the test code and Unity source files
gcc test_plugins_Runner.c test_plugins.c unity.c ../src/plugin.c slog.c -I ../src/ -I ../src/include/ -o RUN_TESTS

./RUN_TESTS


if [ $? -eq 0 ]; then
  rm RUN_TESTS test_plugins_Runner.c
else
  echo "Tests failed. Files will not be deleted."
fi
