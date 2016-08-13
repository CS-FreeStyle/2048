/*
ProjectName: 2048
Author: ����С���
Blog: http://www.cnblogs.com/msxh/
Github:https://github.com/XINCGer
Date: 2016/08/09
*/

#include "ScoreBroad.h"

ScoreBroad* ScoreBroad::createScoreBroad(int score, int width, int height, const char*title, int type, float x, float y){
	//���ö��ι������ģʽ������ģ�棩
	ScoreBroad *enemy = new ScoreBroad();
	if (enemy&&enemy->init()){
		enemy->autorelease();
		enemy->enemyInit(score, width, height, title, type, x, y);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool ScoreBroad::init(){
	if (!Layer::init()){
		return false;
	}
	return true;
}

void ScoreBroad::enemyInit(int score, int width, int height, const char*title, int type, float x, float y){
	this->type = type;
	this->score = score;
	if (type == 1){		//�ж�����һ��Ƿ���
		background = LayerColor::create(Color4B(2, 168, 209, 255), width, height);
		background->setPosition(x, y);
		addChild(background);
		scoreLabel = Label::create(String::createWithFormat("%d", score)->getCString(),"Arial",40);
		scoreLabel->setPosition(width / 2, height / 2);
		background->addChild(scoreLabel);
	}
	else{
		background = LayerColor::create(Color4B(215, 224, 223, 255), width, height);
		background->setPosition(x, y);
		addChild(background);
		auto *label = Label::create(title, "Arial", 26);
		label->setPosition(width / 2, height-20);
		background->addChild(label);
		scoreLabel = Label::create(String::createWithFormat("%d", score)->getCString(), "Arial", 34);
		scoreLabel->setPosition(width / 2, 30);
		background->addChild(scoreLabel);
	}
}

void ScoreBroad::setScore(int number){		//�޸ļǷ��Ƶķ���
	this->score = number;
	scoreLabel->setString(String::createWithFormat("%d", number)->getCString());
}

int ScoreBroad::getScore(){		//��ȡ�Ƿ�����ʾ�ķ���
	return this->score;
}
