#include <Geode/Geode.hpp>

#include <Geode/modify/CCFileUtils.hpp>

using namespace geode::prelude;

#include "../profile.hpp"
#include "../str.hpp"

// TODO: get better
/*
class $modify(CCFileUtils) {
	unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize) {
		//log::debug("getFileData: '{}', '{}'", (std::string)pszFileName, (std::string)pszFileName);

		std::string replace = pszFileName;

		if (replace.find("Resources/levels") != std::string::npos) {
			strReplace(replace, "Resources/levels", fmt::format("Resources/{}levels", activeProfile != DEFAULT_PROFILE ? activeProfile + "-" : ""));

			log::debug("try overwrite to '{}'", replace);

			if (!(std::filesystem::exists(replace) && std::filesystem::is_regular_file(replace))) replace = pszFileName;
		}

		return CCFileUtils::getFileData(replace.c_str(), pszMode, pSize);
	}

	void loadFilenameLookupDictionaryFromFile(const char* filename) {
		log::debug("DictionaryFromFile: '{}'", (std::string)filename);

		return CCFileUtils::loadFilenameLookupDictionaryFromFile(filename);
	}

	void setFilenameLookupDictionary(CCDictionary* pFilenameLookupDict) {
		log::debug("loopup sniff start");

		auto keys = pFilenameLookupDict->allKeys();
		for (int i; i < pFilenameLookupDict->count(); i++) {
			log::debug("Key '{}' with value '{}'", std::string(keys->stringAtIndex(i)->getCString()), std::string(pFilenameLookupDict->valueForKey(keys->stringAtIndex(i)->getCString())->getCString()));
		}

		log::debug("loopup sniff end");

		return CCFileUtils::setFilenameLookupDictionary(pFilenameLookupDict);
	}
};
*/
