#pragma once

#include "libpsutil.h"

#include <string>
	
struct display_text
{
	int localclientnum;
	std::string text;
	int x;
	int y;
	std::string font;
	float font_size;
	float color[ 4 ];
};

struct display_rect
{
	int localclientnum;
	int x;
	int y;
	int w;
	int h;
	std::string material;
	float color[ 4 ];
};

struct print
{
	int localclientnum;
	std::string text;
	int x;
	int y;
	int font;
	float font_size;
};

extern std::vector<display_text> texts;
extern std::vector<display_rect> rects;
extern std::vector<print> prints;
	
extern int print_y;
extern int clear_prints;
extern int clear_texts;
extern int clear_rects;

extern bool key_toggled_table[ 4 ][ 128 ]; 
extern std::string key_cmd_table[ 4 ][ 128 ]; 

enum Games
{
	Games_Unknown,
	Games_Ghost,
	Games_Mw3,
};

extern Games global_current_game;