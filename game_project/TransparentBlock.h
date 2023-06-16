#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define TB_BBOX_WIDTH 16
#define TB_BBOX_HEIGHT 16
#define TB_ID_ANIMATION	60000

class CTransparentBlock : public CGameObject {
public:
	CTransparentBlock(float x, float y) : CGameObject(x, y) { this->x = x; this->y = y; }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
};