#include <iostream>
#include <fstream>
#include <vector>
#include <random>
using namespace std;

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
                cout << occurrences.size() << endl;
            }
    }
    return occurrences;
}

void showOccurences(vector<int> occurrences) {
    for (int idx = 0; idx < occurrences.size(); idx++)
    {
        cout << occurrences[idx] << ", ";
    }
    cout << endl;
}

int randint(int min, int max)
{
    int rand_num;
    rand_num = rand() % (min + max);
    return rand_num;
}

vector<string> generateReads(string genome, int numReads, int readLen)
{
    vector<string> reads;
    int start;
    for (int idx = 0; idx < numReads; idx++) 
    {
        start = randint(0, genome.length() - readLen);
        reads.push_back(genome.substr(start, readLen));
    }
    return reads;
}

void showReads(vector<string> reads) 
{
    for(int idx = 0; idx < reads.size(); idx++)
    {
        cout << idx << ") " << reads[idx] << endl;
    }
}
int main() 
{   
    string genome;
    //system("wget http://d28rh4a8wq0iu5.cloudfront.net/ads1/data/phix.fa");
    vector<int> matches;
    vector<string> reads;
    genome = readGenome("phix.fa");
    // first example - mad up strings
    matches = naive("AG", "AGCTTAGATAGC");
    // showOccurences(matches);
    // second example: random substrings of length 100
    reads = generateReads(genome, 100, 100);
    // showReads(reads);
    for (string read : reads) 
    {
        cout << read << endl;
        matches = naive(read, genome);
        showOccurences(matches);
    }
    return 0;
}