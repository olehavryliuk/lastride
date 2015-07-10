//Author Oleh Havryliuk 07.2015
#include "GameManager.h"
#include "Constants.h"

GameManager::GameManager()
{
	m_mainMenu = nullptr;
	m_optionsMenu = nullptr;
	m_eventReceiver = nullptr;
	m_gameState = GS_MAIN_MENU;
}

bool GameManager::Initialize()
{
	m_eventReceiver = new GameEventReceiver();

	m_device = irr::createDevice(VIDEO_DRIVER_TYPE,
								 irr::core::dimension2d<irr::u32>(SCREEN_WIDTH_DEFAULT, SCREEN_HEIGHT_DEFAULT),
								 COLOR_BITS,
								 IS_FULLSCREEN,
								 HAS_STENCILBUFFER,
								 IS_VSYNC,
								 m_eventReceiver);

	if (!m_device)
        return false;

	m_driver = m_device->getVideoDriver();
	m_sceneManager = m_device->getSceneManager();
	m_GUIEnviroment = m_device->getGUIEnvironment();

	m_mainMenu = new MainMenu(m_device);
	m_optionsMenu = new OptionsMenu(m_device);

	return true;
}

GameManager::~GameManager()
{
	delete m_mainMenu;
	delete m_optionsMenu;
	delete m_eventReceiver;

	m_device->drop();
}

irr::IrrlichtDevice* GameManager::getDevice()
{
	return m_device;
}

void GameManager::run()
{
	m_driver->beginScene(true, true, irr::video::SColor(255,100,100,140));
	
	m_sceneManager->drawAll();
	m_GUIEnviroment->drawAll();

	m_driver->endScene();
}