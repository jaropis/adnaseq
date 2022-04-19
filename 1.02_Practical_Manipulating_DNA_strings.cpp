#include <iostream>
#include <string>
#include <map>
using namespace std;

string longestCommonPrefix(string s1, string s2) 
{
    int idx = 0;
    while (idx < s1.length() && idx < s2.length() && s1[idx] == s2[idx])
    {
        idx++;
    }
    return s1.substr(0, idx);
}

bool match(string s1, string s2)
{
    if (s1.length() != s2.length()) 
    {
        return false;
    }

    for (int idx=0; idx < s1.length(); idx++) 
    {
        if (s1[idx] != s2[idx]) 
        {
            return false;
        }
    }
    return true;
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
    cout << longestCommonPrefix("ACCATGT", "ACCAGAC") << endl;
    cout<< std::boolalpha;
    cout << "do the strings match? " << match("ATGCT", "ATGCT") << endl;
    std::map<char, char> COMPLEMENT = {
        { 'T', 'A'}, 
        {'A', 'T'}, 
        {'G', 'C'}, 
        {'C', 'G' }
    };
    cout << COMPLEMENT['A'] << endl;
    cout << COMPLEMENT['C'] << endl;
    cout << "reverse complement of ACCATTG is: " 
        << reverseComplement("ACCATTG", COMPLEMENT) 
        << endl; 
}