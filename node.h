#ifndef node_h
#define node_h

#include<iostream>

using namespace std;

typedef unsigned int uint;

class linkedlist;
class tany;

// readonly class by design
class node {
private:
	string key;
	tany* data;
	uint hash;
	node* nxt;
	node* prv;
	linkedlist* owner;
	node(tany* data, linkedlist* owner, node* prev = 0, node* next = 0);
	node(tany* data, linkedlist* owner, string key, uint hash, node* prev = 0, node* next = 0);
	friend class linkedlist;
public:
	string getkey();
	tany*& getdata();
	uint gethash();
	node* next();
	node* prev();
};

#endif