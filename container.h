#ifndef container_h
#define container_h

#include <functional>

typedef unsigned int uint;

using namespace std;

class tany;

class container {
protected:
	uint sz;
public:
	virtual void iterate(function<bool(tany*)> cb) = 0;
	uint size() { return sz; }
	virtual ~container() {}
};

#endif