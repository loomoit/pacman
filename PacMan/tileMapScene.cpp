#include "stdafx.h"
#include "tileMapScene.h"


tileMapScene::tileMapScene()
{
}


tileMapScene::~tileMapScene()
{
}

HRESULT tileMapScene::init(void)
{
	IMAGEMANAGER->addFrameImage("mapTiles", "image/tilemap.bmp", 0, 0, 512, 160, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	setup();

	return S_OK;
}

void tileMapScene::release(void)
{

}

void tileMapScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) _isLButtonDown = true;
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) _isLButtonDown = false;
		
	if(_isLButtonDown) setMap();
}

void tileMapScene::render(void)
{
	IMAGEMANAGER->render("mapTiles", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth(), 0);

	//지형
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}

	//오브젝트
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		//오브젝트 속성이 아니면 그리지마라
		if (_tiles[i].obj == OBJ_NONE) continue;
		IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}

	for (int i = 0; i < 5; ++i)
	{
		Rectangle(getMemDC(), _btn[i].rc.left, _btn[i].rc.top, _btn[i].rc.right, _btn[i].rc.bottom);
		if (i == 0) TextOut(getMemDC(), _btn[i].rc.left + 30, _btn[i].rc.top + 6, "세이브", strlen("세이브"));
		if (i == 1) TextOut(getMemDC(), _btn[i].rc.left + 30, _btn[i].rc.top + 6, "로드", strlen("저장"));
		if (i == 2) TextOut(getMemDC(), _btn[i].rc.left + 30, _btn[i].rc.top + 6, "지형", strlen("저장"));
		if (i == 3) TextOut(getMemDC(), _btn[i].rc.left + 20, _btn[i].rc.top + 6, "오브젝트", strlen("오브젝트"));
		if (i == 4) TextOut(getMemDC(), _btn[i].rc.left + 30, _btn[i].rc.top + 6, "지우개", strlen("지우개"));
	}

	char str[256];
	sprintf_s(str, "현재 컨트롤 : %d (2 : 지형, 3 : 오브젝트, 4 : 지우개)", _ctrSelect);
	TextOut(getMemDC(), 700, 600, str, strlen(str));
	
}

void tileMapScene::setup()
{
	/*_btnSave = CreateWindow("button", "저장", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 500, 100, 30, _hWnd, HMENU(0), _hInstance, NULL);
	_btnLoad = CreateWindow("button", "불러오기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 500, 100, 30, _hWnd, HMENU(1), _hInstance, NULL);
	_btnTerrainDraw = CreateWindow("button", "지형", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 560, 100, 30, _hWnd, HMENU(2), _hInstance, NULL);
	_btnObjectDraw = CreateWindow("button", "오브젝트", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 560, 100, 30, _hWnd, HMENU(3), _hInstance, NULL);
	_btnEraser = CreateWindow("button", "지우개", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 900, 560, 100, 30, _hWnd, HMENU(4), _hInstance, NULL);*/

	_btn[CTRL_SAVE].rc			= RectMake(700, 500, 100, 30);	_btn[CTRL_SAVE].ctrl = CTRL_SAVE;
	_btn[CTRL_LOAD].rc			= RectMake(800, 500, 100, 30);	_btn[CTRL_LOAD].ctrl = CTRL_LOAD;
	_btn[CTRL_TERRAINDRAW].rc	= RectMake(700, 560, 100, 30);	_btn[CTRL_TERRAINDRAW].ctrl	= CTRL_TERRAINDRAW;
	_btn[CTRL_OBJDRAW].rc		= RectMake(800, 560, 100, 30);	_btn[CTRL_OBJDRAW].ctrl = CTRL_OBJDRAW;
	_btn[CTRL_ERASER].rc		= RectMake(900, 560, 100, 30);	_btn[CTRL_ERASER].ctrl = CTRL_ERASER;
		
	//처음에는 지형을 그린다 로 둡시다
	_ctrSelect = CTRL_TERRAINDRAW;

	//타일셋 (샘플타일)
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;

			//렉트 셋팅 함수 SetRect
			//렉트 메모리 번지, left, top, right, bottom
			SetRect(&_sampleTile[i * SAMPLETILEX + j].rcTile,
				(WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth()) + j * TILESIZE,
				i * TILESIZE,
				(WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth()) + j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);

		}
	}

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	//기본 셋팅을 미리 해둡시다
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].terrainFrameX = 13;
		_tiles[i].terrainFrameY = 2;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJ_NONE;
	}

}

void tileMapScene::setMap()
{
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTile[i].rcTile, _ptMouse))
		{
			_currentTile.x = _sampleTile[i].terrainFrameX;
			_currentTile.y = _sampleTile[i].terrainFrameY;
			break;
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			if (_ctrSelect == CTRL_TERRAINDRAW)
			{
				_tiles[i].terrainFrameX = _currentTile.x;
				_tiles[i].terrainFrameY = _currentTile.y;

				_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
			}
			else if (_ctrSelect == CTRL_OBJDRAW)
			{
				_tiles[i].objFrameX = _currentTile.x;
				_tiles[i].objFrameY = _currentTile.y;

				_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
			}
			else if (_ctrSelect == CTRL_ERASER)
			{
				_tiles[i].objFrameX = NULL;
				_tiles[i].objFrameY = NULL;

				_tiles[i].obj = OBJ_NONE;
			}
			
			InvalidateRect(_hWnd, NULL, false);
			break;
		}
	}

	/*if (PtInRect(&_btnSave.rc, _ptMouse))
	{
		//_ctrSelect = CTRL_SAVE;
		save();		
	}
	if (PtInRect(&_btnLoad.rc, _ptMouse))
	{
		//_ctrSelect = CTRL_LOAD;		
		load();
		InvalidateRect(_hWnd, NULL, false);
	}

	if (PtInRect(&_btnEraser.rc, _ptMouse)) _ctrSelect = CTRL_ERASER;
	if (PtInRect(&_btnObjectDraw.rc, _ptMouse)) _ctrSelect = CTRL_OBJDRAW;
	if (PtInRect(&_btnTerrainDraw.rc, _ptMouse)) _ctrSelect = CTRL_TERRAINDRAW;*/

	for (int i = 0; i < 5; ++i)
	{
		if (PtInRect(&_btn[i].rc, _ptMouse))
			_ctrSelect = i;
	}

	if (_ctrSelect == CTRL_SAVE) { save(); _ctrSelect = CTRL_TERRAINDRAW; }
	if (_ctrSelect == CTRL_LOAD) { load(); _ctrSelect = CTRL_TERRAINDRAW; }

}

void tileMapScene::save()
{
	HANDLE file;
	DWORD save;

	file = CreateFile("mapTool.map", GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &save, NULL);

	CloseHandle(file);
}

void tileMapScene::load()
{
	HANDLE file;
	DWORD load;

	file = CreateFile("mapTool.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &load, NULL);

	CloseHandle(file);
}

TERRAIN tileMapScene::terrainSelect(int frameX, int frameY)
{
	/*if (frameX == 1 && frameY == 0) return TR_CEMENT;
	if (frameX == 2 && frameY == 0) return TR_DESERT;
	if (frameX == 3 && frameY == 0) return TR_GRASS;
	if (frameX == 4 && frameY == 0) return TR_WATER;*/
	
	if (frameY >= 2 && frameY < 4 && frameX >= 12 && frameX < 16)
	{
		return TR_GRASS;
	}			
			
	return TR_WALL;
}

OBJECT tileMapScene::objSelect(int frameX, int frameY)
{	
	/*else if (frameX == 0 && frameY == 9)
	{
		return OBJ_TANK2;
	}
	else if (frameX == 0 && frameY == 1)
	{
		return OBJ_BLOCK1;
	}
	else if (frameX == 0 && frameY == 2)
	{
		return OBJ_BLOCK3;
	}
	else if (frameX == 15 && frameY == 3)
	{
		return OBJ_BLOCKS;
	}*/	
	if (frameX == 12 && frameY == 2)
	{
		return OBJ_EAT;
	}
	if (frameX == 15 && frameY == 4)
	{
		return OBJ_TANK1;
	}

	/*for (int i = 2; i < 4; ++i)
	{
		for (int j = 12; j < 16; ++j)
		{
			if (frameX == 12 && frameY == 2)
			{
				return OBJ_EAT;
			}
			if (frameX == 15 && frameY == 4)
			{
				return OBJ_TANK1;
			}
			return OBJ_NONE;
		}
	}*/
	
	return OBJ_NONE;
}
