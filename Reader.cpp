#include "Reader.h"
#include <cctype>

using namespace std;
Reader::Reader() {
	this->paragraphPath = "default.txt";
}
Reader::Reader(std::string paragraphPath) {
	this->paragraphPath = paragraphPath;
}

std::string Reader::read() {
	paragraphFile.open(paragraphPath, std::ios::in);
	try {
		if (paragraphFile.is_open()) {
			while (std::getline(paragraphFile, line))
				paragraph += line + "\n";
		}
		else
			throw std::runtime_error("Error: File is not open");
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
	return paragraph;
}

map<string, int> Reader::readGeneralmap() {
	map<string, int> general;
	string temp = "";
	paragraphFile.open(paragraphPath, std::ios::in);
	try {
		if (paragraphFile.is_open()) {
			while (std::getline(paragraphFile, line)) {
				if (isdigit(line[0]))
					general[temp] = stoi(line);
				else
					temp = line;
			}
		}
		else
			throw std::runtime_error("Error: File is not open");
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
	return general;

}

void Reader::writeGeneralmap( std::map<std::string, int> general) {
	paragraphFile.open(paragraphPath, std::ios::out);
	try {
		if (paragraphFile.is_open()) {
			for (const auto& pair : general) {
				paragraphFile << pair.first << "\n";  // Write word
				paragraphFile << pair.second << "\n"; // Write count
			}
		}
		else {
			throw std::runtime_error("Error: File is not open");
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
	paragraphFile.close();
}

void Reader::write(std::string paragraph) {
	paragraphFile.open(paragraphPath, std::ios::out);
	//paragraphFile.clear();
	try {
		paragraphFile << paragraph;
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
	paragraphFile.close();
}
/*
* string uploadFile(const string& filename) {
*    ifstream file(filename);
*   if (!file.is_open())
*    {
*        cerr << "Error opening file " << filename <<endl;
*        return "";
*    }
*    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
*    file.close();
*    return content;
*  }
*	void runUpload(){

	string filename;
	cout << "Enter the filename to upload:";
	cin >> filename;
	string fileContent = uploadFile(filename);
	if (!fileContent.empty()) {
    cout << "File uploaded successfully\n";
	}
	else 
	{
		cout << "Failed to upload file\n";
	}



}
* 
* 
* 
* 
* 
* 
* 
* 
* 
*/


Reader::~Reader() {
	if (paragraphFile.is_open())
		paragraphFile.close();
}