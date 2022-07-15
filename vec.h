#ifndef vec_h
#define vec_h

#include "container.h"

typedef unsigned int uint;

using namespace std;

class vec : public container {
private:
	uint sz;
	uint cap;
	tany** base;
	void resize();
	void ushift(int at);
	void dshift(int at);
public:
	class iterator {
	private:
		uint sz;
		tany** base;
		tany** ptr;
	public:
		iterator(
			tany** base,
			uint sz
		) : sz(sz),
			base(base),
			ptr(base)
		{
			
		}

		bool operator!=(const iterator& it) const;
		bool operator==(const iterator& it) const;
		iterator& operator++();
		tany*& operator*() const;
		tany** operator->() const;
	};

	iterator begin();
	iterator end();

	void iterate(function<bool(tany*)> cb) override {
		iterator it = begin();

		for (; it != end(); ++it)
			if (!cb(*it))
				return;
	}

	uint size();
	vec(uint cap = 20);
	tany*& operator[](int ind);
	void insert(tany* dat, int at);
	void erase(int at);
	void append(tany* dat);
	~vec();
};

#endif