#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.0005f
#define KOOPA_JUMP_SPEED    0.3f
#define KOOPA_WALKING_SPEED 0.04f
#define KOOPA_SHELL_MOVING_SPEED    0.2f


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_HEIGHT_SHELL 14

#define KOOPA_SHELL_AWAKE    4000
#define KOOPA_SHELL_TIMEOUT 6000

#define KOOPA_STATE_WALKING 100        // 100: left, 101: right

#define KOOPA_STATE_SHELL 200        // 200: green, 201: red
#define KOOPA_STATE_SHELL_MOVING    300
#define KOOPA_STATE_AWAKE    400
#define KOOPA_STATE_CARRIED    500
//#define KOOPA_STATE_DIE 


//ANIMATIONS
//Normal Red
#define ID_ANI_KOOPA_NORMAL_RED_WALKING_LEFT 93100
#define ID_ANI_KOOPA_NORMAL_RED_WALKING_RIGHT 93200

#define ID_ANI_KOOPA_RED_SHELL    93300

#define ID_ANI_KOOPA_RED_SHELL_AWAKE    93400

#define ID_ANI_KOOPA_RED_SHELL_MOVING    93500

#define ID_ANI_KOOPA_RED_SHELL_FLIPPED    93600


class CKoopa : public CGameObject
{
protected:
    float ax;
    float ay;
    int type;        // 0: green normal, 1: green fly, 2: red normal, 3: red fly
    bool minusY_flag = true;
    int dir = 1;    // 1: left, -1: right
    bool isFlipped = false;

    ULONGLONG shell_start;
    BOOLEAN isOnPlatform = false;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

    virtual int IsCollidable()
    {
        if (isFlipped)
            return 0;
        return 1;
    };
    virtual int IsBlocking() { return 0; }
    virtual void OnNoCollision(DWORD dt);
    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
    virtual void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
    virtual void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
    virtual void OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e);
    //virtual void OnCollisionWithTransparentBlock(LPCOLLISIONEVENT e);

public:
    CKoopa(float x, float y, int type = 0);
    virtual void SetState(int state);
    virtual int GetType() { return type; }
    virtual void SetType(int level) { type = level; }
    virtual void SetDir(int dir) { this->dir = dir; }
    virtual bool GetStateFlipped() { return isFlipped; }
    virtual void SetStateFlipped(bool state) { isFlipped = state; }
};