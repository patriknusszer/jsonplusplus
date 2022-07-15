#include "node.h"

node::node(tany* data, linkedlist* owner, node* prev, node* next) {
	this->nxt = next;
	this->prv = prev;
	this->data = data;
	this->owner = owner;
}

node::node(tany* data, linkedlist* owner, string key, uint hash, node* prev, node* next) {
	this->nxt = next;
	this->prv = prev;
	this->data = data;
	this->hash = hash;
	this->key = key;
	this->owner = owner;
}

string node::getkey() { return key; }
tany*& node::getdata() { return data; }
uint node::gethash() { return hash; }
node* node::next() { return nxt; }
node* node::prev() { return prv; }