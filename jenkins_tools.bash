#!/usr/bin/env bash


echo
echo
echo "==============================="
echo "==== Step 5: Code Coverage ===="
echo "==============================="
echo
echo

cd mediaManager
ROOT=`pwd`
support/gcovr.py --root=$ROOT --xml --output=test_reports/gcovr.xml
echo Done!


echo
echo
echo "=========================="
echo "==== Step 6: Cppcheck ===="
echo "=========================="
echo
echo

cd ..
cppcheck --enable=all --std=posix -I mediaManager/include/ mediaManager/source/ --xml >& mediaManager/test_reports/cppcheck-mediaManager.xml
echo Done!


echo
echo
echo "========================="
echo "==== Step 7: Cpplint ===="
echo "========================="
echo
echo

cd ..
trunk/mediaManager/support/run_cpplint.pl
echo Done!
