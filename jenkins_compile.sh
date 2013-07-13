#!/bin/bash
set -o nounset


echo
echo
echo "==============================="
echo "==== Step 2: Media Manager ===="
echo "==============================="
echo
echo

pushd mediaManager > /dev/null
export DEBUG=on
export RELEASE=off
export COVERAGE=on
export PROFILE=off
make -wB |& tee reports/gcc-mediaManager.log
popd > /dev/null

