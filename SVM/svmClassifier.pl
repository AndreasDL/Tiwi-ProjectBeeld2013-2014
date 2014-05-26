# SVM programs
my $svmLearn = "svm_perf_learn.exe";
my $svmClassify = "svm_perf_classify.exe";

# Variable initialization
my $inputFile = "featurevectors.dat";

my $modelGroot = "modelTegelGroot.dat";
my $modelMiddel = "modelTegelMiddel.dat";
my $modelKlein = "modelTegelKlein.dat";

my $modelGrasLinks = "modelGrasLinks.dat";
my $modelGrasRechts = "modelGrasRechts.dat";

my $modelGeel = "modelGeel.dat";

#Cache size of 10
#value 0 = no clue
@cache = (1,1,1,1,1,1,1,1,1 ,1);

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

sub checkYellow{
	`$svmClassify tmp_dat.dat $modelGeel tmp_predictions`;
	
	open(DAT, "tmp_predictions");
	my @lines = <DAT>;
	my $svmValue = $lines[0];

	if($svmValue > 0) {
		return 1;
	} else {
		return -1;
	}
}

sub findRegion{
	my %resultSet = ();
	foreach $region(@cache){
		$resultSet{$region}++;
	}
	my $region = 0;
	while(my ($k, $v) = each %resultSet ){
		if($v > $resultSet{$region}){
			$region = $k;
		}
	}
	
	return $region;
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
		#print "The SVM has no clue\n";
		$cache[$count%10] = 0;
	}	
	#Geen
	elsif($tileSize == 0){
		my $grassLeft = checkGrassLeft($_);
		my $grassRight = checkGrassRight($_);
		my $yellow = checkYellow($_);
<<<<<<< HEAD
		if ($yellow == 1 && $grassRight == 1 && $grassLeft == -1){
			print "$count -> Zone 3\n"; #gele kleur in straatje in begin, volgens killian links geen gras daar en rechts wel
		#} elsif($yellow == 1 && $grassLeft == 1 && $grassRight == -1){
			#print "$count -> Zone 8\n"; #gele kleur bij de struiken, links wel gras, rechts geen
=======
		if ($yellow == 1 && $grassRight == 1){
			#print "$count -> Zone 3\n"; #gele kleur in straatje in begin
			$cache[$count%10] = 3;
		} elsif($yellow == 1 && $grassLeft == 1){
			#print "$count -> Zone 8\n"; #gele kleur bij de struiken, links wel gras, rechts geen
			$cache[$count%10] = 8;
>>>>>>> 899f5f9b57048fe7fb3996748996f5bb143722d9
		} elsif($grassLeft == 1 && $grassRight == 1){
			#print "$count -> Zone 4\n";
			$cache[$count%10] = 4;
		} elsif($grassLeft == 1 && $grassRight == -1){
			#print "$count -> Zone 7\n";
			$cache[$count%10] = 7;
		} elsif($grassLeft == -1 && $grassRight == -1 && $yellow == -1){
			#print "$count -> Zone 10 of 11\n";
			$cache[$count%10] = 10;
		} else {
			#print "$count -> None, grassLeft $grassLeft, grassRight $grassRight, yellow $yellow\n";
			$cache[$count%10] = 0;
		}
	}
	#Klein
	elsif($tileSize == 1){
		my $grassLeft = checkGrassLeft($_);
		my $grassRight = checkGrassRight($_);
		if($grassLeft == 1 && $grassRight == 1){
			#print "$count -> Zone 2\n";
			$cache[$count%10] = 2;
		} elsif($grassLeft == 1 && $grassRight == -1){
			#print "$count -> Zone 5\n";
			$cache[$count%10] = 5;
		} elsif($grassLeft == -1){
			#print "$count -> Zone 9\n";
			$cache[$count%10] = 9;
		} else {
			#print "$count -> Small, grassLeft $grassLeft, grassRight $grassRight\n";
			$cache[$count%10] = 0;
		}
	}
	#Middel
	elsif($tileSize == 2){
		#print "$count -> Zone 9\n";
		$cache[$count%10] = 9;
	}
	#Groot
	elsif($tileSize == 3){
		my $grassLeft = checkGrassLeft($_);
		my $grassRight = checkGrassRight($_);
		if($grassRight == 1){
			#print "$count -> Zone 1\n";
			$cache[$count%10] = 1;
		} elsif ($grassLeft == 1){
			#print "$count -> Zone 6\n";
			$cache[$count%10] = 6;
		} else {
			#print "$count -> Zone 10 of 11\n";
			$cache[$count%10] = 10;
		}
	}
	$selectedRegion = findRegion();
	print "$count -> $selectedRegion\n";

	$count++;
}

close(DAT);
close(DATWR);

`del tmp_predictions tmp_dat.dat`
