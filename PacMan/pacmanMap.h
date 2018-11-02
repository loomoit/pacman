#pragma once
#include "tileNode.h"
#include "gameNode.h"

class pacmanMap : public gameNode
{
private:
	tagTile	_tiles[TILEX * TILEY];
	DWORD	_attribute[TILEX * TILEY];	// Ÿ�� �Ӽ�

	int _pos[2];

public:
	pacmanMap();
	~pacmanMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void load();

	//Ÿ�� ������
	tagTile* getTiles() { return _tiles; }
	//Ÿ�� �Ӽ��� ���� �����ڰ� �ʿ��ϰ���? ��2
	DWORD* getAttribute() { return _attribute; }

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }
};

