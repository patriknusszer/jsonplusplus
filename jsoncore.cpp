#include "jsoncore.h"
#include <cmath>

string jsoncore::prepend(string s, string p, int n) {
    for (int i = 0; i < n; i++)
        s = p + s;
    
    return s;
}

string jsoncore::writearray(vec* din, int indent, jindentcfg& cfg) {
    string tmp = "[\n";
    if (indent != 0 && cfg.indentopencurlybrace)
        tmp = "\n" + prepend(tmp, cfg.getindentstr(), indent);
    
    for (int i = 0; i < (int)din->size() - 1; i++) {
        tmp += prepend(jsoncore::writevalue((*din)[i], indent + 1, cfg), cfg.getindentstr(), indent);
        tmp += ",\n";
        
        for (int x = 0; x < (int)cfg.arrayspacing; x++)
            tmp += cfg.indentspacing ? prepend("\n", cfg.getindentstr(), indent + 1) : "\n";
    }
    
    if (1 <= din->size())
        tmp += prepend(writevalue((* din)[din->size() - 1], indent + 1, cfg), cfg.getindentstr(), indent + 1);
    
    return tmp + "\n" + prepend("]", cfg.getindentstr(), indent);
}

string jsoncore::writevalue(tany* val, int indent, jindentcfg& cfg) {
    if (val->ishashmap())
        return writeobject(val->tohashmap(), indent, cfg);
    else if (val->isvec())
        return writearray(val->tovec(), indent, cfg);
    else {
        if (val->isnull())
            return writenull();
        else if (val->isstring())
            return writestring(*val->tostring());
        else if (val->isbool())
            return writeboolean(*val->tobool());
        else if (val->isdouble())
            return writenumber(*val->todouble());
        else throw "Error: can not write type to JSON configuration";
    }
}

string jsoncore::writemember(string key, tany* value, int indent, jindentcfg& cfg) {
    string tmp = "\"" + key + "\"" + cfg.getstuffingaftermemberkey() + ":";
    
    if (!(value->iscontainer() && cfg.indentopencurlybrace))
        tmp += cfg.getstuffingbeforememberkey();
    
    return tmp + writevalue(value, indent, cfg);
}

string jsoncore::writeobject(hashmap* hmap, int indent, jindentcfg& cfg) {
    string tmp = "{\n";
    
    if (indent != 0 && cfg.indentopencurlybrace)
        tmp = prepend(tmp, cfg.getindentstr(), indent);

    hashmap::iterator it = hmap->begin();
    
    for (int i = 0; i < (int)hmap->size() - 1; ++it, i++) {
        tmp += prepend(writemember(it->getkey(), it->getdata(), indent + 1, cfg), cfg.getindentstr(), indent + 1);
        tmp += ",\n";
        
        for (int j = 0; j < (int)cfg.objectspacing; j++)
            tmp += cfg.indentspacing ? prepend("\n", cfg.getindentstr(), indent + 1) : "\n";
    }
    
    if (it != hmap->end())
        tmp += prepend(writemember(it->getkey(), it->getdata(), indent + 1, cfg), cfg.getindentstr(), indent + 1);
    
    return tmp + "\n" + prepend("}", cfg.getindentstr(), indent);
}

string jsoncore::writenull() { return "null"; }
string jsoncore::writestring(string s) { return "\"" + s + "\""; }
string jsoncore::writeboolean(bool b) { return b ? "true" : "false"; }
string jsoncore::writenumber(double d) { return to_string(d); }

void* jsoncore::readnullat(int& i, string& s) {
    eatstuffing(i, s);
    if (s.length() - i < 4) throw "Error: input too short to make sense";
    
    if (s.substr(i, 4) == "null")
    {
        i += 4;
        return 0;
    }
    else throw "Error: unexpected token where null was expected";
}

valuetype jsoncore::guessvaluetypeat(int& i, string& s) {
    switch (s[i]) {
        case '{': return valuetype::object;
        case '[': return valuetype::array;
        case 't': return valuetype::booleantrue;
        case 'f': return valuetype::booleanfalse;
        case '\"': return valuetype::text;
        case 'n': return valuetype::null;
        default:
            if ((s[i] == '-') ^ isdigit(s[i])) return valuetype::number;
            else return valuetype::none;
    }
}

void jsoncore::eatstuffing(int& i, string& s) {
    while (true) {
        if (i != (int)s.length() - 1) {
            if ((s[i] == ' ') ^ (s[i] == '\t') ^ (s[i] == '\r') ^ (s[i] == '\n'))
                i++;
            else
                return;
        }
        else return;
    }
}

pair<string, tany*> jsoncore::readmemberat(int& i, string& s) {
    eatstuffing(i, s);
    string* keyp = readstringat(i, s);
    string key = *keyp;
    delete keyp;
    eatstuffing(i, s);
    
    if (s[i] == ':') {
        i++;
        tany* val = readvalueat(i, s);
        return make_pair(key, val);
    }
    else throw "Error: unexpected token where key-value separator was expected";
}

hashmap* jsoncore::readobjectat(int& i, string& s) {
    eatstuffing(i, s);
    
    if (s.length() - i < 2)
        throw "Error: input too short to make sense";
    
    if (s[i] != '{')
        throw "Error: unexpected token where beginning of object was expected";
    
    hashmap* hmap = new hashmap();
    i++;
    
    if (s[i] != '}') {
        do {
            pair<string, tany*> p = readmemberat(i, s);
            (*hmap)[p.first] = p.second;
            
            if (s[i] != ',') break;
            else i++;
        } while (true);
        
        if (s[i] != '}')
            throw "Error: unexpected token where closing of object was expected";
    }
    
    i++;
    eatstuffing(i, s);
    return hmap;
}

vec* jsoncore::readarrayat(int& i, string& s) {
    eatstuffing(i, s);
    if (s.length() - i < 2) throw "Error: input too short to make sense";
    if (s[i] != '[') throw "Error: unexpected token where beginning of array was expected";
    
    vec* v = new vec();
    i++;
    
    if (s[i] != ']') {
        do {
            v->append(readvalueat(i, s));
            
            if (s[i] != ',') break;
            else
                i++;
        } while (true);
        
        if (s[i] != ']')
            throw "Error: unexpected token where array closing was expected";
    }
    
    i++;
    eatstuffing(i, s);
    return v;
}

string* jsoncore::readstringat(int& i, string& s) {
    eatstuffing(i, s);
    if (s[i] != '\"') throw "Error: unexpected token where beginning of string was expected!";
    
    string str = "";
    
    for (int x = ++i; x < (int)s.length(); x++, i++) {
        if (0x0020 <= s[x]) {
            switch (s[x]) {
                case '\"':
                    i++;
                    eatstuffing(i, s);
                    return new string(str);
                case '\\':
                    if (x != (int)s.length() - 1) {
                        x++;
                        
                        switch (s[x]) {
                            case '\b':
                                str += '\b';
                                break;
                            case 'f':
                                str += '\f';
                                break;
                            case 't':
                                str += '\t';
                                break;
                            case '\\':
                                str += '\\';
                                break;
                            case '/':
                                str += '/';
                                break;
                            case 'u': {
                                x++;
                                
                                if (!(x + 3 <= (int)s.length() - 1))
                                    throw "Error: Input too short to make sense";
                                
                                string hex = "";
                                
                                for (int _x = x; _x < x + 4; _x++) {
                                    if (isalpha(s[_x]) ^ ('a' <= s[_x] && s[_x] <= 'f') ^ ('A' <= s[_x] && s[_x] <= 'F'))
                                        hex += s[_x];
                                    else throw "Error: unexpected token where hexadecimal character was expected";
                                }
                                
                                stringstream ss;
                                ss << std::hex << hex;
                                int num;
                                ss >> num;
                                str += to_string(num);
                                break;
                            }
                            default:
                                throw "Error: unexpected token where escape character was expected";
                                break;
                        }
                    }
                    
                    break;
                default:
                    str += s[x];
                    break;
            }
        }
    }
    
    throw "Error: input too short to make sense. Expected string closing quotes.";
}

bool* jsoncore::readbooleantrueat(int& i, string& s) {
    eatstuffing(i, s);
    if (s.length() - i < 4) throw "Error: input too short to make sense";
    
    if (s.substr(i, 4) == "true") {
        i += 4;
        eatstuffing(i, s);
        return new bool(true);
    }
    else throw "Error: unexpected token where boolean true was expected";
}

bool* jsoncore::readbooleanfalseat(int& i, string& s) {
    eatstuffing(i, s);
    if (s.length() - i < 5) throw "Error: input too short to make sense";
    
    if (s.substr(i, 5) == "false") {
        i += 5;
        eatstuffing(i, s);
        return new bool(false);
    }
    else throw "Error: unexpected token where boolean true was expected";
}

bool* jsoncore::readbooleanat(int& i, string& s) {
    eatstuffing(i, s);
    
    switch (guessvaluetypeat(i, s))
    {
    case valuetype::booleantrue:
        return readbooleantrueat(i, s);
    case valuetype::booleanfalse:
        return readbooleanfalseat(i, s);
    default:
        throw "Error: unexpected token where boolean false or boolean true was expected";
    }
}

double* jsoncore::readnumberat(int& i, string& s) {
    eatstuffing(i, s);
    bool negative = false;
    
    if (s[i] == '-') {
        negative = true;
        i++;
    }
    
    stage stg = stage::integer;
    string integer = "";
    string fraction = "";
    char expsig = '+';
    string exponent = "";
    
    for (int x = i; x < (int)s.length(); x++, i++) {
        if (s[x] == '.') {
            if (integer.length() == 0)
                throw "Error: integer part expected before decimal point";
            
            if (stg != stage::integer)
                throw "Error: invalid integer format before decimal point";
            
            stg = stage::fraction;
        }
        else if (s[x] == 'e' || s[x] == 'E') {
            if (integer.length() == 0)
                throw "Error: integer part expected in decimal";
            
            if (stg == stage::exponent)
                throw "Error: more than one exponent part found in decimal";
            
            if (x == (int)s.length() - 1)
                throw "Error: input too short to make sense";
            
            if (stg == stage::fraction && fraction.length() == 0)
                throw "Error: nonempty fraction part was expected in decimal format";
            
            x++;
            i++;
            
            if ((s[x] == '+') ^ (s[x] == '-'))
                expsig = s[x];
            
            stg = stage::exponent;
        }
        else if (isdigit(s[x])) {
            if (stg == stage::integer)
                integer += s[x];
            
            else if (stg == stage::fraction)
                fraction += s[x];
            
            else if (stg == stage::exponent)
                exponent += s[x];
        }
        else {
            if (integer.length() == 0) {
                throw "Error: number was expected, integral part was not found";
            }

            
            if (stg == stage::exponent && exponent.length() == 0) {
                throw "Error: number exponent part was expected, but not found";
            }
            
            break;
        }
    }
    
    double d = stod(integer + "." + fraction);
    
    if (exponent.length() != 0) {
        d = pow(d, stoi(exponent));
        if (expsig == '-') d = 1 / d;
    }
    
    if (negative) d*= -1;
    eatstuffing(i, s);
    return new double(d);
}

tany* jsoncore::readvalueat(int& i, string& s) {
    eatstuffing(i, s);
    
    if (i == (int)s.length())
        throw "Error: input too short to make ssense";
    
    tany* val;
    
    switch (guessvaluetypeat(i, s))
    {
        case valuetype::object:
            val = new mnghashmap(readobjectat(i, s));
            break;
        case valuetype::array:
            val = new mngvec(readarrayat(i, s));
            break;
        case valuetype::text:
            val = new mngstring(readstringat(i, s));
            break;
        case valuetype::booleantrue:
            val = new mngbool(readbooleantrueat(i, s));
            break;
        case valuetype::booleanfalse:
            val = new mngbool(readbooleanfalseat(i, s));
            break;
        case valuetype::number:
            val = new mngdouble(readnumberat(i, s));
            break;
        default: throw "Error: unexpected token where valid JSON type beginning was expected";
    }
    
    eatstuffing(i, s);
    return val;
}