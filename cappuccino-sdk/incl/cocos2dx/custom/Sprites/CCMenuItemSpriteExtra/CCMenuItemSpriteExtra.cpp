#include "CCMenuItemSpriteExtra.h"

void CCMenuItemSpriteExtra::selected() {
	CCMenuItemSprite::selected();
	auto resize = cocos2d::CCScaleBy::create(0.3, m_fSizeMult);
	auto bounce = cocos2d::CCEaseBounceOut::create(resize);
	this->runAction(bounce);
}

void CCMenuItemSpriteExtra::unselected() {
	CCMenuItemSprite::unselected();
	auto resize = cocos2d::CCScaleBy::create(0.3, 1.0 / m_fSizeMult);
	auto bounce = cocos2d::CCEaseBounceOut::create(resize);
	this->runAction(bounce);
}

void CCMenuItemSpriteExtra::activate() {
	this->stopAllActions();
	auto reset = cocos2d::CCScaleTo::create(0.0, m_fOriginalSizeMult);
	this->runAction(reset);
	CCMenuItemSprite::activate();
}

CCMenuItemSpriteExtra* CCMenuItemSpriteExtra::create(CCNode *normalSprite, CCNode *selectedSprite, CCObject *target, cocos2d::SEL_MenuHandler selector){
	auto spriteItem = new CCMenuItemSpriteExtra;
	if (spriteItem && spriteItem->initWithNormalSprite(normalSprite, selectedSprite, nullptr, target, selector)) {
		spriteItem->autorelease();
		spriteItem->m_fOriginalSizeMult = normalSprite->getScale();
	}
	else {
		delete spriteItem;
		spriteItem = nullptr;
	}
	return spriteItem;
}