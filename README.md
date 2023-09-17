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
Generating runner for test_a.c...
Compiling test_a_runner.c...
Compiling test_a.c...
Compiling unity.c...
Compiling a.c...
Compiling cmock.c...
Linking test_a.out...
Running test_a.out...


Test 'test_fpga_copy.c'
-----------------------
Generating runner for test_fpga_copy.c...
Compiling test_fpga_copy_runner.c...
Compiling test_fpga_copy.c...
test/test_fpga_copy.c: In function ‘test_vaccel_arraycopy_valid’:
test/test_fpga_copy.c:57:18: warning: format ‘%f’ expects argument of type ‘double’, but argument 2 has type ‘int’ [-Wformat=]
   57 |         printf("%f", output_array[i]);
      |                 ~^   ~~~~~~~~~~~~~~~
      |                  |               |
      |                  double          int
      |                 %d
Compiling fpga.c...
Compiling noop.c...
Compiling session.c...
Linking test_fpga_copy.out...
Running test_fpga_copy.out...


Test 'test_fpga_vadd.c'
-----------------------
Generating runner for test_fpga_vadd.c...
Compiling test_fpga_vadd_runner.c...
Compiling test_fpga_vadd.c...
Linking test_fpga_vadd.out...
Running test_fpga_vadd.out...


Test 'test_noop.c'
------------------
Generating runner for test_noop.c...
Compiling test_noop_runner.c...
Compiling test_noop.c...
Linking test_noop.out...
Running test_noop.out...


Test 'test_plugin.c'
--------------------
Generating runner for test_plugin.c...
Compiling test_plugin_runner.c...
Compiling test_plugin.c...
Compiling plugin.c...
Linking test_plugin.out...
Running test_plugin.out...


Test 'test_session.c'
---------------------
Generating runner for test_session.c...
Compiling test_session_runner.c...
Compiling test_session.c...
Linking test_session.out...
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
  - "The value of the integer is: 0"
  - "{0.000000.0.000000.0.000000.0.000000.0.000000}"

[test_fpga_vadd.c]
  - "[noop] Calling v_vectoradd for session 1"
  - "[noop] Dumping arguments for v_vectoradd:"
  - "[noop] len_a: 5 len_b: 5 "
  - "The value of the integer is: 0"
  - "{9.100000.9.100000.9.100000.9.100000.9.100000}"

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

