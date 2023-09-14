#!/bin/bash

# # Generate the test runner using Ruby script
# ruby auto/generate_test_runner.rb test_plugins.c
# # Compile the test code and Unity source files
# gcc test_plugins_Runner.c test_plugins.c unity.c ../src/plugin.c slog.c -I ../src/ -I ../src/include/ -o RUN_TEST_PLUGINS
# ./RUN_TEST_PLUGINS
# if [ $? -eq 0 ]; then
#   rm RUN_TEST_PLUGINS test_plugins_Runner.c
# else
#   echo "Tests failed. Files will not be deleted."
# fi



ruby auto/generate_test_runner.rb test_session.c
gcc test_session_Runner.c test_session.c unity.c -I ../src/include/ -I ../third-party/slog/src -I ../src/ -o RUN_TEST_SESSION -lvaccel
./RUN_TEST_SESSION
if [ $? -eq 0 ]; then
  rm RUN_TEST_SESSION test_session_Runner.c
else
  echo "Tests failed. Files will not be deleted."
fi


ruby auto/generate_test_runner.rb test_noop.c
gcc test_noop_Runner.c test_noop.c unity.c -I ../src/include/ -I ../third-party/slog/src -I ../src/include/ops -o RUN_TEST_NOOP -lvaccel
./RUN_TEST_NOOP
if [ $? -eq 0 ]; then
  rm RUN_TEST_NOOP test_noop_Runner.c
else
  echo "Tests failed. Files will not be deleted."
fi
