#!/usr/bin/env bash


echo
echo
echo "============================"
echo "==== Step 4: Unit Tests ===="
echo "============================"
echo
echo

cd mediaManager/support
./run_all_unit_tests.pl
cd ../..
