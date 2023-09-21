Testing build:

Uses ceedling for framework + Ruby 3.0.5
NOTE: (sometimes it caches your previous files and doesn't show changes as easily for some reason...not a problem if its just you executing your tests I guess.)
```
ceedling clean
ceedling cobbler
```

Higher versions of ruby doesn't work with the framework at the moment.


Testing results - tests only use the shared library now. 

Next step: check if output of API calls are as expected. >> LOOKS OK

Next step: Memory -> additional tests -> fix up copy function.


Note : test_a.c is just a basic test - just to make sure the framework itself is working. -> I probably don't need this anymore.


```
ceedling test:all


Test 'test_fpga_copy.c'
-----------------------
Running test_fpga_copy.out...


Test 'test_fpga_mmult.c'
------------------------
Running test_fpga_mmult.out...


Test 'test_fpga_vadd.c'
-----------------------
Running test_fpga_vadd.out...


Test 'test_noop.c'
------------------
Running test_noop.out...


Test 'test_plugin.c'
--------------------
Running test_plugin.out...


Test 'test_session.c'
---------------------
Running test_session.out...

-----------
TEST OUTPUT
-----------
[test_noop.c]
  - "[noop] Calling no-op for session 1"

-------------------
FAILED TEST SUMMARY
-------------------
[test_fpga_mmult.c]
  Test: test_vaccel_mmult_valid
  At line (55): "Element 0 Expected 5.1 Was 9.1"

--------------------
OVERALL TEST SUMMARY
--------------------
TESTED:  20
PASSED:  19
FAILED:   1
IGNORED:  0

---------------------
BUILD FAILURE SUMMARY
---------------------
Unit test failures.
```


20/9:

Added memory test using valgrind:

```./run_scripts.sh``` in terminal -> which results in a folder in the same directory as the memory tests.

Example output:

```
==27343== Memcheck, a memory error detector
==27343== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==27343== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==27343== Command: ../build_test/test/out/test_a.out
==27343== 
Running a()
test_a.c:1:test_a:PASS

-----------------------
1 Tests 0 Failures 0 Ignored 
OK
==27343== 
==27343== HEAP SUMMARY:
==27343==     in use at exit: 0 bytes in 0 blocks
==27343==   total heap usage: 1 allocs, 1 frees, 4,096 bytes allocated
==27343== 
==27343== All heap blocks were freed -- no leaks are possible
==27343== 
==27343== For lists of detected and suppressed errors, rerun with: -s
==27343== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

For a more verbose output change:


``` 
declare -a ARGUMENTS=("valgrind --leak-check=full --track-origins=yes --verbose")
```



