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

	SCENEMANAGER->addScene("Å¸ÀÏ¸Ê¾À", new tileMapScene);
	SCENEMANAGER->addScene("ÆÑ¸Ç¾À", new pacmanScene);
	SCENEMANAGER->changeScene("ÆÑ¸Ç¾À");
	
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
		SCENEMANAGER->changeScene("ÆÑ¸Ç¾À");
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
		SCENEMANAGER->changeScene("Å¸ÀÏ¸Ê¾À");


	SCENEMANAGER->update();

}

void playGround::render(void)
{
	
	//Èò»öµµÈ­Áö ÇÑ Àå ±ò¾ÆµÐ´Ù
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//============== ÀÌ À§·Î´Â °Çµå¸®Áö ¸»ÀÚ ==============
	
	SCENEMANAGER->render();

	//TIMEMANAGER->render(getMemDC());
	//================ÀÌ ¹ØÀ¸·Îµµ °Çµå¸®Áö ¸»ÀÚ =============
	this->getBackBuffer()->render(getHDC(), 0, 0);

}

