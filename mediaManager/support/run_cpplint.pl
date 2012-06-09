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
    my $dir = shift;
    my $ext  = shift;

    # find the absolute path
    my $absDir = `cd $dir ; pwd`;
    chomp($absDir);

    opendir(DIR, $dir) || die "Failed to open $dir: $!\n";
    my @files = readdir(DIR); 

    foreach my $file (@files) {
        if($file =~ m/[.]*$ext$/) {
            system("$cpplint_exe $absDir/$file |& tee $TEST_REP_DIR/cpplint-$file.log");
        }
    } 
    closedir(DIR);
}
