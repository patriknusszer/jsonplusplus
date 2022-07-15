#include "jobject.h"

void jobject::init() {
	if (this->cfg->ishashmap())
		cache = this->cfg->tohashmap();
	else throw "Error: parsed configuratin is not an object";
}

jobject::jobject(tany* a, shared_origin& so) : jcontainer(a, so) { init(); }

jobject::jobject(string cfg) : jcontainer(cfg) { init(); }

uint jobject::size() { return cache->size(); }

joproxy jobject::operator[](string key) {
	return joproxy(this, key);
}

void* joproxy::operator=(int i32) {
	tany** apt;

	if ((apt = ptr->cache->get(key)) != 0)
	{
		(*apt)->release();
		delete* apt;
	}

	ptr->cache->insert(key, new mngdouble(new double(i32)));
	return 0;
}

void* joproxy::operator=(short i16) {
	tany** apt;

	if ((apt = ptr->cache->get(key)) != 0)
	{
		(*apt)->release();
		delete* apt;
	}

	ptr->cache->insert(key, new mngdouble(new double(i16)));
	return 0;
}

void* joproxy::operator=(ulong ui64) {
	tany** apt;

	if ((apt = ptr->cache->get(key)) != 0)
	{
		(*apt)->release();
		delete* apt;
	}

	ptr->cache->insert(key ,new mngdouble(new double(ui64)));
	return 0;
}

void* joproxy::operator=(uint ui32) {
	tany** apt;

	if ((apt = ptr->cache->get(key)) != 0)
	{
		(*apt)->release();
		delete* apt;
	}

	ptr->cache->insert(key, new mngdouble(new double(ui32)));
	return 0;
}

void* joproxy::operator=(ushort ui16) {
	tany** apt;

	if ((apt = ptr->cache->get(key)) != 0)
	{
		(*apt)->release();
		delete* apt;
	}

	ptr->cache->insert(key, new mngdouble(new double(ui16)));
	return 0;
}

void* joproxy::operator=(double d) {
	tany** apt;

	if ((apt = ptr->cache->get(key)) != 0)
	{
		(*apt)->release();
		delete* apt;
	}

	ptr->cache->insert(key, new mngdouble(new double(d)));
	return 0;
}

void* joproxy::operator=(long i64) {
	tany** apt;

	if ((apt = ptr->cache->get(key)) != 0)
	{
		(*apt)->release();
		delete* apt;
	}

	ptr->cache->insert(key, new mngdouble(new double(i64)));
	return 0;
}

void* joproxy::operator=(string str) {
	tany** apt;

	if ((apt = ptr->cache->get(key)) != 0)
	{
		(*apt)->release();
		delete* apt;
	}

	ptr->cache->insert(key, new mngstring(new string(str)));
	return 0;
}

void* joproxy::operator=(bool b) {
	tany** apt;

	if ((apt = ptr->cache->get(key)) != 0)
	{
		(*apt)->release();
		delete* apt;
	}

	ptr->cache->insert(key, new mngbool(new bool(b)));
	return 0;
}

void* joproxy::operator=(void* nulladdr) {
	ptr->cache->insert(key, new mngnull());
	return 0;
}

joproxy::operator jvalue() const {
	return jvalue(ptr->cache->operator[](key), ptr->origin);
}

joproxy::joproxy(jobject* ptr, string key) {
	this->ptr = ptr;
	this->key = key;
}

jobject::jobject(const jobject& cpy) : jcontainer(cpy.cfg, cpy.origin) {
	init();
	cache = cpy.cache;
}

bool jobject::del(string key) {
	tany** apt;

	if ((apt = cache->get(key)) == 0)
		return false;

	(*apt)->release();
	delete(*apt);
	cache->del(key);
	return true;
}