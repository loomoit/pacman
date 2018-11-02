#pragma once
#include "gameNode.h"
#include "pacmanMap.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

enum PACDIRECTION
{
	PACDIRECTION_LEFT,
	PACDIRECTION_UP,
	PACDIRECTION_RIGHT,
	PACDIRECTION_DOWN
};


class pacman : public gameNode
{
private:
	pacmanMap *			_pacmanMap;
	PACDIRECTION		_direction;

	image*			_image;			
	RECT			_rc;			
	float			_x, _y;			
	float			_speed;			

	int _frameCount;

public:
	pacman();
	~pacman();

	HRESULT init();
	void release();
	void update();
	void render();

	void pacmanMove();
	void setPacmanPosition();

	void setPacmanMapMemoryAddressLink(pacmanMap* tm) { _pacmanMap = tm; }

	POINT getPosition() { return PointMake(_x, _y); }
};

