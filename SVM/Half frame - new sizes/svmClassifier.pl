# SVM programs
my $svmLearn = "svm_perf_learn.exe";
my $svmClassify = "svm_perf_classify.exe";

##########################################
# Program starts here
##########################################

# Variable initialization
my $inputFile = "testData.dat";

my $modelGroot = "modelGroot.dat";
my $modelMiddel = "modelMiddel.dat";
my $modelKlein = "modelKlein.dat";

# SVM stuff
open (INFILE , $inputFile)  or die "Can't open $inputFile: $!";
my $count = 0;
while (<INFILE>) {
	open(DATWR, ">tmp_dat.dat");
	print DATWR $_;
	`$svmClassify tmp_dat.dat $modelGroot tmp_predictions`;
	
	open(DAT, "tmp_predictions");
	my @lines = <DAT>;
	my $svmValue = $lines[0];
	#print "svmGroot: $svmValue\n";
	
	if($svmValue < 0) {
		`$svmClassify tmp_dat.dat $modelMiddel tmp_predictions`;
		open(DAT, "tmp_predictions");
		my @lines = <DAT>;
		my $svmValue = $lines[0];
		#print "svmMiddel: $svmValue\n";	
		
		if($svmValue < 0) {
			`$svmClassify tmp_dat.dat $modelKlein tmp_predictions`;
			open(DAT, "tmp_predictions");
			my @lines = <DAT>;
			my $svmValue = $lines[0];
			#print "svmKlein: $svmValue\n";
			
			if($svmValue < 0) {
				print "$count -> The SVM has no clue..\n";
			} elsif($svmValue == 0) {
				print "$count -> The SVM thinks there's no tiles here. Value: $svmValue";
			} else {
				print "$count -> The SVM thinks it's small tiles! Value: $svmValue";
			}
		} elsif($svmValue == 0) {
			print "$count -> The SVM thinks there's no tiles here. Value: $svmValue";
		} else {
			print "$count -> The SVM thinks it's medium tiles! Value: $svmValue";
		}
	} elsif($svmValue == 0) {
		print "$count -> The SVM thinks there's no tiles here. Value: $svmValue";
	} else {
		print "$count -> The SVM thinks it's large tiles! Value: $svmValue";
	}
	
	$count+= 6;
}

