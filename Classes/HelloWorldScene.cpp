/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	   


    /////////////////////////////
	SpriteBatchNode *spriteNode = SpriteBatchNode::create("Xanimation.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Xanimation.plist");
	Idle1 = Sprite::createWithSpriteFrameName("Idle0.png");
	Idle1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	spriteNode->addChild(Idle1);
	this->addChild(spriteNode);
	auto animate = Animate::create(HelloWorld::createAnimation("Idle", 9, 0.1f));
	animate->retain();
	Idle1->runAction(RepeatForever::create(animate));

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}


void HelloWorld::Idle()
{
	animation->release();
	animation = HelloWorld::createAnimation("Idle", 9, 0.1f);
	auto animate = Animate::create(animation);
	animate->retain();
	Idle1->runAction(RepeatForever::create(animate));

}

cocos2d::Animation *HelloWorld::createAnimation(std::string prefixName, int spriteNumber, float delay) 
{
	Vector<SpriteFrame*> animationFrames;
	char spriteTail[20] = { 0 };
	for (int i = 0; i < spriteNumber; i++)
	{
		sprintf(spriteTail, "%d.png", i);
		std::string str = prefixName + spriteTail;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animationFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animationFrames, delay);
	return animation;


}

bool HelloWorld::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	animation->release();
	animation = HelloWorld::createAnimation("Jump", 15, 0.05f);
	auto animate = Animate::create(animation);
	animate->retain();
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(HelloWorld::Idle, this)), NULL);
	Idle1->runAction(seq);
	return true;
}





void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
