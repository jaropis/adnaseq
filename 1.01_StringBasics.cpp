#include<iostream>
#include<string>

using namespace std;

int main() {
    cout << "# define a new sequence" << endl;
    string seq = "ACGT";
    cout << "# Get a character from a string" << endl;
    cout << seq[1] << endl; 
    cout << "# get the length of a sequence" << endl;
    cout << seq.length() << endl;
    cout << "# empty string (epsilon)" << endl;
    string e = ""; 
    cout << e.length() << endl;
    cout << "# concatenation" << endl;
    string seq1 = "AACC";
    string seq2 = "GGTT";
    string seq_sum = seq1 + seq2;
    cout << seq_sum << endl;
    cout << "# gneerate random nucleotide" << endl;
    srand ( time(NULL) ); // random seed
    int RandIndex = rand() % 4;
    cout << RandIndex << endl;
    cout << seq[RandIndex] << endl;
    cout << "# generate a random sequence" << endl;
    string randSeq = "";
    for (int idx = 0; idx < 100; idx ++) 
    {
        RandIndex = rand() % 4;
        randSeq += seq[RandIndex];
    }
    cout << randSeq << endl;
    cout << "# get a substring" << endl;
    cout<< seq.substr(1, 3) << endl; // notice that this is incluseve!!!
    cout << "# get a prefix" << endl;
    cout << seq.substr(0, 3) << endl;
    cout << "# get a suffix" << endl;
    cout << seq_sum << " has " << seq_sum.length() << " letters" << endl;
    cout << seq_sum.substr(6, seq_sum.length()-6) << endl;
}