#include "jarray.h"

void jarray::init() {
	if (this->cfg->isvec())
		cache = this->cfg->tovec();
	else throw "Error: parsed configuratin is not an object";
}

jarray::jarray(tany* a, const shared_origin& so) : jcontainer(a, so) { init();}

jarray::jarray(string cfg) : jcontainer(cfg) { init(); }

uint jarray::size() { return cache->size(); }

japroxy jarray::operator[](int ind) {
	return japroxy(this, ind);
}

void* japroxy::operator=(int i32) {
	tany* tmp = ptr->cache->operator[](ind);
	tmp->release();
	delete tmp;
	ptr->cache->operator[](ind) = new mngdouble(new double(i32));
	return 0;
}

void* japroxy::operator=(short i16) {
	tany* tmp = ptr->cache->operator[](ind);
	tmp->release();
	delete tmp;
	ptr->cache->operator[](ind) = new mngdouble(new double(i16));
	return 0;
}

void* japroxy::operator=(ulong ui64) {
	tany* tmp = ptr->cache->operator[](ind);
	tmp->release();
	delete tmp;
	ptr->cache->operator[](ind) = new mngdouble(new double(ui64));
	return 0;
}

void* japroxy::operator=(uint ui32) {
	tany* tmp = ptr->cache->operator[](ind);
	tmp->release();
	delete tmp;
	ptr->cache->operator[](ind) = new mngdouble(new double(ui32));
	return 0;
}

void* japroxy::operator=(ushort ui16) {
	tany* tmp = ptr->cache->operator[](ind);
	tmp->release();
	delete tmp;
	ptr->cache->operator[](ind) = new mngdouble(new double(ui16));
	return 0;
}

void* japroxy::operator=(double d) {
	tany* tmp = ptr->cache->operator[](ind);
	tmp->release();
	delete tmp;
	ptr->cache->operator[](ind) = new mngdouble(new double(d));
	return 0;
}

void* japroxy::operator=(long i64) {
	tany* tmp = ptr->cache->operator[](ind);
	tmp->release();
	delete tmp;
	ptr->cache->operator[](ind) = new mngdouble(new double(i64));
	return 0;
}

void* japroxy::operator=(string str) {
	tany* tmp = ptr->cache->operator[](ind);
	tmp->release();
	delete tmp;
	ptr->cache->operator[](ind) = new mngstring(new string(str));
	return 0;
}

void* japroxy::operator=(bool b) {
	tany* tmp = ptr->cache->operator[](ind);
	tmp->release();
	delete tmp;
	ptr->cache->operator[](ind) = new mngbool(new bool(b));
	return 0;
}

void* japroxy::operator=(void* nulladdr) {
	tany* tmp = ptr->cache->operator[](ind);
	tmp->release();
	delete tmp;
	ptr->cache->operator[](ind) = new mngnull();
	return 0;
}

japroxy::operator jvalue() const {
	return jvalue(ptr->cache->operator[](ind), ptr->origin);
}

japroxy::japroxy(jarray* ptr, int ind) {
	this->ptr = ptr;
	this->ind = ind;
}
bool jarray::del(int ind) {
	if ((int)cache->size() <= ind || ind < 0)
		return false;

	tany* tmp = cache->operator[](ind);
	tmp->release();
	delete tmp;
	cache->erase(ind);
	return true;
}

jarray::jarray(const jarray& cpy) : jcontainer(cpy.cfg, cpy.origin) {
	cache = cpy.cache;
}