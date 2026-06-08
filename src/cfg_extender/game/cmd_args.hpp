#pragma once

#include <stdlib.h>
#include <libpsutil.h>

#include "global.hpp"

#include "../utils/logging.hpp"

struct cmd_function_s
{
	cmd_function_s *next;
	const char *name;
	void (*function)();
};

#pragma pack(push, 1)
struct CmdArgs
{
	int nesting;
	int localClientNum[8];
	int controllerIndex[8];
	int argc[8];
	const char **argv[8];
};
#pragma pack(pop)

static CmdArgs* CmdArgs_GetCmdArgs( void )
{
	switch( global_current_game )
	{
		case Games_Ghost:
				return reinterpret_cast<CmdArgs*>( 0x103EBB0 );
		case Games_Mw3:
				return reinterpret_cast<CmdArgs*>( 0x11708A0 );
		default:
			LogWrite( "GetCmdArgs: called, but no game case definied for %i", ( int )global_current_game );

			return NULL;
		break;
	}
}

static int CmdArgs_ArgC( void ) 
{
	static CmdArgs* cmd_args = CmdArgs_GetCmdArgs();

	if( cmd_args == NULL )
	{
		return -1;
	}
	
	return cmd_args->argc[ cmd_args->nesting ];
}

static const char* CmdArgs_ArgV( int index )
{
	static CmdArgs* cmd_args = CmdArgs_GetCmdArgs();

	if( cmd_args == NULL )
	{
		return "";
	}
	
	return cmd_args->argv[ cmd_args->nesting ][ index ];
}

static int CmdArgs_LocalClientNum( void )
{
	static CmdArgs* cmd_args = CmdArgs_GetCmdArgs();

	if( cmd_args == NULL )
	{
		return -1;
	}
	
	return cmd_args->localClientNum[ cmd_args->nesting ];
}

static int CmdArgs_ControllerIndex( void )
{
	static CmdArgs* cmd_args = CmdArgs_GetCmdArgs();

	if( cmd_args == NULL )
	{
		return -1;
	}
	
	return cmd_args->controllerIndex[ cmd_args->nesting ];
}

static void Cmd_AddCommandInternal( const char* cmdName, void (*function)(), cmd_function_s *allocedCmd )
{
	static libpsutil::symbol<void( const char *cmdName, void (*function)(), cmd_function_s *allocedCmd )> Cmd_AddCommandInternal_Ghost{ 0x2B2EC0 };
	static libpsutil::symbol<void( const char *cmdName, void (*function)(), cmd_function_s *allocedCmd )> Cmd_AddCommandInternal_Mw3{ 0x1DC4FC };
	
	switch( global_current_game )
	{
		case Games_Ghost:
			Cmd_AddCommandInternal_Ghost( cmdName, function, allocedCmd );
		break;
		case Games_Mw3:
			Cmd_AddCommandInternal_Mw3( cmdName, function, allocedCmd );
		break;
		default:
			LogWrite( "Cmd_AddCommandInternal: called, but no game case definied for %i", ( int )global_current_game );
		break;
	}
}