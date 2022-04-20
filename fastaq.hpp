#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sciplot/sciplot.hpp>
using namespace std;
using namespace sciplot;
class fastaq {
    public:
        fastaq(string filename);
        void print_seqencies();
        void print_qualities();
        int phred33ToQ(char qual);
        void createHist();
        void printHist();
        void plotHIst();
        void findGCByPos();
        void printGCByPos();
        void plotGCByPos();
        void baseCounter();
        void printBaseCount();
        string getSequenceNo(int no);
        int getSeqenceCount();
        vector<string> getQualities();
    private:
        vector<string> sequencies;
        vector<string> qualities;
        map<int, int> histogram;
        map<int, int> gc;
        map<int, float> gc_frac;
        map<char, int> base_count = {
            {'A', 0},
            {'T', 0},
            {'G', 0},
            {'C', 0},
            {'N', 0}
        };
};