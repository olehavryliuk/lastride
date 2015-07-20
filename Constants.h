//Author Oleh Havryliuk 07.2015
#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

#include <irrTypes.h>
#include <irrString.h>
#include <EDriverTypes.h>
#include <vector3d.h>
#include <SColor.h>

//screen resolution
extern const irr::u32 SCREEN_WIDTH_DEFAULT;
extern const irr::u32 SCREEN_HEIGHT_DEFAULT;

//default device
extern const irr::video::E_DRIVER_TYPE VIDEO_DRIVER_TYPE;
extern const irr::u8 COLOR_BITS;
extern const bool IS_FULLSCREEN;
extern const bool HAS_STENCILBUFFER;
extern const bool IS_VSYNC;
extern const irr::u8 ANTIALIASING;

//default button width, height, margin
extern const irr::u32 BUTTON_WIDTH;
extern const irr::u32 BUTTON_HEIGHT;
extern const irr::u32 BUTTON_MARGIN;

//Path
extern const irr::core::stringw FONT_PATH;
extern const irr::core::stringw MODEL_PATH;
extern const irr::core::stringw TEXTURE_PATH;
extern const irr::core::stringw LEVEL_PATH;
extern const irr::core::stringw DEFAULT_FONT;

//Resources names
extern const irr::core::stringw ROOM_TEXTURE_NAME_DEFAULT;
extern const irr::core::stringw WALL_TEXTURE_NAME_DEFAULT;
extern const irr::core::stringw VEHICLE_MODEL_NAME_DEFAULT;

//Debug
extern const bool SHOW_FPS;

//Room proportions
extern const irr::core::vector3df ROOM_PROPORTIONS;
extern const irr::core::vector3df ROOM_SCALE;
extern const irr::f32 WALL_WIDTH;

//Vehicle
extern const irr::core::vector3df VEHICLE_SCALE;
extern const irr::core::vector3df VEHICLE_START_SPEED;

//Camera
extern const irr::core::vector3df CAMERA_POSITION;

//Light
extern const irr::core::vector3df LIGHT_POSITION;
extern const irr::video::SColorf LIGHT_COLOR;
extern const irr::f32 LIGHT_RADIUS;

//CurveRoomSceneNode
#define MAX_CURVE_SECTIONS 10
extern const irr::u8 CURVE_SECTIONS;
extern const irr::f32 CURVE_RADIUS;

//StraightRoomSceneNode
#define MAX_STRAIGHT_SECTIONS 100
extern const irr::u8 STRAIGHT_SECTIONS_DEFAULT;

#endif
