#include "WordFilter.h"
#include <map>
#include<iostream>
#include<string>
#include <vector>
using namespace std;


WordFilter::WordFilter(TextProcessor& textprocess) {

    this->textprocess = &textprocess;
}


void WordFilter::filter(vector<string>& filterWords, bool stop)
{
    vector<string> unnecessary_words;
    if (stop)
        unnecessary_words = { "he","she","it","is" ,"we","you","are","they","the","a","an","in","on","at","of","or","so","to","for","very" };
    for (auto const& filter : filterWords)
        unnecessary_words.push_back(filter);
    map<string, int> words = this->textprocess->getWords();
    for (auto it = unnecessary_words.begin(); it != unnecessary_words.end(); it++)
    {
        map<string, int>::iterator iter = words.find(*it);
        if (iter == words.end()) {
            continue;
        }   
        else {
           words.erase(*it);
        }

    }
    this->textprocess->setWords(words);
    this->textprocess->sortedfreq();

}