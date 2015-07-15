//Author Oleh Havryliuk 07.2015
#ifndef __GAME_MANAGER_H_INCLUDED__
#define __GAME_MANAGER_H_INCLUDED__

#include "MainMenu.h"
#include "OptionsMenu.h"
#include "GameEventReceiver.h"
#include "LevelSceneNode.h"

enum GAME_STATE
{
	GS_INTRO		= 0,
	GS_MAIN_MENU	= 1,
	GS_OPTIONS_MENU = 2,
	GS_PLAYING		= 3
};

class GameManager
{
private:
	irr::IrrlichtDevice* m_device;               //weak ref
	irr::video::IVideoDriver* m_driver;			//weak ref
	irr::scene::ISceneManager* m_sceneManager;	//weak ref
	irr::gui::IGUIEnvironment* m_GUIEnviroment;	//weak ref
	MainMenu* m_mainMenu;						//strong ref
	OptionsMenu* m_optionsMenu;					//strong ref
	GameEventReceiver* m_eventReceiver;			//strong ref
	LevelSceneNode* m_levelSceneNode;			//strong ref
	irr::scene::ICameraSceneNode* m_FPSCamera;	//weak
	GAME_STATE m_gameState;

public:
	GameManager();
	~GameManager();

	bool initialize();
	bool loadTestLevel();
	void run();
	irr::IrrlichtDevice* getDevice();

	bool addFPSCamera();
};

#endif