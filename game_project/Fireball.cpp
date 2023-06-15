#include "Fireball.h"

CFireball::CFireball(float x, float y, int zone, int dir) :CGameObject(x, y)
{
	int angle = 1;

	if (zone > 2) angle = -1;

	if (zone == 1 || zone == 3)
	{
		vx = BULLET_SPEED_1 * dir;
		vy = BULLET_SPEED_1 * angle;
	}
	else
	{
		vx = BULLET_SPEED_2 * dir * 2;
		vy = BULLET_SPEED_2 * angle;
	}
}

void CFireball::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BULLET_BBOX_WIDTH / 2;
	top = y - BULLET_BBOX_HEIGHT / 2;
	right = left + BULLET_BBOX_WIDTH;
	bottom = top + BULLET_BBOX_HEIGHT;
}


void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx;
	y += vy;
}


void CFireball::Render()
{
	int aniId = ID_ANI_BULLET;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}
