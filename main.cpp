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
/*
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
	GameEventReceiver eventReceiver;

    IrrlichtDevice *device =
		createDevice( video::EDT_DIRECT3D9, dimension2d<u32>(SCREEN_WIDTH_DEFAULT, SCREEN_HEIGHT_DEFAULT), 32,
            false, false, false, &eventReceiver);

	if (!device)
        return 1;

	IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();
	MainMenu mainMenu(device);

/*
    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
        rect<s32>(10,10,260,22), true);*/
/*
	SquareRoomSceneNode* roomNode;
	CubicSceneNode* wall;
	int random = 0;
	core::vector3df position;
	core::vector3df scale;
	srand((unsigned)time(NULL));

	for (int i = 0; i < 100; i++)
	{
		roomNode = new SquareRoomSceneNode(smgr->getRootSceneNode(),
										smgr,
										-1,
										driver->getTexture("Resources/Textures/wall.jpg"),
										driver->getTexture("Resources/Textures/wall.jpg"),
										driver->getTexture("Resources/Textures/wall.jpg"),
										driver->getTexture("Resources/Textures/wall.jpg"),
										core::vector3df(4.0f, 2.0f, 4.0f),
										core::vector3df(0.0f, 50.0f, 0.0f - (irr::f32)(i * 100 * 8)),
										core::vector3df(0.0f, 0.0f, 0.0f),
										core::vector3df(100.0f, 100.0f, 100.0f));

		random = rand() % 4;
		switch (random)
		{
		case 0:
			position = core::vector3df(-2.0f, 0.0f, 0.0f);
			scale = core::vector3df(1.0f, 2.0f, 1.0f);
			break;
		case 1:
			position = core::vector3df(2.0f, 0.0f, 0.0f);
			scale = core::vector3df(1.0f, 2.0f, 1.0f);
			break;
		case 2:
			position = core::vector3df(0.0f, 1.0f, 0.0f);
			scale = core::vector3df(2.0f, 1.0f, 1.0f);
			break;
		case 3:
			position = core::vector3df(0.0f,-1.0f, 0.0f);
			scale = core::vector3df(2.0f, 1.0f, 1.0f);
			break;
		default:
			position = core::vector3df(0.0f, 0.0f, 0.0f);
			scale = core::vector3df(1.0f, 1.0f, 1.0f);
			break;
		}

		wall = new CubicSceneNode(roomNode,
								  smgr,
								  -1,
								  driver->getTexture("Resources/Textures/wall.bmp"),
								  driver->getTexture("Resources/Textures/wall.bmp"),
								  driver->getTexture("Resources/Textures/wall.bmp"),
								  driver->getTexture("Resources/Textures/wall.bmp"),
								  driver->getTexture("Resources/Textures/wall.bmp"),
								  driver->getTexture("Resources/Textures/wall.bmp"),
								  core::vector3df(2.0f, 1.0f, 0.2f),
								  position,
								  core::vector3df(0.0f, 0.0f, 0.0f),
								  scale);
		wall->drop();
		roomNode->drop();
	}

	IMesh* mesh = smgr->getMesh("Resources/Meshes/Vehicle/Feisar_Ship.3DS");
    if (!mesh)
    {
        device->drop();
        return 1;
    }
    IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
	node->setPosition(irr::core::vector3df(0.0f, -50.0f, 0.0f));
	node->setScale(irr::core::vector3df(0.5f, 0.5f, 0.5f));
	node->setMaterialFlag(EMF_LIGHTING, false);
/*	scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0,0.5,0));
		if (anim)
		{
			node->addAnimator(anim);
			anim->drop();
		} */

    //smgr->addCameraSceneNodeFPS();
/*	vector3df cameraTarget(0.0f ,0.0f ,-1200.0f);
	vector3df cameraPosition(0.0f , 150.0f ,450.0f);
	smgr->addCameraSceneNode(node, cameraPosition, cameraTarget);
	ICameraSceneNode* cameraNode = smgr->getActiveCamera();
	device->getCursorControl()->setVisible(true);

	/*
	We have done everything, so lets draw it. We also write the current
	frames per second and the name of the driver to the caption of the
	window.
	*/
/*	int lastFPS = -1;

	// In order to do framerate independent movement, we have to know
	// how long it was since the last frame
	u32 then = device->getTimer()->getTime();
	// This is the movemen speed in units per second.
	const f32 MOVEMENT_SPEED = 1000.0f;
	f32 delta;

    while(device->run())
    {
		// Work out a frame delta time.
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		/* Check if keys W, S, A or D are being held down, and move the
		sphere node around respectively. */
/*		core::vector3df nodePosition = node->getPosition();

		if(eventReceiver.IsKeyDown(irr::KEY_KEY_W))
			nodePosition.Y += MOVEMENT_SPEED * frameDeltaTime;
		else if(eventReceiver.IsKeyDown(irr::KEY_KEY_S))
			nodePosition.Y -= MOVEMENT_SPEED * frameDeltaTime;

		if(eventReceiver.IsKeyDown(irr::KEY_KEY_A))
			nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
		else if(eventReceiver.IsKeyDown(irr::KEY_KEY_D))
			nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;

		delta = MOVEMENT_SPEED * frameDeltaTime;
		nodePosition.Z -= delta;
		cameraTarget.Z -= delta;
		//cameraPosition.Z -= delta;
		node->setPosition(nodePosition);
		//cameraNode->setPosition(cameraPosition);
		cameraNode->setTarget(cameraTarget);

        driver->beginScene(true, true, SColor(255,100,101,140));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
			core::stringw tmp(L"Last Ride Demo [");
			tmp += driver->getName();
			tmp += L"] fps: ";
			tmp += fps;

			device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}
    }

    device->drop();

    return 0;
}
*/

int main()
{
	GameManager gameManager;
	if (!gameManager.Initialize())
		return 1;

	irr::IrrlichtDevice* device = gameManager.getDevice();
	
	while(device->run())
	{
		gameManager.run();
	}

	return 0;
}