#pragma once
#include "gameNode.h"
#include "pacmanMap.h"
#include "pacman.h"
#include "aStarTest.h"

enum ENEMYDIRECTION
{
	ENEMYDIRECTION_LEFT,
	ENEMYDIRECTION_UP,
	ENEMYDIRECTION_RIGHT,
	ENEMYDIRECTION_DOWN
};

class pacmanEnemy : public gameNode
{
private:
	pacmanMap *			_pacmanMap;
	pacman*				_pacman;
	ENEMYDIRECTION		_direction;
	aStarTest*			_astar;

	image*			_image;
	RECT			_rc;
	float			_x, _y;
	float			_speed;

	int _frameCount;

	int index;

public:
	pacmanEnemy();
	~pacmanEnemy();

	HRESULT init();
	void release();
	void update();
	void render();

	void enemyMove();
	void setEnemyPosition();

	void setPacmanMapMemoryAddressLink(pacmanMap* pm) { _pacmanMap = pm; }
	void setPacmanMemoryAddressLink(pacman* pacman) { _pacman = pacman; }

};

