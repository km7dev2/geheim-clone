/**
* Include the Geode headers.
*/
#include <Geode/DefaultInclude.hpp>
#include <network/HttpRequest.h>
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

#include <Geode/modify/GManager.hpp>
#include <filesystem>

#include "http.hpp"
#include "profile.hpp"
#include "str.hpp"

using namespace geode::prelude;

void CCHTTPRequestSetUrlHook(CCHttpRequest* self, const char* url) {
	log::debug("Requesting HTTP url '{}'", url);

	std::string newUrl = url;

	if (activeProfile != DEFAULT_PROFILE && newUrl.find("www.boomlings.com/database") != std::string::npos) {
		strReplace(newUrl, "www.boomlings.com/database", profiles[activeProfile].mURL);

		log::debug("Overriden HTTP request to use url '{}'", newUrl);
	} else if (newUrl == "https://www.google.com") {
		// Robert Nicholas Christian Topala must be SOBBING right now (I messed up his online check for performance reasons :trol:)
		newUrl = "127.0.0.1"; // Nah, we connecting to our own computers in this house
		log::debug("Overriden HTTP request to use url '{}'", newUrl);
	}

	// Horrifying
	reinterpret_cast<void(__thiscall*)(CCHttpRequest*, const char*)>(CCHTTPRequestSetUrlAddress)(self, newUrl.c_str());
}
