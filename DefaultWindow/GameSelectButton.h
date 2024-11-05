#pragma once

class GameSelectButton
{
public:
	GameSelectButton();
	~GameSelectButton();

	void init(RECT& rect, int number);
	void render(HDC _hdc);

	const RECT& buttonArea() const { return area; }
	const int& stageNumber() const { return stageNum; }

private:
	RECT area;
	int stageNum;
};
