#!/usr/bin/env bash
set -o errexit


###############################################################################
#
# This is the command to place as the one Jenkins build step
#
#   #!/bin/bash
#   [[ -s "/usr/local/rvm/scripts/rvm" ]] && . "/usr/local/rvm/scripts/rvm"
#   cd $WORKSPACE/trunk
#   ./jenkins_run.bash
#
###############################################################################


#### Versions that cannot be found normally ####

# Google Test - this is used in subsequent scripts
readonly GTEST=`ls | grep gtest`

# Cpplint
readonly CPPLINTVER="google-styleguide - Revision 86"

# set the column widths
readonly COL1SIZE=12
readonly COL2SIZE=86

# table character
readonly TABLECHAR="-"

function printEnds {
    for((i = 0; i < $COL1SIZE + $COL2SIZE + 11; i++))
    do
        printf "%s" $TABLECHAR
    done
    printf "\n"
}

function printRemaining {
    strLen=$1
    colSize=$2
    for((i = $1; i < $colSize; i++))
    do
        printf "%s" " "
    done
}

function printVersion {
    name=$1
    nameLen=${#name}
    version=$2
    versionLen=${#version}

    printf "|  %s" "$name"
    printRemaining $nameLen $COL1SIZE
    printf "  |  %s  " "$version"
    printRemaining $versionLen $COL2SIZE
    printf "|\n"
}

echo
echo
echo "====================================="
echo "==== Step 1: Dependency versions ===="
echo "====================================="
echo
echo

# header
printEnds

# print the versions
printVersion "Cppcheck" "$(cppcheck --version)"
printVersion "Cpplint" "$CPPLINTVER"
printVersion "Cucumber" "$(cucumber --version)"
printVersion "G++" "$(g++ --version | head -1)"
printVersion "Gcov" "$(gcov --version | head -1)"
printVersion "gcovr.py" "$(mediaManager/support/gcovr.py --version | head -1)"
printVersion "Google Test" "$GTEST"
printVersion "Linux Kernel" "$(uname -r)"
printVersion "Make" "$(make --version | head -1)"
printVersion "Perl" "$(perl --version | head -2 | tail -1)"
printVersion "Python" "$(python --version 2>&1 > /dev/null)"
printVersion "Ruby" "$(ruby --version)"
printVersion "Sed" "$(sed --version | head -1)"

# footer
printEnds


# farm the work out to sub scripts
source jenkins_compile.bash
source jenkins_test.bash
source jenkins_tools.bash
echo
echo
