#pragma once
#include "VisibleGameObject.h"

class Spider :
	public VisibleGameObject
{
public:
	Spider();
	~Spider();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);
	
	float GetXVelocity() const;
	float GetYVelocity() const;

private:
	float _xvelocity;  // -- left ++ right
	float _yvelocity;  // -- down ++ up
	bool canMoveRight;
	bool canMoveLeft;
	bool canMoveUp;
	bool canMoveDown;
};

