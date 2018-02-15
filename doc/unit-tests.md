Compiling/running unit tests
------------------------------------

<<<<<<< HEAD
Unit tests will be automatically compiled if dependencies were met in `./configure`
and tests weren't explicitly disabled.

After configuring, they can be run with `make check`.

To run the gelcoind tests manually, launch `src/test/test_gelcoin`.

To add more gelcoind tests, add `BOOST_AUTO_TEST_CASE` functions to the existing
.cpp files in the `test/` directory or add new .cpp files that
implement new BOOST_AUTO_TEST_SUITE sections.

To run the gelcoin-qt tests manually, launch `src/qt/test/test_gelcoin-qt`

To add more gelcoin-qt tests, add them to the `src/qt/test/` directory and
=======
Unit tests will be automatically compiled if dependencies were met in configure
and tests weren't explicitly disabled.

After configuring, they can be run with 'make check'.

To run the luxd tests manually, launch src/test/test_lux .

To add more luxd tests, add `BOOST_AUTO_TEST_CASE` functions to the existing
.cpp files in the test/ directory or add new .cpp files that
implement new BOOST_AUTO_TEST_SUITE sections.

To run the lux-qt tests manually, launch src/qt/test/lux-qt_test

To add more lux-qt tests, add them to the `src/qt/test/` directory and
>>>>>>> 3131a6d88548d8b42d26bcadc35b0cb4ab1441a3
the `src/qt/test/test_main.cpp` file.
