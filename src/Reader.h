#pragma once
#ifndef READER_H
#define READER_H


#include <fstream>
#include <string>
#include <map>
#include <iostream>
class Reader
{
	std::fstream paragraphFile;
	std::string paragraphPath;
	std::string line;
	std::string paragraph;
public:
	Reader();
	void writeGeneralmap(std::map<std::string,int>);
	std::map<std::string, int> readGeneralmap();
	Reader(std::string);
	std::string read();
	void write(std::string);
	~Reader();

};
#endif