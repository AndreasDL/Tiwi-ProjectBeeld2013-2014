use strict;
use warnings;

my $aantalframes = 10000; #+1 x  $aantalframes  + -1 x $aantalframes
my $trainFile = "zebra.dat";
open (F , ">$trainFile");
for (my $i = 0 ; $i < 500 ; $i++){
#	my $aant = int(1+rand(5));
	print F "+1 7:1\n";
}

for (my $i = 0 ; $i < 500 ; $i++){
	print F "+1 7:0\n";
}


close F;