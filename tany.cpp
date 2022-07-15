#include "tany.h"

bool* mngnull::tobool() { return 0; }
double* mngnull::todouble() { return 0; }
string* mngnull::tostring() { return 0; }
vec* mngnull::tovec() { return 0; }
hashmap* mngnull::tohashmap() { return 0; }
container* mngnull::tocontainer() { return 0; }
bool mngnull::isnull() { return true; }
bool mngnull::isbool() { return false; }
bool mngnull::isdouble() { return false; }
bool mngnull::isstring() { return false; }
bool mngnull::isvec() { return false; }
bool mngnull::ishashmap() { return false; }
bool mngnull::iscontainer() { return false;}
void mngnull::release() {}

string mngnull::write(int indent, jindentcfg& cfg) {
	return writenull();
}

bool* mngcontainer::tobool() { return 0; }
double* mngcontainer::todouble() { return 0; }
string* mngcontainer::tostring() { return 0; }
container* mngcontainer::tocontainer() { return c; }

mngcontainer::mngcontainer(container* c) {
	this->c = c;
}

bool mngcontainer::isnull() { return false; }
bool mngcontainer::isbool() { return false; }
bool mngcontainer::isdouble() { return false; }
bool mngcontainer::isstring() { return false; }
bool mngcontainer::isvec() { return false; }
bool mngcontainer::ishashmap() { return false; }

bool mngcontainer::iscontainer() {
	return true;
}


hashmap* mnghashmap::tohashmap() { return h; }
vec* mnghashmap::tovec() { return 0; }

mnghashmap::mnghashmap(hashmap* h) : mngcontainer((container*)h) {
	this->h = h;
}

bool mnghashmap::isnull() { return false; }
bool mnghashmap::isbool() { return false; }
bool mnghashmap::isdouble() { return false; }
bool mnghashmap::isstring() { return false; }
bool mnghashmap::isvec() { return false; }
bool mnghashmap::ishashmap() { return true; }

bool mnghashmap::iscontainer() {
	return true;
}

void mnghashmap::release() {
	h->iterate([](tany* tmp) -> bool {
		tmp->release();
		delete tmp;
		return true;
		});

	delete h;
}

string mnghashmap::write(int indent, jindentcfg& cfg) {
	return writeobject(h, indent, cfg);
}

hashmap* mngvec::tohashmap() { return 0; }
vec* mngvec::tovec() { return v; }

mngvec::mngvec(vec* v) : mngcontainer((container*)v) {
	this->v = v;
}

bool mngvec::isnull() { return false; }
bool mngvec::isbool() { return false; }
bool mngvec::isdouble() { return false; }
bool mngvec::isstring() { return false; }
bool mngvec::isvec() { return true; }
bool mngvec::ishashmap() { return false; }

bool mngvec::iscontainer() {
	return true;
}

void mngvec::release() {
	v->iterate([](tany* tmp) -> bool {
		tmp->release();
		delete tmp;
		return true;
		});

	delete v;
}

string mngvec::write(int indent, jindentcfg& cfg) {
	return writearray(v, indent, cfg);
}


bool* mngbool::tobool() { return b; }
double* mngbool::todouble() { return 0; }
string* mngbool::tostring() { return 0; }
vec* mngbool::tovec() { return 0; }
hashmap* mngbool::tohashmap() { return 0; }
container* mngbool::tocontainer() { return 0; }

mngbool::mngbool(bool* b) {
	this->b = b;
}

bool mngbool::isnull() { return false; }
bool mngbool::isbool() { return true; }
bool mngbool::isdouble() { return false; }
bool mngbool::isstring() { return false; }
bool mngbool::isvec() { return false; }
bool mngbool::ishashmap() { return false; }

bool mngbool::iscontainer() {
	return false;
}

void mngbool::release() {
	delete b;
}

string mngbool::write(int indent, jindentcfg& cfg) {
	return writeboolean(*b);
}


bool* mngstring::tobool() { return 0; }
double* mngstring::todouble() { return 0; }
string* mngstring::tostring() { return s; }
vec* mngstring::tovec() { return 0; }
hashmap* mngstring::tohashmap() { return 0; }
container* mngstring::tocontainer() { return 0; }

mngstring::mngstring(string* s) {
	this->s = s;
}

bool mngstring::isnull() { return false; }
bool mngstring::isbool() { return false; }
bool mngstring::isdouble() { return false; }
bool mngstring::isstring() { return true; }
bool mngstring::isvec() { return false; }
bool mngstring::ishashmap() { return false; }

bool mngstring::iscontainer() {
	return false;
}

void mngstring::release() {
	delete s;
}

string mngstring::write(int indent, jindentcfg& cfg) {
	return writestring(*s);
}

bool* mngdouble::tobool() { return 0; }
double* mngdouble::todouble() { return d; }
string* mngdouble::tostring() { return 0; }
vec* mngdouble::tovec() { return 0; }
hashmap* mngdouble::tohashmap() { return 0; }
container* mngdouble::tocontainer() { return 0; }

mngdouble::mngdouble(double* d) {
	this->d = d;
}

bool mngdouble::isnull() { return false; }
bool mngdouble::isbool() { return false; }
bool mngdouble::isdouble() { return true; }
bool mngdouble::isstring() { return false; }
bool mngdouble::isvec() { return false; }
bool mngdouble::ishashmap() { return false; }

bool mngdouble::iscontainer() {
	return false;
}

void mngdouble::release() {
	delete d;
}

string mngdouble::write(int indent, jindentcfg& cfg) {
	return writenumber(*d);
}

string tany::prepend(string s, string p, int n) {
	for (int i = 0; i < n; i++)
		s = p + s;

	return s;
}

string tany::writearray(vec* din, int indent, jindentcfg& cfg) {
	string tmp = "[\n";
	if (indent != 0 && cfg.indentopencurlybrace)
		tmp = "\n" + prepend(tmp, cfg.getindentstr(), indent);

	for (int i = 0; i < (int)din->size() - 1; i++) {
		tmp += prepend((*din)[i]->write(indent + 1, cfg), cfg.getindentstr(), indent);
		tmp += ",\n";

		for (int x = 0; x < (int)cfg.arrayspacing; x++)
			tmp += cfg.indentspacing ? prepend("\n", cfg.getindentstr(), indent + 1) : "\n";
	}

	if (1 <= din->size())
		tmp += prepend((*din)[din->size() - 1]->write(indent + 1, cfg), cfg.getindentstr(), indent + 1);

	return tmp + "\n" + prepend("]", cfg.getindentstr(), indent);
}

string tany::writemember(string key, tany* value, int indent, jindentcfg& cfg) {
	string tmp = "\"" + key + "\"" + cfg.getstuffingaftermemberkey() + ":";

	if (!(value->iscontainer() && cfg.indentopencurlybrace))
		tmp += cfg.getstuffingbeforememberkey();

	return tmp + value->write(indent, cfg);
}

string tany::writeobject(hashmap* hmap, int indent, jindentcfg& cfg) {
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

string tany::writenull() { return "null"; }
string tany::writestring(string s) { return "\"" + s + "\""; }
string tany::writeboolean(bool b) { return b ? "true" : "false"; }
string tany::writenumber(double d) { return to_string(d); }