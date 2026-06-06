#pragma once

#include <libpsutil.h>
#include <vector>
#include <string>

void Render( void );

void AddText( int localclientnum, const char* text, int x, int y, const char* font, float font_size, float r, float g, float b, float a );

void ClearTexts( void );

void AddRect( int localclientnum, int x, int y, int w, int h, const char* material, float r, float g, float b, float a );

void ClearRects( void );