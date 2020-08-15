#ifndef STUDENTCLASS_HPP
#define STUDENTCLASS_HPP
#include<bits/stdc++.h>
using namespace std;

class studentclass
{
public:
    unordered_map<string, int [2] > object_detail;
    string name;
    string age;
    string id;
    string about;
    studentclass(string ids){
        this->id = ids;
    }
    
};

#endif



