#pragma once
#include "tileNode.h"
#include "gameNode.h"

class pacmanMap : public gameNode
{
private:
	tagTile	_tiles[TILEX * TILEY];
	DWORD	_attribute[TILEX * TILEY];	// 타일 속성

	int _pos[2];

public:
	pacmanMap();
	~pacmanMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void load();

	//타일 접근자
	tagTile* getTiles() { return _tiles; }
	//타일 속성에 대한 접근자가 필요하겠죠? 팁2
	DWORD* getAttribute() { return _attribute; }

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }
};

