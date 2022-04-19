#include <iostream>
#include <fstream>
#include "fastaq.cpp"

int main() 
{
    fastaq * full_fasta;
    //system("wget http://d28rh4a8wq0iu5.cloudfront.net/ads1/data/SRR835775_1.first1000.fastq");
    full_fasta = new fastaq("SRR835775_1.first1000.fastq");
    full_fasta->findGCByPos();
    full_fasta->printGCByPos();
    full_fasta->plotGCByPos();
    full_fasta->baseCounter();
    full_fasta->printBaseCount();
    return 0;
}