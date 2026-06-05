#pragma once

#include <stdlib.h>
#include <libpsutil.h>

#define WEAK __declspec( selectany )

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

static CmdArgs* cmd_args = reinterpret_cast<CmdArgs*>(0x103EBB0);;

static int ArgC( void ) 
{
	if( cmd_args == NULL )
	{
		return -1;
	}
	
	return cmd_args->argc[ cmd_args->nesting ];
}


static const char* ArgV( int index )
{
	if( cmd_args == NULL )
	{
		return NULL;
	}
	
	return cmd_args->argv[ cmd_args->nesting ][ index ];
}

WEAK libpsutil::symbol<void( const char *cmdName, void (*function)(), cmd_function_s *allocedCmd )> Cmd_AddCommandInternal{ 0x2B2EC0 };