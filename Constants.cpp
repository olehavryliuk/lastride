//Author Oleh Havryliuk 07.2015
#include "Constants.h"

//screen resolution
const irr::u32 SCREEN_WIDTH_DEFAULT = 1280;
const irr::u32 SCREEN_HEIGHT_DEFAULT = 1024;

//default device
//const irr::video::E_DRIVER_TYPE VIDEO_DRIVER_TYPE = irr::video::EDT_DIRECT3D9;
const irr::video::E_DRIVER_TYPE VIDEO_DRIVER_TYPE = irr::video::EDT_OPENGL;
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
//const irr::core::stringw ROOM_TEXTURE_NAME_DEFAULT = L"167.JPG";
const irr::core::stringw ROOM_TEXTURE_NAME_DEFAULT = L"rockwall.JPG";
const irr::core::stringw ROOM_NORMAL_MAP_TEXTURE_NAME_DEFAULT = L"rockwall_NRM.png";
const irr::core::stringw WALL_TEXTURE_NAME_DEFAULT = L"ft_stone01_c.png";
//const irr::core::stringw WALL_TEXTURE_NAME_DEFAULT = L"rockwall.JPG";
const irr::core::stringw WALL_NORMAL_MAP_TEXTURE_NAME_DEFAULT = "ft_stone01_n.png";
const irr::core::stringw VEHICLE_MODEL_NAME_DEFAULT = L"Vehicle/Feisar_Ship.3DS";
const irr::core::stringw EXPLOSION_TEXTURE_NAME_DEFAULT = L"explosion.png";

//Debug
const bool SHOW_FPS = true;

//Room proportions
const irr::core::vector3df ROOM_PROPORTIONS = irr::core::vector3df(12.0f, 8.0f, 12.0f);
const irr::core::vector3df ROOM_SCALE = irr::core::vector3df(10.0f, 10.0f, 10.0f);
const irr::f32 WALL_WIDTH = 1.0f;

//Vehicle
const irr::core::vector3df VEHICLE_SCALE = irr::core::vector3df(0.15f, 0.15f, 0.15f);
const irr::core::vector3df VEHICLE_START_SPEED = irr::core::vector3df(0.0f, 0.0f, 400.0f);

//Camera
const irr::core::vector3df CAMERA_POSITION = irr::core::vector3df(0.0f, 100.0f, 100.0f);
const irr::f32 CAMERA_TARGET_DISTANCE = 10000000.0f;

//Light
const irr::core::vector3df LIGHT_POSITION = irr::core::vector3df(0.0f , 0.0f, 500.0f);
const irr::video::SColorf LIGHT_COLOR = irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f);
const irr::f32 LIGHT_RADIUS = 800.0f;
const irr::f32 LIGHT_CONE_ANGLE = 40.0f;

const irr::video::SColorf AMBIENT_MATERIAL_DEFAULT = irr::video::SColorf(0.1f, 0.1f, 0.1f, 1.0f);
const irr::video::SColorf DIFFUSE_MATERIAL_DEFAULT = irr::video::SColorf(0.6f, 0.6f, 0.6f, 1.0f);
const irr::video::SColorf SPECULAR_MATERIAL_DEFAULT = irr::video::SColorf(0.1f, 0.1f, 0.1f, 1.0f);
const irr::f32 SPECULAR_POWER = 2.0f;

//Shader, Bump Mapping, Parallax Mapping
const bool CREATE_MIP_MAPS = true;
const bool USE_OWN_SHADER_LIGHTING = true;
const bool USE_BUMP_MAPPING = false;
const bool USE_PARALLAX_MAPPING = true;
const bool USE_HEIGHT_MAP_TEXTURE = false;
const irr::f32 NORMAL_MAP_HEIGHT_TEXTURE_FACTOR = 20.0f;
const irr::f32 ADJUST_HEIGHT_FOR_PARALLAX = 0.02f;

//Explosion
const irr::core::dimension2df EXPLOSION_TEXTURE_DIMENSION = irr::core::dimension2df(50.0f, 50.0f);
const irr::u32 EXPLOSION_TEXTURE_WIDTH_FRAMES = 7;
const irr::u32 EXPLOSION_TEXTURE_HEIGHT_FRAMES = 7;
const irr::u32 EXPLOSION_TIME_PER_FRAME = 50;

//CurveSceneNode
const irr::u8 CURVE_SECTIONS = 10;
const irr::f32 CURVE_RADIUS = 100.0f;

//StraightRoomSceneNode
const irr::u8 STRAIGHT_SECTIONS_DEFAULT = 10;

//Obstacles
const irr::f32 BOX_INCREASE_MULTIPLIER = 4.0f;

//Input
const irr::f32 KEY_REACTION_SPEED_DEFAULT = 3000.0f;
const irr::f32 WALL_SIDE_MARGIN = 5.0f;
const irr::f32 WALL_BOTTOM_MARGIN = 5.0f;
const irr::f32 WALL_TOP_MARGIN = 30.0f;