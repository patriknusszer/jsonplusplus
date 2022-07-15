#pragma once

#ifndef jarray_h
#define jarray_h

#include "jcontainer.h"
#include "jobject.h"
#include "jleaf.h"

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

class jarray;

class japroxy {
private:
	jarray* ptr;
	int ind;
	japroxy(jarray*, int);
	friend class jarray;
public:
	void* operator=(double);
	void* operator=(int);
	void* operator=(short);
	void* operator=(long);
	void* operator=(ulong);
	void* operator=(uint);
	void* operator=(ushort);
	void* operator=(string);
	void* operator=(bool);
	void* operator=(void*);
	operator jvalue() const;
};

class jarray : public jcontainer {
private:
	void init();
	vec* cache;
	friend class jconvert;
	jarray(tany*, const shared_origin&);
	friend class japroxy;
public:
	bool del(int ind);
	uint size();
	jarray(string);
	jarray(const jarray& cpy);
	japroxy operator[](int);
};

#endif
