#pragma once

#include "jleaf.h"
#include "jobject.h"
#include "jarray.h"
#include "jcontainer.h"

// intended for safe downcasting
class jconvert {
public:
	static bool try_jobject(jvalue in, jobject& out);
	static jobject to_jobject(jvalue jv);
	static bool try_jcontainer(jvalue in, jcontainer& out);
	static jcontainer to_jcontainer(jvalue jv);
	static bool try_jarray(jvalue jv, jvalue& out);
	static jarray to_jarray(jvalue jv);
	static bool try_jleaf(jvalue in, jvalue& out);
	static jleaf to_jleaf(jvalue jv);
	static bool try_doubleptr(jvalue in, double** out);
	static bool try_double(jvalue in, int* out);
	static double* to_doubleptr(jvalue jv);
	static double to_double(jvalue jv);
	static bool try_stringptr(jvalue in, string** out);
	static bool try_string(jvalue in, string* out);
	static string* to_stringptr(jvalue jv);
	static string to_string(jvalue jv);
	static bool try_boolptr(jvalue in, bool** out);
	static bool try_bool(jvalue in, bool* out);
	static bool* to_boolptr(jvalue jv);
	static bool to_bool(jvalue jv);
	static bool isnull(jvalue jv);
};

