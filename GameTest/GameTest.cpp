//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <iostream>
//------------------------------------------------------------------------
#include "app\app.h"
#include "table.h"
#include "Editor.h"
#include "Player.h"
#include "Mushroom.h"
#include "Teleporter.h"
#include "Spinner.h"
#include "GameObjectManager.h"

//@desc Initalising all the gameobjects
//--------------------------------------------------------------------------------------------------
CTable* gTable;
GameObjectManager* _gameObjectManager = new GameObjectManager();

Player* player = new Player();

Mushroom* mush1 = new Mushroom((APP_INIT_WINDOW_WIDTH / 2) - 145, (APP_INIT_WINDOW_HEIGHT / 2) + 120, 30);
Mushroom* mush2 = new Mushroom((APP_INIT_WINDOW_WIDTH / 2), (APP_INIT_WINDOW_HEIGHT / 2) + 100, 30);
Mushroom* mush3 = new Mushroom((APP_INIT_WINDOW_WIDTH / 2) + 145, (APP_INIT_WINDOW_HEIGHT / 2) + 120, 30);

Teleporter* tele1 = new Teleporter((APP_INIT_WINDOW_WIDTH / 2) - 200, (APP_INIT_WINDOW_HEIGHT / 2) + 200);
Teleporter* tele2 = new Teleporter((APP_INIT_WINDOW_WIDTH / 2) + 200, (APP_INIT_WINDOW_HEIGHT / 2) + 200);

Spinner* spin1 = new Spinner((APP_INIT_WINDOW_WIDTH / 2) - 100, (APP_INIT_WINDOW_HEIGHT / 2) - 100);
Spinner* spin2 = new Spinner((APP_INIT_WINDOW_WIDTH / 2) + 100, (APP_INIT_WINDOW_HEIGHT / 2) - 100);

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	gTable = new CTable;
	Editor::Load("table.txt");

	//Adding gameobjects into the gameobject manager
	_gameObjectManager->addChild("Player", player);
	_gameObjectManager->addChild("Mushroom", mush1);
	_gameObjectManager->addChild("Mushroom2", mush2);
	_gameObjectManager->addChild("Mushroom3", mush3);
	_gameObjectManager->addChild("Tele1", tele1);
	_gameObjectManager->addChild("Tele2", tele2);
	_gameObjectManager->addChild("Spin1", spin1);
	_gameObjectManager->addChild("Spin2", spin2);

}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	//Updating all gameobject in scene
	_gameObjectManager->update(deltaTime);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine or Print) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	//Rendering all lines and looping through all gameobjects and rendering them
	_gameObjectManager->render(gTable, _gameObjectManager->_gameObjects);

	for (auto& line : gTable->m_lines)
	{
		CLineDefinition& def = gTable->m_lineDefs[line.m_type];
		App::DrawLine(line.m_start.m_x, line.m_start.m_y, line.m_end.m_x, line.m_end.m_y, def.m_Red, def.m_Green, def.m_Blue);
	}
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	//Destructor
	delete _gameObjectManager;
}