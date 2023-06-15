#pragma once
#include "GameObject.h"

#define BULLET_SPEED_1	0.4f
#define BULLET_SPEED_2	0.4f

#define BULLET_BBOX_WIDTH 8
#define BULLET_BBOX_HEIGHT 8

#define ID_ANI_BULLET	5700

class CFireball : public CGameObject
{
public:
	CFireball(float x, float y, int zone, int dir);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};