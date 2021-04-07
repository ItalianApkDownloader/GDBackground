#pragma once
#include "pch.h"

namespace hooks {
	template<typename T, typename U>
	inline bool detour(const T src, const U dst, const int len) {
		if (len < 5) return false;

		//make sure that pointer arithmetic is byte-by-byte
		char* _src = reinterpret_cast<char*>(src);
		char* _dst = reinterpret_cast<char*>(dst);

		int jmp = static_cast<int>(_dst - _src - 5);
		unsigned long old = 0;
		VirtualProtect(_src, len, PAGE_EXECUTE_READWRITE, &old);
		*_src = 0xE9;
		*reinterpret_cast<int*>(_src + 1) = jmp;
		return VirtualProtect(_src, len, old, &old);
	}

	namespace MenuLayer {
		int __fastcall init(cocos2d::CCLayer*);
	}
}

namespace gates {
	namespace MenuLayer {
		inline int(__thiscall* init)(cocos2d::CCLayer*) = nullptr;
	}
}

