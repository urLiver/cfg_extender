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
				LogWrite( "%s is not a string-based dvar, type: %i\n", dvar->name, dvar->type );
			}
		}
		else
		{
			LogWrite( "%s doesn't exist\n", string );
		}
	}
	else
	{
		LogWrite( "vstr <variablename> : execute a variable command, argc: %i\n", ArgC() );
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
		LogWrite( "iprintln <message> : prints a message on the screen, argc: %i\n", ArgC() );
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
		LogWrite( "iprintlnbold <message> : prints a message on the screen, argc: %i\n", ArgC() );
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
					LogWrite( "%s cloudn't read file content\n", file_path );
				}

				_sys_free( space );
				space = NULL;
			}
			else
			{
				LogWrite( "%s cloudn't get file size\n", file_path );
			}
		}
		else
		{
			LogWrite( "%s doesn't exist\n", file_path );
		}

		cellFsClose( file_descriptor );
	}
	else
	{
		LogWrite( "execfromdisk <filepath> : loads a file into memory and runs it, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_DvarRegisterString_VAR;
void Cmd_DvarRegisterString( void )
{
	if ( ArgC() == 3 )
	{
		Dvar_RegisterString( ArgV( 1 ), ArgV( 2 ), 0 );
	}
	else
	{
		LogWrite( "dvar_string <dvar> <value> : set a dvar string, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_DvarRegisterInt_VAR;
void Cmd_DvarRegisterInt( void )
{
	if ( ArgC() == 5 )
	{
		Dvar_RegisterInt( ArgV( 1 ), StringToInt( ArgV( 2 ) ), StringToInt( ArgV( 3 ) ), StringToInt( ArgV( 4 ) ), 0 );
	}
	else
	{
		LogWrite( "dvar_int <dvar> <value> <min> <max> : set a dvar string, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_DvarRegisterFloat_VAR;
void Cmd_DvarRegisterFloat( void )
{
	if ( ArgC() == 5 )
	{
		Dvar_RegisterFloat( ArgV( 1 ), StringToFloat( ArgV( 2 ) ), StringToFloat( ArgV( 3 ) ), StringToFloat( ArgV( 4 ) ), 0 );
	}
	else
	{
		LogWrite( "dvar_float <dvar> <value> <min> <max> : set a dvar string, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_DvarRegisterBool_VAR;
void Cmd_DvarRegisterBool( void )
{
	if ( ArgC() == 3 )
	{
		Dvar_RegisterBool( ArgV( 1 ), StringToInt( ArgV( 2 ) ), 0 );
	}
	else
	{
		LogWrite( "dvar_bool <dvar> <value> : set a dvar string, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_DvarRegisterVector_VAR;
void Cmd_DvarRegisterVector( void )
{
	if ( ArgC() == 7 )
	{
		Dvar_RegisterVec3( ArgV( 1 ), StringToFloat( ArgV( 2 ) ), StringToFloat( ArgV( 3 ) ), StringToFloat( ArgV( 4 ) ), StringToFloat( ArgV( 5 ) ), StringToFloat( ArgV( 6 ) ), 0 );
	}
	else
	{
		LogWrite( "dvar_vector <dvar> <x> <y> <z> <min> <max> : set a dvar string, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_DvarRegisterVectorColor_VAR;
void Cmd_DvarRegisterVectorColor( void )
{
	if ( ArgC() == 6 )
	{
		Dvar_RegisterVec3Color( ArgV( 1 ), StringToFloat( ArgV( 2 ) ), StringToFloat( ArgV( 3 ) ), StringToFloat( ArgV( 4 ) ), StringToFloat( ArgV( 5 ) ), 0 );
	}
	else
	{
		LogWrite( "dvar_vectorcolor <dvar> <x> <y> <z> <max> : set a dvar string, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_DumpCommands_VAR;
void Cmd_DumpCommands( void )
{
	if( ArgC() == 1 )
	{
		cmd_function_s* command;
		for( command = ( cmd_function_s* )0x1063D28; command != NULL; command = command->next )
		{
			WriteFile( "/dev_hdd0/tmp/cfg_extender.command_dump", "%s\n", command->name );
		}
	}
	else
	{
		LogWrite( "dump_commands called with arguments, while it shouldnt have any, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_DumpDvars_VAR;
void Cmd_DumpDvars( void )
{
	if( ArgC() == 1 )
	{
		DumpDvars();
	}
	else
	{
		LogWrite( "dump_dvar called with arguments, while it shouldnt have any, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_MemChar_VAR;
void Cmd_MemChar( void )
{
	if( ArgC() == 3 )
	{
		unsigned int offset = StringToHex( ArgV( 1 ) );
		unsigned int byte = StringToHex( ArgV( 2 ) );

		*( char* )offset = byte;
	}
	else
	{
		LogWrite( "mem_char <offset> <byte> : write a single byte to an offset, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_MemInt_VAR;
void Cmd_MemInt( void )
{
	if( ArgC() == 3 )
	{
		unsigned int offset = StringToHex( ArgV( 1 ) );
		int value = StringToInt( ArgV( 2 ) );

		*( int* )offset = value;
	}
	else
	{
		LogWrite( "mem_int <offset> <value> : write an int to an offset, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_MemFloat_VAR;
void Cmd_MemFloat( void )
{
	if( ArgC() == 3 )
	{
		unsigned int offset = StringToHex( ArgV( 1 ) );
		float value = StringToFloat( ArgV( 2 ) );

		*( float* )offset = value;
	}
	else
	{
		LogWrite( "mem_float <offset> <value> : write an float to an offset, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_ClearTexts_VAR;
void Cmd_ClearTexts( void )
{
	if( ArgC() == 1 )
	{
		ClearTexts();
	}
	else
	{
		LogWrite( "clear_texts called with arguments, while it shouldnt have any, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_ClearRects_VAR;
void Cmd_ClearRects( void )
{
	if( ArgC() == 1 )
	{
		ClearRects();
	}
	else
	{
		LogWrite( "clear_rects called with arguments, while it shouldnt have any, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_Text_VAR;
void Cmd_Text( void )
{
	if( ArgC() == 10 )
	{
		AddText( cmd_args->localClientNum[ cmd_args->nesting ], ArgV( 1 ), StringToInt( ArgV( 2 ) ), StringToInt( ArgV( 3 ) ), ArgV( 4 ), StringToFloat( ArgV( 5 ) ), StringToFloat( ArgV( 6 ) ), StringToFloat( ArgV( 7 ) ), StringToFloat( ArgV( 8 ) ), StringToFloat( ArgV( 9 ) ) );
	}
	else
	{
		LogWrite( "text <text> <x> <y> <font> <size> <r> <g> <b> <a> : renders text to the screen, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_Rect_VAR;
void Cmd_Rect( void )
{
	if( ArgC() == 10 )
	{
		AddRect( cmd_args->localClientNum[ cmd_args->nesting ], StringToInt( ArgV( 1 ) ), StringToInt( ArgV( 2 ) ), StringToInt( ArgV( 3 ) ), StringToInt( ArgV( 4 ) ), ArgV( 5 ), StringToFloat( ArgV( 6 ) ), StringToFloat( ArgV( 7 ) ), StringToFloat( ArgV( 8 ) ), StringToFloat( ArgV( 9 ) ) );
	}
	else
	{
		LogWrite( "rect <x> <y> <w> <h> <material> <r> <g> <b> <a> : renders a rect to the screen, argc: %i\n", ArgC() );
	}
}

bool key_toggled_table[ 4 ][ 128 ] = { 0 }; 
std::string key_cmd_table[ 4 ][ 128 ] = { std::string( "" ) }; 
cmd_function_s Cmd_BindCmd_VAR;
void Cmd_BindCmd( void )
{
	if( ArgC() == 3 )
	{
		int key = Key_StringToKeynum( ArgV( 1 ) );

		if( key != -1 )
		{
			key = std::tolower( key );

			key_toggled_table[ cmd_args->localClientNum[ cmd_args->nesting ] ][ key ] = 1;

			key_cmd_table[ cmd_args->localClientNum[ cmd_args->nesting ] ][ key ] = std::string( ArgV( 2 ) );
		}
		else
		{
			LogWrite( "invalid key for %s", ArgV( 1 ) );
		}
	}
	else
	{
		LogWrite( "bind_cmd <key> <cmd> : binds a command to a key, argc: %i\n", ArgC() );
	}
}

cmd_function_s Cmd_UnbindCmd_VAR;
void Cmd_UnbindCmd( void )
{
	if( ArgC() == 2 )
	{
		int key = Key_StringToKeynum( ArgV( 1 ) );

		if( key != -1 )
		{
			key = std::tolower( key );

			key_toggled_table[ cmd_args->localClientNum[ cmd_args->nesting ] ][ key ] = 0;
		}
		else
		{
			LogWrite( "invalid key for %s", ArgV( 1 ) );
		}
	}
	else
	{
		LogWrite( "unbind_cmd <key> : unbinds a command from a key, argc: %i\n", ArgC() );
	}
}