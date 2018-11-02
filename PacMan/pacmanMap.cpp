#include "stdafx.h"
#include "pacmanMap.h"


pacmanMap::pacmanMap()
{
}


pacmanMap::~pacmanMap()
{
}

HRESULT pacmanMap::init()
{
	IMAGEMANAGER->addFrameImage("mapTiles", "image/tilemap.bmp", 0, 0, 512, 160, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	load();

	return S_OK;
}

void pacmanMap::release()
{
}

void pacmanMap::update()
{
}

void pacmanMap::render()
{
	IMAGEMANAGER->render("mapTiles", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth(), 0);

	//지형
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	//오브젝트
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//오브젝트 속성이 아니면 그리지마라
		if (_tiles[i].obj == OBJ_NONE)	continue;

		IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}

void pacmanMap::load()
{
	HANDLE file;
	DWORD load;

	file = CreateFile("mapTool.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &load, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &load, NULL);

	CloseHandle(file);

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].obj == OBJ_TANK1) _tiles[i].obj = OBJ_NONE;
	}

	memset(_attribute, 0, sizeof(DWORD) * TILEX * TILEY);

	// 속성 정의
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].terrain == TR_WALL)  _attribute[i] |= ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_EAT)	   _attribute[i] |= ATTR_EAT;
	}
}


/*
	언니이이이이이이
	사랑해요오오오오오오
	하트하트~~~
	언니가 있어서 아주 아주 든든하답니다ㅎㅎㅎㅎㅎㅎ
	><><><><><><><><><
	언니이 조아요오오오오오♡♡

	re: 나두 많이 조와해♡♡
*/