//Author Oleh Havryliuk 07.2015
#ifndef __OPTIONS_MENU_H_INCLUDED__
#define __OPTIONS_MENU_H_INCLUDED__

#include <irrlicht.h>

class OptionsMenu : public irr::IEventReceiver
{
private:
	bool m_isActive;
	irr::IrrlichtDevice* m_device;
public:
	OptionsMenu(irr::IrrlichtDevice* device);
	bool isActive();
	void setActive(bool value);
	
	virtual bool OnEvent(const irr::SEvent& event);
};

#endif