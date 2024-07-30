#pragma once

#include <network/HttpRequest.h>

using namespace geode::prelude;

inline static void* CCHTTPRequestSetUrlAddress = reinterpret_cast<void*>(
	#ifdef GEODE_IS_WINDOWS
	GetProcAddress(
		GetModuleHandleA("libExtensions.dll"),
		"?setUrl@CCHttpRequest@extension@cocos2d@@QEAAXPEBD@Z"
	)
	#else
		#error "Unsupported target!"
	#endif
);

void CCHTTPRequestSetUrlHook(CCHttpRequest* self, const char* url);
