#include "linkedlist.h"

bool linkedlist::iterator::operator!=(const iterator& it) const {
	return ptr != it.ptr;
}

bool linkedlist::iterator::operator==(const iterator& it) const {
	return ptr == it.ptr;
}

linkedlist::iterator& linkedlist::iterator::operator++() {
	if (ptr != 0)
		ptr = ptr->next();

	return *this;
}

node& linkedlist::iterator::operator*() const {
	if (ptr == 0)
		throw "Error: end iterator can not be dereferenced";

	return *ptr;
}

linkedlist::iterator::operator node* () const {
	if (ptr == 0)
		throw "Error: end iterator can not be dereferenced";

	return ptr;
}

node* linkedlist::iterator::operator->() const {
	if (ptr == 0)
		throw "Error: end iterator can not be dereferenced";

	return ptr;
}

linkedlist::iterator::iterator(node* ptr) {
	this->ptr = ptr;
}

linkedlist::iterator linkedlist::begin() {
	return iterator(head);
}

linkedlist::iterator linkedlist::end() {
	return iterator(0);
}

void traverse() {

}

linkedlist::linkedlist() {
	sz = 0;
	tail = head = 0;
}

void linkedlist::append(tany*& data, string key, uint hash) {
	if (head == 0)
		tail = head = new node(data, this, key, hash);
	else
		tail = tail->nxt = new node(data, this, key, hash, tail);
}

void linkedlist::append(tany*& data) {
	if (head == 0)
		tail = head = new node(data, this);
	else
		tail = new node(data, this, tail);
}

node* linkedlist::find(const string& key) const {
	node* n = head;

	for (; n != 0; n = n->next())
		if (n->key == key)
			return n;

	return 0;
}

void linkedlist::del(node* n) {
	if (n->owner != this)
		throw "Error: can not delete a node of another linked list";

	if (n->prv != 0)
		n->prv->nxt = n->nxt;
	else
		head = n->nxt;

	if (n->nxt != 0)
		n->nxt->prv = n->prv;
	else
		tail = n->prv;

	delete n;
}

linkedlist::~linkedlist() {
	iterator it = begin();

	while (it != end()) {
		node* cur = it;
		++it;
		delete cur;
	}
}