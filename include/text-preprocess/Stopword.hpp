#ifndef STOPWORD_HPP
#define STOPWORD_HPP
#include<bits/stdc++.h>
using namespace std;
 string stopword_file = "include/text-preprocess/stopword.txt";

void tokens(std::string const &str, set<string>& stopword_list, const char delimiter)
{
    size_t start;  // size_t is return type of npos which is returned
    size_t end = 0; // when no more word being searched exsist

    while ((start = str.find_first_not_of(delimiter, end)) != string::npos)
    {
        end = str.find(delimiter, start);
        stopword_list.insert(str.substr(start, end - start));
    }
}

string filter( string word){
    string res;
    for(int i = 0; i<word.length();i++){
        if((word[i] == ',') || (word[i] == '?' )|| (word[i] == '!' )|| (word[i] == '-' )|| (word[i] == '.'))
        {
            res += ' ';
        }
        else{
            res += word[i];
        }
    }
    return res;
}

bool stopword (set<string>& stopword_list){
   // set<string> stopword_list; since we have to perform searching words they must be sorted
    // parse and store stopwords 
   // return bool true if everything is ok
    ifstream file(stopword_file);
    string line;
    const char delimiter = ',';
    if(!file.is_open()){
        return false;
    }
    while(getline(file,line)){
        tokens(line,stopword_list, delimiter);
    }
    file.close();
    return true;

}

#endif