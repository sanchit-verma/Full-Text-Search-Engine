#include"../include/parsedbinfo.hpp"
using namespace std;

bool cmp(text_info& a, text_info& b)
{
    if(a.term_freq == b.term_freq)
        return a.id < b.id;
    return a.term_freq > b.term_freq;
}

int main(){
    unordered_map<string, vector<text_info> > info; string st;
    assert(parse_dbinfo(info) == true);
    while(1){
            cout<<"enter a string"<<endl;
            cin>>st;
            if(st == "bye") break;
            st = lowercase(st);
            if(stopword_list.find(st) != stopword_list.end())
            {
                    cout<<"stopword not to be searched, try again!"<<endl;
                    continue;
            }
                
            st = portstem(st);
            if(info.find(st) == info.end()){
                cout<<"not in database!"<<endl;
                continue;
            }

            vector<text_info> informer = info[st];
            sort(informer.begin(),informer.end(), cmp);
            set<string> ids;
            for(text_info& show : informer){
                if(ids.find(show.id) != ids.end())
                    continue;
                cout<<show.id<<" "<<show.name<<" "<<show.term_freq<<endl;
                ids.insert(show.id);
            }

    }
   


    return 0;
}