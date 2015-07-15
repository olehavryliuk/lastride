//Author Oleh Havryliuk 07.2015
#include "GameManager.h"
#include "Constants.h"

GameManager::GameManager()
{
	m_mainMenu = nullptr;
	m_optionsMenu = nullptr;
	m_eventReceiver = nullptr;
	m_levelSceneNode = nullptr;
	m_FPSCamera = nullptr;
	m_gameState = GS_MAIN_MENU;
}

bool GameManager::initialize()
{
	m_eventReceiver = new GameEventReceiver();
/*
	m_device = irr::createDevice(VIDEO_DRIVER_TYPE,
								 irr::core::dimension2d<irr::u32>(SCREEN_WIDTH_DEFAULT, SCREEN_HEIGHT_DEFAULT),
								 COLOR_BITS,
								 IS_FULLSCREEN,
								 HAS_STENCILBUFFER,
								 IS_VSYNC,
								 m_eventReceiver);
*/
    irr::SIrrlichtCreationParameters p;
	p.DriverType = VIDEO_DRIVER_TYPE;
	p.WindowSize = irr::core::dimension2d<irr::u32>(SCREEN_WIDTH_DEFAULT, SCREEN_HEIGHT_DEFAULT);
	p.Bits = (irr::u8)COLOR_BITS;
	p.Fullscreen = IS_FULLSCREEN;
	p.Stencilbuffer = HAS_STENCILBUFFER;
	p.Vsync = IS_VSYNC;
	p.EventReceiver = m_eventReceiver;
	p.AntiAlias = 0;

	m_device = irr::createDeviceEx(p);

	if (!m_device)
        return false;

	m_driver = m_device->getVideoDriver();
	m_sceneManager = m_device->getSceneManager();
	m_GUIEnviroment = m_device->getGUIEnvironment();

	m_mainMenu = new MainMenu(this);
	m_mainMenu->setActive(true);
	m_optionsMenu = new OptionsMenu(m_device);

	m_eventReceiver->setMainMenu(m_mainMenu);
	m_eventReceiver->setOptionsMenu(m_optionsMenu);

	return true;
}

GameManager::~GameManager()
{
	delete m_mainMenu;
	delete m_optionsMenu;
	delete m_eventReceiver;
	delete m_levelSceneNode;

	m_device->drop();
}

irr::IrrlichtDevice* GameManager::getDevice()
{
	return m_device;
}

bool GameManager::loadTestLevel()
{
	m_levelSceneNode = new LevelSceneNode(m_device, NULL, m_sceneManager);
	if (!m_levelSceneNode)
		return false;

	addFPSCamera();
	m_levelSceneNode->loadTestLevel();

	m_gameState = GS_PLAYING;
	m_device->getCursorControl()->setVisible(false);

	return true;
}

void GameManager::run()
{
	m_driver->beginScene(true, true, irr::video::SColor(255,100,100,140));
	
	if (m_gameState == GS_PLAYING)
		m_sceneManager->drawAll();
	else
		m_GUIEnviroment->drawAll();

	m_driver->endScene();
}

bool GameManager::addFPSCamera()
{
	if(m_FPSCamera = m_sceneManager->addCameraSceneNodeFPS())
		return true;
	return false;
}