#pragma once

using namespace std;

#include "hashmap.h"
#include "vec.h"
#include "jindentcfg.h"



class tany {
public:
	static string prepend(string s, string p, int n);
	static string writearray(vec* din, int indent, jindentcfg& cfg);
	static string writemember(string key, tany* value, int indent, jindentcfg& cfg);
	static string writeobject(hashmap* hmap, int indent, jindentcfg& cfg);
	static string writenull();
	static string writestring(string s);
	static string writeboolean(bool b);
	static string writenumber(double d);


	virtual bool isbool() = 0;
	virtual bool isnull() = 0;
	virtual bool isdouble() = 0;
	virtual bool isstring() = 0;
	virtual bool isvec() = 0;
	virtual bool ishashmap() = 0;
	virtual bool iscontainer() = 0;
	virtual bool* tobool() = 0;
	virtual double* todouble() = 0;
	virtual string* tostring() = 0;
	virtual vec* tovec() = 0;
	virtual hashmap* tohashmap() = 0;
	virtual container* tocontainer() = 0;
	virtual void release() = 0;
	virtual string write(int indent, jindentcfg& cfg) = 0;
	virtual ~tany() {}
};

class mngnull : public tany {
private:
public:
	bool* tobool();
	double* todouble();
	string* tostring();
	vec* tovec();
	hashmap* tohashmap();
	container* tocontainer();
	bool isnull() override;
	bool isbool() override;
	bool isdouble() override;
	bool isstring() override;
	bool isvec() override;
	bool ishashmap() override;
	bool iscontainer() override;
	void release() override;
	string write(int indent, jindentcfg& cfg);
};

class mngcontainer : public tany {
private:
	container* c;
public:
	bool* tobool();
	double* todouble();
	string* tostring();
	container* tocontainer();
	mngcontainer(container* c);
	bool isnull() override;
	bool isbool() override;
	bool isdouble() override;
	bool isstring() override;
	bool isvec() override;
	bool ishashmap() override;
	bool iscontainer() override;
};

class mnghashmap : public mngcontainer {
private:
	hashmap* h;
public:
	hashmap* tohashmap();
	vec* tovec();
	mnghashmap(hashmap* h);
	bool isnull() override;
	bool isbool() override;
	bool isdouble() override;
	bool isstring() override;
	bool isvec() override;
	bool ishashmap() override;
	bool iscontainer() override;
	void release() override;
	string write(int indent, jindentcfg& cfg) override;
};

class mngvec : public mngcontainer {
private:
	vec* v;
public:
	hashmap* tohashmap();
	vec* tovec();
	mngvec(vec* v);

	bool isnull() override;
	bool isbool() override;
	bool isdouble() override;
	bool isstring() override;
	bool isvec() override;
	bool ishashmap() override;
	bool iscontainer() override;
	void release() override;
	string write(int indent, jindentcfg& cfg) override;
};

class mngbool : public tany {
private:
	bool* b;
public:
	bool* tobool();
	double* todouble();
	string* tostring();
	vec* tovec();
	hashmap* tohashmap();
	container* tocontainer();
	mngbool(bool* b);
	bool isnull();
	bool isbool();
	bool isdouble();
	bool isstring();
	bool isvec();
	bool ishashmap();
	bool iscontainer() override;
	void release() override;
	string write(int indent, jindentcfg& cfg) override;
};

class mngstring : public tany {
private:
	string* s;
public:
	bool* tobool();
	double* todouble();
	string* tostring();
	vec* tovec();
	hashmap* tohashmap();
	container* tocontainer();
	mngstring(string* s);
	bool isnull() override;
	bool isbool() override;
	bool isdouble() override;
	bool isstring() override;
	bool isvec() override;
	bool ishashmap() override;
	bool iscontainer() override;
	void release() override;
	string write(int indent, jindentcfg& cfg) override;
};


class mngdouble : public tany {
private:
	double* d;
public:
	bool* tobool();
	double* todouble();
	string* tostring();
	vec* tovec();
	hashmap* tohashmap();
	container* tocontainer();
	mngdouble(double* d);
	bool isnull() override;
	bool isbool() override;
	bool isdouble() override;
	bool isstring() override;
	bool isvec() override;
	bool ishashmap() override;
	bool iscontainer() override;
	void release() override;
	string write(int indent, jindentcfg& cfg) override;
};