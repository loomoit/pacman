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

	//走莫
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	//神崎詮闘
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//神崎詮闘 紗失戚 焼艦檎 益軒走原虞
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

	// 紗失 舛税
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].terrain == TR_WALL)  _attribute[i] |= ATTR_UNMOVE;
		if (_tiles[i].obj == OBJ_EAT)	   _attribute[i] |= ATTR_EAT;
	}
}


/*
	情艦戚戚戚戚戚戚
	紫櫛背推神神神神神神
	馬闘馬闘~~~
	情艦亜 赤嬢辞 焼爽 焼爽 窮窮馬岩艦陥ぞぞぞぞぞぞ
	><><><><><><><><><
	情艦戚 繕焼推神神神神神⊇⊇

	re: 蟹砧 弦戚 繕人背⊇⊇
*/