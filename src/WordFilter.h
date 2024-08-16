#pragma once
#ifndef WORDFILTER_H
#define WORDFILTER_H
#include <map>
#include <string>
#include "TextProcessor.h"
using namespace std;
class WordFilter
{
    TextProcessor* textprocess;
 
public:
    WordFilter(TextProcessor&);
    void filter(vector<string>&, bool);
};
#endif