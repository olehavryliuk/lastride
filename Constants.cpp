#include "Constants.h"

//screen resolution
const irr::u32 SCREEN_WIDTH_DEFAULT = 1280;
const irr::u32 SCREEN_HEIGHT_DEFAULT = 1024;

//default device
const irr::video::E_DRIVER_TYPE VIDEO_DRIVER_TYPE = irr::video::EDT_DIRECT3D9;
const irr::u32 COLOR_BITS = 32;
const bool IS_FULLSCREEN = false;
const bool HAS_STENCILBUFFER = false;
const bool IS_VSYNC = false;

//default button width, height, margin
const irr::u32 BUTTON_WIDTH = 300;
//Author Oleh Havryliuk 07.2015
const irr::u32 BUTTON_HEIGHT = 50;
const irr::u32 BUTTON_MARGIN = 5;

//path
const irr::core::stringw FONT_PATH = L"Resources\\Fonts\\";
const irr::core::stringw MODEL_PATH = L"Resources\\Models\\";
const irr::core::stringw TEXTURE_PATH = L"Resources\\Textures\\";
const irr::core::stringw DEFAULT_FONT = L"fonthaettenschweiler.bmp";

//Debug
const bool SHOW_FPS = true;