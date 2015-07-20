//Author Oleh Havryliuk 07.2015
#include "Constants.h"

//screen resolution
const irr::u32 SCREEN_WIDTH_DEFAULT = 1280;
const irr::u32 SCREEN_HEIGHT_DEFAULT = 1024;

//default device
const irr::video::E_DRIVER_TYPE VIDEO_DRIVER_TYPE = irr::video::EDT_DIRECT3D9;
const irr::u8 COLOR_BITS = 32;
const bool IS_FULLSCREEN = false;
const bool HAS_STENCILBUFFER = true;
const bool IS_VSYNC = false;
const irr::u8 ANTIALIASING = 0;

//default button width, height, margin
const irr::u32 BUTTON_WIDTH = 300;
const irr::u32 BUTTON_HEIGHT = 50;
const irr::u32 BUTTON_MARGIN = 5;

//path
const irr::core::stringw FONT_PATH = L"Resources/Fonts/";
const irr::core::stringw MODEL_PATH = L"Resources/Models/";
const irr::core::stringw TEXTURE_PATH = L"Resources/Textures/";
const irr::core::stringw LEVEL_PATH = L"Resources/Levels/";
const irr::core::stringw DEFAULT_FONT = L"CourierNew_24px_bold.xml";

//Resources names
const irr::core::stringw ROOM_TEXTURE_NAME_DEFAULT = L"wall.jpg";
const irr::core::stringw WALL_TEXTURE_NAME_DEFAULT = L"wall.bmp";
const irr::core::stringw VEHICLE_MODEL_NAME_DEFAULT = L"Vehicle/Feisar_Ship.3DS";

//Debug
const bool SHOW_FPS = true;

//Room proportions
const irr::core::vector3df ROOM_PROPORTIONS = irr::core::vector3df(10.0f, 6.0f, 10.0f);
const irr::core::vector3df ROOM_SCALE = irr::core::vector3df(10.0f, 10.0f, 10.0f);
const irr::f32 WALL_WIDTH = 0.2f;

//Vehicle
const irr::core::vector3df VEHICLE_SCALE = irr::core::vector3df(0.2f, 0.2f, 0.2f);
const irr::core::vector3df VEHICLE_START_SPEED = irr::core::vector3df(0.0f, 0.0f, 300.0f);

//Camera
const irr::core::vector3df CAMERA_POSITION = irr::core::vector3df(0.0f, 200.0f, 300.0f);

//Light
const irr::core::vector3df LIGHT_POSITION = irr::core::vector3df(0.0f , 100.0f, 200.0f);
const irr::video::SColorf LIGHT_COLOR = irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f);
const irr::f32 LIGHT_RADIUS = 800.0f;

//CurveSceneNode
const irr::u8 CURVE_SECTIONS = 10;
const irr::f32 CURVE_RADIUS = 70.0f;

//StraightRoomSceneNode
const irr::u8 STRAIGHT_SECTIONS_DEFAULT = 10;