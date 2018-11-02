#pragma once
#include "gameNode.h"
#include "tileNode.h"

enum CTRL
{
	CTRL_SAVE,			//���̺� ��ư
	CTRL_LOAD,			//�ε� ��ư
	CTRL_TERRAINDRAW,	//���� ��ư
	CTRL_OBJDRAW,		//������Ʈ ��ư
	CTRL_ERASER,		//���찳 ��ư
	CTRL_END
};

struct tagButton
{
	RECT rc;
	CTRL ctrl;
};

class tileMapScene : public gameNode
{
private:
	tagButton _btn[5];

	tagCurrentTile	_currentTile;
	tagSampleTile	_sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagTile			_tiles[TILEX * TILEY];


	bool _isLButtonDown;
	int _pos[2];

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setup();
	virtual void setMap();
	virtual void save();
	virtual void load();

	//� ����, � ������Ʈ�� �����ߴ��� ���θ� ��ȯ�ϴ� �Լ�
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);

	tileMapScene();
	~tileMapScene();
};

