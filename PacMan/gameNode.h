#pragma once
#include "image.h"

//백버퍼 선언
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;	//매니져들 초기화 할껀지 여부

public:
	int _ctrSelect;		//컨트롤 버튼 

	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//맵 셋팅 관련 함수
	virtual void setMap();
	virtual void save();
	virtual void load();
	//뭘 선택했냐
	void setCtrlSelect(int num) { _ctrSelect = num; }


	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	image* getBackBuffer() { return _backBuffer; }

	//DC 접근자
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	gameNode();
	virtual ~gameNode();
};

