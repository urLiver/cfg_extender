#include "commands.hpp"


cmd_function_s Cmd_Vstr_VAR;
void Cmd_Vstr( void ) 
{
	if ( ArgC() == 2 )
	{
		const char* string = ArgV( 1 );
		
		dvar_t* dvar = Dvar_FindVar( string );
		
		if ( dvar )
		{
			char dvar_type = dvar->type;
			if ( dvar_type == 6 || dvar_type == 7 )
			{
				const char* dvar_newline = va( "%s\n", dvar->current.string );
		
				Cbuf_InsertText( cmd_args->localClientNum[ cmd_args->nesting ], dvar_newline );
			}
			else
			{
				Com_Printf( "%s is not a string-based dvar, type: %i\n", dvar->name, dvar->type );
			}
		}
		else
		{
			Com_Printf( "%s doesn't exist\n", string );
		}
	}
	else
	{
		Com_Printf( "vstr <variablename> : execute a variable command, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_DvarRegisterString_VAR;
void Cmd_DvarRegisterString( void )
{
	if ( ArgC() == 3 )
	{
		const char* name = ArgV( 1 );
		const char* value = ArgV( 1 );

		Dvar_RegisterString( name, value, 0 );
	}
	else
	{
		Com_Printf( "dvar_string <variablename> <variablevalue> : set a dvar string, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_iPrintLn_VAR;
void Cmd_iPrintLn( void )
{
	if ( ArgC() == 2 )
	{
		const char* message = ArgV( 1 );

		CG_GameMessage( cmd_args->localClientNum[ cmd_args->nesting ], message );
	}
	else
	{
		Com_Printf( "iprintln <message> : prints a message on the screen, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_iPrintLnBold_VAR;
void Cmd_iPrintLnBold( void )
{
	if ( ArgC() == 2 )
	{
		const char* message = ArgV( 1 );

		CG_GameMessageBold( cmd_args->localClientNum[ cmd_args->nesting ], message );
	}
	else
	{
		Com_Printf( "iprintlnbold <message> : prints a message on the screen, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_Cmd_ExecFromDisk_VAR;
void Cmd_ExecFromDisk( void ) 
{
	if( ArgC() == 2 )
	{
		const char* file_path = ArgV( 1 );
		int file_descriptor;
		uint64_t pos;
		uint64_t nread;
		
		CellFsErrno error = cellFsOpen( file_path, 0, &file_descriptor, NULL, 0 );

		if( ! error )
		{
			CellFsStat stat;
			error = cellFsFstat( file_descriptor, &stat );

			if( ! error )
			{
				void* space = _sys_malloc( stat.st_size + 1 );
				memset( space, 0 , stat.st_size + 1 );
				
				cellFsLseek( file_descriptor, 0, CELL_FS_SEEK_SET, &pos );
				error = cellFsRead( file_descriptor, space, stat.st_size, &nread );

				if( ! error )
				{
					Cbuf_ExecuteBuffer( cmd_args->localClientNum[ cmd_args->nesting ], cmd_args->controllerIndex[ cmd_args->nesting ], ( char* )space );
				}
				else
				{
					Com_Printf( "%s cloudn't read file content\n", file_path );
				}

				_sys_free( space );
				space = NULL;
			}
			else
			{
				Com_Printf( "%s cloudn't get file size\n", file_path );
			}
		}
		else
		{
			Com_Printf( "%s doesn't exist\n", file_path );
		}

		cellFsClose( file_descriptor );
	}
	else
	{
		Com_Printf( "execfromdisk <filepath> : loads a file into memory and runs it, argc: %i\n", ArgC() );
	}
}

/*
Planned addons: 

text				text x y font size r g b a
rect				x y w h r g b a
dumpassetxheader	void
dumpcmds			void
dumpdvars			void

gravity				value
speed				value
jumpheight			value 
For games that dont have the dvars like g_speed

dvar_vector
dvar_float
...

*/