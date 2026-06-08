#pragma once

#include <libpsutil.h>

#include "../utils/webman.hpp"

#define WEAK __declspec( selectany )

namespace CodModernWarfare3
{
	WEAK libpsutil::symbol<void( int localClientNum, int controllerIndex, const char *buffer )> Cbuf_ExecuteBuffer{ 0x1DBAEC };
	WEAK libpsutil::symbol<void( int localClientNum, const char *text )> Cbuf_InsertText{ 0x1DB424 };
	WEAK libpsutil::symbol<void( int localClientNum, const char *text )> Cbuf_AddText{ 0x1DB240 };
	WEAK libpsutil::symbol<void( char *dest, int size, const char *fmt, char *vargs )> Com_vsnprintf{ 0x49286C };
	WEAK libpsutil::symbol<char*( const char* format, ... )>va{ 0x299490 };
	WEAK libpsutil::symbol<void( int localClientNum, const char *text )>CG_GameMessage{ 0x7A588 };
	WEAK libpsutil::symbol<void( int localClientNum, const char *text )>CG_GameMessageBold{ 0x7A5C8 };
	WEAK libpsutil::symbol<int( const char *text, const char* fmt, ... )>_sscanf{ 0x492488 };
	WEAK libpsutil::symbol<int( const char *str )>Key_StringToKeynum{ 0xD1D18 };

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