#include "pch.h"

#include "hooks.h"
#include "extern/gd.h"



namespace hooks {
	namespace MenuLayer {		

		int __fastcall init(cocos2d::CCLayer* MenuLayer) {
			using namespace cocos2d;
			using namespace GD;

			int ret = gates::MenuLayer::init(MenuLayer);

			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			auto dir = CCDirector::sharedDirector();
			float middleX = (dir->getScreenRight() - dir->getScreenLeft()) / 2;
			const std::string name = "Resources/background.jpg";

			auto sprite = CCSprite::create(name.c_str());
			if (sprite != nullptr) {
				float f = winSize.height / sprite->getContentSize().height;
				sprite->setScaleY(winSize.height / sprite->getContentSize().height);
				sprite->setScaleX(sprite->getScaleX() * f);
				sprite->setPositionX(winSize.width / 2);
				sprite->setPositionY(winSize.height / 2);
				CCLayerColor* bg = CCLayerColor::create();
				bg->initWithColor(ccc4(0, 0, 0, 255));
				bg->setContentSize(CCDirector::sharedDirector()->getWinSize());
				auto node = ((CCNode*)MenuLayer->getChildren()->objectAtIndex(0));
				node->addChild(bg, 98);
				node->addChild(sprite, 99);
			}
					
			return ret;
		}
	}
}
