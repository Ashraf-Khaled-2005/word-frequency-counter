#pragma once
#ifndef WORDSEARCHER_H
#define WORDSEARCHER_H

#include <utility>
#include <string>
#include <map>
class WordSearcher
{

	std::pair<std::string, int> search(std::map<std::string, int>, std::string);

};
#endif