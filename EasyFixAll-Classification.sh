#Linux only, simulair approach for windows 
#linux binairies are found in /bin => compiled on 64bit linux
MOVIE_PATH="/home/drew/data/20140226_h_10fps.avi";

RESULTS_NAME="test.txt";
SVM_PATH="SVM_BIN_LINUX_64bit/svm_perf_classify";

#cleanup
rm featurevectors.dat; #the results are appended to this file
rm $RESULTS_NAME;

#create new featurevector
echo "creating feature vector";
./bin/example $MOVIE_PATH;


#classify
echo "classifiying this might take a while";
perl SVM/svmClassifierHeen.pl $SVM_PATH "featurevectors.dat" | tee $RESULTS_NAME; #heenweg
#perl SVM/svmClassifierTerug.pl $SVM_PATH "featurevectors.dat" | tee $RESULTS_NAME; #heenweg