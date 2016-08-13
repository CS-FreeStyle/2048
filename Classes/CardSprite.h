/*
ProjectName: 2048
Author: ����С���
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/03
*/
#ifndef __CARDSPRITE_H__
#define __CARDSPRITE_H__
#include "cocos2d.h"
USING_NS_CC;
#define CARD_BORDER 4

class CardSprite :public Sprite{
public:
	int number;  //��Ƭ�е���ֵ
	int getNumber();   //��ȡ��Ƭ�е���ֵ
	void setNumber(int num);  //���ÿ�Ƭ�е���ֵ
	Label* labelNumber;		//������ʾ��ֵ�ı�ǩ
	LayerColor* layerColorBG;	//��Ƭ�ı�����ɫ
	static CardSprite* createCardSprite(int number, int size, float x, float y);  //������Ƭ�ľ�̬����
	void enemyInit(int number, int size, float x, float y);  //��Ƭ�ĳ�ʼ������
	virtual bool init();
	CREATE_FUNC(CardSprite);
};
#endif