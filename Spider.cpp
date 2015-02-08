#include "StdAfx.h"
#include "Spider.h"
#include "Game.h"


Spider::Spider() :
_xvelocity(0),
_yvelocity(0),
canMoveRight(true),
canMoveLeft(true),
canMoveUp(true),
canMoveDown(true)
{
	Load("images/spider.png");
	assert(IsLoaded());

	GetSprite().SetCenter(GetSprite().GetSize().x /2, GetSprite().GetSize().y / 2);

}


Spider::~Spider()
{
}

void Spider::Draw(sf::RenderWindow & rw)
{
	VisibleGameObject::Draw(rw);
}

float Spider::GetXVelocity() const
{
	return _xvelocity;
}

float Spider::GetYVelocity() const
{
	return _yvelocity;
}

void Spider::Update(float elapsedTime)
{

	if(Game::GetInput().IsKeyDown(sf::Key::Left) && canMoveLeft)
	{
		_xvelocity = -100.0f;
		_yvelocity = 0.0f;
	}
	if(Game::GetInput().IsKeyDown(sf::Key::Right) && canMoveRight)
	{
		_xvelocity = 100.0f;
		_yvelocity = 0.0f;
	}

	if(Game::GetInput().IsKeyDown(sf::Key::Down) && canMoveDown)
	{
		_yvelocity = 100.0f;
		_xvelocity = 0.0f;
	}

	if(Game::GetInput().IsKeyDown(sf::Key::Up) && canMoveUp)
	{
		_yvelocity = -100.0f;
		_xvelocity = 0.0f;
	}
	GetSprite().Move(_xvelocity * elapsedTime, _yvelocity * elapsedTime);
	sf::Vector2f pos = this->GetPosition();

	/*if(((pos.x  <= GetSprite().GetSize().x/2) || (pos.x >= (Game::SCREEN_HEIGHT - GetSprite().GetSize().x/2))) && 
	  ((pos.y  <= GetSprite().GetSize().y/2) || (pos.y >= (Game::SCREEN_HEIGHT - GetSprite().GetSize().y/2))))
	{
		_yvelocity = 0; 
		_xvelocity = 0;
	} */

	if(pos.y <= GetSprite().GetSize().y/2){
		_yvelocity = 0;
		canMoveUp = false;
	} else canMoveUp = true;

	if(pos.y >= (Game::SCREEN_HEIGHT - GetSprite().GetSize().y/2)){ 
		_yvelocity = 0;
		canMoveDown = false;
	} else canMoveDown = true;

	if(pos.x <= GetSprite().GetSize().x/2){
		_xvelocity = 0;
		canMoveLeft = false;
	} else canMoveLeft = true;

	if(pos.x >= (Game::SCREEN_WIDTH - GetSprite().GetSize().x/2)){
		_xvelocity = 0;
		canMoveRight = false;
	} else canMoveRight = true;
	
}