//Author Oleh Havryliuk 07.2015
#ifndef __MAIN_MENU_H_INCLUDED__
#define __MAIN_MENU_H_INCLUDED__

#include <irrlicht.h>

enum
{
	GUI_ID_RESUME_BUTTON = 101,
	GUI_ID_NEW_GAME_BUTTON = 102,
	GUI_ID_OPTIONS_BUTTON = 103,
	GUI_ID_EXIT_BUTTON = 104
};

class MainMenu : public irr::IEventReceiver
{
private:
	irr::u32 m_buttonCount;
	irr::IrrlichtDevice* m_device;
	irr::gui::IGUIEnvironment* m_guiEnviroment;
	irr::gui::IGUISkin* m_skin;
	irr::gui::IGUIFont* m_font;

	irr::gui::IGUIButton* m_resume;
	irr::gui::IGUIButton* m_newGame;
	irr::gui::IGUIButton* m_options;
	irr::gui::IGUIButton* m_exit;

public:
	MainMenu(irr::IrrlichtDevice* device);
	virtual bool OnEvent(const irr::SEvent& event);
};

#endif