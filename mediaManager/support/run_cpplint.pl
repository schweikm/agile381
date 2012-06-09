#!/usr/bin/env perl

use strict;
use warnings;

# directories
my $INC_DIR = "../include";
my $SRC_DIR = "../source";
my $TEST_REP_DIR = "../test_reports";

# scripts
my $cpplint_exe = "./cpplint.py";

# other constants
my $INC_EXT = ".h";
my $SRC_EXT = ".cpp";

# main
{
    &runCpplint($INC_DIR, $INC_EXT);
    &runCpplint($SRC_DIR, $SRC_EXT);
}

sub runCpplint {
    my $directory = shift;
    my $extension  = shift;

    opendir(DIR, $directory) || die "Failed to open $directory: $!\n";
    my @files = readdir(DIR); 

    foreach my $file (@files) {
        if($file =~ m/[.]*$extension$/) {
            system("$cpplint_exe $directory/$file |& tee $TEST_REP_DIR/cpplint-$file.log");
        }
    } 
}
