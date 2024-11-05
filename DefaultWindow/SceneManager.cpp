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
}

void CSceneManager::Initialize()
{
	CMainMenu* mainMenu = new CMainMenu();
	mainMenu->Initialize();
	m_cCurrentScene = mainMenu;
	m_Scenes.push_back(mainMenu);
	CStage01* stage01 = new CStage01();
	m_Scenes.push_back(stage01);
	CStage02* stage02 = new CStage02();
	m_Scenes.push_back(stage02);
	CStage03* stage03 = new CStage03();
	m_Scenes.push_back(stage03);
}

void CSceneManager::Update()
{
	m_cCurrentScene->Update();
}

void CSceneManager::LateUpdate()
{
	m_cCurrentScene->LateUpdate();


	if (m_cCurrentScene != m_Scenes[0])
	{
		if (m_cCurrentScene->ReturnToMainMenu())
		{
			m_cCurrentScene->ConfirmReturn();
			m_cCurrentScene->Release();

			m_cCurrentScene = m_Scenes[0];
			m_cCurrentScene->Initialize();
		}

	}
	else
	{
		int sceneNumber = m_cCurrentScene->changeScene();
		if (sceneNumber != -1)
		{
			m_cCurrentScene->Release();

			m_cCurrentScene = m_Scenes[sceneNumber];
			m_cCurrentScene->Initialize();
		}
	}
}

void CSceneManager::Render(HDC _hdc)
{
	m_cCurrentScene->Render(_hdc);
}

void CSceneManager::Release()
{
	m_cCurrentScene->Release();
	for (auto& scene : m_Scenes)
	{
		delete scene;
	}
	m_Scenes.clear();
}

void CSceneManager::Destroy()
{
	Release();
	delete this;
}
