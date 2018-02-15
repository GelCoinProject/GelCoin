# Notes
The sources in this directory are unit test cases.  Boost includes a
<<<<<<< HEAD
unit testing framework, and since GelCoin already uses boost, it makes
=======
unit testing framework, and since bitcoin already uses boost, it makes
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
sense to simply use this framework rather than require developers to
configure some other framework (we want as few impediments to creating
unit tests as possible).

<<<<<<< HEAD
The build system is setup to compile an executable called "test_gelcoin"
that runs all of the unit tests.  The main source file is called
test_gelcoin.cpp, which simply includes other files that contain the
=======
The build system is setup to compile an executable called "test_lux"
that runs all of the unit tests.  The main source file is called
test_lux.cpp, which simply includes other files that contain the
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
actual unit tests (outside of a couple required preprocessor
directives).  The pattern is to create one test file for each class or
source file for which you want to create unit tests.  The file naming
convention is "<source_filename>_tests.cpp" and such files should wrap
their tests in a test suite called "<source_filename>_tests".  For an
examples of this pattern, examine uint160_tests.cpp and
uint256_tests.cpp.

<<<<<<< HEAD
Add the source files to /src/Makefile.test.include to add them to the build.

For further reading, I found the following website to be helpful in
explaining how the boost unit test framework works:
[http://www.alittlemadness.com/2009/03/31/c-unit-testing-with-boosttest/](http://www.alittlemadness.com/2009/03/31/c-unit-testing-with-boosttest/).

test_gelcoin has some built-in command-line arguments; for
example, to run just the getarg_tests verbosely:

    test_gelcoin --log_level=all --run_test=getarg_tests

... or to run just the doublegelcoin test:

    test_gelcoin --run_test=getarg_tests/doublegelcoin

Run  test_gelcoin --help   for the full list.

=======
For further reading, I found the following website to be helpful in
explaining how the boost unit test framework works:
[http://www.alittlemadness.com/2009/03/31/c-unit-testing-with-boosttest/](http://www.alittlemadness.com/2009/03/31/c-unit-testing-with-boosttest/).
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
