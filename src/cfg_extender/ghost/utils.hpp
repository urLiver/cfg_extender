#pragma once

#include <libpsutil.h>

#include "../utils/webman.hpp"

#define WEAK __declspec( selectany )

namespace CodGhost
{
	WEAK libpsutil::symbol<void( int localClientNum, int controllerIndex, const char *buffer )> Cbuf_ExecuteBuffer{ 0x2B24C8 };
	WEAK libpsutil::symbol<void( int localClientNum, const char *text )> Cbuf_InsertText{ 0x2B1DF4 };
	WEAK libpsutil::symbol<void( int localClientNum, const char *text )> Cbuf_AddText{ 0x2B1C14 };
	WEAK libpsutil::symbol<void( char *dest, int size, const char *fmt, char *vargs )> Com_vsnprintf{ 0x38CF48 };
	WEAK libpsutil::symbol<char*( const char* format, ... )>va{ 0x38DC30 };
	WEAK libpsutil::symbol<void( int localClientNum, const char *text )>CG_GameMessage{ 0x5BB454 };
	WEAK libpsutil::symbol<void( int localClientNum, const char *text )>CG_GameMessageBold{ 0x5A9F14 };
	WEAK libpsutil::symbol<int( const char *text, const char* fmt, ... )>_sscanf{ 0x7763D4 };
	WEAK libpsutil::symbol<int( const char *str )>Key_StringToKeynum{ 0x18EEF8 };

	static unsigned int StringToHex( const char* string )
	{
		unsigned int ret = 0;
		_sscanf( string, "%x", &ret );

		return ret;
	}

	static int StringToInt( const char* string )
	{
		int ret = 0;
		_sscanf( string, "%i", &ret );

		return ret;
	}

	static float StringToFloat( const char* string )
	{
		float ret = 0;
		_sscanf( string, "%f", &ret );

		return ret;
	}
}