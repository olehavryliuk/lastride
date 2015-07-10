//Author Oleh Havryliuk 07.2015
#ifndef __GAME_EVENT_RECEIVER_H_INCLUDED__
#define __GAME_EVENT_RECEIVER_H_INCLUDED__

#include <IEventReceiver.h>
#include <KeyCodes.h>

class GameEventReceiver : public irr::IEventReceiver
{
public:
	GameEventReceiver();

	bool OnEvent(const irr::SEvent& event);
	bool IsKeyDown(irr::EKEY_CODE keyCode) const;
private:
	// We use this array to store the current state of each key
	bool m_keyIsDown[irr::KEY_KEY_CODES_COUNT];
};

#endif