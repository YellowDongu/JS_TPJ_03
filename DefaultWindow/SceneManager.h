#pragma once
#include "Scene.h"

class CSceneManager
{
private:
	CSceneManager();
	~CSceneManager();

public:
	static void Instantiate();
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC _hdc);
	void Release();
	void destroy();

private:
	vector<CScene*> m_Scenes;
	CScene* m_cCurrentScene;

};

extern CSceneManager* sceneMgr;