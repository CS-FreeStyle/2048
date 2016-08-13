/*
ProjectName: 2048
Author: ����С���
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/03
*/
#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

#define TOUCH_LONG 50 //�������������ϵľ���
#define TOUCH_SHORT 10 //����������ֱ�����ƫ�Ʒ�Χ

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getVisibleSize();

	this->isPlay = true;	//isPlay���г�ʼ��
	this->isLock = false; //isLock���г�ʼ��
	auto *dispatcher = Director::getInstance()->getEventDispatcher();
	auto *listener = EventListenerTouchOneByOne::create(); //����������
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto* background = cocos2d::LayerColor::create(cocos2d::Color4B(255, 255, 255, 255));
	addChild(background);

	int width = size.width;				// ��Ļ���
	int height = size.height;				// ��Ļ�߶�
	int cardSize = (width - 30) / 4;			// ��Ƭ�Ŀ��

	//��Ƭ�ĵ���
	auto *baseBG = LayerColor::create(cocos2d::Color4B(186, 191, 191, 255), width - 30, width - 30);
	baseBG->setPosition(15, (height - 100 - width - 15) / 2);
	addChild(baseBG);

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			//Ԥ�ȴ���4x4�Ŀ�Ƭ����ʹ���ǵ�ֵȫ��Ϊ0
			card[i][j] = CardSprite::createCardSprite(0, cardSize, cardSize * i + CARD_BORDER / 2, cardSize * j + CARD_BORDER / 2);
			baseBG->addChild(card[i][j]);	//����Ƭ�����ڵ�������
		}
	}

	//��Ϸ��ʼʱ����ʾ������ֵΪ2�Ŀ�Ƭ
	this->createCard();
	this->createCard();

	record = UserDefault::getInstance()->getIntegerForKey("record");
	demo = 2048;
	score = 0;
	broad1 = ScoreBroad::createScoreBroad(demo, 120, 90, "", 1, 15, size.height - 100);
	broad2 = ScoreBroad::createScoreBroad(record, 90, 90, "high", 2, 150, size.height - 100);
	broad3 = ScoreBroad::createScoreBroad(score, 90, 90, "score", 2, 255, size.height - 100);
	addChild(broad1);
	addChild(broad2);
	addChild(broad3);
	return true;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event){
	this->x = touch->getLocation().x; //��¼������ʼʱ������λ��
	this->y = touch->getLocation().y;
	return true;
}

void  HelloWorld::onTouchMoved(Touch *touch, Event *event){
	if (!isLock){      //�жϴ�ʱ�����¼��Ƿ��Ѿ���Ч
		float dx = touch->getLocation().x - this->x;  //��ȡ�����ƶ��Ĳ�ֵ
		float dy = touch->getLocation().y - this->y;
		//���ʶ����Ƚϣ��жϴ������ƶ�����
		if (dx > TOUCH_LONG &&fabs(dy) < TOUCH_SHORT){
			if (doRight()){			//���Ҳ���
				createCard();
			}
			this->isLock = true;	//isLockΪtrueʱ��ʾ���������Ѿ�����Ӧ
		}
		else if (dx < -TOUCH_LONG && fabs(dy) < TOUCH_SHORT){
			if (doLeft()){		//�������
				createCard();
			}
			this->isLock = true;
		}
		else if (dy>TOUCH_LONG &&fabs(dx) < TOUCH_SHORT){
			if (doUp()){	//���ϲ���
				createCard();
			}
			this->isLock = true;
		}
		else if (dy < -TOUCH_LONG &&fabs(dx) < TOUCH_SHORT){
			if (doDown()){		//���²���
				createCard();
			}
			this->isLock = true;
		}
	}
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event){
	//��������ʱ����isLock��ԭΪfalse��ֵ
	this->isLock = false;
	if (isGameOver()){
		SimpleAudioEngine::getInstance()->stopAllEffects();
		SimpleAudioEngine::getInstance()->playEffect("death.mp3");
		auto transtion = TransitionFade::create(1.0, GameOverScene::createScene());
		Director::getInstance()->replaceScene(transtion);
	}
}

bool HelloWorld::doLeft(){
	bool isdo = false;		//�����жϻ��������Ƿ���Ч
	for (int y = 0; y < 4; y++){	//y��ʾ��
		for (int x = 0; x < 4; x++){	//��ÿһ������һ����Ƭ��ʼ
			log("x:%d", x);
			for (int x1 = x + 1; x1 < 4; x1++){		//ָ��Ƭ�Ҳ�
				if (card[x1][y]->getNumber()>0){	//�����ǰָ��Ƭ���Ҳ࿨Ƭ��ֵ����0
					if (card[x][y]->getNumber() <= 0){		//�����ǰָ��Ƭ��ֵΪ0����ֱ���ƶ����Ҳ࿨Ƭ
						card[x][y]->setNumber(card[x1][y]->getNumber());
						card[x1][y]->setNumber(0);
						x--;  //ָ�����
						log("x->%d", x);
						isdo = true;
					}
					else if (card[x][y]->getNumber() == card[x1][y]->getNumber()){  //���ڵ�������Ƭ���������ͬ��ϲ�
						refreshBroad(card[x][y]->getNumber());
						card[x][y]->setNumber(card[x][y]->getNumber() * 2);
						card[x1][y]->setNumber(0);
						isdo = true;
					}
					SimpleAudioEngine::getInstance()->playEffect("move.wav");
					break;
				}
			}
		}

	}
	log("LEFT");
	return isdo;
}

bool HelloWorld::doRight(){
	bool isdo = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >= 0; x--) 				// �����ұߵĿ�Ƭ��ʼ
		{
			for (int x1 = x - 1; x1 >= 0; x1--) 	// ָ��ǰ��Ƭ���Ŀ�Ƭ
			{
				if (card[x1][y]->getNumber() > 0)
				{
					if (card[x][y]->getNumber() <= 0)
					{
						card[x][y]->setNumber(card[x1][y]->getNumber());
						card[x1][y]->setNumber(0);
						x++;
						isdo = true;
					}
					else if (card[x][y]->getNumber() == card[x1][y]->getNumber())
					{
						refreshBroad(card[x][y]->getNumber());
						card[x][y]->setNumber(card[x][y]->getNumber() * 2);
						card[x1][y]->setNumber(0);
						isdo = true;
					}
					SimpleAudioEngine::getInstance()->playEffect("move.wav");
					break;
				}
			}
		}
	}
	log("RIGHT");
	return isdo;

}

bool HelloWorld::doUp(){
	bool isdo = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int y1 = y - 1; y1 >= 0; y1--)
			{
				if (card[x][y1]->getNumber() > 0)
				{
					if (card[x][y]->getNumber() <= 0)
					{
						card[x][y]->setNumber(card[x][y1]->getNumber());
						card[x][y1]->setNumber(0);
						y++;
						isdo = true;
					}
					else if (card[x][y]->getNumber() == card[x][y1]->getNumber())
					{
						refreshBroad(card[x][y]->getNumber());
						card[x][y]->setNumber(card[x][y]->getNumber() * 2);
						card[x][y1]->setNumber(0);
						isdo = true;
					}
					SimpleAudioEngine::getInstance()->playEffect("move.wav");
					break;
				}
			}
		}
	}
	log("UP");
	return isdo;
}

bool HelloWorld::doDown(){
	bool isdo = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int y1 = y + 1; y1 < 4; y1++)
			{
				if (card[x][y1]->getNumber() > 0)
				{
					if (card[x][y]->getNumber() <= 0)
					{
						card[x][y]->setNumber(card[x][y1]->getNumber());
						card[x][y1]->setNumber(0);
						y--;
						isdo = true;
					}
					else if (card[x][y]->getNumber() == card[x][y1]->getNumber())
					{
						refreshBroad(card[x][y]->getNumber());
						card[x][y]->setNumber(card[x][y]->getNumber() * 2);
						card[x][y1]->setNumber(0);
						isdo = true;
					}
					SimpleAudioEngine::getInstance()->playEffect("move.wav");
					break;
				}
			}
		}
	}
	log("DOWN");
	return isdo;
}

void HelloWorld::createCard(){
	int i = CCRANDOM_0_1() * 4;
	int j = CCRANDOM_0_1() * 4;
	//�ж����λ���Ƿ���ֵ
	if (card[i][j]->getNumber() > 0){
		createCard();	 //�ݹ����
	}
	else{
		card[i][j]->setNumber(2);		//�����µĿ�Ƭ
	}
}

void HelloWorld::scoreAddUp(ScoreBroad* broad, int number){
	int score = broad->getScore();
	broad->setScore(score + number);
}

void HelloWorld::refreshBroad(int x){
	if (2 * x == demo){
		demo = 4 * x;
		broad1->setScore(demo);
	}
	score += x;

	if (x % 32 == 0){
		SimpleAudioEngine::getInstance()->stopAllEffects();
		SimpleAudioEngine::getInstance()->playEffect("good1.wav");
	}
	if (score > record){
		record = score;
		UserDefault::getInstance()->setIntegerForKey("record", record);
		broad2->setScore(record);
		if (isPlay && record >= 100){
			SimpleAudioEngine::getInstance()->stopAllEffects();
			SimpleAudioEngine::getInstance()->playEffect("good2.wav");
			isPlay = !isPlay;
		}

	}
	broad3->setScore(score);
}

bool HelloWorld::isGameOver(){
	for (int idx = 0; idx < 4; idx++)
	{
		for (int idy = 0; idy < 4; idy++)
		{
			if (card[idx][idy]->getNumber() == 0)
			{
				return false;
			}
		}
	}

	for (int idx = 0; idx < 4; idx++)
	{
		auto num = 0;
		auto index = 0;
		for (int idy = 3; idy >= 0; idy--)
		{
			auto grid = card[idx][idy];
			if (grid->getNumber() == 0) continue;
			if (num == 0)
			{
				num = grid->getNumber();
				index = idy;
				continue;
			}
			if (num == grid->getNumber())
			{
				return false;
			}
			num = grid->getNumber();
			index = idy;
		}
	}

	for (int idy = 0; idy < 4; idy++)
	{
		auto num = 0;
		auto index = 0;
		for (int idx = 0; idx < 4; idx++)
		{
			auto grid = card[idx][idy];
			if (grid->getNumber() == 0) continue;
			if (num == 0)
			{
				num = grid->getNumber();
				index = idx;
				continue;
			}
			if (num == grid->getNumber())
			{
				return false;
			}
			num = grid->getNumber();
			index = idx;
		}
	}

	return true;
}