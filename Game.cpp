#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"

/*
	This is called once when the game is first started
*/
void Game::Start(void)
{
	//if game state is uninitialized do nothing
	if(_gameState != Uninitialized)
		return;

	//creates game window width, height, and text
	_mainWindow.Create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"Spider");

	//create player object
	Spider *player1 = new Spider();
	player1->SetPosition((SCREEN_WIDTH/2),700);
	
	//add player reference to game object manager
	_gameObjectManager.Add("SpiderMAMA",player1);

	//set game state to show splash screen
	_gameState= Game::ShowingSplash;


	while(!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.Close();
}

/*
	If exit button is clicked
*/
bool Game::IsExiting()
{
	if(_gameState == Game::Exiting) 
		return true;
	else 
		return false;
}

/*
	Gets game window object
*/
sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

/*
	get input of main window
*/
const sf::Input& Game::GetInput() 
{
	return _mainWindow.GetInput();
}

/*
	gets game object manager
*/
const GameObjectManager& Game::GetGameObjectManager()
{
	return _gameObjectManager;
}

/*
	Main game loop
*/
void Game::GameLoop()
{
	//create and get current event
	sf::Event currentEvent;
	_mainWindow.GetEvent(currentEvent);
	
	//determine functionality based on game state
	switch(_gameState)
	{
		case Game::ShowingMenu:
			{
				ShowMenu();
				break;
			}
		case Game::ShowingSplash:
			{
				ShowSplashScreen();
				break;
			}
		case Game::Playing:
			{
				_mainWindow.Clear(sf::Color(255,255,255));

				//updates all coordinates of our game objects and draws them to the screen
				_gameObjectManager.UpdateAll();
				_gameObjectManager.DrawAll(_mainWindow);
				
				//displays the drawing on the pop up window
				_mainWindow.Display();

				if(currentEvent.Type == sf::Event::Closed) _gameState = Game::Exiting;
				
				//go to menu on escape key
				if(currentEvent.Type == sf::Event::KeyPressed)
					{
						if(currentEvent.Key.Code == sf::Key::Escape) ShowMenu();
					}

				break;
			}
	}
}

/*
	Shows title screen
*/
void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

/*
	Waits for user input on menu screen
*/
void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
		case MainMenu::Exit:
			_gameState = Exiting;
			break;
		case MainMenu::Play:
			_gameState = Playing;
			break;
	}
}

//initiliazations
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;