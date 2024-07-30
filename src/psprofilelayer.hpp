#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

using namespace cocos2d;

class ProfileLayer : public CCLayer {
protected:
	bool init();

	static ProfileLayer* create();

	void keyBackClicked();

	void onClick(CCObject* sender);

	void onGoBack(CCObject* sender);
	void onNewServer(CCObject* sender);

	CCLabelBMFont* cGDPS;

	// Lists
	GJListLayer* listLayer;
	ListView* listView;
public:
	static ProfileLayer* scene();
};
