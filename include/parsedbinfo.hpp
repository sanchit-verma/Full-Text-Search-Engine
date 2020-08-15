#include"../include/parsers/handler.hpp"
#include"../include/text-preprocess/class_text-info.hpp"
#include"../include/dataclass/studentclass.hpp"
#include"../include/text-preprocess/porterstemming.hpp"
#include"../include/text-preprocess/Stopword.hpp"
using json = nlohmann::json;
using namespace std;
// this file drives the entire package

// this will remain global to be used everywhere in source file
set<string> stopword_list;

bool parse_dbinfo(unordered_map<string, vector<text_info> >& info)
{
     // returns mapping of string and info
    unordered_set<studentclass*> student_set;
    saxhandler handler;
    string dbpath = "include/../data/database.json"; // databse path
    ifstream database_file(dbpath);
    bool parse_result = json::sax_parse(database_file, &handler);

    if(!parse_result)
    {
        cout<<"error parsing the database file!"<<endl;
        return 0; // return program indicating error code 1
    }
    // ok, recieved parsed database of students
    student_set = handler.studentset;

    //ok, recieved stopword list
    if(!stopword(stopword_list)){
        cout<<"Error Parsing stopword file! Program will terminate"<<endl;
        return 0; // return indicating error
    }
    
    // preprocessing starts here....

    for(auto itr : student_set){

        set<string> names, abouts;
        // process raw info and eliminate white space and store in different set
        // stem if needed;
        string sname,sabout;
        sname = itr->name;
        sabout = itr->about;
        // filter removes every special chars possible
        sabout = filter(sabout);
        // tokenize white space
        tokens(sname,names,' ');
        tokens(sabout,abouts,' ');
        for(string name : names){
            sname = lowercase(name);
            if(stopword_list.find(sname) == stopword_list.end())
            {
                // the string is not stopword
                // stem the string using portstemmer
                sname = portstem(sname);
                // power of cpp stl.. if found increment,not then create it
                // and incremnt value 0->1
                itr->object_detail[sname][0]++;
            }
            
        }
        // same process for about array
        for(string about : abouts)
        {
            sabout = lowercase(about);
            
             if(stopword_list.find(sabout) == stopword_list.end())
            {
                // the string is not stopword
                // stem the string using portstemmer
                sabout = portstem(sabout);
                // power of cpp stl.. if found increment,not then create it
                // and incremnt value 0->1
                itr->object_detail[sabout][1]++;
            }
        }

    }
    
   for(auto itr : student_set){
        set<string> names, abouts;
        string sname; string sabout;
        sabout = filter(itr->about);

        tokens(itr->name,names,' ');
        tokens(sabout,abouts,' ');
        int val[2]; 
        for(string name : names){ 
            sname = lowercase(name); // sname will be stemmed and diff from name
            if(stopword_list.find(sname) == stopword_list.end())
            {
                sname = portstem(sname);
                text_info objinfo;
                objinfo.term_freq = 0;
                objinfo.id = itr->id; // stemmed word in all names storing diff students
                objinfo.name = itr->name;// dont get confuse.. its name of student stored in info of stemmed word in the name
                objinfo.term_freq += ((1000*itr->object_detail[sname][0]) + (50*itr->object_detail[sname][1]));
                info[sname].push_back(objinfo); 
            }
        } 

        // for about

        for(string about : abouts){ 
            sabout = lowercase(about); // sname will be stemmed and diff from name
            if(stopword_list.find(sabout) == stopword_list.end())
            {
                sabout = portstem(sabout);
                text_info objinfo;
                objinfo.term_freq = 0;
                objinfo.id = itr->id; // stemmed word in all names storing diff students
                objinfo.name = itr->name;// dont get confuse.. its name of student stored in info of stemmed word in the name
                objinfo.term_freq += 1000*itr->object_detail[sabout][0] + 50*itr->object_detail[sabout][1];
                info[sabout].push_back(objinfo);
            }
        }

    }
    
    database_file.close();
    return 1;
}












    
 
