//Author Oleh Havryliuk 07.2015
#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

#include <irrTypes.h>
#include <irrString.h>
#include <EDriverTypes.h>
#include <vector3d.h>
#include <dimension2d.h>
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
extern const irr::core::stringw ROOM_NORMAL_MAP_TEXTURE_NAME_DEFAULT;
extern const irr::core::stringw WALL_TEXTURE_NAME_DEFAULT;
extern const irr::core::stringw WALL_NORMAL_MAP_TEXTURE_NAME_DEFAULT;
extern const irr::core::stringw MINE_MODEL_NAME_DEFAULT;
extern const irr::core::stringw MINE_TEXTURE_NAME_DEFAULT;
extern const irr::core::stringw MINE_NORMAL_MAP_TEXTURE_NAME_DEFAULT;
extern const irr::core::stringw VEHICLE_MODEL_NAME_DEFAULT;
extern const irr::core::stringw EXPLOSION_TEXTURE_NAME_DEFAULT;

//Debug
extern const bool SHOW_FPS;

//Room proportions
extern const irr::core::vector3df ROOM_PROPORTIONS;
extern const irr::core::vector3df ROOM_SCALE;
extern const irr::f32 WALL_WIDTH;

//Mine
extern const irr::core::vector3df MINE_SCALE;

//Vehicle
extern const irr::core::vector3df VEHICLE_SCALE;
extern const irr::core::vector3df VEHICLE_START_SPEED;

//Camera
extern const irr::core::vector3df CAMERA_POSITION;
extern const irr::f32 CAMERA_TARGET_DISTANCE;


//Light
extern const irr::core::vector3df LIGHT_POSITION;
extern const irr::video::SColorf LIGHT_COLOR;
extern const irr::f32 LIGHT_RADIUS;
extern const irr::f32 LIGHT_CONE_ANGLE;

extern const irr::video::SColorf AMBIENT_MATERIAL_DEFAULT;
extern const irr::video::SColorf DIFFUSE_MATERIAL_DEFAULT;
extern const irr::video::SColorf SPECULAR_MATERIAL_DEFAULT;
extern const irr::f32 SPECULAR_POWER;

//Shader, Bump Mapping, Parallax Mapping
extern const bool CREATE_MIP_MAPS;
extern const bool USE_OWN_SHADER_LIGHTING;
extern const bool USE_BUMP_MAPPING;
extern const bool USE_PARALLAX_MAPPING;
extern const bool USE_HEIGHT_MAP_TEXTURE;
extern const irr::f32 NORMAL_MAP_HEIGHT_TEXTURE_FACTOR;
extern const irr::f32 ADJUST_HEIGHT_FOR_PARALLAX;

//Explosion
extern const irr::core::dimension2df EXPLOSION_TEXTURE_DIMENSION;
extern const irr::u32 EXPLOSION_TEXTURE_WIDTH_FRAMES;
extern const irr::u32 EXPLOSION_TEXTURE_HEIGHT_FRAMES;
extern const irr::u32 EXPLOSION_TIME_PER_FRAME;

//CurveRoomSceneNode
#define MAX_CURVE_SECTIONS 10
extern const irr::u8 CURVE_SECTIONS;
extern const irr::f32 CURVE_RADIUS;

//StraightRoomSceneNode
#define MAX_STRAIGHT_SECTIONS 100
extern const irr::u8 STRAIGHT_SECTIONS_DEFAULT;

//Obstacles
extern const irr::f32 BOX_INCREASE_MULTIPLIER;

//Input
extern const irr::f32 KEY_REACTION_SPEED_DEFAULT;
extern const irr::f32 WALL_SIDE_MARGIN;
extern const irr::f32 WALL_BOTTOM_MARGIN;
extern const irr::f32 WALL_TOP_MARGIN;

#endif
