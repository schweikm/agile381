#!/usr/bin/env perl

use strict;
use warnings;

my $UT_DIR = "bin/UnitTest";
my $TEST_REP_DIR = "test_reports";

# main
{
    opendir(DIR, $UT_DIR) || die "Failed to open $UT_DIR: $!\n";
    my @files = readdir(DIR); 

    foreach my $file (@files) {
        if($file !~ m/^\./) {
            # grab the test name
            my $testName = $file;
            for(my $count = 0; $count < 7; $count++) {
                chop($testName);
            }
            
            system("$UT_DIR/$file --gtest_output=xml:$TEST_REP_DIR/$testName.xml\n");
        }
    } 
}
