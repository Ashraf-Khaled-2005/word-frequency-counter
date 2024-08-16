#pragma once
#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include<map> 
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include<stack>
using namespace std;
class TextProcessor
{
	vector<pair<string, int>> sortedwords;
	std::map<std::string, int> words;
	vector<string> unnecessary_words;
	stack<map<string, int>> history;
	
public:
	static map<string, int> generalWords;
	static vector< pair<string, int>> sortedGeneralWords;
	TextProcessor();
	vector<pair<string,int>> searchauto(string word);
	vector<pair<string,int>> searchcorrect(string word);
	map<string, int> getWords();
	void setWords(map<string, int>);
	vector<pair<string, int>> getSortedWords();
	TextProcessor(string paragraph,vector<string>filterWords);
	void WordSplitter(std::string&,bool);
	bool searchWordFrequency(std::string word, std::map<std::string, int> wordFrequency);
	void sortedfreq();
	int rankkingbyitChar(std::string s);
	int rankkingbyfreq(string,bool);
	bool contain(string s,bool);
	string Tolowercase(string sentence);
	void modify(string returnString);
	/*void filter(vector<string>& filterWords, bool stop);*/
	//void modify(string& s);
	void Display();



};
#endif