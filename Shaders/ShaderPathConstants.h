//Author Oleh Havryliuk 08.2015
#ifndef __SHADER_PATH_CONSTANTS_H_INCLUDED__
#define __SHADER_PATH_CONSTANTS_H_INCLUDED__

#include <path.h>

//bump mapping and blinn-phong lighting
extern const irr::io::path BUMP_HLSL_VERTEX_SHADER_PATH;
extern const irr::io::path BUMP_HLSL_PIXEL_SHADER_PATH;
extern const irr::io::path BUMP_GLSL_VERTEX_SHADER_PATH;
extern const irr::io::path BUMP_GLSL_FRAGMENT_SHADER_PATH;

//parallax mapping and blinn-phong lighting
extern const irr::io::path PARALLAX_HLSL_VERTEX_SHADER_PATH;
extern const irr::io::path PARALLAX_HLSL_PIXEL_SHADER_PATH;
extern const irr::io::path PARALLAX_GLSL_VERTEX_SHADER_PATH;
extern const irr::io::path PARALLAX_GLSL_FRAGMENT_SHADER_PATH;

#endif