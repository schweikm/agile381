#!/usr/bin/env perl

use strict;
use warnings;

# XML parsing
use XML::Simple;
use Data::Dumper;

# directories
my $UT_DIR = "../bin/UnitTest";
my $TEST_REP_DIR = "../test_reports";

# executables
my $valgrind = "/usr/bin/valgrind";

# other constants
my $namePrefix = "xunit";

# main
{
    opendir(DIR, $UT_DIR) || die "Failed to open $UT_DIR: $!\n";
    my @files = readdir(DIR); 

    foreach my $file (@files) {
        if($file =~ m/[.]*_UT.exe$/) {
            # define the local variables
            my $testName = substr($file, 0, length($file) - 7);
            my $valgrindFile = $TEST_REP_DIR . "/valgrind_$testName" . ".xml";
            my $xUnitFile = $TEST_REP_DIR . "/" . $namePrefix . "-" .$testName . "Valgrind.xml";

            # run the Unit Test
            system("$valgrind --leak-check=full --show-reachable=yes --xml=yes --xml-file=$valgrindFile " .
                   "$UT_DIR/$file --gtest_output=xml:$TEST_REP_DIR/" . $namePrefix . "-" . $testName . ".xml")
              && die "Could not execute Unit Test \"$file\": $!\n";

            # then convert the valgrind XML file
            &convertValgrindXML($valgrindFile, $xUnitFile, $testName);

            # delete the temp file
            system("rm -f $valgrindFile") && die "Failed to remove $valgrindFile: $!\n";
        }
    } 
    closedir(DIR);
}


sub convertValgrindXML {
    my $valgrindFile  = shift;
    my $xUnitFile     = shift;
    my $testName      = shift;

    # find the number of errors
    my $numErrors = `grep \"<error>\" $valgrindFile | wc -l`;
    chomp($numErrors);

    open(XUNIT, ">", $xUnitFile) || die "Could not open \"$xUnitFile\" for writing: $!\n";

    # print the header information
    print XUNIT "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    print XUNIT "<testsuite name=\"" . $testName . "Valgrind\" tests=\"1\" errors=\"0\" failures=\"" . $numErrors . "\" skip=\"0\">\n";
    print XUNIT "    <testcase name=\"Memory Check\" status=\"run\" time=\"0\" classname=\"" . $testName . "Valgrind\">\n";

    # add the failures if necessary
    &parseValgrindXMLFailures($valgrindFile, \*XUNIT);

    # print the footer information
    print XUNIT "    </testcase>\n";
    print XUNIT "</testsuite>\n";

    close(XUNIT);
}

sub parseValgrindXMLFailures {
    my $valgrindFile = shift;
    my $XUNIT = shift;

    # create object
    my $valgrindXML = new XML::Simple;
   
    # read XML file
    my $valgrindData = $valgrindXML->XMLin($valgrindFile, KeyAttr => {error => 'unique'});

    my $unique = 4;
    for(;;) {
        my $hex = sprintf("%#x", $unique);
        last if !defined($valgrindData->{'error'}->{$hex}->{'kind'});

        my $message = $valgrindData->{'error'}->{$hex}->{'xwhat'}->{'text'};
        my $type    = $valgrindData->{'error'}->{$hex}->{'kind'};
        my @stack   = $valgrindData->{'error'}->{$hex}->{'stack'}->{'frame'};

        my $count = 0;
        my @stackTrace = ();

        for(;;) {
            my $hash = $stack[0][$count];
            last if !defined($hash->{'ip'});

            my $file = $hash->{'file'};
            my $line = $hash->{'line'};
            my $fn   = $hash->{'fn'};

            if(defined($file) && defined($line)) {
                push(@stackTrace, "at $fn ($file:$line)");
            }
            $count++;
        }

        # create the XML failure message
        my $failureMessage = "        <failure message=\"$message\" type=\"$type\"><![CDATA[\n";
        foreach my $trace (@stackTrace) {
            $failureMessage .= $trace . "\n";
        }
        $failureMessage .=   "]]>\n" .
                             "        </failure>\n";

        print $XUNIT $failureMessage;
        $unique++;
    }
}
