#pragma once

class GameSelectButton
{
public:
	GameSelectButton();
	~GameSelectButton();

	void init(RECT& rect);
	void render(HDC _hdc);
	bool hoveringMouse();

	const RECT& buttonArea() const { return area; }
	

private:
	bool hover;
	HPEN pen;
	RECT area;
};
