/*
ProjectName: 2048
Author: ����С���
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/03
*/

#include "CardSprite.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

CardSprite* CardSprite::createCardSprite(int number, int size, float x, float y){
	//���ö��ι������ģʽ������ģ�棩
	CardSprite *enemy = new CardSprite();
	if (enemy&&enemy->init()){
		enemy->autorelease();
		enemy->enemyInit(number, size, x, y);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool CardSprite::init(){
	//����ģ��
	if (!Sprite::init()){
		return false;
	}
	return true;
}

void CardSprite::enemyInit(int number, int size, float x, float y){
	//���ó�ʼ��ֵ
	this->number = number;
	//������Ƭ�ı�����ɫ
	layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(216, 210, 214, 255), size - CARD_BORDER, size - CARD_BORDER);
	layerColorBG->setPosition(Point(x, y));
	//�ж��������0����ʾ��������ʾ��
	if (number > 0){
		//������ʾ��ֵ��������ɫ
		labelNumber = Label::create(String::createWithFormat("%i", number)->getCString(), "Arial", 36);
		labelNumber->setPosition(Vec2((size - CARD_BORDER) / 2, (size - CARD_BORDER) / 2));
		layerColorBG->addChild(labelNumber);
	}
	else{
		//����ʾ������ɫ������ʾ������ֵ
		labelNumber = Label::create("", "Arial", 28);
		labelNumber->setPosition(Vec2(size / 2, size / 2));
		layerColorBG->addChild(labelNumber);
	}
	this->addChild(layerColorBG);
}

int CardSprite::getNumber(){
	return this->number;
}

void CardSprite::setNumber(int num){
	number = num;
	if (number > 0)
	{
		labelNumber->setString(String::createWithFormat("%i", number)->getCString());
		if (number == 2)
		{
			layerColorBG->setColor(Color3B(255, 246, 247));
			labelNumber->setColor(Color3B(33, 33, 7));
		}
		else if (number == 4)
		{
			layerColorBG->setColor(Color3B(255, 218, 163));
			labelNumber->setColor(Color3B(255, 255, 255));
		}
		else if (number == 8)
		{
			layerColorBG->setColor(Color3B(255, 144, 91));
		}
		else if (number == 16)
		{
			layerColorBG->setColor(Color3B(255, 101, 46));
		}
		else if (number == 32)
		{
			layerColorBG->setColor(Color3B(255, 80, 46));
		}
		else if (number == 64)
		{
			layerColorBG->setColor(Color3B(254, 56, 60));
		}
		else if (number == 128)
		{
			layerColorBG->setColor(Color3B(6, 194, 240));
		}
		else if (number == 256)
		{
			layerColorBG->setColor(Color3B(5, 140, 240));
		}
		else if (number == 512)
		{
			layerColorBG->setColor(Color3B(4, 140, 200));
		}
		else if (number == 1024)
		{
			layerColorBG->setColor(Color3B(3, 112, 154));
		}
		else if (number == 2048)
		{
			layerColorBG->setColor(Color3B(2, 98, 131));
		}
		else if (number == 4096)
		{
			layerColorBG->setColor(Color3B(1, 93, 118));
		}
		else if (number == 8192)
		{
			layerColorBG->setColor(Color3B(58, 49, 132));
		}
		else if (number == 16384)
		{
			layerColorBG->setColor(Color3B(41, 41, 49));
		}
		else if (number == 32768)
		{
			layerColorBG->setColor(Color3B(33, 33, 7));
		}
		else
		{
			layerColorBG->setColor(Color3B(0, 0, 0));
		}

		if (num > 10000)					// 5λ������
		{
			labelNumber->setSystemFontSize(24);
		}
		else if (num > 1000)					// 4λ��
		{
			labelNumber->setSystemFontSize(28);
		}
		else if (num > 100)					// 3λ��
		{
			labelNumber->setSystemFontSize(34);
		}
		else if (num > 10)					// 2λ��
		{
			labelNumber->setSystemFontSize(38);
		}
		else								// ��λ��
		{
			labelNumber->setSystemFontSize(44);
		}
	}
	else
	{
		labelNumber->setString("");
		layerColorBG->setColor(Color3B(216, 210, 214));
	}
}
