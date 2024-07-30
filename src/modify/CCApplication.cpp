#include <Geode/Geode.hpp>

#include <Geode/modify/CCApplication.hpp>

#include "../profile.hpp"
#include "../str.hpp"

using namespace geode::prelude;

class $modify(CCApplication) {
	void openURL(const char* url) {
		std::string newUrl = url;

		if (activeProfile != DEFAULT_PROFILE && newUrl.find("www.boomlings.com/database") != std::string::npos) {
			strReplace(newUrl, "www.boomlings.com/database", profiles[activeProfile].mURL);

			log::debug("Overriden HTTP request to use url '{}'", newUrl);
		}

		CCApplication::openURL(newUrl.c_str());
	}
};
