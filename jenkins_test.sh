#!/bin/bash


echo
echo
echo "============================"
echo "==== Step 3: Unit Tests ===="
echo "============================"
echo
echo

pushd mediaManager/support > /dev/null
mkdir ../reports
./run_all_unit_tests.pl
popd > /dev/null

