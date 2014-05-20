#usage: groen.pl folder outputfile comment
if (-d $ARGV[0]) {
	opendir(D, $ARGV[0]) || die "Can't open directory: $!\n";
	while (my $f = readdir(D)) {
		if (!($f eq '.' || $f eq '..')){
			`./bin/groen_kant $ARGV[2] $ARGV[0]"/"$f $ARGV[1]`
		}
	}
	closedir(D);
}
