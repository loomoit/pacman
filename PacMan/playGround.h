#pragma once
#include "gameNode.h"
#include "pacmanScene.h"
#include "tileMapScene.h"

class playGround : public gameNode
{
private:
	//dididi	

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	playGround();
	~playGround();
};

