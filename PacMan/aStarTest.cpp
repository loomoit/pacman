#include "stdafx.h"
#include "aStarTest.h"
#include "tileNode.h"

aStarTest::aStarTest()
{
}


aStarTest::~aStarTest()
{
}

HRESULT aStarTest::init()
{
	_startTile = new tile;
	_endTile = new tile;
	return S_OK;
}

void aStarTest::setTiles(int startX, int startY, int endX, int endY)
{
	if (startX / TILEWIDTH == endX / TILEWIDTH && startY/ TILEHEIGHT == endY/ TILEHEIGHT) return;

	_vTotalList.clear();
	_vOpenList.clear();
	_vClosedList.clear();
	_vMoveList.clear();
	
	//시작 타일	
	_startTile->init(startX/ TILEWIDTH, startY/ TILEHEIGHT);
	_startTile->setAttribute("start");
	
	//도착 타일	
	_endTile->init(endX/ TILEWIDTH, endY/ TILEHEIGHT);
	_endTile->setAttribute("end");

	_currentTile = _startTile;

	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{
			if (j == _startTile->getIdX() && i == _startTile->getIdY())
			{
				_startTile->setColor(RGB(0, 255, 255));
				_endTile->setIsOpen(true);
				_vTotalList.push_back(_startTile);
				continue;
			}
			if (j == _endTile->getIdX() && i == _endTile->getIdY())
			{
				_endTile->setColor(RGB(10, 120, 55));
				_endTile->setIsOpen(true);
				_vTotalList.push_back(_endTile);
				// 팩맨이랑 겹치게 하고싶으면 추가
				_vMoveList.push_back(_endTile);
				continue;
			}

			
			tile* node = new tile;
			node->init(j, i);

			if (_pacmanMap->getTiles()[i * TILENUMY + j].terrain == TR_WALL)
			{
				node->setIsOpen(false);
				node->setAttribute("wall");
				node->setColor(RGB(230, 140, 200));
			}
			else node->setIsOpen(true);

			_vTotalList.push_back(node);
		}
	}

	pathFinder();
}

vector<tile*> aStarTest::addOpenList(tile* currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if ((i == 0 && j == 0) || (i == 0 && j == 2) || (i == 2 && j == 0) || (i == 2 && j == 2)) continue;

			tile* node = _vTotalList[(startY * TILENUMX) + startX + j + (i * TILENUMX)];

			//예외처리
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			//현재 타일은 계속 갱신해준다
			node->setParentNode(_currentTile);

			//임의의 불값을 두고 체크를했는지 판단
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			if (node->getAttribute() != "end")
				node->setColor(RGB(128, 64, 28));

			if (!addObj) continue;

			_vOpenList.push_back(node);
			
		}
	}

	return _vOpenList;
}

void aStarTest::pathFinder()
{
	//비교하기 편하게 임의의 경로비용을 설정해두자
	float tempTotalCost = 500;
	tile* tempTile = NULL;		// 가장 빠른 경로로 갈 수 있는 타일

	//오픈리스트 벡터에서 가장 빠른 경로를 뽑아낸다
	for (int i = 0; i < addOpenList(_currentTile).size(); ++i)
	{
		if (_vOpenList[i] == NULL) continue;
		// F = G + H

		//H 새로운 사각형(주변 8칸 중 하나)에서 최종 목적지(end)까지의 예상이동비용
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
			 abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		//G : 시작점(parentNode)으로 부터 새로운 사각형(주변 8칸 중 하나)까지의 이동비용						// 14 : 대각선이동 비용, 10 : 가로세로이동 비용
		_vOpenList[i]->setCostFromStart(getDistance(center1.x, center1.y, center2.x, center2.y) > TILESIZE ? 14 : 10);

		//F = G + H 총비용
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + 
									_vOpenList[i]->getCostFromStart());

		//빠른 경로비용을 뽑자
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;

		_vOpenList.push_back(tempTile);
	}

	//도착했으면
	if (tempTile->getAttribute() == "end")
	{
		while (_currentTile->getParentNode() != NULL)
		{
			_currentTile->setColor(RGB(22, 14, 128));
			// 가장 빠른 경로 타일을 추가(저장)
			_vMoveList.push_back(_currentTile);
			_currentTile = _currentTile->getParentNode();			
		}

		if (_vMoveList.size() >= 1)
		{
			// 가장 빠른 경로 타일 중, 맨 마지막 타일은 start위치와 제일 가까운 타일이다( = 다음에 움직이는 타일이다)
			_nextMoveTile = _vMoveList[_vMoveList.size() - 1];
		}
		return;
	}

	_vClosedList.push_back(tempTile);

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;

	pathFinder();
}

void aStarTest::release()
{
}

void aStarTest::update()
{
	
}

void aStarTest::render()
{	
}
