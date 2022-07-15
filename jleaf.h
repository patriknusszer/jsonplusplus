#pragma once

#ifndef jleaf_h
#define jleaf_h

#include "jvalue.h"

class jleaf : public jvalue {
private:
	void init();
	jleaf(tany* a, shared_origin& so);
	friend class jconvert;
public:
	jleaf(const jleaf& cpy);
	jleaf(string cfg);
};

#endif