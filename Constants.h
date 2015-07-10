//Author Oleh Havryliuk 07.2015
#ifndef __CONSTANTS_H_INCLUDED__
#define __CONSTANTS_H_INCLUDED__

#include <irrTypes.h>
#include <irrString.h>
#include <EDriverTypes.h>
//screen resolution
extern const irr::u32 SCREEN_WIDTH_DEFAULT;
extern const irr::u32 SCREEN_HEIGHT_DEFAULT;

//default device
extern const irr::video::E_DRIVER_TYPE VIDEO_DRIVER_TYPE;
extern const irr::u32 COLOR_BITS;
extern const bool IS_FULLSCREEN;
extern const bool HAS_STENCILBUFFER;
extern const bool IS_VSYNC;

//default button width, height, margin
extern const irr::u32 BUTTON_WIDTH;
extern const irr::u32 BUTTON_HEIGHT;
extern const irr::u32 BUTTON_MARGIN;

//Path
extern const irr::core::stringw FONT_PATH;
extern const irr::core::stringw MODEL_PATH;
extern const irr::core::stringw TEXTURE_PATH;
extern const irr::core::stringw DEFAULT_FONT;

//Debug
extern const bool SHOW_FPS;

#endif
