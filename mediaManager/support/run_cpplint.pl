#!/usr/bin/env perl

use strict;
use warnings;

# directories
my $INC_DIR = "trunk/mediaManager/include";
my $SRC_DIR = "trunk/mediaManager/source";
my $TEST_REP_DIR = "trunk/mediaManager/test_reports";

# scripts
my $cpplint_exe = "trunk/mediaManager/support/cpplint.py";

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

    opendir(DIR, $dir) || die "Failed to open $dir: $!\n";
    my @files = readdir(DIR); 

    foreach my $file (@files) {
        if($file =~ m/[.]*$ext$/) {
            system("$cpplint_exe $dir/$file >& $TEST_REP_DIR/cpplint-$file.log");
        }
    } 
    closedir(DIR);
}
