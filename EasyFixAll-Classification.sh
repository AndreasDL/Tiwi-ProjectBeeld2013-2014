#achievement unlocked : shell scripting

#cleanup
rm featurevectors.dat SVM/featurevectors.dat;

#create new featurevector
./bin/example /home/drew/school\ 2013-2014/Beeldverwerking/project/dataProject/20140226_h_10fps.avi;

#put in SVM dir
mv featurevectors.dat SVM/;

#goto SVM dir to avoid workingdir probs
cd SVM;
#classify
perl svmClassifier.pl > SVM_RESULTS_ANDREAS_IS_COOL;

#cleanup
rm tmp_predictions tmp_dat.dat;

#go back up
cd ..;