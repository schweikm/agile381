#!/usr/bin/env bash


echo
echo
echo "==============================="
echo "==== Step 5: Code Coverage ===="
echo "==============================="
echo
echo

# set the root for code coverage
cd mediaManager/source
ROOT=`pwd`

# then run the tool
cd ../../..
trunk/mediaManager/support/gcovr.py --root=$ROOT --xml --output=trunk/mediaManager/test_reports/gcovr.xml

# manually change the paths - needs update
sed --in-place "s/obj_lin64/source/g;s/obj-UT_lin64/source/g" trunk/mediaManager/test_reports/gcovr.xml

echo Done!


echo
echo
echo "=========================="
echo "==== Step 6: Cppcheck ===="
echo "=========================="
echo
echo

cppcheck --enable=all --std=posix -I trunk/mediaManager/include/ trunk/mediaManager/source/ --xml >& trunk/mediaManager/test_reports/cppcheck-mediaManager.xml
echo Done!


echo
echo
echo "========================="
echo "==== Step 7: Cpplint ===="
echo "========================="
echo
echo

trunk/mediaManager/support/run_cpplint.pl
echo Done!
