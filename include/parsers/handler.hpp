#include "jsonparser.hpp"
#include "../dataclass/studentclass.hpp"
using json = nlohmann::json;
using namespace std;

bool isequals(const std::string& a, const std::string& b)
{
    return std::equal(a.begin(), a.end(),
                      b.begin(), b.end(),
                      [](char a, char b) {
                          return tolower(a) == tolower(b);
                      });
}

class saxhandler : public json::json_sax_t
 {
    private:
            // these bools params help us to tell which specific key in json file has been parsed
            bool bid = false;
            bool bName=false;
            bool bAge=false;
            bool bAbout=false;
    public:
            unordered_set<studentclass*> studentset;
            studentclass* stud;
            // overrided functions help us identify if element is parsed
            bool key(string_t& val) override ;
            bool string(string_t& val) override;
            bool end_object() override;
            //rest of the functions not needed in project but 
            //declared because of parent class have them
            // number-integer fxn not working properly
            bool number_integer(number_integer_t val) override
            {
                return true;
            }
            bool null() override
            {
                return true;
            }
            bool boolean(bool val) override
            {
                return true;
            }
            bool number_unsigned(number_unsigned_t val) override
            {
                return true;
            }
            bool number_float(number_float_t val, const string_t& s) override
            {
                return true;
            }
            bool start_object(std::size_t elements) override
            {
                return true;
            }
            bool start_array(std::size_t elements) override
            {
                return true;
            }
            bool end_array() override
            {
                return true;
            }
            bool parse_error(std::size_t position, const std::string& last_token, const json::exception& ex) override
            {
                return false;
            }
        
 };

bool saxhandler::key(string_t& val)
        {
            if(isequals(val,"id")){
                bid = true;
            }
            else if(isequals(val,"name")){
                bName = true;
            }
            else if(isequals(val,"age")){
                bAge = true;
            }
            else if(isequals(val,"about")){
                bAbout = true;
            }
            return true;
        }

bool saxhandler::string(string_t& val)
        {
            if(bid == true){
                stud = new studentclass(val);
                bid = false;
            }
            else if(bName == true){
                if(stud == NULL) 
                    return false;
                stud->name = val;
                bName = false; // already discovered and filled, now turn 0 for next one
            }
            else if(bAbout == true){
                if(stud == NULL)
                    return false;
                stud->about = val;
                bAbout = false;
            }
            else if (bAge == true){
                if(stud == NULL)
                    return false;
                stud->age = val;
                bAge = false;
            }

            return true;
        }
bool saxhandler::end_object()
        {
            if(stud != NULL){
                studentset.insert(stud);
                stud = NULL;
            }
            return true;
        }
