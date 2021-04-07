#pragma once
#include "pch.h"

namespace GD {
	//making it a char pointer because usually offsets are in bytes
	const inline char* base = reinterpret_cast<char*>(GetModuleHandle(0));

	namespace MenuLayer {
		inline int(__thiscall const* init)(cocos2d::CCLayer* MenuLayer) = 
			reinterpret_cast<decltype(init)>(base + 0x1907B0);
	}

	inline bool init() {
		//make sure base is valid, if it is then everything else should be fine
		return base;
	}
}