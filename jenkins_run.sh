#!/bin/bash
set -o nounset


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


# get the verbose level for glog
VLVL=0

while getopts ":v:" opt; do
    case ${opt} in
    v)
        VLVL=${OPTARG}
        ;;
    \?)
        echo "Invalid option: -${OPTARG}" >&2
        exit 1
        ;;
    :)
        echo "Option -${OPTARG} requires an argument." >&2
        exit 1
        ;;
    esac
done


#### COTS Products ####
readonly COTS_BASE="/mnt/data/Development/Linux/COTS"
readonly BOOST_DIR="${COTS_BASE}/boost_1_55_0"
readonly GLOG_DIR="${COTS_BASE}/glog-0.3.3"
readonly GTEST_DIR="${COTS_BASE}/gtest-1.7.0"


#### Environment Variables ####
if [[ -z ${LD_LIBRARY_PATH:-} ]]; then
    export LD_LIBRARY_PATH=
fi

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${BOOST_DIR}/lib
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${GLOG_DIR}/lib

export GLOG_log_dir=$(pwd)/mediaManager/log
export GLOG_v=${VLVL}


#### These product versions are special ####

## Google Test ##
GTESTVER=`head -1 ${GTEST_DIR}/CHANGES | cut -d ' ' -f 3`
GTESTVER=${GTESTVER%?}  # remove last character

## Cpplint ##
readonly CPPLINTVER="google-styleguide - Revision 99"


# set the column widths
readonly COL1SIZE=12
readonly COL2SIZE=86

# table character
readonly TABLECHAR="-"

printEnds() {
    for((i = 0; i < ${COL1SIZE} + ${COL2SIZE} + 11; i++))
    do
        printf "%s" ${TABLECHAR}
    done
    printf "\n"
}

printRemaining() {
    strLen=$1
    colSize=$2
    for((i = ${strLen}; i < ${colSize}; i++))
    do
        printf "%s" " "
    done
}

printVersion() {
    name=$1
    nameLen=${#name}
    version=$2
    versionLen=${#version}

    printf "|  %s" "${name}"
    printRemaining ${nameLen} ${COL1SIZE}
    printf "  |  %s  " "${version}"
    printRemaining ${versionLen} ${COL2SIZE}
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
printVersion "Boost" "$(grep "#define BOOST_LIB_VERSION" ${BOOST_DIR}/include/boost/version.hpp | cut -d '"' -f 2)"
printVersion "Cpplint" "${CPPLINTVER}"
#printVersion "Cucumber" "$(cucumber --version)"
printVersion "Doxygen" "$(doxygen --version)"
printVersion "G++" "$(g++ --version | head -1)"
printVersion "Gcov" "$(gcov --version | head -1)"
printVersion "gcovr.py" "$(mediaManager/support/gcovr.py --version | head -1)"
printVersion "Google Log" "$(head -3 ${GLOG_DIR}/share/doc/glog*/ChangeLog | grep google-glog | cut -d ' ' -f 4)"
printVersion "Google Test" "${GTESTVER}"
printVersion "Linux Kernel" "$(uname -r)"
printVersion "Make" "$(make --version | head -1)"
printVersion "Perl" "$(perl --version | head -2 | tail -1)"
printVersion "Python" "$(python --version 2>&1 > /dev/null)"
#printVersion "Ruby" "$(ruby --version)"
printVersion "valgrind" "$(valgrind --version)"

# footer
printEnds


# farm the work out to other scripts
./jenkins_compile.sh
./jenkins_test.sh
./jenkins_tools.sh
echo
echo

