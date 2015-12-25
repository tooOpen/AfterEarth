#include "GamePlayScene.h"


Scene* GamePlayScene::createScene() {
	auto scene = Scene::create();

	auto layer = GamePlayScene::create();

	scene->addChild(layer);

	return scene;
}

bool GamePlayScene::init() {

	if (!LayerColor::initWithColor(Color4B(0, 255, 255, 255))) {
		return false;
	}
	this->setKeypadEnabled(true);

	_isend = false;
	count = UserDefault::getInstance()->getIntegerForKey("leftcount",999999999);
	_countLabel = LabelTTF::create(addComma(count), "fonts/Sho-CardCapsNF.ttf", 70);
	    // position the label on the center of the screen
	_countLabel->setPosition(Vec2(240, 650));
	    // add the label as a child to this layer
	    this->addChild(_countLabel, 10);

	_holdBack = Sprite::create("commons/images/holdback.png");
	_holdBack->setPosition(Vec2(240, 400));
	this->addChild(_holdBack, 0);

	_slideBack = Sprite::create("commons/images/slideback.png");
	_slideBack->setAnchorPoint(Vec2(0.5, 0.0));
	_slideBack->setPosition(Vec2(240, 0));
	this->addChild(_slideBack, 1);


	_earth = Sprite::create(matchState(UserDefault::getInstance()->getIntegerForKey("nowstate",1)));
	_earth->setPosition(Vec2(240, 350));
	this->addChild(_earth, 3);

	_homeButton = MenuItemImage::create(
		"playscene/images/home.png",
		"playscene/images/homeclicked.png",
		CC_CALLBACK_1(GamePlayScene::menuCloseCallback, this));
	_homeButton->setAnchorPoint(Vec2(0.5, 0.5));
	_homeButton->setPosition(Vec2(-200, 360));
	_homeButton->setTag(1);

	_muteButton = MenuItemImage::create(
		"playscene/images/sound.png",
		"playscene/images/sound.png",
		CC_CALLBACK_1(GamePlayScene::menuCloseCallback, this));
	_muteButton->setAnchorPoint(Vec2(0.5, 0.5));
	_muteButton->setPosition(Vec2(200, 360));
	_muteButton->setTag(2);
	auto menu = Menu::create( _homeButton, _muteButton,NULL);

	menu->setPosition(Vec2(240, 400));

	this->addChild(menu, 3);



	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GamePlayScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GamePlayScene::onTouchMoved, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GamePlayScene::onTouchCancelled,
			this);
	listener->onTouchEnded = CC_CALLBACK_2(GamePlayScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//AudioManager::getAudioManager()->playEffectAudio(SOUND_PALYAUDIO);

	this->schedule(schedule_selector(GamePlayScene::backgroundSlideSchedule), 20.0f, CC_REPEAT_FOREVER, 20.0f);

	return true;
}
void GamePlayScene::menuCloseCallback(Ref* pSender)
{
	auto bmenuItem = (MenuItemImage*)pSender;
	 

		if(bmenuItem->getTag() ==1 )
		{
	//		AudioManager::getAudioManager()->stopSound();

			auto tscene = TitleScene::createScene();
			Director::getInstance()->replaceScene(tscene);
		}
		else if(bmenuItem->getTag() ==2 )
		{


			if(!_ismute)
				{
				_muteButton->setNormalImage(Sprite::create("playscene/images/mute.png"));
			//	AudioManager::getAudioManager()->mute();

				_ismute =!_ismute;
				}
				else{
					_muteButton->setNormalImage(Sprite::create("playscene/images/sound.png"));
			//		AudioManager::getAudioManager()->mute();

					_ismute =!_ismute;
				}
		}


}
void GamePlayScene::onExit()
{
	UserDefault::getInstance()->setIntegerForKey("leftcount", count);
	if(UserDefault::getInstance()->getIntegerForKey("nowstate")==6)
	{
		UserDefault::getInstance()->setIntegerForKey("nowstate",1);
		UserDefault::getInstance()->setIntegerForKey("leftcount",999999999);
	}
}
void GamePlayScene::backgroundSlideSchedule(float f)
{
	if (_backSlide)
	{
		auto transiAction = MoveTo::create(2.2, Vec2(240, 0));
		_slideBack->runAction(transiAction);
		_backSlide = !_backSlide;
	}
	else
	{
		auto transiAction = MoveTo::create(2.0, Vec2(240, 800));
		auto gotoAction = MoveTo::create(0.0, Vec2(240, -1000));
		auto upAction = MoveTo::create(1.0, Vec2(240, -930));
		auto backAction = Sequence::create(transiAction, gotoAction, upAction, NULL);

		_slideBack->runAction(backAction);
		_backSlide = !_backSlide;
	}
}



bool GamePlayScene::onTouchBegan(Touch* touch, Event* unused_event){

	if(!_isend)
	{
		Vec2 locationInNode = touch->getLocation();
		if (_earth->boundingBox().containsPoint(locationInNode))
		{
	//		AudioManager::getAudioManager()->playEffectAudio(SOUND_HITEARTH);

			auto lefta = MoveBy::create(0.1, Vec2(-5, 0));
					auto reset = MoveBy::create(0.1, Vec2(10, 0));
					auto righta = MoveBy::create(0.1, Vec2(-5, 0));
			auto seq = Sequence::create(lefta, reset, righta,NULL);
			_earth->runAction(seq);

			if(count-1 == 800000000)
			{
				UserDefault::getInstance()->setIntegerForKey("nowstate",2);
				_earth->setTexture(Director::getInstance()->getTextureCache()->addImage(matchState(2)));
			}
			else if(count-1 == 600000000)
			{
				UserDefault::getInstance()->setIntegerForKey("nowstate",3);
				_earth->setTexture(Director::getInstance()->getTextureCache()->addImage(matchState(3)));
			}
			else if(count-1 == 400000000)
			{
				UserDefault::getInstance()->setIntegerForKey("nowstate",4);
				_earth->setTexture(Director::getInstance()->getTextureCache()->addImage(matchState(4)));
			}
			else if(count-1 == 200000000)
			{
				UserDefault::getInstance()->setIntegerForKey("nowstate",5);
				_earth->setTexture(Director::getInstance()->getTextureCache()->addImage(matchState(5)));
			}
			else if(count-1 == 0)
			{
				_isend = true;
				UserDefault::getInstance()->setIntegerForKey("nowstate",6);
				_earth->setTexture(Director::getInstance()->getTextureCache()->addImage(matchState(6)));
		//		AudioManager::getAudioManager()->playEffectAudio(SOUND_EXPLOSION);
				auto move1 = MoveTo::create(0.1, Vec2(230, 350));
				auto move2 = MoveTo::create(0.1, Vec2(260, 350));
				auto seqe = Spawn::create(move1,move2,NULL);
				auto rep1 = RepeatForever::create(seqe);
				_earth->runAction(rep1);
				auto boom = Sprite::create("playscene/images/explosion.png");
				boom->setPosition(Vec2(240,350));
				boom->setScale(0.1);
				this->addChild(boom,10);
				auto sca = ScaleTo::create(0.5,1.0);
				auto spin = RotateBy::create(1.5,360);
				auto seq = Spawn::create(sca,spin,NULL);
				boom->runAction(seq);

				auto particleTest2 = ParticleExplosion::create();

				auto texture2 =
						Director::getInstance()->getTextureCache()->addImage(
								"playscene/images/rock.png");
				particleTest2->setTexture(texture2);
				if (particleTest2 != NULL) {
					particleTest2->setScale(1.0);
					particleTest2->setEmissionRate(100.0);
					particleTest2->setStartSize(50.0);
					particleTest2->setLife(3.0);
					particleTest2->setDuration(-1);
					particleTest2->setEndSize(0.0);
					particleTest2->setPosition(Vec2(240, 350));
					particleTest2->setStartColor(Color4F(25, 125, 79, 255));
					particleTest2->setEndColor(Color4F(35, 213, 48, 255));
					this->addChild(particleTest2, 9);
				}
				_countLabel->setString("What the hell \n did you do?!");
				_countLabel->setFontSize(60);
			}
			if(count-1!=0)
			_countLabel->setString(addComma(--count));
		}
	}
	return true;
}

void GamePlayScene::onTouchMoved(Touch* touch, Event* unused_event){

}

void GamePlayScene::onTouchCancelled(Touch* touch, Event* unused_event){}

void GamePlayScene::onTouchEnded(Touch* touch, Event* unused_event){

}

std::string GamePlayScene::addComma(int value)
{
	std::string result;
	int cnt = 0;
	do
	{
		result.insert(0, 1, char('0' + value % 10));
		value /= 10;
		if (++cnt == 3 && value)
		{
			result.insert(0, 1, ',');
			cnt = 0;
		}
	} while (value);
	return result;

}

std::string GamePlayScene::matchState(int v)
{
	std::string temp = "";
	switch(v)
	{
		case 1:
			temp = "playscene/images/earth1.png";
		break;
		case 2:
			temp = "playscene/images/earth2.png";
		break;
		case 3:
			temp = "playscene/images/earth3.png";
		break;
		case 4:
			temp = "playscene/images/earth4.png";
		break;
		case 5:
			temp = "playscene/images/earth5.png";
		break;
		case 6:
			temp = "playscene/images/explosionearth.png";
			break;
	}
	return temp;
}

