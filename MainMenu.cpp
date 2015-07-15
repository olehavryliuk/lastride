//Author Oleh Havryliuk 07.2015
#include "MainMenu.h"
#include "Constants.h"
#include "GameManager.h"

MainMenu::MainMenu(GameManager* gameManager)
{
	m_gameManager = gameManager;
	irr::IrrlichtDevice* device = m_gameManager->getDevice();
	if (device)
		m_guiEnviroment = device->getGUIEnvironment();
	m_skin = m_guiEnviroment->getSkin();
	m_font = m_guiEnviroment->getFont(FONT_PATH + DEFAULT_FONT);
	if (m_font)
		m_skin->setFont(m_font);
	m_isActive = false;
	m_buttonCount = 4;

	//Position buttons relative on screen width half and height quarter
	irr::core::dimension2d<irr::u32> screenSize = device->getVideoDriver()->getScreenSize();
	irr::u32 xStartPosition = screenSize.Width / 2 - BUTTON_WIDTH / 2;
	irr::u32 yStartPosition = screenSize.Height * 3 / 4 - m_buttonCount / 2 * (BUTTON_HEIGHT + BUTTON_MARGIN);
	irr::core::rect<irr::s32> rect = irr::core::rect<irr::s32>(xStartPosition,
																yStartPosition,
																xStartPosition + BUTTON_WIDTH,
																yStartPosition + BUTTON_HEIGHT);
	m_resume = m_guiEnviroment->addButton(rect,
										  NULL,
										  GUI_ID_RESUME_BUTTON,
										  L"RESUME",
										  L"Click to resume last saved level");
	rect = irr::core::rect<irr::s32>(xStartPosition,
									yStartPosition + BUTTON_HEIGHT + BUTTON_MARGIN,
									xStartPosition + BUTTON_WIDTH,
									yStartPosition + 2 * BUTTON_HEIGHT + BUTTON_MARGIN);
	m_newGame = m_guiEnviroment->addButton(rect,
										   NULL,
										   GUI_ID_NEW_GAME_BUTTON,
										   L"NEW GAME",
										   L"Click to start a new game");
	rect = irr::core::rect<irr::s32>(xStartPosition,
									yStartPosition + 2 * (BUTTON_HEIGHT + BUTTON_MARGIN),
									xStartPosition + BUTTON_WIDTH,
									yStartPosition + 3 * BUTTON_HEIGHT + 2 * BUTTON_MARGIN);
	m_options = m_guiEnviroment->addButton(rect,
										   NULL,
										   GUI_ID_OPTIONS_BUTTON,
										   L"OPTIONS",
										   L"Click to access game options");
	rect = irr::core::rect<irr::s32>(xStartPosition,
									yStartPosition + 3 * (BUTTON_HEIGHT + BUTTON_MARGIN),
									xStartPosition + BUTTON_WIDTH,
									yStartPosition + 4 * BUTTON_HEIGHT + 3 * BUTTON_MARGIN);
	m_exit = m_guiEnviroment->addButton(rect,
										NULL,
										GUI_ID_EXIT_BUTTON,
										L"EXIT",
										L"Click to quit the game");
}

bool MainMenu::isActive()
{
	return m_isActive;
}
void MainMenu::setActive(bool value)
{
	m_isActive = value;
}

bool MainMenu::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_GUI_EVENT)
	{
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
		{
			irr::s32 id = event.GUIEvent.Caller->getID();
			switch (id)
			{
			case GUI_ID_RESUME_BUTTON:
				return true;
			case GUI_ID_NEW_GAME_BUTTON:
				m_gameManager->loadTestLevel();
				return true;
			case GUI_ID_OPTIONS_BUTTON:
				return true;
			case GUI_ID_EXIT_BUTTON:
				m_gameManager->getDevice()->closeDevice();
				return true;
			default:
				return false;
			}
		}
	}

	return false;
}