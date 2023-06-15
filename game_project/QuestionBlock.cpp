#include "QuestionBlock.h"
#include "debug.h"


void CQuestionBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (this->isEmpty == false)
		animations->Get(ID_ANI_QUESTIONBLOCK)->Render(x, y);
	else
		animations->Get(ID_ANI_EMTY_QUESTIONBLOCK)->Render(x, y);
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTION_BLOCK_BBOX_WIDTH / 2;
	t = y - QUESTION_BLOCK_BBOX_HEIGHT / 2;
	r = l + QUESTION_BLOCK_BBOX_WIDTH;
	b = t + QUESTION_BLOCK_BBOX_HEIGHT;
}

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if (y < beforeHit_y && this->isEmpty == true)
	{
		vy = QUESTION_BLOCK_DOWN * dt;
	}
	else
	{
		vy = 0;
		y = beforeHit_y;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}