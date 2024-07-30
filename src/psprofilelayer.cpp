#include <cocos2d.h>
#include <Geode/binding/MenuLayer.hpp>

#include <Geode/binding/FLAlertLayer.hpp>
#include <Geode/cocos/label_nodes/CCLabelBMFont.h>
#include <Geode/ui/ListView.hpp>

#include "psprofilelayer.hpp"
#include "profile.hpp"
#include "psprofilepopup.hpp"

// TODO: REWORK THIS, IT FUCKING SUCKS

static CCSize LAYER_SIZE = { 230.f, 190.f };

bool ProfileLayer::init() {
	if (!CCLayer::init())
		return false;

	this->setKeypadEnabled(true);
	this->addChild(createLayerBG());

	auto winSize = CCDirector::get()->getWinSize();

	auto title = CCLabelBMFont::create("Servers", "goldFont.fnt");
	title->setPosition(winSize.width / 2, winSize.height - 20.f);
	this->addChild(title);

	cGDPS = CCLabelBMFont::create(("Current Server: " + profiles[activeProfile].mName).c_str(), "goldFont.fnt");
	cGDPS->setPosition(winSize.width / 2, 20.f);
	this->addChild(cGDPS);

	auto menu = CCMenu::create();

	auto backBtn = CCMenuItemSpriteExtra::create(
		CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
		this, menu_selector(ProfileLayer::onGoBack)
	);
	backBtn->setPosition(-winSize.width / 2 + 25.f, winSize.height / 2 - 25.f);
	menu->addChild(backBtn);

	auto newBtn = CCMenuItemSpriteExtra::create(
		CCSprite::createWithSpriteFrameName("GJ_newBtn_001.png"),
		this, menu_selector(ProfileLayer::onNewServer)
	);
	newBtn->setPosition(winSize.width / 2 - 30.f, -winSize.height / 2 + 33.f);
	menu->addChild(newBtn);


	auto array = CCArray::create();

	for (auto entry : profiles) {
		auto node = CCMenu::create();

		auto text = CCLabelBMFont::create(entry.second.mName.c_str(), "bigFont.fnt");
		text->setPosition(160, 20);
		text->setContentSize({200, 16});

		auto spr = ButtonSprite::create("Set");
		
		auto btn = CCMenuItemSpriteExtra::create(
			spr, this, menu_selector(ProfileLayer::onClick)
		);
		btn->setUserObject(CCString::create(entry.first));

		log::debug("Button created for '{}' has userObject '{}'", entry.first, static_cast<CCString*>(btn->getUserObject())->getCString());

		//btn->setScale(0.5);
		//btn->setPosition(150, 20);


		node->addChild(text);
		node->addChild(btn);

		btn->setPosition(300, 13);
		btn->setContentSize({64, 30});

		array->addObject(node);
		node->setContentSize({340, 32.5});
		node->setPosition({174, 18});

		text->updateLabel();
		text->updateLayout();
		text->updateTransform();

		node->updateLayout();
		node->updateTransform();
	}

	listView = ListView::create(array);

	listLayer = GJListLayer::create(listView, "", {0,0,0,255}, 358, 220, 1);
	listLayer->setPosition(-(winSize/3));

	menu->addChild(listLayer);

	this->addChild(menu);

	return true;
}

ProfileLayer* ProfileLayer::create() {
	auto ret = new ProfileLayer;
	if (ret->init()) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

void ProfileLayer::keyBackClicked() {
	this->onGoBack(nullptr);
}

void ProfileLayer::onClick(CCObject* sender) {
	log::debug("ProfileLayer::onClick");

	auto obj = static_cast<CCNode*>(sender)->getUserObject();
	// Cast it to a CCString and get its data
	std::string str = static_cast<CCString*>(obj)->getCString();

	log::debug("Requested profile change '{}'", str);
	if (profiles.contains(str)) {
		//activeProfile = str;
		//log::debug("Set profile to '{}'", activeProfile);
		//cGDPS->setString(("GDPS: " + profiles[activeProfile].mName).c_str());
		//cGDPS->updateLabel();

		if (Mod::get()->setSavedValue<std::string>("lastProfile", str) != str) {
			FLAlertLayer::create(
				"Server changed",            // title
				"Please restart in order for this change to take effect.",   // content
				"Ok"
			)->show();
		} else {
			FLAlertLayer::create(
				"Server change didn't happen",
				"You requested to change to the already enabled server. As a result, nothing happened.",
				"Ok"
			)->show();
		}
	}
}

void ProfileLayer::onGoBack(CCObject*) {
	CCDirector::get()->replaceScene(CCTransitionFade::create(0.5, MenuLayer::scene(false)));
}

void ProfileLayer::onNewServer(CCObject*) {
	ProfilePopup::create("")->show();
}

ProfileLayer* ProfileLayer::scene() {
	auto layer = ProfileLayer::create();
	switchToScene(layer);
	return layer;
}
