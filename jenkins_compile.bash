#!/usr/bin/env bash
set -o errexit


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
make -wB manager |& tee reports/gcc-mediaManager.log
make -wB test
cd ..
