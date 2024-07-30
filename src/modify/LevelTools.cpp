#include <Geode/Geode.hpp>

#include <Geode/binding/LevelTools.hpp>

#include "../profile.hpp"

using namespace geode::prelude;

class $modify(LevelTools) {
	bool verifyLevelIntegrity(gd::string p0, int p1) {
		if (activeProfile == "default")
			return LevelTools::verifyLevelIntegrity(p0, p1);

		// Hijack workaround for custom main level support... eventually
		return true;
	}
};
