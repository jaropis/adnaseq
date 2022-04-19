#include "fastaq.hpp"
#include <iostream>
#include <fstream>
#include <sciplot/sciplot.hpp>
#include <string>
using namespace std;
fastaq::fastaq(string filename)
{
    string line;
    ifstream file(filename);
    int idx = 0;
    while(getline(file, line)) {
        if (idx == 4) 
        {
            idx = 0;
        }
        if (idx == 0) 
        {   
            idx++;
            continue;
        }
        if (idx == 1) 
        {
            idx++;
            sequencies.push_back(line);
            continue;
        }
        if (idx == 2) 
        {
            idx++;
            continue;
        }
        if (idx == 3) {
            idx++;
            qualities.push_back(line);
            continue;
        }
    }
    // now creating histogram map
    for (int idx=0; idx < 50; idx++)
    {
        this->histogram.insert (pair<int, int>(idx, 0));
    } 
}
void fastaq::print_seqencies() 
{
    for (string elem : this->sequencies) {
        cout << elem << endl;
    }
}
void fastaq::print_qualities()
{
    for (string elem : this->qualities) {
        cout << elem << endl;
    }
}

int fastaq::phred33ToQ(char qual) 
{
    return (int)qual - 33;
}

void fastaq::createHist()
{
    int current_quality;
    for (int idx = 0; idx < qualities.size(); idx++)
    {
        for (char elem : qualities[idx])
        {
            current_quality = phred33ToQ(elem);
            histogram[current_quality]++;
        }
    }
}

void fastaq::printHist() {
    for (int idx = 0; idx < histogram.size(); idx++)
    {
        cout << idx << ":" << histogram[idx] << endl;
    }
}

void fastaq::plotHIst() {
    vector<int> x;
    vector<int> y;
    for (int idx = 0; idx < this->histogram.size() ; idx++)
    {
        x.push_back(idx);
        y.push_back(histogram[idx]);
    } 
    Plot hist;
    hist.palette("set2");
    hist.drawCurve(x, y).label("Quality");
    hist.show();
}

void fastaq::findGCByPos() {
    map<int, int> totals;
    // populate gc and totals
    for (int idx=0; idx < 100; idx++)
    {
        gc.insert(pair<int, int>(idx, 0));
        totals.insert(pair<int, int>(idx, 0));
        gc_frac.insert(pair<int, int>(idx, 0.0));
    } 
    for (int idx = 0; idx < sequencies.size(); idx++)
    {
        for (int elem_pos = 0; elem_pos < sequencies[idx].length(); elem_pos++) 
        {
            if (sequencies[idx][elem_pos] == 'C' || sequencies[idx][elem_pos] == 'G') 
            {
                gc[elem_pos]++;
            }
            totals[elem_pos] ++;
        }
    }
    for (int idx = 0; idx < 100; idx++)
    {
        if(totals[idx] > 0) 
        {
            gc_frac[idx] = (float)gc[idx]/float(totals[idx]);
        }
    }
}

void fastaq::printGCByPos()
{
    for(int idx = 0; idx < 100; idx++)
    {
        cout << idx << ": " << gc[idx] << ", " << gc_frac[idx] << endl;
    }
}

void fastaq::plotGCByPos() {
    vector<int> x;
    vector<float> y;
    for (int idx = 0; idx < this->gc_frac.size() ; idx++)
    {
        x.push_back(idx);
        y.push_back(gc_frac[idx]);
    } 
    Plot hist;
    hist.palette("set2");
    hist.drawCurve(x, y).label("GC fraction");
    hist.show();
}

void fastaq::baseCounter() {
    for (int idx = 0; idx < sequencies.size(); idx++)
        {
            for (char elem : sequencies[idx])
            {
                if (elem == 'A' || elem == 'T' || elem == 'C' || elem == 'G' ) 
                {
                    base_count[elem]++;
                } else {
                    base_count['N']++;
                }
            }
        }
}

void fastaq::printBaseCount() {
    for (char elem : "ATGCN") {
        cout << elem << ": " << base_count[elem]  << endl;
    }
}

string fastaq::getSequenceNo(int no) 
{
    return sequencies[no];
}

int fastaq::getSeqenceCount()
{
    return sequencies.size();
}