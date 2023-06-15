#pragma once
#include "GameObject.h"

#define PLAIN_SPEED	0.4f

#define PLAIN_BBOX_WIDTH 16
#define PLAIN_BBOX_HEIGHT 24

#define DETECTZONE	128
#define SHOOT_TIME	3000
#define BITE_TIME	2000
#define OFFSET	24

#define ID_ANI_PLAIN_SHOOTING_LEFT	5500
#define ID_ANI_PLAIN_SHOOTING_MOVING_LEFT 5600
#define ID_ANI_PLAIN_SHOOTING_RIGHT	5550
#define ID_ANI_PLAIN_SHOOTING_MOVING_RIGHT	5650

#define ID_ANI_PLAIN_SHOOTING_LEFT_GREEN	5555
#define ID_ANI_PLAIN_SHOOTING_MOVING_LEFT_GREEN 5655
#define ID_ANI_PLAIN_SHOOTING_RIGHT_GREEN	5556
#define ID_ANI_PLAIN_SHOOTING_MOVING_RIGHT_GREEN	5656

#define ID_ANI_PLAIN_BITING	5770

#define PLAIN_STATE_SHOOTING	100
#define PLAIN_STATE_BITING	200

class CFireFlower : public CGameObject
{
protected:
	int type;			//0: shooting red, 1: shooting green, 2: biting green
	float base_y;
	int dir;			//-1: left, 1: right
	int isShooting;
	bool bulletOut;

	ULONGLONG shoot_start;
	ULONGLONG biting_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; }
public:
	CFireFlower(float x, float y, int type);

	virtual int GetType() { return type; }
	virtual void SetState(int state);
};