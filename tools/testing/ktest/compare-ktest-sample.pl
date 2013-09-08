#!/usr/bin/perl

open (IN,"ktest.pl");
while (<IN>) {
<<<<<<< HEAD
    # hashes are now used
    if (/\$opt\{"?([A-Z].*?)(\[.*\])?"?\}/ ||
	/^\s*"?([A-Z].*?)"?\s*=>\s*/ ||
=======
    if (/\$opt\{"?([A-Z].*?)(\[.*\])?"?\}/ ||
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	/set_test_option\("(.*?)"/) {
	$opt{$1} = 1;
    }
}
close IN;

open (IN, "sample.conf");
while (<IN>) {
<<<<<<< HEAD
    if (/^\s*#?\s*([A-Z]\S*)\s*=/) {
=======
    if (/^\s*#?\s*(\S+)\s*=/) {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	$samp{$1} = 1;
    }
}
close IN;

foreach $opt (keys %opt) {
    if (!defined($samp{$opt})) {
	print "opt = $opt\n";
    }
}

foreach $samp (keys %samp) {
    if (!defined($opt{$samp})) {
	print "samp = $samp\n";
    }
}
