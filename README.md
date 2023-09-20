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
ceedling verbosity[3] test:all


Test 'test_a.c'
---------------
Running test_a.out...


Test 'test_fpga_copy.c'
-----------------------
Running test_fpga_copy.out...


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
[test_a.c]
  - "Running a()"

[test_fpga_copy.c]
  - "[noop] Calling v_arraycopy for session 1"
  - "[noop] Dumping arguments for v_arracycopy:"
  - "[noop] size: 5 "
  - "{1.2.3.4.5}"

[test_fpga_vadd.c]
  - "[noop] Calling v_vectoradd for session 1"
  - "[noop] Dumping arguments for v_vectoradd:"
  - "[noop] len_a: 5 len_b: 5 "
  - "{2.000000.4.000000.9.000000.8.000000.10.000000}"

[test_noop.c]
  - "[noop] Calling no-op for session 1"

--------------------
OVERALL TEST SUMMARY
--------------------
TESTED:  18
PASSED:  18
FAILED:   0
IGNORED:  0
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



