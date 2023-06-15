#include "FireFlower.h"
#include "Fireball.h"
#include "Debug.h"
#include "Scene.h"

CFireFlower::CFireFlower(float x, float y, int type) :CGameObject(x, y)
{
	this->type = type;
	base_y = y;
	shoot_start = -1;
	isShooting = 0;
	bulletOut = false;
	dir = -1;
}

void CFireFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PLAIN_BBOX_WIDTH / 2;
	top = y - PLAIN_BBOX_HEIGHT / 2;
	right = left + PLAIN_BBOX_WIDTH;
	bottom = top + PLAIN_BBOX_HEIGHT;
}

void CFireFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy;

	if (y < base_y - OFFSET)
	{
		vy = 0;
		y = base_y - OFFSET;
	}
	else if (y > base_y)
	{
		vy = 0;
		y = base_y;
	}

	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
	LPGAMEOBJECT player = thisscene->GetPlayer();

	float px, py;
	player->GetPosition(px, py);


	if (abs(x - px) < DETECTZONE && !isShooting && type == 0)
	{
		SetState(PLAIN_STATE_SHOOTING);

		if (x - px <= 0) dir = 1; else dir = -1;

		vy = -PLAIN_SPEED;
	}
	else if (GetTickCount64() - shoot_start > SHOOT_TIME && isShooting == 1)
	{
		shoot_start = -1;
		isShooting = 0;
		//shoot_start = -1;

		int zone = -1;
		if (abs(x - px) <= 64)
		{
			if (y < py)
				zone = 1;
			else
				zone = 3;
		}
		else {
			if (y < py)
				zone = 2;
			else
				zone = 4;
		}

		CFireball* newbullet = new CFireball(x, y, zone, dir);
		LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

		thisscene->AddObjectToScene(newbullet);

		vy = PLAIN_SPEED;
		shoot_start = -1;
		isShooting = 0;
	}
}

void CFireFlower::SetState(int state)
{
	if (state == PLAIN_STATE_SHOOTING)
	{
		isShooting = 1;
		shoot_start = GetTickCount64();
	}
	else if (state == PLAIN_STATE_BITING)
	{
		biting_start = GetTickCount64();
	}
}

void CFireFlower::Render()
{
	int aniId = NULL;

	switch (type)
	{
	case 0:
		if (dir == -1)
		{
			if (y <= base_y - OFFSET)
				aniId = ID_ANI_PLAIN_SHOOTING_MOVING_LEFT;
			else
				aniId = ID_ANI_PLAIN_SHOOTING_LEFT;
		}
		else
		{
			if (y <= base_y - OFFSET)
				aniId = ID_ANI_PLAIN_SHOOTING_MOVING_RIGHT;
			else
				aniId = ID_ANI_PLAIN_SHOOTING_RIGHT;
		}
		break;
	case 1:
		if (dir == -1)
		{
			if (y <= base_y - OFFSET)
				aniId = ID_ANI_PLAIN_SHOOTING_MOVING_LEFT_GREEN;
			else
				aniId = ID_ANI_PLAIN_SHOOTING_LEFT_GREEN;
		}
		else
		{
			if (y <= base_y - OFFSET)
				aniId = ID_ANI_PLAIN_SHOOTING_MOVING_RIGHT_GREEN;
			else
				aniId = ID_ANI_PLAIN_SHOOTING_RIGHT_GREEN;
		}
		break;
	case 2:
		aniId = ID_ANI_PLAIN_BITING;
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

