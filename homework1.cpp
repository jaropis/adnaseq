#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "fastaq.cpp"
using namespace std;
std::map<char, char> COMPLEMENT = {
        { 'T', 'A'}, 
        {'A', 'T'}, 
        {'G', 'C'}, 
        {'C', 'G'},
        {'N', 'N'}
    };

string reverseComplement(string seq, map<char, char>complement); 

vector<int> concatenate(vector<int> v1, vector<int> v2) {
    if(v1.size() > v2.size()) 
    {
        v1.insert(v1.end(),v2.begin(),v2.end());
        return v1;
    } else {
        v2.insert(v2.end(),v1.begin(),v1.end());
        return v2;
    }
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
            }
    }
    return occurrences;
}

vector<int> naive_2mm(string p, string t, int tolerance) {
    vector<int> occurrences;
    bool match;
    int miss_accumulator = 0;
    for (int i = 0; i < (t.length() - p.length()); i++)
    {
        match = true;
        miss_accumulator = 0;
        for(int j = 0; j < p.length(); j++)
        {   
            if(t[i+j] != p[j])
            {
                if (miss_accumulator > tolerance - 1) {
                    match = false;
                    break;
                } else {
                    miss_accumulator++;
                }
            }
        }
        if (match) 
        {
            occurrences.push_back(i);
        }
    }
    return occurrences;
}

vector<int> naive_with_rc(string p, string t)
{
    vector<int> occurrences;
    vector<int> occurrences_reverse;
    occurrences = naive(p, t);
    if (p != reverseComplement(p, COMPLEMENT)) 
    {
        cout << "reverse complement not identical" << endl;
        occurrences_reverse = naive(reverseComplement(p, COMPLEMENT), t);
        occurrences = concatenate(occurrences, occurrences_reverse);
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

string reverseComplement(string seq, map<char, char>complement)
{
    string t = "";
    for (char base : seq) 
    {
        t = complement[base] + t;
    }
    return t;
}

void showOccurrences(vector<int> occurrences) {
    for (int idx = 0; idx < occurrences.size(); idx++)
    {
        cout << occurrences[idx] << ", ";
    }
    cout << endl;
}

vector<int> which_idx(vector<int> t, int p) {
    vector<int> matches;
    for (int idx = 0; idx < t.size(); idx++)
    {
        if(t[idx] == p)
        {
            matches.push_back(idx);
        }
    }
    return(matches);
}
int main()
{
    // this is the example notebook from the homework
    // 1
    string p, t, ten_as, phix_genome, genome;
    vector<int> occurrences;
    p = "CCC";
    ten_as = "AAAAAAAAAA";
    t = ten_as + "CCC" + ten_as + "GGG" + ten_as;
    cout << t << endl;

    occurrences = naive_with_rc(p, t);
    showOccurrences(occurrences);

    // 2
    p = "CGCG";
    t = ten_as + "CGCG" + ten_as + "CGCG" + ten_as;
    occurrences = naive_with_rc(p, t);
    showOccurrences(occurrences);

    // 3
    phix_genome = readGenome("phix.fa");
    occurrences = naive_with_rc("ATTA", phix_genome);
    showOccurrences(occurrences);
    cout << "\nMin Element = "
         << *min_element(occurrences.begin(), occurrences.end()) 
         << endl;

    cout << "occurrences: " << occurrences.size() << endl;

    // programming assignment
    // 1 How many times does AGGT or its reverse complement (ACCT) occur in the lambda virus genome?  E.g. if \verb|AGGT|AGGT occurs 10 times and \verb|ACCT|ACCT occurs 12 times, you should report 22.
    genome = readGenome("lambda_virus.fa");
    cout << 1 << endl;
    occurrences = naive_with_rc("AGGT", genome);
    //showOccurrences(occurrences);
    cout << "\nMin Element = "
         << *min_element(occurrences.begin(), occurrences.end()) 
         << endl;

    cout << "occurrences: " << occurrences.size() << endl;

    // 2 TTAA
    cout << 2 << endl;
    occurrences = naive_with_rc("TTAA", genome);
    //showOccurrences(occurrences);
    cout << "\nMin Element = "
         << *min_element(occurrences.begin(), occurrences.end()) 
         << endl;

    cout << "occurrences: " << occurrences.size() << endl;

    // 3 What is the offset of the leftmost occurrence of \verb|ACTAAGT|ACTAAGT or its reverse complement in the Lambda virus genome?  E.g. if the leftmost occurrence of \verb|ACTAAGT|ACTAAGT is at offset 40 (0-based) and the leftmost occurrence of its reverse complement \verb|ACTTAGT|ACTTAGT is at offset 29, then report 29.
    cout << 3 << endl;
    occurrences = naive_with_rc("ACTAAGT", genome);
    //showOccurrences(occurrences);
    cout << "\nMin Element = "
         << *min_element(occurrences.begin(), occurrences.end()) 
         << endl;

    cout << "occurrences: " << occurrences.size() << endl;

    // 4 AGTCGA
    cout << 4 << endl;
    occurrences = naive_with_rc("AGTCGA", genome);
    //showOccurrences(occurrences);
    cout << "\nMin Element = "
         << *min_element(occurrences.begin(), occurrences.end()) 
         << endl;

    cout << "occurrences: " << occurrences.size() << endl;

    // 5 
    /* As we will discuss, sometimes we would like to find approximate matches for P in T. That is, we want to find occurrences with one or more differences.

    For Questions 5 and 6, make a new version of the \verb|naive|naive function called \verb|naive_2mm|naive_2mm that allows up to 2 mismatches per occurrence. Unlike for the previous questions, do not consider the reverse complement here.  We're looking for approximate matches for P itself, not its reverse complement.

￼

    For example, \verb|ACTTTA|ACTTTA occurs twice in \verb|ACTTACTTGATAAAGT|ACTTACTTGATAAAGT, once at offset 0 with 2 mismatches, and once at offset 4 with 1 mismatch. So \verb|naive_2mm('ACTTTA', 'ACTTACTTGATAAAGT')|naive_2mm(’ACTTTA’, ’ACTTACTTGATAAAGT’) should return the list \verb|[0, 4]|[0, 4].

    Hint: See  this notebook for a few examples you can use to test your \verb|naive_2mm|naive_2mm function.

    How many times does \verb|TTCAAGCC|TTCAAGCC occur in the Lambda virus genome when allowing up to 2 mismatches?  */

    // test 1
    cout << "5: test 1" << endl;
    occurrences = naive_2mm("ACTTTA", "ACTTACTTGATAAAGT", 2);
    showOccurrences(occurrences);
    cout << "\nMin Element = "
         << *min_element(occurrences.begin(), occurrences.end()) 
         << endl;

    cout << "5" << endl;
    occurrences = naive_2mm("TTCAAGCC", genome, 2);
    cout << "\nMin Element = "
         << *min_element(occurrences.begin(), occurrences.end()) 
         << endl;
    cout << "occurrences: " << occurrences.size() << endl;
    
    cout << "6" << endl;
    occurrences = naive_2mm("AGGAGGTT", genome, 2);
    cout << "\nMin Element = "
         << *min_element(occurrences.begin(), occurrences.end()) 
         << endl;
    cout << "occurrences: " << occurrences.size() << endl;

    cout << "7" << endl;
    fastaq * full_fasta;
    vector<string> qualities;
    vector<int> read_qualities;
    vector<int> read_qalities_mins;
    vector<int> read_qalities_maxs;
    int current_min;
    full_fasta = new fastaq("ERR037900_1.first1000.fastq");
    qualities = full_fasta->getQualities();
    cout << "there are: " << qualities.size() << " reads" << endl;

    for (int i = 0; i < qualities.size(); i++) 
    {   
        read_qualities.clear();
        for (int j = 0; j < qualities[i].length(); j++)
        {   
            read_qualities.push_back(full_fasta->phred33ToQ(qualities[i][j]));
            // read_qalities_mins.push_back(which_idx(qualities[i], curent_min));
            //read_qalities_maxs.push_back(*max_element(read_qualities.begin(), read_qualities.end()));
        }
        current_min = *min_element(read_qualities.begin(), read_qualities.end());
        read_qalities_mins = which_idx(read_qualities, current_min);
        cout << i << ": ";
        for (int k = 0; k < read_qalities_mins.size(); k++)
        {
            cout << read_qalities_mins[k] << ", ";
        }
        cout << endl;
    }
    cout << "66 seems to be the problematic one" << endl;
    return 0;
}