#pragma once
#include "gameNode.h"
#include "tileNode.h"

enum CTRL
{
	CTRL_SAVE,			//세이브 버튼
	CTRL_LOAD,			//로드 버튼
	CTRL_TERRAINDRAW,	//지형 버튼
	CTRL_OBJDRAW,		//오브젝트 버튼
	CTRL_ERASER,		//지우개 버튼
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

	//어떤 지형, 어떤 오브젝트를 선택했는지 여부를 반환하는 함수
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);

	tileMapScene();
	~tileMapScene();
};

