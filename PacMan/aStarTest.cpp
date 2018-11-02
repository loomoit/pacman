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
	
	//���� Ÿ��	
	_startTile->init(startX/ TILEWIDTH, startY/ TILEHEIGHT);
	_startTile->setAttribute("start");
	
	//���� Ÿ��	
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
				// �Ѹ��̶� ��ġ�� �ϰ������ �߰�
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

			//����ó��
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			//���� Ÿ���� ��� �������ش�
			node->setParentNode(_currentTile);

			//������ �Ұ��� �ΰ� üũ���ߴ��� �Ǵ�
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
	//���ϱ� ���ϰ� ������ ��κ���� �����ص���
	float tempTotalCost = 500;
	tile* tempTile = NULL;		// ���� ���� ��η� �� �� �ִ� Ÿ��

	//���¸���Ʈ ���Ϳ��� ���� ���� ��θ� �̾Ƴ���
	for (int i = 0; i < addOpenList(_currentTile).size(); ++i)
	{
		if (_vOpenList[i] == NULL) continue;
		// F = G + H

		//H ���ο� �簢��(�ֺ� 8ĭ �� �ϳ�)���� ���� ������(end)������ �����̵����
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) +
			 abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		//G : ������(parentNode)���� ���� ���ο� �簢��(�ֺ� 8ĭ �� �ϳ�)������ �̵����						// 14 : �밢���̵� ���, 10 : ���μ����̵� ���
		_vOpenList[i]->setCostFromStart(getDistance(center1.x, center1.y, center2.x, center2.y) > TILESIZE ? 14 : 10);

		//F = G + H �Ѻ��
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + 
									_vOpenList[i]->getCostFromStart());

		//���� ��κ���� ����
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

	//����������
	if (tempTile->getAttribute() == "end")
	{
		while (_currentTile->getParentNode() != NULL)
		{
			_currentTile->setColor(RGB(22, 14, 128));
			// ���� ���� ��� Ÿ���� �߰�(����)
			_vMoveList.push_back(_currentTile);
			_currentTile = _currentTile->getParentNode();			
		}

		if (_vMoveList.size() >= 1)
		{
			// ���� ���� ��� Ÿ�� ��, �� ������ Ÿ���� start��ġ�� ���� ����� Ÿ���̴�( = ������ �����̴� Ÿ���̴�)
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
