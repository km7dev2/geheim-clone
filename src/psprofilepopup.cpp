#include "psprofilepopup.hpp"

#include "profile.hpp"

#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/binding/FLAlertLayer.hpp>

bool ProfilePopup::setup(const std::string& value) {
	auto winSize = CCDirector::sharedDirector()->getWinSize();

	// convenience function provided by Popup
	// for adding/setting a title to the popup
	this->setTitle("Add Profile");

	auto label = CCLabelBMFont::create(value.c_str(), "bigFont.fnt");
	label->setPosition(winSize / 2);
	this->addChild(label);

	idInput = geode::TextInput::create(200, "Profile ID...", "chatFont.fnt");
	idInput->setFilter("abcdefghijklmnopqrstuvwxyz");
	// idInput->addTextArea(TextArea::create("", "chatFont.fnt", 100, 16, {0,
	// 1}, 1.0f, true));
	idInput->setMaxCharCount(32);

	displayInput = geode::TextInput::create(200, "Display Name...", "chatFont.fnt");
	displayInput->setCommonFilter(CommonFilter::Any);
	displayInput->setMaxCharCount(32);

	urlInput = geode::TextInput::create(200, "Server URL...", "chatFont.fnt");
	urlInput->setFilter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ:/.?%");
	urlInput->setMaxCharCount(64);

	auto addProfileBtn = CCMenuItemSpriteExtra::create(
		ButtonSprite::create("Add server profile"), this,
		menu_selector(ProfilePopup::tryRegister));

	idInput->setPositionY(180);
	displayInput->setPositionY(127.5f);
	urlInput->setPositionY(75);
	addProfileBtn->setPositionY(30);

	m_mainLayer->addChild(idInput);
	m_mainLayer->addChild(displayInput);
	m_mainLayer->addChild(urlInput);
	m_buttonMenu->addChild(addProfileBtn);

	// m_buttonMenu->setPositionX(winSize.width / 2);

	idInput->setPositionX(m_buttonMenu->getContentSize().width / 2);
	displayInput->setPositionX(m_buttonMenu->getContentSize().width / 2);
	urlInput->setPositionX(m_buttonMenu->getContentSize().width / 2);
	addProfileBtn->setPositionX(m_buttonMenu->getContentSize().width / 2);

	return true;
}

void ProfilePopup::tryRegister(CCObject*) {
	log::debug( "Requested ID: '{}', Display Name: '{}', URL: '{}'", idInput->getString(), displayInput->getString(), urlInput->getString());

	if (profiles.contains(idInput->getString())) {
		FLAlertLayer::create("Cannot add profile", fmt::format("The profile '{}' is already in use!", (std::string)idInput->getString()), "OK")->show();
	} else if (idInput->getString().empty() || displayInput->getString().empty() || urlInput->getString().empty()) {
		FLAlertLayer::create("Cannot add profile", "One of the required values (ProfileID, Display Name or Server URL) was not provided, please fill these in!", "OK")->show();
	} else {
		customProfiles.emplace_back(ProfileInfo{
			idInput->getString(),
			StringPair{displayInput->getString(), urlInput->getString()}
		});
		profiles.emplace(
			idInput->getString(),
			StringPair{displayInput->getString(), urlInput->getString()}
		);

		//Mod::get()->setSavedValue<std::vector<ProfileInfo>>("savedProfiles", customProfiles);
		saveProfiles();

		log::debug("Added profile with ID: '{}', Display Name: '{}', URL: '{}'", idInput->getString(), displayInput->getString(), urlInput->getString());
	}
}

ProfilePopup* ProfilePopup::create(const std::string& text) {
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	auto ret = new ProfilePopup();
	if (ret && ret->initAnchored(winSize.width / 1.5, winSize.height / 1.5, text)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}
