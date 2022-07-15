#include "jleaf.h"

void jleaf::init() {
	if (this->cfg->iscontainer())
		throw "Error: parsed configuration is not jleaf";
}

jleaf::jleaf(tany* a, shared_origin& so) : jvalue(a, so) { init(); }

jleaf::jleaf(string cfg) : jvalue(cfg) {
	init();
}

jleaf::jleaf(const jleaf& cpy) : jvalue(cpy.cfg, cpy.origin) {}