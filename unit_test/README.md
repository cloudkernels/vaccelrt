Using Ruby 3.0.5 for ceedling - higher version has problems:

Test results:



Test 'test_exec.c'
------------------
Running test_exec.out...


Test 'test_noop.c'
------------------
Running test_noop.out...


Test 'test_plugins.c'
---------------------
Running test_plugins.out...


Test 'test_session.c'
---------------------
Running test_session.out...

-------------------
FAILED TEST SUMMARY
-------------------
[test_noop.c]
  Test: test_vaccel_noop_valid
  At line (48): "Expected 0 Was 95"

--------------------
OVERALL TEST SUMMARY
--------------------
TESTED:  13
PASSED:  12
FAILED:   1
IGNORED:  0

---------------------
BUILD FAILURE SUMMARY
---------------------
Unit test failures.



Need to refactor how the tests are done here - using the shared object is better.