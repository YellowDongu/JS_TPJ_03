#include "stdafx.h"
#include "GameSelectButton.h"


GameSelectButton::GameSelectButton()
{
}

GameSelectButton::~GameSelectButton()
{
}

void GameSelectButton::init(RECT& rect, int number)
{
	area = rect;
	stageNum = number;
}

void GameSelectButton::render(HDC _hdc)
{
	Rectangle(_hdc, area.left, area.top, area.right, area.bottom);

}
