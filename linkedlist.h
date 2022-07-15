#ifndef linkedlist_h
#define linkedlist_h

#include "node.h"
#include "container.h"

typedef unsigned int uint;

class linkedlist : public container {
private:
	node* head;
	node* tail;
public:
	class iterator {
	private:
		node* ptr;
		iterator(node* ptr);
		friend class linkedlist;
	public:
		iterator() {}
		bool operator!=(const iterator& it) const;
		bool operator==(const iterator& it) const;
		iterator& operator++();
		node& operator*() const;
		operator node* () const;
		node* operator->() const;
	};

	iterator begin();
	iterator end();

	void iterate(function<bool(tany*)> cb) override {
		iterator it = begin();

		for (; it != end(); ++it)
			if (!cb(it->data))
				return;
	}

	linkedlist();
	void append(tany*& data, string key, uint hash);
	void append(tany*& data);
	node* find(const string& key) const;
	void del(node* n);
	~linkedlist();
};

#endif