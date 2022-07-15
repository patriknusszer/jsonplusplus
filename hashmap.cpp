#include "hashmap.h"

uint hashmap::rollhash32(const string& key, int b, int m) {
    uint hash = 0;
    uint coeff = 1;

    for (uint i = 0; i < key.size(); i++) {
        hash = (hash + key[i] * coeff) % m;
        coeff *= b;
        coeff %= m;
    }

    return hash;
}

uint hashmap::hashof(const string& key) {
    return rollhash32(key, 257, 1761471161);
}

void hashmap::calc(const string& key, uint bsz, uint& hash, int& bi) {
    hash = hashof(key);
    bi = hash % bsz;
}


bool hashmap::insert(const string& key, tany* value) {
    uint hash;
    int bi;
    calc(key, bsz, hash, bi);
    node* n;

    if ((n = buckets[bi].find(key)) != 0) {
        n->getdata() = value;
        return false;
    }

    if (sz == bsz * 2) resize();

    buckets[bi].append(value, key, hash);
    sz++;
    return true;
}

void hashmap::resize() {
    uint nsz = bsz * 2;
    linkedlist* nbuckets = new linkedlist[nsz];

    for (uint i = 0; i < bsz; i++) {
        linkedlist::iterator it = buckets[i].begin();

        while (it != buckets[i].end()) {
            nbuckets[it->gethash() % nsz].append(it->getdata(), it->getkey(), it->gethash());
            ++it;
        }
    }

    bsz = nsz;
    delete[] buckets;
    buckets = nbuckets;
}

tany** hashmap::get(const string& key) const {
    uint hash;
    int bi;
    calc(key, bsz, hash, bi);
    node* ptr;

    if ((ptr = buckets[bi].find(key)) == 0)
        return 0;

    return &ptr->getdata();
}

hashmap::hashmap() {
    buckets = new linkedlist[bsz = 5];
    sz = 0;
}

proxy hashmap::operator[](const string& key) {
    return proxy(key, this);
}

bool hashmap::del(string key) {
    uint hash;
    int bi;
    calc(key, bsz, hash, bi);
    node* p = buckets[bi].find(key);

    if (p == 0)
        return false;

    buckets[bi].del(p);
    sz--;
    return true;
}

void* proxy::operator=(tany* a) {
    ptr->insert(key, a);
    return 0;
}

proxy::operator tany*& () {
    tany** p = ptr->get(key);

    if (p == 0)
        throw "Error: queried entity not found";

    return *p;
}


hashmap::~hashmap() {
    delete[] buckets;
}

hashmap::iterator hashmap::begin() {
    return iterator(buckets, bsz, sz, 0);
}

hashmap::iterator hashmap::end() {
    return iterator(buckets, bsz, sz, sz);
}

bool hashmap::iterator::operator!=(const iterator& it) const {
    return i != it.i;
}

bool hashmap::iterator::operator==(const iterator& it) const {
    return i == it.i;
}

hashmap::iterator& hashmap::iterator::operator++() {
    if (i < sz - 1) {
        i++;
        ++it;

        while (it == buckets[bi].end())
            it = buckets[++bi].begin();
    }
    else if (i == sz - 1) i = sz;

    return *this;
}

hashmap::iterator::operator node* () const {
    return it.operator node*();
}

node* hashmap::iterator::operator->() const {
    return it.operator->();
}

void hashmap::iterate(function<bool(tany*)> cb) {
    iterator it = begin();

    for (; it != end(); ++it) {
        if (!cb(it->getdata()))
            return;
    }
}