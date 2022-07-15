#pragma once

#ifndef jobject_h
#define jobject_h

#include "jcontainer.h"

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

class jobject;

class joproxy {
private:
	jobject* ptr;
	string key;
	joproxy(jobject*, string);
	friend class jobject;
public:
	// void* operator=(double num);
	// void* operator=(double num);
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

class jobject : public jcontainer {
private:
	void init();
	hashmap* cache;
	friend class jconvert;
	jobject(tany*, shared_origin& so);
	friend class joproxy;
public:
	jobject(const jobject& cpy);
	bool del(string key);
	uint size();
	jobject(string);
	joproxy operator[](string);
};

#endif