#!/usr/bin/env bash
set -o errexit


echo
echo
echo "==============================="
echo "==== Step 5: Code Coverage ===="
echo "==============================="
echo
echo

# set the root for code coverage
cd mediaManager/manager
readonly ROOT=`pwd`

# then run the tool
cd ../..
mediaManager/support/gcovr.py --root=$ROOT --xml --output=mediaManager/reports/gcovr.xml

# manually change the paths - needs update
sed --in-place "s/obj_lin64\///g;s/manager\///g" mediaManager/reports/gcovr.xml

echo Done!


echo
echo
echo "=========================="
echo "==== Step 6: Cppcheck ===="
echo "=========================="
echo
echo

cppcheck --enable=all --std=posix -I mediaManager/manager/ -I mediaManager/ mediaManager/manager/*.cpp --xml >& mediaManager/reports/cppcheck-mediaManager.xml
echo Done!


echo
echo
echo "========================="
echo "==== Step 7: Cpplint ===="
echo "========================="
echo
echo

mediaManager/support/run_cpplint.pl
echo Done!
