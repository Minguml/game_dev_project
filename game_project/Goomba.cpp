#include "Goomba.h"

CGoomba::CGoomba(float x, float y, int type) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	this->type = type;
	die_start = -1;
	jump_start = -1;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		if (type == 0)
		{
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
		}
	}
	else
	{
		if (type == 0)
		{
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT;
		}
		else if (type == 1)
		{
			left = x - GOOMBA_BBOX_WIDTH_WING / 2;
			top = y - GOOMBA_BBOX_HEIGHT_WING / 2;
			right = left + GOOMBA_BBOX_WIDTH_WING;
			bottom = top + GOOMBA_BBOX_HEIGHT_WING;
		}
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

	if (type == 1 && e->ny != 0 && e->obj->IsBlocking())
	{
		if (jumpable || e->ny >= 0)
		{
			vy = 0;
			ay = -ay;
			jumpable = false;
		}

		if (!isOnPlatform)
		{
			isOnPlatform = true;
			jump_start = GetTickCount64();
		}
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (type == 1)
	{
		if (vy <= -GOOMBA_JUMP_SPEED)
		{
			vy = 0;
			ay = -ay;
		}
	}

	if ((state == GOOMBA_STATE_DIE || state == GOOMBA_STATE_FLIPPED) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	if (type == 1 && GetTickCount64() - jump_start > GOOMBA_JUMP_TIMEOUT)
	{
		jumpable = true;
		isOnPlatform = false;
		ay = GOOMBA_GRAVITY;
		jump_start = -1;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = -1;

	switch (type)
	{
	case 0:
		aniId = ID_ANI_GOOMBA_WALKING;
		break;
	case 1:
		aniId = ID_ANI_GOOMBA_WALKING_WING;
		break;

	}

	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;

	}
	else if (state == GOOMBA_STATE_FLIPPED && type == 0)
		aniId = ID_ANI_GOOMBA_FLIP;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		if (type == 0)
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_FLIPPED:
		die_start = GetTickCount64();
		y -= GOOMBA_BBOX_HEIGHT;
		vx = 0;
		ay = GOOMBA_GRAVITY;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	}
}
