#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16
#define COIN_DISTANCE 3.0f
#define COIN_SPEED 0.169f


class CCoin : public CGameObject {
	int coin_type = 0; //0: normal 1: in question block
	bool flyable = false;
	float flyDistance = 0;
public:
    CCoin(float x, float y, int ct = 0) : CGameObject(x, y) {
        this->coin_type = ct;
        if (coin_type == 1)
            this->vy = COIN_SPEED;
    }
    void Render();
    /*virtual void OnNoCollision(DWORD dt);*/
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    void SetFly(bool state) { this->flyable = state; }
    int GetCoinType() { return this->coin_type; }
    void OnNoCollision(DWORD dt) { y -= vy * dt; }
    int IsBlocking() { return 0; }
};