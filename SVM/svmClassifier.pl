# SVM programs
my $svmLearn = "svm_perf_learn.exe";
my $svmClassify = "svm_perf_classify.exe";

# Variable initialization
my $inputFile = "featurevectorsALL.dat";

my $modelGroot = "modelTegelGroot.dat";
my $modelMiddel = "modelTegelMiddel.dat";
my $modelKlein = "modelTegelKlein.dat";

my $modelGrasLinks = "modelGrasLinks.dat";
my $modelGrasRechts = "modelGrasRechts.dat";

my $modelGeel = "modelGeel.dat";

##########################################
# Subs here
##########################################

# -1 -> no clue
#  0 -> none
#  1 -> small
#  2 -> medium
#  3 -> large
sub checkTileSize{
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
				#print "$count -> The SVM has no clue..\n";
				return -1;
			} elsif($svmValue == 0) {
				#print "$count -> The SVM thinks there's no tiles here. Value: $svmValue";
				return 0;
			} else {
				#print "$count -> The SVM thinks it's small tiles! Value: $svmValue";
				return 1;
			}
		} elsif($svmValue == 0) {
			#print "$count -> The SVM thinks there's no tiles here. Value: $svmValue";
			return 0;
		} else {
			#print "$count -> The SVM thinks it's medium tiles! Value: $svmValue";
			return 2;
		}
	} elsif($svmValue == 0) {
		#print "$count -> The SVM thinks there's no tiles here. Value: $svmValue";
		return 0;
	} else {
		#print "$count -> The SVM thinks it's large tiles! Value: $svmValue";
		return 3;
	}
}

sub checkGrassLeft{
	`$svmClassify tmp_dat.dat $modelGrasLinks tmp_predictions`;
	
	open(DAT, "tmp_predictions");
	my @lines = <DAT>;
	my $svmValue = $lines[0];
	
	if($svmValue > 0) {
		return 1;
	} else {
		return -1;
	}
}

sub checkGrassRight{
	`$svmClassify tmp_dat.dat $modelGrasRechts tmp_predictions`;
	
	open(DAT, "tmp_predictions");
	my @lines = <DAT>;
	my $svmValue = $lines[0];
	
	if($svmValue > 0) {
		return 1;
	} else {
		return -1;
	}
}


##########################################
# Program starts here
##########################################

# SVM stuff
open (INFILE , $inputFile)  or die "Can't open $inputFile: $!";
my $count = 0;
while (<INFILE>) {
	open(DATWR, ">tmp_dat.dat");
	print DATWR $_;
	`$svmClassify tmp_dat.dat $modelGroot tmp_predictions`;
	
	my $tileSize = checkTileSize();
	
	if($tileSize == -1){
		print "The SVM has no clue\n";
	}	
	#Geen
	elsif($tileSize == 0){
		my $grassLeft = checkGrassLeft($_);
		my $grassRight = checkGrassRight($_);
		if($grassLeft == 1 && $grassRight == 1){
			print "$count -> Zone 4\n";
		} elsif($grassLeft == 1 && $grassRight == -1){
			print "$count -> Zone 7\n";
		} else {
			print "$count -> None\n";
		}
	}
	#Klein
	elsif($tileSize == 1){
		my $grassLeft = checkGrassLeft($_);
		my $grassRight = checkGrassRight($_);
		if($grassLeft == 1 && $grassRight == 1){
			print "$count -> Zone 2\n";
		} elsif($grassLeft == 1 && $grassRight == -1){
			print "$count -> Zone 5\n";
		} elsif($grassLeft == -1 && $grassRight == -1){
			print "$count -> Zone 9\n";
		} else {
			print "$count -> Small\n";
		}
	}
	#Middel
	elsif($tileSize == 2){
		print "$count -> Zone 9\n";
	}
	#Groot
	elsif($tileSize == 3){
		my $grassLeft = checkGrassLeft($_);
		my $grassRight = checkGrassRight($_);
		if($grassLeft == -1 && $grassRight == 1){
			print "$count -> Zone 1\n";
		} elsif ($grassLeft == 1 && $grassRight == -1){
			print "$count -> Zone 6\n";
		} elsif ($grassLeft == -1 && grassRight == -1){
			print "$count -> Zone 10 of 11\n";
		} else {
			print "$count -> Large\n";
		}
	}
	
	$count++;
}

close(DAT);
close(DATWR);

`del tmp_predictions tmp_dat.dat`
