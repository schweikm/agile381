#!/usr/bin/env bash


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


# find the google test directory
GTEST=`ls | grep gtest`

# python prints the version to stderr
# so we have to do this stupid hack
PYVER=$(python --version 2>&1 > /dev/null)


echo
echo
echo "====================================="
echo "==== Step 1: Dependency versions ===="
echo "====================================="
echo
echo
echo "-----------------------------------------------------------------------------------------------------------------"
echo "|  Make          |  `make --version | head -1`                                                                               |"
echo "|  g++           |  `g++ --version | head -1`                                                  |"
echo "|  Perl          |  `perl --version | head -2 | tail -1`      |"
echo "|  Python        |  $PYVER                                                                                |"
echo "|  Ruby          |  `ruby --version`                                   |"
echo "|  Sed           |  `sed --version | head -1`                                                                       |"
echo "|  Cucumber      |  `cucumber --version`                                                                                       |"
echo "|  Google Test   |  $GTEST                                                                                 |"
echo "|  gcov          |  `gcov --version | head -1`                                                 |"
echo "|  gcovr.py      |  `mediaManager/support/gcovr.py --version | head -1`                                                                |"
echo "|  Cppcheck      |  `cppcheck --version`                                                                               |"
echo "|  Cpplint       |  google-styleguide - Revision 83                                                             |"
echo "-----------------------------------------------------------------------------------------------------------------"


# farm the work out to sub scripts
source jenkins_compile.bash
source jenkins_test.bash
source jenkins_tools.bash
echo
echo
