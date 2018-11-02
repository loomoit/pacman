#pragma once
#include "image.h"

//����� ����
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;	//�Ŵ����� �ʱ�ȭ �Ҳ��� ����

public:
	int _ctrSelect;		//��Ʈ�� ��ư 

	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//�� ���� ���� �Լ�
	virtual void setMap();
	virtual void save();
	virtual void load();
	//�� �����߳�
	void setCtrlSelect(int num) { _ctrSelect = num; }


	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	image* getBackBuffer() { return _backBuffer; }

	//DC ������
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	gameNode();
	virtual ~gameNode();
};

