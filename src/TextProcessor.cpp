#include "TextProcessor.h"
using namespace std;
std::vector<std::pair<std::string, int>> TextProcessor::sortedGeneralWords;


TextProcessor::TextProcessor() {
    sortedfreq();
}
TextProcessor::TextProcessor(string paragraph,vector<string>filterWords) {
   unnecessary_words = { "he","she","it","is" ,"we","you","are","they","the","a","an","in","on","at","of","or","so","to","for","very",",",".","?","!",":","_"};
   if(!filterWords.empty())
       for (auto const& filter : filterWords)
           unnecessary_words.push_back(filter);

    WordSplitter(paragraph,false);
    sortedfreq();
}

map<string, int> TextProcessor::getWords() {
    return this->words;
}
vector<pair<string, int>> TextProcessor::getSortedWords() {
    return this->sortedwords;
}

bool TextProcessor::searchWordFrequency(string word, map<string, int> wordFrequency)
{
    auto it = wordFrequency.find(word);
    if (it != wordFrequency.end())
    {
        cout << "Frequency of " << word << ":" << it->second << endl;
        return true;
    }
    else
    {
        cout << "Frequency of " << word << " not found\n";
        return false;
    }
}

void TextProcessor::sortedfreq() {
    if (!words.empty()) {
        vector<pair<string, int>>vec(words.begin(), words.end());
        sort(vec.begin(), vec.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second; // Sort by the second element of the pair
            });
        sortedwords = vec;

    }
    vector<pair<string, int>>vecGeneral(generalWords.begin(), generalWords.end());

    sort(vecGeneral.begin(), vecGeneral.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second; // Sort by the second element of the pair
        });
    sortedGeneralWords = vecGeneral;
}

int TextProcessor::rankkingbyitChar(string s)
{
    vector<pair<string, int>>v(words.begin(), words.end());
    if (contain(s,false) == 1) {
        for (int i = 0; i < v.size(); i++)
        {
            if (v[i].first == s)
            {
                return i + 1;
            }
        }
    }
    else
        return -1;

}



int TextProcessor::rankkingbyfreq(string s,bool global)
{
    int counter = 0;
    if(global)
    if (contain(s,global) == 1) {
        for (int i = 0; i < sortedGeneralWords.size(); i++)
        {
            if (i == 0 && sortedGeneralWords[i].first == s)
                return counter + 1;


            if (sortedGeneralWords[i].first == s)
            {
                if (sortedGeneralWords[i - 1].second != sortedGeneralWords[i].second) counter++;
                return counter;
            }
            else
            {
                if (i == 0)
                    counter++;

                else
                {
                    if (sortedGeneralWords[i - 1].second == sortedGeneralWords[i].second)
                        continue;
                    else counter++;
                }
            }
        }
    }
    else
        return 0;
    else
    if (contain(s,global) == 1) {
        for (int i = 0; i < sortedwords.size(); i++)
        {
            if (i == 0 && sortedwords[i].first == s)
                return counter + 1;


            if (sortedwords[i].first == s)
            {
                if (sortedwords[i - 1].second != sortedwords[i].second) counter++;
                return counter;
            }
            else
            {
                if (i == 0)
                    counter++;

                else
                {
                    if (sortedwords[i - 1].second == sortedwords[i].second)
                        continue;
                    else counter++;
                }
            }
        }
    }
    else
        return 0;

    // اللوب اللى بترجع كلهم عشان لو احتجنها قدام

   /* int counter = 1;
    for (int i = 0; i < sortedwords.size(); i++)
    {
        if (i == 0)
            cout << counter << " rank ( " << sortedwords[i].first << " => " << sortedwords[i].second << " ) " << endl;
        else
        {
            if(sortedwords[i].second==sortedwords[i-1].second)
                cout << counter << " rank ( " << sortedwords[i].first << " => " << sortedwords[i].second << " ) " << endl;
            else
            {
                cout << ++counter << " rank ( " << sortedwords[i].first << " => " << sortedwords[i].second << " ) " << endl;

            }
        }
    }


    */
    return 0;

}

bool TextProcessor::contain(string s,bool global) {
    if(global)
        return (generalWords.find(s) != generalWords.end());

    return (words.find(s) != words.end());

}


string TextProcessor::Tolowercase(string sentence) {
    
    for (int i = 0; i < sentence.size(); ++i) {
        if (sentence[i] != ',' && sentence[i] != '.' && sentence[i] != '?' && sentence[i] != '_' && sentence[i] != '!')
            
        sentence[i] = tolower(sentence[i]);
        else
        {
            sentence.erase(i);
        }
    }
    return sentence;
}

void TextProcessor::WordSplitter(string& paragraph,bool modify) {
    istringstream iss(paragraph);
    map<string, int>temp;
    string word;
    while (iss >> word) {
        bool unnecessary = false;
        for (int i = 0; i < unnecessary_words.size(); ++i) {
            if (word == unnecessary_words[i]) {
                unnecessary = true;
                break;
            }
        }
        if (unnecessary)
            continue;
        word = Tolowercase(word);
        temp[word]++;
        if(!modify)
        generalWords[word]++;
        // cout << word << "  " << temp[word] << endl;
    }
    history.push(temp);
    words = temp;
}


//void TextProcessor::filter(vector<string>& filterWords, bool stop)
//{
//     
//    for (auto it = unnecessary_words.begin(); it != unnecessary_words.end(); it++)
//    {
//        map<string, int>::iterator iter = words.find(*it);
//        if (iter == words.end()) {
//            continue;
//        }
//        else {
//            words.erase(*it);
//        }
//
//    }
//    /*this->textprocess->setWords(words);
//    this->textprocess->sortedfreq();*/
//
//}
//void TextProcessor::Display() {
//
//    for (auto it : sortedwords) {
//        cout << it.first << " " << it.second << endl;
//    }
//
//}

vector<pair<string,int>> TextProcessor::searchauto(string word) {
    vector<pair<string, int>> searchQuery;
        for (auto it : generalWords)
        {
            if (it.first.substr(0, word.size()) == Tolowercase(word))
            {
                searchQuery.push_back(it);
            }
        }
        return searchQuery;
  
}

void TextProcessor::setWords(map<string,int> words) {
    this->words = words;

}
 vector<pair<string,int>> TextProcessor::searchcorrect(string word)
{    vector<pair<string, int>>mm;
    int size = word.size(); 
    int diff = 0;
    for (auto& nn : generalWords)
    {
        diff = 0;
        if (nn.first.size() == size)
        {
            for (int i = 0; i < size; i++)
            {
                if (word[i] != nn.first[i] && diff < 3)
                {
                    diff++;
                }
                else
                {
                    break;
                }
            }
            if (diff < 3)
                mm.push_back(nn);

        }
    }
    return mm;
}

 void TextProcessor::modify(string returnString) //bta5od el string elly rag3 
 {
     WordSplitter(returnString,true);
     map<string, int> tempMap = history.top();
     history.pop();
     int operation = 0;
     for (auto it2 = tempMap.begin(); it2 != tempMap.end(); ++it2) {

         auto global_it = this->generalWords.find(it2->first);
         auto it1 = history.top().find(it2->first);
         if (it1 != history.top().end())
         {
             operation = it1->second - it2->second;

             if (it1->second > it2->second) // keda m3naha eno shal value mn el map 'delete'
             {
                 //cout << "you deleted that word:  " << it1->first << endl;
                 it1->second = it1->second - abs(operation);
                 global_it->second = global_it->second - abs(operation);
             }
             else if (it1->second < it2->second) //keda hwa zwd nfs el kelma tany fe mkan tany
             {
                 //cout << "You added a word which is was in the paragraph before:  " << it1->first << endl;
                 it1->second = it1->second + abs(operation);
                 global_it->second = global_it->second + abs(operation);
                 //this->generalWords[global_it->first] = global_it->second - abs(operation);

             }
             else {
                 //cout << "No change have done  " << endl;
             }
         }
         else //m3naha en ana zwdt kelma gdeda msh mwgoda khales fe el map
         {
             if (this->generalWords.find(it2->first) == this->generalWords.end())
             {
                 this->generalWords[it2->first] = it2->second;
             }
             else
             {
                 global_it->second++;
             }
             history.top()[it2->first] = it2->second;
             //cout << "New word added: " << it2->first << endl;
         }
     }
     // Check for keys in words that are not in tempMap and delete them
     for (auto it1 = history.top().begin(); it1 != history.top().end();) {

         auto it2 = tempMap.find(it1->first);
         auto global_it = this->generalWords.find(it1->first);
         if (it2 == tempMap.end()) {
             //cout << "word deleted: " << it1->first << endl;
             it1 = history.top().erase(it1);
             (global_it->second) -= operation;

         }
         else {
             ++it1;
         }
         /*if (global_it != this->generalWords.end()) {
             if (global_it->second < 1) {
                 this->generalWords[global_it->first];
             }
             else {
             }
         }*/

         
     }
     history.pop();
     history.push(tempMap);
     this->words = tempMap;
     sortedfreq();
 }
