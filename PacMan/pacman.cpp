#include "stdafx.h"
#include "pacman.h"


pacman::pacman()
{
}


pacman::~pacman()
{
}

HRESULT pacman::init()
{
	_direction = PACDIRECTION_LEFT;

	_image = IMAGEMANAGER->addFrameImage("pacman", "image/pacman.bmp", 0, 0, 64, 128, 2, 4, true, RGB(255, 0, 255));

	_x = 200, _y = 180;
	_speed = 100.0f;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

void pacman::release()
{
}

void pacman::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_direction = PACDIRECTION_LEFT;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_direction = PACDIRECTION_RIGHT;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_direction = PACDIRECTION_UP;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_direction = PACDIRECTION_DOWN;
	}

	pacmanMove();

	// 아이템 먹었을때
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		RECT rc;
		if (_pacmanMap->getAttribute()[i] == ATTR_EAT)
		{
			if (_pacmanMap->getTiles()[i].rc.left / TILEWIDTH == (_rc.left+2) / TILEWIDTH 
				&& _pacmanMap->getTiles()[i].rc.top / TILEHEIGHT == (_rc.top+2) / TILEHEIGHT)
			{
				_pacmanMap->getAttribute()[i] = 0;
				_pacmanMap->getTiles()[i].obj = OBJ_NONE;
				break;
			}
		}
	}

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
}

void pacman::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
	if (KEYMANAGER->isToggleKey(VK_F1))
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

}

void pacman::pacmanMove()
{
	//오늘 과제에 핵심 포인트가 되는 함수

	//가상의 충돌판정 렉트를 선언
	RECT rcCollision;

	int tileIndex[2];	//이동 방향에 따른 타일속성을 검출하기위한 타일 인덱스 값 계산용 배열
	int tileX, tileY;	//탱크 이동 방향에 따라 '검출'하기 위한 인덱스 계산용 변수

						//가상의 충돌판정 렉트에 탱크 렉트를 대입한다
	rcCollision = _rc;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;

	switch (_direction)
	{
	case PACDIRECTION_LEFT:
		_image->setFrameY(3);

		_x -= moveSpeed;

		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case PACDIRECTION_UP:
		_image->setFrameY(0);

		_y -= moveSpeed;

		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case PACDIRECTION_RIGHT:
		_image->setFrameY(2);

		_x += moveSpeed;

		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	case PACDIRECTION_DOWN:
		_image->setFrameY(1);

		_y += moveSpeed;

		rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	}


	//임의의 충돌렉트 사이즈를 좀 줄이면 훨씬 쉽게 처리할수있다.
	rcCollision.left += 2;
	rcCollision.top += 2;
	rcCollision.right -= 2;
	rcCollision.bottom -= 2;

	//밟고 있는 타일 인덱스 번호 알아온다
	//        64
	//2.2 
	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	//방향에 따른 타일 검출
	//타일 검출을 통해서 내 진행 방향(좌표)에 있는 타일의 속성을 검출한다
	switch (_direction)
	{
	case PACDIRECTION_LEFT:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1) * TILEX;
		break;	
	case PACDIRECTION_UP:
		tileIndex[0] = tileX + tileY * TILEY;
		tileIndex[1] = tileX + 1 + tileY * TILEX;
		break;
	case PACDIRECTION_RIGHT:
		tileIndex[0] = (tileX + tileY * TILEY) + 1;
		tileIndex[1] = (tileX + (1 + tileY) * TILEX) + 1;
		break;
	case PACDIRECTION_DOWN:
		tileIndex[0] = (tileX + tileY * TILEX) + TILEX;
		tileIndex[1] = (tileX + 1 + tileY * TILEX) + TILEX;
		break;
	}

	cout << tileIndex[0] << ", " << tileIndex[1] << endl;

	//팁4
	//한 타일의 규격 32
	for (int i = 0; i < 2; i++)
	{
		RECT rc;
		if (((_pacmanMap->getAttribute()[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE) &&
			IntersectRect(&rc, &_pacmanMap->getTiles()[tileIndex[i]].rc, &rcCollision))
		{
			switch (_direction)
			{
			case PACDIRECTION_LEFT:
				_rc.left = _pacmanMap->getTiles()[tileIndex[i]].rc.right;
				_rc.right = _rc.left + 30;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				break;
			case PACDIRECTION_UP:
				_rc.top = _pacmanMap->getTiles()[tileIndex[i]].rc.bottom;
				_rc.bottom = _rc.top + 30;
				_y = _rc.bottom - (_rc.bottom - _rc.top) / 2;
				break;
			case PACDIRECTION_RIGHT:
				_rc.right = _pacmanMap->getTiles()[tileIndex[i]].rc.left;
				_rc.left = _rc.right - 30;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				break;
			case PACDIRECTION_DOWN:
				_rc.bottom = _pacmanMap->getTiles()[tileIndex[i]].rc.top;
				_rc.top = _rc.bottom - 30;
				_y = _rc.bottom - (_rc.bottom - _rc.top) / 2;
				break;

			}
			return;
		}
	}

	if (_x > 640 - 16) _x = 0 + 32; 
	if (_x < 0 + 16) _x = 640 - 32;
	if (_y > WINSIZEY - 16) _y = 0 + 32;
	if (_y < 0 + 16) _y = WINSIZEY - 32; 0 + 32;

	rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_rc = rcCollision;

}

void pacman::setPacmanPosition()
{
	_rc = _pacmanMap->getTiles()[_pacmanMap->getPosFirst()].rc;

	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;
}
