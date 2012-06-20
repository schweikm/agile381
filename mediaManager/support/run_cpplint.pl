#!/usr/bin/env perl

use strict;
use warnings;

# directories
my $SRC_DIR = "mediaManager/manager";
my $INC_DIR = $SRC_DIR;
my $REP_DIR = "mediaManager/reports";

# scripts
my $cpplint_exe = "mediaManager/support/cpplint.py";

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
            system("$cpplint_exe $dir/$file >& $REP_DIR/cpplint-$file.log");
        }
    } 
    closedir(DIR);
}
