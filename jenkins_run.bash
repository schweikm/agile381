#!/usr/bin/env bash


###############################################################################
#
# This is the command to place as the one Jenkins build step
#
#   #!/bin/bash
#   [[ -s "/usr/local/rvm/scripts/rvm" ]] && . "/usr/local/rvm/scripts/rvm"
#   cd $WORKSPACE/trunk
#   ./jenkins_run.bash
#
###############################################################################


# set up some variables
GTEST=`ls | grep gtest`

# python prints the version to stderr
# so we have to do this stupid hack
PYVER=$(python --version 2>&1 > /dev/null)


echo
echo
echo "====================================="
echo "==== Step 1: Dependency versions ===="
echo "====================================="
echo
echo
echo "-----------------------------------------------------------------------------------------------------------------"
echo "|  Make          |  `make --version | head -1`                                                                               |"
echo "|  G++           |  `g++ --version | head -1`                                                  |"
echo "|  Perl          |  `perl --version | head -2 | tail -1`      |"
echo "|  Python        |  $PYVER                                                                                |"
echo "|  Ruby          |  `ruby --version`                                   |"
echo "|  Cucumber      |  `cucumber --version`                                                                                       |"
echo "|  Google Test   |  $GTEST                                                                                 |"
echo "|  gcovr script  |  `mediaManager/support/gcovr --version | head -1`                                                                |"
echo "|  Cppcheck      |  `cppcheck --version`                                                                               |"
echo "-----------------------------------------------------------------------------------------------------------------"


echo
echo
echo "============================="
echo "==== Step 2: Google Test ===="
echo "============================="
echo
echo

cd $GTEST
./configure
make -wB


echo
echo
echo "==============================="
echo "==== Step 3: Media Manager ===="
echo "==============================="
echo
echo

cd ../mediaManager
export DEBUG=on
export RELEASE=off
export COVERAGE=on
export PROFILE=off
make -wB


echo
echo
echo "============================"
echo "==== Step 4: Unit Tests ===="
echo "============================"
echo
echo

cd support
./run_all_unit_tests.pl


echo
echo
echo "==============================="
echo "==== Step 5: Code Coverage ===="
echo "==============================="
echo
echo

cd ..
ROOT=`pwd`
support/gcovr --root=$ROOT --xml --output=test_reports/gcovr.xml


echo
echo
echo "=========================="
echo "==== Step 6: Cppcheck ===="
echo "=========================="
echo
echo

cd ..
cppcheck --enable=all --std=posix -I mediaManager/include/ mediaManager/source/ --xml >& mediaManager/test_reports/cppcheck-mediaManager.xml
