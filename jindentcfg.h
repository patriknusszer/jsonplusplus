#ifndef jindentcfg_hpp
#define jindentcfg_hpp

#include <stdio.h>
#include <string>

using namespace std;

typedef unsigned int uint;

class jindentcfg {
private:
    static bool isstuffing(string str);
    string indentstr = "\t";
    string stuffing_after_member_key = " ";
    string stuffing_before_member_value = " ";
public:
    void setindentstr(string s);
    string getindentstr();
    void setstuffingaftermemberkey(string s);
    string getstuffingaftermemberkey();
    void setstuffingbeforemembervalue(string s);
    string getstuffingbeforememberkey();
    uint objectspacing = 0;
    uint arrayspacing = 0;
    bool indentspacing = false;
    bool indentopencurlybrace = false;
    
    jindentcfg();
    
    jindentcfg(string indentString, string stuffingAfterMemberKey, string BeforeMemberValue, bool indentOpenCurlyBrace, int objectSpacing,
        int arraySpacing);
};

#endif /* jindentcfg_hpp */
