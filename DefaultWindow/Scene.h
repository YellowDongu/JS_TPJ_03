#pragma once


class CScene
{
public:
	CScene() : m_bReturn(false), m_iOtherStage(-1) {}
	virtual ~CScene() {}

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC _hdc) = 0;
	virtual void Release() = 0;

	const bool& ReturnToMainMenu() const { return m_bReturn; }
	void ConfirmReturn() { m_bReturn = false; }

	// ���θ޴���
	const int& changeScene() const { return m_iOtherStage; }
protected:
	bool m_bReturn;
	int m_iOtherStage; // ���θ޴���
};
