#include "game_finder.hpp"

#include "webman.hpp"

bool IsCodGhost( void ) 
{
	const char* part1 = ( const char* )0xA8C512;
	const char* part2 = ( const char* )0xA8C521;

	return ( strncmp( part1, "Call of Duty", 12 ) == 0 && strncmp( part2, "Ghosts", 6 ) == 0 );
}

bool IsCodMw3( void )
{
	const char* part1 = ( const char* )0x73098E;
	const char* part2 = ( const char* )0x73099F;

	return ( strncmp( part1, "Modern Warfare", 14 ) == 0 && strncmp( part2, "3", 1 ) == 0 );
}