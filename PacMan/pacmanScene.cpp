#include "stdafx.h"
#include "pacmanScene.h"


pacmanScene::pacmanScene()
{
}


pacmanScene::~pacmanScene()
{
}

HRESULT pacmanScene::init()
{
	_pacmanMap = new pacmanMap;
	_pacmanMap->init();

	_pacman = new pacman;
	_pacman->init();
	_pacman->setPacmanMapMemoryAddressLink(_pacmanMap);
	//_tank->setTankPosition();
	
	_pacmanEnemy = new pacmanEnemy;
	_pacmanEnemy->setPacmanMapMemoryAddressLink(_pacmanMap);
	_pacmanEnemy->setPacmanMemoryAddressLink(_pacman);
	_pacmanEnemy->init();

	return S_OK;
}

void pacmanScene::release()
{
}

void pacmanScene::update()
{
	_pacmanMap->update();
	_pacman->update();
	_pacmanEnemy->update();
}

void pacmanScene::render()
{
	_pacmanMap->render();
	_pacman->render();
	_pacmanEnemy->render();
}
