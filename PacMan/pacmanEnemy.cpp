#include "stdafx.h"
#include "pacmanEnemy.h"


pacmanEnemy::pacmanEnemy()
{
}


pacmanEnemy::~pacmanEnemy()
{
}

HRESULT pacmanEnemy::init()
{
	_direction = ENEMYDIRECTION_RIGHT;

	_image = IMAGEMANAGER->addFrameImage("enemy", "image/pacmanEnemy.bmp", 0, 0, 64, 128, 2, 4, true, RGB(255, 0, 255));

	_x = 400, _y = WINSIZEY / 2 - 50;
	_speed = 1.2f;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	_astar = new aStarTest;
	_astar->init();
	_astar->setPacmanMapMemoryAddressLink(_pacmanMap);
	_astar->setTiles(_x, _y, _pacman->getPosition().x, _pacman->getPosition().y);

	index = 0;

	return S_OK;
}

void pacmanEnemy::release()
{
}

void pacmanEnemy::update()
{
	enemyMove();

	//프레임전환
	_frameCount++;
	if (_frameCount > 10)
	{
		_frameCount = 0;
		if (_image->getFrameX() >= _image->getMaxFrameX())
			_image->setFrameX(0);
		else
			_image->setFrameX(_image->getFrameX() + 1);

	}

	_astar->update();
}

void pacmanEnemy::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
	_astar->render();

	if (KEYMANAGER->isToggleKey(VK_F1))
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void pacmanEnemy::enemyMove()
{	
	// 다음 목적지 타일 받아오기
	tile* nextTile = _astar->getNextMoveTile();
	// 예외처리 : 다음 목적지 타일이 없으면 더이상 움직이지 않는다.
	if (nextTile == NULL) return;			
	// 플레이어가 다음 목적지의 타일까지 도달했으면, 다시 길찾기 경로 바꿔주기
	if (nextTile->getCenter().x == _x && nextTile->getCenter().y == _y)
	{
		_astar->setTiles(_x, _y, _pacman->getPosition().x, _pacman->getPosition().y);
	}

	if		(_x > nextTile->getCenter().x) _direction = ENEMYDIRECTION_LEFT;
	else if (_x < nextTile->getCenter().x) _direction = ENEMYDIRECTION_RIGHT;
	else if (_y > nextTile->getCenter().y) _direction = ENEMYDIRECTION_UP;
	else if (_y < nextTile->getCenter().y) _direction = ENEMYDIRECTION_DOWN;


	switch (_direction)
	{
	case PACDIRECTION_LEFT:
		_image->setFrameY(3);
		_x -= _speed;
		if (_x < nextTile->getCenter().x) _x = nextTile->getCenter().x;
		break;
	case PACDIRECTION_UP:
		_image->setFrameY(0);
		_y -= _speed;
		if (_y < nextTile->getCenter().y) _y = nextTile->getCenter().y;
		break;
	case PACDIRECTION_RIGHT:
		_image->setFrameY(2);
		_x += _speed;
		if (_x > nextTile->getCenter().x) _x = nextTile->getCenter().x;
		break;
	case PACDIRECTION_DOWN:
		_image->setFrameY(1);
		_y += _speed;
		if (_y > nextTile->getCenter().y) _y = nextTile->getCenter().y;
		break;
	}


	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

}

void pacmanEnemy::setEnemyPosition()
{
}
