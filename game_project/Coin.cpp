#include "Coin.h"
#include "debug.h"

void CCoin::Render()
{
    CAnimations* animations = CAnimations::GetInstance();
    animations->Get(ID_ANI_COIN)->Render(x, y);

    //RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - COIN_BBOX_WIDTH / 2;
    t = y - COIN_BBOX_HEIGHT / 2;
    r = l + COIN_BBOX_WIDTH;
    b = t + COIN_BBOX_HEIGHT;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    flyDistance += vy;
    if (this->flyable == true && coin_type == 1)
    {
        if (flyDistance > COIN_DISTANCE)
        {
            vy = -vy;
        }
        else if (flyDistance < 0)
        {
            this->Delete();
        }
    }

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}