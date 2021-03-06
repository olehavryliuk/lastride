//Author Oleh Havryliuk 07.2015
#include "GameManager.h"
#include "Constants.h"

GameManager::GameManager()
{
	m_shaderManager  = nullptr;
	m_mainMenu		 = nullptr;
	m_optionsMenu	 = nullptr;
	m_eventReceiver	 = nullptr;
	m_levelSceneNode = nullptr;
	m_FPSCamera		 = nullptr;
	m_lastTime		 = 0;
	m_gameState		 = GS_MAIN_MENU;
}

bool GameManager::initialize()
{
	m_eventReceiver = new GameEventReceiver();

    irr::SIrrlichtCreationParameters p;
	p.DriverType	= VIDEO_DRIVER_TYPE;
	p.WindowSize	= irr::core::dimension2d<irr::u32>(SCREEN_WIDTH_DEFAULT, SCREEN_HEIGHT_DEFAULT);
	p.Bits			= (irr::u8)COLOR_BITS;
	p.Fullscreen	= IS_FULLSCREEN;
	p.Stencilbuffer = HAS_STENCILBUFFER;
	p.Vsync			= IS_VSYNC;
	p.EventReceiver = m_eventReceiver;
	p.AntiAlias		= 0;

	m_device = irr::createDeviceEx(p);

	if (!m_device)
        return false;

	m_driver = m_device->getVideoDriver();
	m_sceneManager = m_device->getSceneManager();
	m_GUIEnviroment = m_device->getGUIEnvironment();

//mip map texture creation flag
	m_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, CREATE_MIP_MAPS);

//add shader manager
	if(USE_OWN_SHADER_LIGHTING)
	{
		m_shaderManager = new ShaderManager(this);
		if(!loadShaders())
			m_device->getLogger()->log("GameManager->loadShaders FAILED!");
	}

//add menus
	m_mainMenu = new MainMenu(this);
	m_mainMenu->setActive(true);
	m_optionsMenu = new OptionsMenu(m_device);

	m_eventReceiver->setMainMenu(m_mainMenu);
	m_eventReceiver->setOptionsMenu(m_optionsMenu);

	return true;
}

GameManager::~GameManager()
{
	delete m_shaderManager;
	delete m_mainMenu;
	delete m_optionsMenu;
	delete m_eventReceiver;

	m_device->drop();
}

ShaderManager* GameManager::getShaderManager()
{
	return m_shaderManager;
}

GAME_STATE GameManager::getGameState()
{
	return m_gameState;
}

void GameManager::setGameState(GAME_STATE gameState)
{
	m_gameState = gameState;
}

irr::IrrlichtDevice* GameManager::getDevice()
{
	return m_device;
}

bool GameManager::loadTestLevel()
{
	m_levelSceneNode = new LevelSceneNode(this ,m_device, m_sceneManager->getRootSceneNode(), m_sceneManager);
	if (!m_levelSceneNode)
		return false;

	m_gameState = GS_LOADING;

	m_levelSceneNode->loadTestLevel();

	m_device->getCursorControl()->setVisible(false);

	m_levelSceneNode->drop();

	return true;
}

bool GameManager::loadLevelFromXML(const irr::io::path& filePath)
{
	m_levelSceneNode = new LevelSceneNode(this, m_device, m_sceneManager->getRootSceneNode(), m_sceneManager);
	if (!m_levelSceneNode)
		return false;

	m_gameState = GS_LOADING;

	m_levelSceneNode->loadLevelFromXML(filePath);

	m_device->getCursorControl()->setVisible(false);

	m_levelSceneNode->drop();

	m_mainMenu->setActive(false);

	return true;
}

bool GameManager::loadShaders()
{
	if (!m_shaderManager)
		return false;

	if (USE_BUMP_MAPPING)
	{
		if(!m_shaderManager->initBumpMaterial())
			return false;
	}
	else if (USE_PARALLAX_MAPPING)
	{
		if (!m_shaderManager->initParallaxMaterial())
			return false;
	}

	return true;
}

void GameManager::update()
{
	//irr::u32 newTime = m_device->getTimer()->getTime();
	//irr::u32 deltaTime = newTime - m_lastTime;
	//m_lastTime = newTime;

	m_levelSceneNode->update();
}

void GameManager::run()
{
	m_driver->beginScene(true, true, irr::video::SColor(255, 50, 100, 100));
	
	if (m_gameState == GS_PLAYING)
	{
		update();
	}

	if (m_gameState == GS_MAIN_MENU || m_gameState == GS_OPTIONS_MENU)
	{
		m_GUIEnviroment->drawAll();
	}
	else if (m_gameState == GS_PLAYING || m_gameState == GS_GAME_OVER)
	{
		m_sceneManager->drawAll();
	}

	m_driver->endScene();
}
/*
bool GameManager::addFPSCamera()
{
	if(m_FPSCamera = m_sceneManager->addCameraSceneNodeFPS())
		return true;
	return false;
}*/

const GameEventReceiver* GameManager::getEventReceiver()
{
	return m_eventReceiver;
}