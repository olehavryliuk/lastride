//Author Oleh Havryliuk 07.2015
#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(irr::IrrlichtDevice* device)
{
	m_device = device;
	m_isActive = false;
}

bool OptionsMenu::isActive()
{
	return m_isActive;
}

void OptionsMenu::setActive(bool value)
{
	m_isActive = value;
}

bool OptionsMenu::OnEvent(const irr::SEvent& event)
{
	return false;
}