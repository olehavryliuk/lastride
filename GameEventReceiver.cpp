//Author Oleh Havryliuk 07.2015
#include "GameEventReceiver.h"

GameEventReceiver::GameEventReceiver()
{
	for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
		m_keyIsDown[i] = false;
}

bool GameEventReceiver::OnEvent(const irr::SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		m_keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

// This is used to check whether a key is being held down
bool GameEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return m_keyIsDown[keyCode];
}