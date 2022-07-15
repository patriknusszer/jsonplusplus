#include "jvalue.h"

shared_origin::~shared_origin() {
	if (shares == 0)
		return;

	(*shares)--; // lehet -1

	if (*shares == 0) {
		origin->release();
		delete origin;
		delete shares;
	}
}

shared_origin& shared_origin::operator=(const shared_origin& so) {
	if (shares == 0) {
		origin = so.origin;
		shares = so.shares;
		(*shares)++;
	}
	else if (shares != so.shares && shares != 0) {
		(*shares)--;

		if (*shares == 0) {
			origin->release();
			delete origin;
			delete shares;
		}

		shares = so.shares;
		origin = so.origin;
		(*shares)++;
	}

	return *this;
}

shared_origin::shared_origin(tany* a) {
	origin = a;
	shares = new int();
	*shares = 1;
}

jvalue::jvalue(const jvalue& cpy) {
	cfg = cpy.cfg;
	origin = cpy.origin;
}

jvalue::jvalue(tany* a, const shared_origin& so) {
	this->cfg = a;
	this->origin = so;
}

string jvalue::to_string(jindentcfg c) {
	return cfg->write(0, c);
}

jvalue::jvalue(string cfg) {
	int i = 0;
	this->cfg = jsoncore::readvalueat(i, cfg);
	this->origin = shared_origin(this->cfg);
}

shared_origin::shared_origin() {
	origin = 0;
	shares = 0;
}