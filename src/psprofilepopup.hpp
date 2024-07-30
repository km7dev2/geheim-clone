#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/TextInput.hpp>

using namespace geode::prelude;

class ProfilePopup : public geode::Popup<std::string const&> {
protected:
	bool setup(std::string const& value) override;

	void tryRegister(CCObject*);

	geode::TextInput* idInput;
	geode::TextInput* displayInput;
	geode::TextInput* urlInput;

public:
	static ProfilePopup* create(std::string const& text);
};
