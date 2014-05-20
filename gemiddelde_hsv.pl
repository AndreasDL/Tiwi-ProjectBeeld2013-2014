#!/usr/bin/perl

#usage: gemiddelde_hsv.pl folder
my $teller = 0;
my $h = 0;
my $s = 0;
my $v = 0;

if (-d $ARGV[0]) {
	opendir(D, $ARGV[0]) || die "Can't open directory: $!\n";
	while (my $f = readdir(D)) {
		if (!($f eq '.' || $f eq '..')){
			my @values = split(' ', `./bin/get_hsv $ARGV[0]"/"$f`);
			$h+= $values[0];
			$s+= $values[1];
			$v+= $values[2];
			$teller++;
		}
	}
	closedir(D);
	
	print $h / $teller . "\n";
	print $s / $teller . "\n";
	print $v / $teller . "\n";
}
