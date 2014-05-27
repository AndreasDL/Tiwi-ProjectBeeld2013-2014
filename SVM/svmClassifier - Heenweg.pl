# SVM programs
#my $svmLearn = "svm_perf_learn.exe";
my $svmClassify = "svm_perf_classify.exe"; #"/home/drew/Downloads/svm/svm_perf_classify";

# Variable initialization
my $inputFile = "featurevectors_film_2.dat";

my $modelGroot = "modelTegelGroot.dat";
my $modelMiddel = "modelTegelMiddel.dat";
my $modelKlein = "modelTegelKlein.dat";

my $modelGrasLinks = "modelGrasLinks.dat";
my $modelGrasRechts = "modelGrasRechts.dat";

my $modelGeel = "modelGeel.dat";
my $modelZebra = "modelZebra.dat";

#Cache size of 10
#value 0 = no clue
@cache = (1,1,1,1,1,1,1,1,1 ,1, 1, 1, 1, 1, 1);
$previousRegion = 0;

#ability unlocked: using readable names!
my @naamZones = ("no clue, i'm sorry",
"grote tegels start (gras rechts)",
"kleine tegels: overgang naar straat (gras links rechts)",
"straat - zandweg (gras links rechts)",
"kleine tegels sporthal (gras links)",
"grote tegels sporthal (gras links)",
"sporthal en struikweg",
"st-denijs",
"zebra (geen tegels)",
"geen tegels (weg in station)"
);

##########################################

# -1 -> no clue
#  0 -> none
#  1 -> small
#  2 -> medium
#  3 -> large
sub checkTileSize{
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

sub checkLargeTiles{
	`$svmClassify tmp_dat.dat $modelGroot tmp_predictions`;
	open(DAT, "tmp_predictions");
	my @lines = <DAT>;
	my $svmValue = $lines[0];

	if($svmValue > 0) {
		return 1;
	} else {
		return -1;
	}
}

sub checkMediumTiles{
	`$svmClassify tmp_dat.dat $modelMiddel tmp_predictions`;
	open(DAT, "tmp_predictions");
	my @lines = <DAT>;
	my $svmValue = $lines[0];

	if($svmValue > 0) {
		return 1;
	} else {
		return -1;
	}
}

sub checkSmallTiles{
	`$svmClassify tmp_dat.dat $modelKlein tmp_predictions`;
	open(DAT, "tmp_predictions");
	my @lines = <DAT>;
	my $svmValue = $lines[0];

	if($svmValue > 0) {
		return 1;
	} else {
		return -1;
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

sub checkZebra{
	`$svmClassify tmp_dat.dat $modelZebra tmp_predictions`;
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

	my $tileSize = checkTileSize();
	my $largeTiles = checkLargeTiles();
	my $mediumTiles = checkMediumTiles();
	my $smallTiles = checkSmallTiles();
	my $grassLeft = checkGrassLeft();
	my $grassRight = checkGrassRight();
	my $yellow = checkYellow();
	my $zebra = checkZebra();

	
	#Geen
	if($largeTiles == -1 && $mediumTiles == -1 && $smallTiles == -1){
		if ($yellow == 1 && $grassRight == 1){
			#print "$count -> Zone 3\n"; #gele kleur in straatje in begin
			$cache[$count%$#cache] = 3;
		} elsif($grassRight == 1){
			$cache[$count%$#cache] = 3;
		} elsif($grassLeft == 1){
			#print "$count -> Zone 8\n"; #gele kleur bij de struiken, links wel gras, rechts geen
			$cache[$count%$#cache] = 6;
		} elsif($yellow == 1){
			$cache[$count%$#cache] = 7;
		} elsif( $grassLeft == -1 && $grassRight == -1 && $yellow == -1){
			#print "$count -> Zone 10 of 11\n";
			if($zebra == 1){
				$cache[$count%$#cache] = 8;
			} else {
				$cache[$count%$#cache] = 9;
			}
		} else {
			#print "$count -> None, grassLeft $grassLeft, grassRight $grassRight, yellow $yellow\n";
			$cache[$count%$#cache] = 0;
		}
	}
	#Klein
	elsif($smallTiles == 1){
		if($grassRight == 1 && $grassLeft == 1){
			#print "$count -> Zone 2\n";
			$cache[$count%$#cache] = 2;
		} elsif($grassLeft == 1){
			#print "$count -> Zone 5\n";
			$cache[$count%$#cache] = 4;
		} else{
			#print "$count -> Zone 9\n";
			$cache[$count%$#cache] = 7;
		} 
	}
	#Middel
	elsif($mediumTiles == 1){
		if($grassLeft == 1 && $yellow == 1){
			$cache[$count%$#cache] = 6;
		} else {
			#print "$count -> Zone 9\n";
			$cache[$count%$#cache] = 7;
		}
	}
	#Groot
	elsif($largeTiles == 1){
		if($grassRight == 1){
			#print "$count -> Zone 1\n";
			$cache[$count%$#cache] = 1;
		} elsif ($grassLeft == 1){
			#print "$count -> Zone 6\n";
			$cache[$count%$#cache] = 5;
		} else {
			#print "$count -> Zone 10 of 11\n"; (station)
			$cache[$count%$#cache] = 9;
		}
	}
	$selectedRegion = findRegion();
	if($selectedRegion - $previousRegion > 1 || $selectedRegion - $previousRegion < -1){
		$selectedRegion = $previousRegion;
	}
	$previousRegion = $selectedRegion;
	print "$count -> $selectedRegion ($naamZones[$selectedRegion])\n";
	#print "$count -> small: $smallTiles, medium: $mediumTiles, large: $largeTiles, grassLeft: $grassLeft, grassRight: $grassRight, yellow: $yellow, zebra: $zebra\n";

	$count++;
}

close(DAT);
close(DATWR);

`del tmp_predictions tmp_dat.dat`