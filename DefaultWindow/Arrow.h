#pragma once


class Arrow
{
public:
	Arrow();
	~Arrow();

	void initalize();
	void render(HDC _hdc);
	void update();
	void release();

	void shoot(float power);
	const bool& isShot() const { return shot; }
	void setPosition(D3DXVECTOR3 _value) { position = _value; }
	void setDirection(D3DXVECTOR3 _value) { moveVector = _value; }
	const D3DXVECTOR3* getVertex() const { return vertex; }
	const D3DXVECTOR3& getPosition() const { return position; }

	bool collision();
private:
	bool shot;
	float angle;

	D3DXVECTOR3 position;
	D3DXVECTOR3 moveVector;
	D3DXVECTOR3 vertex[2];
	D3DXVECTOR3 initalVertex[2];
};
