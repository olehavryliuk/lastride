//Author Oleh Havryliuk 07.2015
#include <stdlib.h>     /* srand, rand */
#include <time.h>   
#include "SquareRoomSceneNode.h"
#include "CubicSceneNode.h"
#include "GameEventReceiver.h"
#include "GameManager.h"
#include "Constants.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
	GameManager gameManager;
	if (!gameManager.initialize())
		return 1;

	irr::IrrlichtDevice* device = gameManager.getDevice();
	
	while(device->run())
	{
		gameManager.run(); //main game loop
	}

	return 0;
}