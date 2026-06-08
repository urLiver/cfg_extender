#pragma once

#include "../utils/webman.hpp"
#include "../utils/logging.hpp"

#include <libpsutil.h>

static void Cbuf_ExecuteBuffer( int localClientNum, int controllerIndex, const char *buffer )
{
    static libpsutil::symbol<void( int localClientNum, int controllerIndex, const char *buffer )> Cbuf_ExecuteBuffer_Ghost{ 0x2B24C8 };
    static libpsutil::symbol<void( int localClientNum, int controllerIndex, const char *buffer )> Cbuf_ExecuteBuffer_Mw3{ 0x1DBAEC };

    switch( global_current_game )
    {
        case Games_Ghost:
            Cbuf_ExecuteBuffer_Ghost( localClientNum, controllerIndex, buffer );
        break;
        case Games_Mw3:
            Cbuf_ExecuteBuffer_Mw3( localClientNum, controllerIndex, buffer );
        break;
        default:
            LogWrite( "Cbuf_ExecuteBuffer: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}

static void Cbuf_InsertText( int localClientNum, const char *text )
{
    static libpsutil::symbol<void( int localClientNum, const char *text )> Cbuf_InsertText_Ghost{ 0x2B1DF4 };
    static libpsutil::symbol<void( int localClientNum, const char *text )> Cbuf_InsertText_Mw3{ 0x1DB424 };

    switch( global_current_game )
    {
        case Games_Ghost:
            Cbuf_InsertText_Ghost( localClientNum, text );
        break;
        case Games_Mw3:
            Cbuf_InsertText_Mw3( localClientNum, text );
        break;
        default:
            LogWrite( "Cbuf_InsertText: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}

static void Cbuf_AddText( int localClientNum, const char *text )
{
    static libpsutil::symbol<void( int localClientNum, const char *text )> Cbuf_AddText_Ghost{ 0x2B1C14 };
    static libpsutil::symbol<void( int localClientNum, const char *text )> Cbuf_AddText_Mw3{ 0x1DB240 };

    switch( global_current_game )
    {
        case Games_Ghost:
            Cbuf_AddText_Ghost( localClientNum, text );
        break;
        case Games_Mw3:
            Cbuf_AddText_Mw3( localClientNum, text );
        break;
        default:
            LogWrite( "Cbuf_AddText: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}

static char* va( const char* format, ... )
{
    static libpsutil::symbol<char*( const char* format, ... )> va_Ghost{ 0x38DC30 };
    static libpsutil::symbol<char*( const char* format, ... )> va_Mw3{ 0x299490 };

    va_list args;
    va_start( args, format );
    
    char* result = nullptr;
    switch( global_current_game )
    {
        case Games_Ghost:
            result = va_Ghost( format, args );
        break;
        case Games_Mw3:
            result = va_Mw3( format, args );
        break;
        default:
            LogWrite( "va: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
    
    va_end( args );

    return result;
}

static void CG_GameMessage( int localClientNum, const char *text )
{
    static libpsutil::symbol<void( int localClientNum, const char *text )> CG_GameMessage_Ghost{ 0x5BB454 };
    static libpsutil::symbol<void( int localClientNum, const char *text )> CG_GameMessage_Mw3{ 0x7A588 };

    switch( global_current_game )
    {
        case Games_Ghost:
            CG_GameMessage_Ghost( localClientNum, text );
        break;
        case Games_Mw3:
            CG_GameMessage_Mw3( localClientNum, text );
        break;
        default:
            LogWrite( "CG_GameMessage: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}

static void CG_GameMessageBold( int localClientNum, const char *text )
{
    static libpsutil::symbol<void( int localClientNum, const char *text )> CG_GameMessageBold_Ghost{ 0x5A9F14 };
    static libpsutil::symbol<void( int localClientNum, const char *text )> CG_GameMessageBold_Mw3{ 0x7A5C8 };

    switch( global_current_game )
    {
        case Games_Ghost:
            CG_GameMessageBold_Ghost( localClientNum, text );
        break;
        case Games_Mw3:
            CG_GameMessageBold_Mw3( localClientNum, text );
        break;
        default:
            LogWrite( "CG_GameMessageBold: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}

static int _sscanf( const char *text, const char* fmt, ... )
{
    static libpsutil::symbol<int( const char *text, const char* fmt, ... )> _sscanf_Ghost{ 0x7763D4 };
    static libpsutil::symbol<int( const char *text, const char* fmt, ... )> _sscanf_Mw3{ 0x492488 };

    va_list args;
    va_start( args, fmt );

    int result = 0;
    switch( global_current_game )
    {
        case Games_Ghost:
            result = _sscanf_Ghost( text, fmt, args );
        break;
        case Games_Mw3:
            result = _sscanf_Mw3( text, fmt, args );
        break;
        default:
            LogWrite( "_sscanf: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }

    va_end( args );

    return result;
}

static int Key_StringToKeynum( const char *str )
{
    static libpsutil::symbol<int( const char *str )> Key_StringToKeynum_Ghost{ 0x18EEF8 };
    static libpsutil::symbol<int( const char *str )> Key_StringToKeynum_Mw3{ 0xD1D18 };

    switch( global_current_game )
    {
        case Games_Ghost:
            return Key_StringToKeynum_Ghost( str );
        break;
        case Games_Mw3:
            return Key_StringToKeynum_Mw3( str );
        break;
        default:
            LogWrite( "Key_StringToKeynum: called, but no game case defined for %i", ( int )global_current_game );
            return 0;
        break;
    }
}

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
