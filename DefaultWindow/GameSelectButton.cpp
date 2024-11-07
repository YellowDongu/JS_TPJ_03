#include "stdafx.h"
#include "GameSelectButton.h"
#include "KeyManager.h"


#define keyMgr KeyManager::Get_Instance()

GameSelectButton::GameSelectButton() : hover(false), pen(NULL), area{}
{
}

GameSelectButton::~GameSelectButton()
{
}

void GameSelectButton::init(RECT& rect)
{
	area = rect;
	pen = CreatePen(PS_SOLID, 5, RGB(200, 0, 0));
}

void GameSelectButton::render(HDC _hdc)
{
	if (hover)
	{
		HPEN oldPen = (HPEN)SelectObject(_hdc, pen);

		MoveToEx(_hdc, area.left, area.top, nullptr);
		LineTo(_hdc, area.right, area.top);
		LineTo(_hdc, area.right, area.bottom);
		LineTo(_hdc, area.left, area.bottom);
		LineTo(_hdc, area.left, area.top);

		hover = false;

		SelectObject(_hdc, oldPen);
	}


}

bool GameSelectButton::hoveringMouse()
{
	hover = true;

	if (keyMgr->Key_Pressing(VK_LBUTTON))
		return true;

	return false;
}
