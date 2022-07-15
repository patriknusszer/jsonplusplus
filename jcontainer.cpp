#include "jcontainer.h"

void jcontainer::init() {
	if (cfg->iscontainer())
		cache = this->cfg->tocontainer();
	else throw "Error: parsed configuration is not a container";
}

jcontainer::jcontainer(tany* a, const shared_origin& so) : jvalue(a, so) {
	init();
}
 
uint jcontainer::size() { return cache->size(); }

jcontainer::jcontainer(string cfg) : jvalue(cfg) {
	init();
}

jcontainer::jcontainer(const jcontainer& cpy) : jvalue(cpy.cfg, cpy.origin) {
	cache = cpy.cache;
}