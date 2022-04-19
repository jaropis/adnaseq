#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;
/* # Following line downloads FASTA file containing the lambda phage reference genome
 !wget http://d28rh4a8wq0iu5.cloudfront.net/ads1/data/lambda_virus.fa */

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
int main() 
{
    // system("wget http://d28rh4a8wq0iu5.cloudfront.net/ads1/data/lambda_virus.fa");
    string seq;
    map<char, int> count = {
        {'A', 0}, 
        {'T', 0}, 
        {'C', 0}, 
        {'G', 0}
    };
    seq = readGenome("lambda_virus.fa");
    for (char base : seq) 
    {
        count[base]++;
    }
    cout << "A: " << count['A'] << endl;
    cout << "T: " << count['T'] << endl;
    cout << "G: " << count['G'] << endl;
    cout << "C: " << count['C'] << endl;
    return 0;
}