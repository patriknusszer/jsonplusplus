#ifndef jcontainer_h
#define jcontainer_h

#include "jvalue.h"
#include "container.h"

class jcontainer : public jvalue {
private:
	void init();
	container* cache;
	friend class jconvert;
protected:
	jcontainer(tany* a, const shared_origin& so);
public:
	jcontainer(const jcontainer& cpy);
	virtual uint size();
	jcontainer(string cfg);
};

#endif