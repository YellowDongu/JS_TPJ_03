#pragma once
#include "Scene.h"
#include "GameSelectButton.h"

class CMainMenu : public CScene
{
public:
	CMainMenu();
	virtual ~CMainMenu();

	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void Release() override;

private:

	vector<GameSelectButton*> buttons;
};
