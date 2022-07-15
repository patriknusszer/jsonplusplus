#ifndef jvalue_h
#define jvalue_h

#include <iostream>
#include "tany.h"
#include "jindentcfg.h"
#include "jsoncore.h"

using namespace std;

class shared_origin {
private:
	tany* origin;
	int* shares;
public:
	shared_origin();
	shared_origin(tany* a);
	shared_origin& operator=(const shared_origin& so);
	~shared_origin();
};

class jleaf;
class jcontainer;
class jobject;
class jarray;

class jvalue {
protected:
	jvalue(tany* a, const shared_origin& so);
	tany* cfg;
	shared_origin origin;
	friend class jobject;
	friend class jarray;
	friend class jconvert;
	friend class joproxy;
	friend class japroxy;
public:
	jvalue(const jvalue& cpy);
	string to_string(jindentcfg c);
	jvalue(string cfg);
};



#endif