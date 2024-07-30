#include <Geode/Geode.hpp>

#include <Geode/modify/GManager.hpp>

#include "../profile.hpp"

using namespace geode::prelude;

class $modify(GManager) {
	void setup() {
		log::debug("File is '{}' (Setup)", m_fileName);

		std::string target = m_fileName;

		if (activeProfile != "default" && std::find(TARGET_NAMES.begin(), TARGET_NAMES.end(), target) != TARGET_NAMES.end()) {
			//renameDefault(target);

			target = activeProfile + "-" + target;

			m_fileName = target;

			log::debug("Hijacked file to be '{}'", m_fileName);
		}

		GManager::setup();
	}

	// Should I remove this? I'm not actually doing anything with this
	void load() {
		//renameDefault(m_fileName);

		log::debug("Loading '{}'...", m_fileName);
	}

	/*void saveGMTo(gd::string to) {
		log::debug("Save path (saveGMTo): {}", to);
		log::debug("PWD (saveGMTo): {}", std::filesystem::current_path().string());

		std::string target = to;

		if (activeProfile != "default" && std::find(TARGET_NAMES.begin(), TARGET_NAMES.end(), target) != TARGET_NAMES.end()) {
			target = activeProfile + "-" + target;

			m_fileName = target;

			log::debug("Hijacked file to be '{}'", m_fileName);
		}

		return GManager::saveGMTo(target);
	}*/

	void firstLoad() {
		log::debug("FirstLoad File is '{}'", m_fileName);
	}
};
