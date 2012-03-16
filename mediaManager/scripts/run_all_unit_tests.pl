#!/usr/bin/env perl

use strict;
use warnings;

# directories
my $UT_DIR = "../bin/UnitTest";
my $TEST_REP_DIR = "../test_reports";

# executables
my $valgrind = "/usr/bin/valgrind";
my $rm = "/bin/rm -fr";
my $pyScript = "valgrind2xunit.py";

# main
{
    opendir(DIR, $UT_DIR) || die "Failed to open $UT_DIR: $!\n";
    my @files = readdir(DIR); 

    foreach my $file (@files) {
        if($file =~ m/[.]*_UT.exe$/) {
            # grab the test name
            my $testName = substr($file, 0, length($file) - 7);

            # run the Unit Test
            system("$valgrind --leak-check=full --show-reachable=yes --xml=yes --xml-file=" .
                   "$TEST_REP_DIR/valgrind_$testName" . ".xml $UT_DIR/$file --gtest_output=xml:$TEST_REP_DIR/$testName" . ".xml")
              && die "Could not execute $file: $!\n";

            # then convert the valgrind XML file
            system("./$pyScript $TEST_REP_DIR $testName")
              && die "Could not invoke python script: $!\n";

            # delete the tmp file
            system("$rm $TEST_REP_DIR/valgrind_$testName" . ".xml")
              && die "Failed to delete tmp XML file: $!\n";
        }
    } 
}
