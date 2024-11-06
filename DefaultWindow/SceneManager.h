#pragma once
#include "Scene.h"

class CSceneManager
{
private:
	CSceneManager();
	~CSceneManager();

public:
	static void Instantiate();
	static void Destroy();
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC _hdc);
	void Release();

private:
	vector<CScene*> m_Scenes;
	CScene* m_cCurrentScene;

};

extern CSceneManager* sceneMgr;