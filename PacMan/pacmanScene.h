#pragma once
#include "gameNode.h"
#include "pacmanMap.h"
#include "pacman.h"
#include "pacmanEnemy.h"

class pacmanScene : public gameNode
{
private:
	pacman * _pacman;
	pacmanEnemy* _pacmanEnemy;
	pacmanMap*	_pacmanMap;

public:
	pacmanScene();
	~pacmanScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

