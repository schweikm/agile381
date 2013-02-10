#!/bin/bash


echo
echo
echo "==============================="
echo "==== Step 4: Code Coverage ===="
echo "==============================="
echo
echo

# set the root for code coverage
pushd mediaManager > /dev/null
readonly ROOT=`pwd`
popd > /dev/null

# then run the tool
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


echo
echo
echo "========================="
echo "==== Step 6: Doxygen ===="
echo "========================="
echo
echo

pushd mediaManager > /dev/null
doxygen support/Doxyfile
popd > /dev/null
echo Done!
