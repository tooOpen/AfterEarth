/*
 * GamePlayScene.h
 *
 *  Created on: Aug 4, 2015
 *      Author: hangSoon
 */

#ifndef GAMEPLAYSCENE_H_
#define GAMEPLAYSCENE_H_

#include "cocos2d.h"
#include "TitleScene.h"
#include "AudioManager.h"
#include <dlog.h>
USING_NS_CC;

class GamePlayScene : public cocos2d::LayerColor
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GamePlayScene)
	bool _backSlide = false;
	bool _ismute = false;
	MenuItemImage* _homeButton;
	MenuItemImage* _muteButton;
	bool _isend;
	Sprite* _earth;
	Sprite* _holdBack;
	Sprite* _slideBack;
	int count;
	LabelTTF* _countLabel;
	virtual void onExit();
	std::string matchState(int v);
	void menuCloseCallback(cocos2d::Ref* pSender);
	void backgroundSlideSchedule(float f);
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchCancelled(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event *unused_event);

	std::string addComma(int value);
};
#endif /* GAMEPLAYSCENE_H_ */
