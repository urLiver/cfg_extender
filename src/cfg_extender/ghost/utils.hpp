#pragma once

#include <libpsutil.h>

#include "../utils/webman.hpp"

#define WEAK __declspec( selectany )

enum errorParm_t : int
{
    ERR_FATAL = 0x0,
    ERR_DROP = 0x1,
    ERR_SERVERDISCONNECT = 0x2,
    ERR_DISCONNECT = 0x3,
    ERR_SCRIPT = 0x4,
    ERR_SCRIPT_DROP = 0x5,
    ERR_LOCALIZATION = 0x6,
    ERR_MAPLOADERRORSUMMARY = 0x7,
};

WEAK libpsutil::symbol<void( int localClientNum, int controllerIndex, const char *buffer )> Cbuf_ExecuteBuffer{ 0x2B24C8 };
WEAK libpsutil::symbol<void( int localClientNum, const char *text )> Cbuf_InsertText{ 0x2B1DF4 };
WEAK libpsutil::symbol<void( int localClientNum, const char *text )> Cbuf_AddText{ 0x2B1C14 };
WEAK libpsutil::symbol<void( char *dest, int size, const char *fmt, char *vargs )> Com_vsnprintf{ 0x38CF48 };
WEAK libpsutil::symbol<char*( const char* format, ... )>va{ 0x38DC30 };
WEAK libpsutil::symbol<void( errorParm_t code, const char *fmt, ... )>Com_Error{ 0x588100 };
WEAK libpsutil::symbol<void( int localClientNum, const char *text )>CG_GameMessage{ 0x5BB454 };
WEAK libpsutil::symbol<void( int localClientNum, const char *text )>CG_GameMessageBold{ 0x5A9F14 };
WEAK libpsutil::symbol<int( const char *text, const char* fmt, ... )>_sscanf{ 0x7763D4 };

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