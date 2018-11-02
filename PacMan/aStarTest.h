#pragma once
#include "gameNode.h"
#include "tile.h"
#include "pacmanMap.h"

class aStarTest : public gameNode
{
private:
	//��ü Ÿ���� ���� ����
	vector<tile*>			_vTotalList;
	vector<tile*>::iterator _viTotalList;

	//�� �� �ִ� ���� ���� ����
	vector<tile*>			_vOpenList;
	vector<tile*>::iterator _viOpenList;

	//���� ���� ���� ���� ����
	vector<tile*>	_vClosedList;
	vector<tile*>::iterator _viClosedList;

	//�����ϼ��ִ� ĭ�� ���� ����
	vector<tile*>	_vMoveList;
	vector<tile*>::iterator _viMoveList;

	tile* _nextMoveTile;
	
	tile* _startTile;
	tile* _endTile;
	tile* _currentTile;
	pacmanMap*	_pacmanMap;

	int _count;
	bool _start;
public:
	aStarTest();
	~aStarTest();

	HRESULT init();

	//Ÿ�� ���� �Լ�
	void setTiles(int startX, int startY, int endX, int endY);

	//���� �ִ� Ÿ���� üũ�ؼ� �߰����ִ� �Լ�
	vector<tile*> addOpenList(tile* currentTile);

	//�� ã�� �Լ�
	void pathFinder();

	//pacmanMap�� �����ϴ� �Լ�
	void setPacmanMapMemoryAddressLink(pacmanMap* pm) { _pacmanMap = pm; }

	vector<tile*> getVClosedList() { return _vClosedList; }
	tile*	getNextMoveTile() { return _nextMoveTile; }

	void release();
	void update();
	void render();
};

