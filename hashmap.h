#ifndef hashmap_h
#define hashmap_h

// a naive, limited unordered_map reimplementation

#include "linkedlist.h"
#include "node.h"
#include "container.h"

typedef unsigned int uint;

class hashmap;

class proxy {
private:
    string key;
    hashmap* ptr;
    friend class hashmap;
public:
    proxy(string key, hashmap* hm) : key(key), ptr(hm) {}
    void* operator=(tany* a);
    operator tany*& ();
};

class hashmap : public container {
private:
	uint bsz;
	linkedlist* buckets;
    static uint rollhash32(const string& key, int b, int m);
    static uint hashof(const string& key);
    static void calc(const string& key, uint bsz, uint& hash, int& bi);
    void resize();
public:
    class iterator
    {
    private:
        linkedlist* buckets;
        linkedlist::iterator it;
        uint bsz;
        int bi;
        uint i;
        uint sz;
    public:
        iterator(
            linkedlist* buckets,
            uint bsz,
            uint sz,
            uint i
        ) : buckets(buckets),
            bsz(bsz),
            bi(-1),
            i(i),
            sz(sz)
        
        {
            do it = buckets[++bi].begin();
            while (it == buckets[bi].end());
        }

        bool operator!=(const iterator& it) const;
        bool operator==(const iterator& it) const;
        iterator& operator++();
        operator node* () const;
        node* operator->() const;
    };

    iterator begin();
    iterator end();
    void iterate(function<bool(tany*)> cb) override;
    bool insert(const string& key, tany* value);
    tany** get(const string& key) const;
    hashmap();
    proxy operator[](const string& key);
    bool del(string key);
    ~hashmap();
};

#endif /* hashmap_h */