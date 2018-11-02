#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

HRESULT playGround::init(void)	
{
	gameNode::init(true);

	SCENEMANAGER->addScene("Ÿ�ϸʾ�", new tileMapScene);
	SCENEMANAGER->addScene("�ѸǾ�", new pacmanScene);
	SCENEMANAGER->changeScene("�ѸǾ�");
	
	return S_OK;
}

void playGround::release(void)	
{
	gameNode::release();

	
}

void playGround::update(void)	
{
	gameNode::update();

	if(KEYMANAGER->isOnceKeyDown(VK_F1))
		SCENEMANAGER->changeScene("�ѸǾ�");
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
		SCENEMANAGER->changeScene("Ÿ�ϸʾ�");


	SCENEMANAGER->update();

}

void playGround::render(void)
{
	
	//�����ȭ�� �� �� ��Ƶд�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//============== �� ���δ� �ǵ帮�� ���� ==============
	
	SCENEMANAGER->render();

	//TIMEMANAGER->render(getMemDC());
	//================�� �����ε� �ǵ帮�� ���� =============
	this->getBackBuffer()->render(getHDC(), 0, 0);

}

