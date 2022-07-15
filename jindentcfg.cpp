#include "jindentcfg.h"

bool jindentcfg::isstuffing(string str)
{
    for (int i = -1; ++i < (int)str.length();)
        if (str[i] != '\n' && str[i] != '\r' && str[i] != '\t' && str[i] != ' ')
            return false;

    return true;
}

void jindentcfg::setindentstr(string s) {
    if (!isstuffing(s))
        throw "Error: stuffing string may only contain linefeed, carriage return, tab or space";

    indentstr = s;
}

string jindentcfg::getindentstr() { return indentstr; }

void jindentcfg::setstuffingaftermemberkey(string s) {
    if (!isstuffing(s))
        throw "Error: stuffing string may only contain linefeed, carriage return, tab or space";

    stuffing_after_member_key = s;
}

string jindentcfg::getstuffingaftermemberkey() { return stuffing_after_member_key; }

void jindentcfg::setstuffingbeforemembervalue(string s) {
    if (!isstuffing(s))
        throw "Error: stuffing string may only contain linefeed, carriage return, tab or space";

    stuffing_before_member_value = s;
}

string jindentcfg::getstuffingbeforememberkey() { return stuffing_before_member_value; }

jindentcfg::jindentcfg() {}

jindentcfg::jindentcfg(string indentString, string stuffingAfterMemberKey, string BeforeMemberValue, bool indentOpenCurlyBrace, int objectSpacing,
    int arraySpacing) {

}

