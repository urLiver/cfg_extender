#include "global.hpp"

std::vector<display_text> texts;
std::vector<display_rect> rects;
std::vector<print> prints;
	
int print_y = -1;
int clear_prints = -1;
int clear_texts = -1;
int clear_rects = -1;

bool key_toggled_table[ 4 ][ 128 ] = { 0 }; 
std::string key_cmd_table[ 4 ][ 128 ] = { std::string( "" ) }; 

Games global_current_game = Games_Unknown;