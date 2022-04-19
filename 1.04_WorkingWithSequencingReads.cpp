#include <iostream>
#include <fstream>
#include <string>
#include "fastaq.cpp"
using namespace std;
using namespace sciplot;

int main() 
{ 
    fastaq * full_fasta;
    //system("wget http://d28rh4a8wq0iu5.cloudfront.net/ads1/data/SRR835775_1.first1000.fastq");
    full_fasta = new fastaq("SRR835775_1.first1000.fastq");
    //full_fasta->print_seqencies();
    //full_fasta->print_qualities();

    cout << full_fasta->phred 33ToQ('A') << endl;
    full_fasta->createHist();
    full_fasta->printHist();
    full_fasta->plotHIst();
    return 0;
}