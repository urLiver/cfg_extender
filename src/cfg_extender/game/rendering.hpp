#pragma once

#include <libpsutil.h>
#include <vector>
#include <string>

#include "dvars.hpp"
#include "global.hpp"

void Render( void );

void AddText( const char* text, int x, int y, int font, float font_size, float r, float g, float b, float a );

void ClearTexts( void );

void AddRect( int x, int y, int w, int h, const char* material, float r, float g, float b, float a );

void ClearRects( void );