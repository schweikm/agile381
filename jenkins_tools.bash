#!/usr/bin/env bash
set -o errexit


echo
echo
echo "==============================="
echo "==== Step 4: Code Coverage ===="
echo "==============================="
echo
echo

# set the root for code coverage
cd mediaManager
readonly ROOT=`pwd`

# then run the tool
cd ..
mediaManager/support/gcovr.py --root=$ROOT --xml --output=mediaManager/reports/gcovr.xml
echo Done!


echo
echo
echo "========================="
echo "==== Step 5: Cpplint ===="
echo "========================="
echo
echo

mediaManager/support/run_cpplint.pl
echo Done!
