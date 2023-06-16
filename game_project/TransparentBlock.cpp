#include "TransparentBlock.h"

void CTransparentBlock::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(TB_ID_ANIMATION)->Draw(x, y);

	//RenderBoundingBox();
}

void CTransparentBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TB_BBOX_WIDTH / 2;
	t = y - TB_BBOX_HEIGHT / 2;
	r = l + TB_BBOX_WIDTH;
	b = t + TB_BBOX_HEIGHT;
}