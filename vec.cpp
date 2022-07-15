#include "vec.h"

vec::iterator vec::begin() {
	return iterator(base, sz);
}

vec::iterator vec::end() {
	return iterator(base + sz, sz);
}

uint vec::size() { return sz; }

vec::vec(uint cap) {
	sz = 0;
	base = new tany*[this->cap = cap];
}

tany*& vec::operator[](int ind) {
	if (ind >= (int)sz || ind < 0)
		throw "Error: index out of range";

	return base[ind];
}

void vec::insert(tany* dat, int at) {
	if (at >= (int)sz || at < 0)
		throw "Error: index out of range";

	if (cap == sz)
		resize();

	dshift(at);
	base[at] = dat;
	sz++;
}

void vec::erase(int at) {
	ushift(at);
	sz--;
}

void vec::append(tany* dat) {
	if (cap == sz)
		resize();

	base[sz++] = dat;
}

vec::~vec() {
	delete[] base;
}

void vec::resize() {
	tany** nbase = new tany*[cap *= 2];

	for (int i = 0; i < (int)sz; i++)
		nbase[i] = base[i];

	delete[] base;
	base = nbase;
}

void vec::ushift(int at) {
	for (int i = at + 1; i < (int)sz; i++)
		base[i - 1] = base[i];
}

void vec::dshift(int at) {
	for (int i = sz; i > (int)at; i--)
		base[i] = base[i - 1];
}

bool vec::iterator::operator!=(const iterator& it) const {
	return ptr != it.ptr;
}

bool vec::iterator::operator==(const iterator& it) const {
	return ptr == it.ptr;
}

vec::iterator& vec::iterator::operator++() {
	if (ptr - base != sz)
		ptr++;

	return *this;
}

tany*& vec::iterator::operator*() const {
	if (ptr - base == sz)
		throw "Error: end iterator can not be dereferenced";

	return *ptr;
}

tany** vec::iterator::operator->() const {
	if (ptr - base == sz)
		throw "Error: end iterator can not be dereferenced";

	return ptr;
}