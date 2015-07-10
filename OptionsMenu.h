//Author Oleh Havryliuk 07.2015
#ifndef __OPTIONS_MENU_H_INCLUDED__
#define __OPTIONS_MENU_H_INCLUDED__

#include <irrlicht.h>

class OptionsMenu
{
private:
	irr::IrrlichtDevice* m_device;
public:
	OptionsMenu(irr::IrrlichtDevice* device);
};

#endif