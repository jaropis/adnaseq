#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "fastaq.cpp"
using namespace std;

vector<int> naive(string p, string t) {
    vector<int> occurrences;
    bool match;
    for (int i = 0; i < (t.length() - p.length()); i++)
    {
        match = true;
        for(int j = 0; j < p.length(); j++)
        {
            if(t[i+j] != p[j])
            {
                match = false;
                break;
            }
        }
        if (match) {
                occurrences.push_back(i);
            }
    }
    return occurrences;
}

string readGenome(string filename) {
    ifstream file(filename);
    string line;
    string seq = "";

    while(getline(file, line)) {
        if (line[0] != '>')
        {
            seq = seq + line;
        }
    } 
    return seq;
}

int sumOcurences(vector<int> occurrences) {
    int occurences_sum = 0;
    for (int idx = 0; idx < occurrences.size(); idx++)
    {
        if (occurrences[idx] > 0) {
            occurences_sum++;
        }
    }
    return occurences_sum;
}

string reverseComplement(string seq, map<char, char>complement)
{
    string t = "";
    for (char base : seq) 
    {
        t = complement[base] + t;
    }
    return t;
}

int main() 
{   
    string genome;
    //system("wget wget http://d28rh4a8wq0iu5.cloudfront.net/ads1/data/ERR266411_1.first1000.fastq");
    vector<int> matches;
    vector<string> reads;
    int numMatched = 0;
    fastaq * phix_reads;
    std::map<char, char> COMPLEMENT = {
        { 'T', 'A'}, 
        {'A', 'T'}, 
        {'G', 'C'}, 
        {'C', 'G'},
        {'N', 'N'}
    };
    phix_reads = new fastaq("ERR266411_1.first1000.fastq");
    genome = readGenome("phix.fa");
    for (int idx = 0; idx < phix_reads->getSeqenceCount(); idx++)
    {
        matches = naive(phix_reads->getSequenceNo(idx), genome);
        numMatched += sumOcurences(matches);
        
    }
    cout << numMatched << " / " << phix_reads->getSeqenceCount() << " matched the genome!" << endl;
    // Now just the first 30 bases
    string subsequ; // declaring here to be close
    numMatched = 0;
    for (int idx = 0; idx < phix_reads->getSeqenceCount(); idx++)
    {
        subsequ = phix_reads->getSequenceNo(idx);
        matches = naive(subsequ.substr(0, 30), genome);
        numMatched += sumOcurences(matches);
    }
    cout << numMatched << " / " << phix_reads->getSeqenceCount() << " matched the genome with just 30 bases" << endl;

    // Now with reverse complement
    numMatched = 0;
    for (int idx = 0; idx < phix_reads->getSeqenceCount(); idx++)
    {
        subsequ = phix_reads->getSequenceNo(idx);
        matches = naive(subsequ.substr(0, 30), genome);
        numMatched += sumOcurences(matches);
        matches = naive(reverseComplement(subsequ.substr(0, 30), COMPLEMENT), genome);
        numMatched += sumOcurences(matches);
    }
    cout << numMatched << " / " << phix_reads->getSeqenceCount() << " matched the genome with just 30 bases and reverse complement" << endl;
    return 0;
}

