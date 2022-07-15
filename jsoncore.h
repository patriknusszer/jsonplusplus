#ifndef jsoncoreore_h
#define jsoncore_h

#include <iostream>
#include <string>
#include <sstream>
#include "vec.h"
#include "hashmap.h"
#include "tany.h"

enum stage {
    integer,
    fraction,
    exponent
};

enum valuetype {
    object,
    array,
    text,
    number,
    booleantrue,
    booleanfalse,
    null,
    none
};

class tany;

class jsoncore {
private:
    static string prepend(string s, string p, int n);
    static valuetype guessvaluetypeat(int& i, string& s);
    static void eatstuffing(int& i, string& s);
    static pair<string, tany*> readmemberat(int& i, string& s);
public:
    static string writemember(string key, tany* value, int indent, jindentcfg& cfg);
    static void* readnullat(int& i, string& s);
    static hashmap* readobjectat(int& i, string& s);
    static vec* readarrayat(int& i, string& s);
    static string* readstringat(int& i, string& s);
    static bool* readbooleantrueat(int& i, string& s);
    static bool* readbooleanfalseat(int& i, string& s);
    static bool* readbooleanat(int& i, string& s);
    static double* readnumberat(int& i, string& s);
    static tany* readvalueat(int& i, string& s);
    static string writevalue(tany* val, int indent, jindentcfg& cfg);
    static string writearray(vec* din, int indent, jindentcfg& cfg);
    static string writeobject(hashmap* hmap, int indent, jindentcfg& cfg);
    static string writenull();
    static string writestring(string s);
    static string writeboolean(bool b);
    static string writenumber(double d);
};

#endif /* jsoncore_h */
