/**
* Include the Geode headers.
*/
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/binding/GameStatsManager.hpp>
#include <Geode/loader/Dirs.hpp>
#include <network/HttpRequest.h>

#include <Geode/modify/GManager.hpp>
#include <Geode/modify/GameStatsManager.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CCApplication.hpp>
#include <Geode/modify/GJAccountManager.hpp>
#include <Geode/modify/GameLevelManager.hpp>
#include <Geode/modify/CCFileUtils.hpp>

#include <algorithm>
#include <filesystem>
#include <matjson.hpp>

#include "Geode/GeneratedPredeclare.hpp"
#include "Geode/cocos/platform/CCFileUtils.h"
#include "Geode/loader/Log.hpp"

#include "http.hpp"
#include "profile.hpp"
#include "psprofilelayer.hpp"
#include "str.hpp"

/**
* Brings cocos2d and all Geode namespaces
* to the current scope.
*/
using namespace geode::prelude;

std::map<std::string, StringPair> profiles {
	{DEFAULT_PROFILE, {"Official (Default)", "www.boomlings.com/database"}}
};

std::vector<ProfileInfo> customProfiles; //Mod::get()->getSavedValue<std::vector<ProfileInfo>>("savedProfiles", {});

std::string activeProfile = Mod::get()->getSavedValue<std::string>("lastProfile", DEFAULT_PROFILE);

void loadProfiles() {
	auto path = Mod::get()->getSaveDir().string() + "/.servers";
	log::debug(fmt::format("Server data save path: {}", path));

	if (std::filesystem::exists(path)) {
		log::debug("Server data save path exists!");
		std::ifstream input(path, std::ios::in);

		std::string line;

		int count = 0;

		while (std::getline(input, line)) {
			auto splitted = strSplit(line, "|");

			log::debug("Parsing line with splitsize '{}': \"{}\"", splitted.size(), line);

			for (auto ent : splitted) {
				log::debug("Ent val: {}", ent);
			}

			if (splitted.size() >= 3) {
				std::string id = splitted[0], displayName = splitted[1], url = splitted[2];

				// Remove whitespace on non-display name entries
				id.erase(std::remove_if(id.begin(), id.end(), [](unsigned char x) { return std::isspace(x); }), id.end());
				url.erase(std::remove_if(url.begin(), url.end(), [](unsigned char x) { return std::isspace(x); }), url.end());

				log::debug("Loading entry {} with data [{}, {}, {}]", count++, id, displayName, url);
				customProfiles.emplace_back(ProfileInfo {id, StringPair {displayName, url}});
				profiles.emplace(id, StringPair {displayName, url});
			}
		}

		return;
	}
}

void saveProfiles() {
	auto path = Mod::get()->getSaveDir().string() + "/.servers";
	std::ofstream output(path);
	int entry = 0;
	for (auto profile : customProfiles) {
		log::debug("Saving entry {} with data [{}, {}, {}]", entry++, profile.id, profile.pair.mName, profile.pair.mURL);
		output << fmt::format("{}|{}|{}", profile.id, profile.pair.mName, profile.pair.mURL) << std::endl;
	}

	output.close();
}

class $modify(GeheimMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init())
			return false;

		auto winSize = CCDirector::get()->getWinSize();

		auto spr = CCSprite::create("GJ_swapServerBtn.png"_spr);

		auto btn = CCMenuItemSpriteExtra::create(
			spr, this, menu_selector(GeheimMenuLayer::onServerButtonClick)
		);

		btn->setID("geheim-serverbtn");

		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(btn);
		menu->updateLayout();

		if (activeProfile != DEFAULT_PROFILE) {
			// :3
			CCNode* robertNicholasChristianTopalaMainMenuTitleCCMenuDeluxeFeaturingDanteFromTheDevilMayCrySeriesAndKnuckles = this->getChildByID("main-title");
			CCLabelBMFont* label = CCLabelBMFont::create(((std::string)"On " + profiles[activeProfile].mName).c_str(), "bigFont.fnt");
			label->setPosition({winSize.width / 2.5f, -7});

			robertNicholasChristianTopalaMainMenuTitleCCMenuDeluxeFeaturingDanteFromTheDevilMayCrySeriesAndKnuckles->addChild(label);
		}

		return true;
	}

	void onServerButtonClick(CCObject* sender) {
		//log::debug("congrats, you pressed button");

		ProfileLayer::scene();
	}
};

// TODO: make equivalents for other platforms or convince the Geode team to find the addresses for this on every platform so I can COOK.
// TODO: override/hook function at 41b950 (levels)
$execute {
	loadProfiles();
	static_cast<void>(Mod::get()->hook(CCHTTPRequestSetUrlAddress, &CCHTTPRequestSetUrlHook, "CCHTTPRequestSetUrlHook", tulip::hook::TulipConvention::Thiscall));
}
