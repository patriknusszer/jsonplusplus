#include "jconvert.h"
#include "tany.h"

bool jconvert::try_jobject(jvalue in, jobject& out) {
	if (!in.cfg->ishashmap())
		return false;

	out = jobject(in.cfg, in.origin);
	return true;
}

jobject jconvert::to_jobject(jvalue jv) {
	if (!jv.cfg->ishashmap())
		throw "Error: jvalue is not a jobject";

	return jobject(jv.cfg, jv.origin);
}

bool jconvert::try_jcontainer(jvalue in, jcontainer& out) {
	if (!in.cfg->iscontainer())
		return false;

	out = jcontainer(in.cfg, in.origin);
	return true;
}

jcontainer jconvert::to_jcontainer(jvalue jv) {
	if (!jv.cfg->iscontainer())
		throw "Error: jvalue is not a jcontainer";

	return jcontainer(jv.cfg, jv.origin);
}

bool jconvert::try_jarray(jvalue jv, jvalue& out) {
	if (!jv.cfg->isvec())
		return false;

	out = jarray(jv.cfg, jv.origin);
	return true;
}

jarray jconvert::to_jarray(jvalue jv) {
	if (!jv.cfg->isvec())
		throw "Error: jvalue is not a jarray";

	return jarray(jv.cfg, jv.origin);
}

bool jconvert::try_jleaf(jvalue in, jvalue& out) {
	if (in.cfg->iscontainer())
		return false;

	out = jleaf(in.cfg, in.origin);
	return true;
}

jleaf jconvert::to_jleaf(jvalue jv) {
	if (jv.cfg->iscontainer())
		throw "Error: jvalue is not a jleaf";

	return jleaf(jv.cfg, jv.origin);
}

bool jconvert::try_doubleptr(jvalue in, double** out) {
	if (!in.cfg->isdouble())
		return false;

	*out = in.cfg->todouble();
	return true;
}

bool jconvert::try_double(jvalue in, int* out) {
	if (!in.cfg->isdouble())
		return false;

	*out = *in.cfg->todouble();
	return true;
}

double* jconvert::to_doubleptr(jvalue jv) {
	if (!jv.cfg->isdouble())
		throw "Error: jleaf is not a number";

	return jv.cfg->todouble();
}

double jconvert::to_double(jvalue jv) {
	return *to_doubleptr(jv);
}

bool jconvert::try_stringptr(jvalue in, string** out) {
	if (!in.cfg->isstring())
		return false;

	*out = in.cfg->tostring();
	return true;
}

bool jconvert::try_string(jvalue in, string* out) {
	if (!in.cfg->isstring())
		return false;

	*out = *in.cfg->tostring();
	return true;
}

string* jconvert::to_stringptr(jvalue jv) {
	if (!jv.cfg->isstring())
		throw "Error: jleaf is not a string";

	return jv.cfg->tostring();
}

string jconvert::to_string(jvalue jv) {
	return *to_stringptr(jv);
}

bool jconvert::try_boolptr(jvalue in, bool** out) {
	if (!in.cfg->isbool())
		return false;

	*out = in.cfg->tobool();
	return true;
}

bool jconvert::try_bool(jvalue in, bool* out) {
	if (!in.cfg->isbool())
		return false;

	*out = *in.cfg->tobool();
	return true;
}

bool* jconvert::to_boolptr(jvalue jv) {
	if (!jv.cfg->isbool())
		throw "Error: jleaf is not a bool";

	return jv.cfg->tobool();
}

bool jconvert::to_bool(jvalue jv) {
	return *to_boolptr(jv);
}

bool jconvert::isnull(jvalue jv) {
	return jv.cfg->isnull();
}

