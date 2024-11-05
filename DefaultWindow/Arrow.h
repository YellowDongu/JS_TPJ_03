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

<<<<<<< Updated upstream
=======
	void shoot(float power);
	const bool& isShot() const { return shot; }
	void setPosition(D3DXVECTOR3 _value) { position = _value; }
	void setDirection(D3DXVECTOR3 _value) { moveVector = _value; }
>>>>>>> Stashed changes

private:
	bool shot;
	float angle;

	D3DXVECTOR3 position;
	D3DXVECTOR3 moveVector;
	D3DXVECTOR3 vertex[2];

};

Arrow::Arrow()
{
}

Arrow::~Arrow()
{
}