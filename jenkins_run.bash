#!/usr/bin/env bash

# set up some variables
GTEST=`ls | grep gtest`

echo
echo
echo "====================================="
echo "==== Step 1: Dependency versions ===="
echo "====================================="
echo
echo
echo "-------------------------------------------------------------------"
echo "|  `which make`     |  `make --version | head -1`                             |"
echo "|  `which g++`      |  `g++ --version | head -1`  |"
#echo "|  `which python`   |  `python --version | head -1`  |"
echo "|  `which python`   |  Python 2.7.2+                             |"
echo "|  Google Test       |  $GTEST                               |"
echo "|  gcovr             |  `mediaManager/support/gcovr --version | head -1`                      |"
echo "-------------------------------------------------------------------"


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
