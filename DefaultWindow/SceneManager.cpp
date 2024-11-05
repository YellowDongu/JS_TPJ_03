#include "stdafx.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "Stage01.h"
#include "Stage02.h"
#include "Stage03.h"

CSceneManager* sceneMgr = nullptr;

CSceneManager::CSceneManager() : m_cCurrentScene(nullptr)
{
}

CSceneManager::~CSceneManager()
{
}

void CSceneManager::Instantiate()
{
	if (sceneMgr) return;
	sceneMgr = new CSceneManager();
	sceneMgr->Initialize();

	CMainMenu* mainMenu = new CMainMenu();
	CStage01* stage01 = new CStage01();
	CStage02* stage02 = new CStage02();
	CStage03* stage03 = new CStage03();

	
}

void CSceneManager::Initialize()
{
}

void CSceneManager::Update()
{
	m_cCurrentScene->Update();

	if (m_cCurrentScene->ReturnToMainMenu())
	{
		m_cCurrentScene->Release();

		m_cCurrentScene = m_Scenes[0];
		m_cCurrentScene->Initialize();
	}
}

void CSceneManager::LateUpdate()
{
	m_cCurrentScene->LateUpdate();
}

void CSceneManager::Render(HDC _hdc)
{
	m_cCurrentScene->Render(_hdc);
}

void CSceneManager::Release()
{
	m_cCurrentScene->Release();
}

void CSceneManager::destroy()
{
	Release();
	for (auto& scene : m_Scenes)
	{
		delete scene;
	}
	m_Scenes.clear();

	delete this;
}
