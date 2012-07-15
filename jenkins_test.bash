#!/usr/bin/env bash
set -o errexit


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
