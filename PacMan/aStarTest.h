#pragma once
#include "gameNode.h"
#include "tile.h"
#include "pacmanMap.h"

class aStarTest : public gameNode
{
private:
	//전체 타일을 담을 벡터
	vector<tile*>			_vTotalList;
	vector<tile*>::iterator _viTotalList;

	//갈 수 있는 길을 담은 벡터
	vector<tile*>			_vOpenList;
	vector<tile*>::iterator _viOpenList;

	//가장 빠른 길이 담기는 벡터
	vector<tile*>	_vClosedList;
	vector<tile*>::iterator _viClosedList;

	//움직일수있는 칸이 담기는 벡터
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

	//타일 셋팅 함수
	void setTiles(int startX, int startY, int endX, int endY);

	//갈수 있는 타일을 체크해서 추가해주는 함수
	vector<tile*> addOpenList(tile* currentTile);

	//길 찾는 함수
	void pathFinder();

	//pacmanMap과 연결하는 함수
	void setPacmanMapMemoryAddressLink(pacmanMap* pm) { _pacmanMap = pm; }

	vector<tile*> getVClosedList() { return _vClosedList; }
	tile*	getNextMoveTile() { return _nextMoveTile; }

	void release();
	void update();
	void render();
};

