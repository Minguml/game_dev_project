#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "PlayScene.h"

#include "Coin.h"
#include "Mushroom.h"

#define ID_ANI_QUESTIONBLOCK 100001
#define ID_ANI_EMTY_QUESTIONBLOCK 100002

#define	QUESTION_BLOCK_WIDTH 16
#define QUESTION_BLOCK_BBOX_WIDTH 16
#define QUESTION_BLOCK_BBOX_HEIGHT 16
#define QUESTION_BLOCK_DOWN 0.007f
#define QUESTION_BLOCK_UP 15

#define QUESTION_BLOCK_STATE_IDLE 100
#define QUESTION_BLOCK_STATE_OPENED 200


class CQuestionBlock : public CGameObject
{
	int brick_type; //0: coin , 1 mushroom, 2 leaf, 3 life up 
	bool isEmpty = false;
	float beforeHit_y;
public:
	CQuestionBlock(float x, float y, int type = 0) : CGameObject(x, y)
	{
		this->brick_type = type;
		this->beforeHit_y = y;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetEmpty(bool state) { this->isEmpty = state; }
	bool IsEmpty() { return this->isEmpty; }
	int GetBrickType() { return this->brick_type; }
};
