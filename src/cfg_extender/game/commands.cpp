#include "commands.hpp"

cmd_function_s Cmd_Vstr_VAR;
void Cmd_Vstr( void ) 
{
	if ( CmdArgs_ArgC() == 2 )
	{
		const char* string = CmdArgs_ArgV( 1 );
		
		void* dvar = Dvar_FindVar( string );
		
		if ( dvar )
		{
			char dvar_type = Dvar_GetType( dvar );
			if ( dvar_type == 6 || dvar_type == 7 )
			{
				const char* dvar_newline = va( "%s\n", Dvar_GetCurrentValue( dvar ).string );
		
				Cbuf_InsertText( CmdArgs_LocalClientNum(), dvar_newline );
			}
			else
			{
				LogWrite( "%s is not a string-based dvar, type: %i\n", Dvar_GetName( dvar ), Dvar_GetType( dvar ) );
			}
		}
		else
		{
			LogWrite( "%s doesn't exist\n", string );
		}
	}
	else
	{
		LogWrite( "vstr <variablename> : execute a variable command, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_iPrintLn_VAR;
void Cmd_iPrintLn( void )
{
	if ( CmdArgs_ArgC() == 2 )
	{
		const char* message = CmdArgs_ArgV( 1 );

		CG_GameMessage( CmdArgs_LocalClientNum(), message );
	}
	else
	{
		LogWrite( "iprintln <message> : prints a message on the screen, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_iPrintLnBold_VAR;
void Cmd_iPrintLnBold( void )
{
	if ( CmdArgs_ArgC() == 2 )
	{
		const char* message = CmdArgs_ArgV( 1 );

		CG_GameMessageBold( CmdArgs_LocalClientNum(), message );
	}
	else
	{
		LogWrite( "iprintlnbold <message> : prints a message on the screen, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_Cmd_ExecFromDisk_VAR;
void Cmd_ExecFromDisk( void ) 
{
	if( CmdArgs_ArgC() == 2 )
	{
		const char* file_path = CmdArgs_ArgV( 1 );
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
					Cbuf_ExecuteBuffer( CmdArgs_LocalClientNum(), CmdArgs_ControllerIndex(), ( char* )space );
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
		LogWrite( "execfromdisk <filepath> : loads a file into memory and runs it, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_DvarRegisterString_VAR;
void Cmd_DvarRegisterString( void )
{
	if ( CmdArgs_ArgC() == 3 )
	{
		Dvar_RegisterString( CmdArgs_ArgV( 1 ), CmdArgs_ArgV( 2 ), 0 );
	}
	else
	{
		LogWrite( "dvar_string <dvar> <value> : set a dvar string, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_DvarRegisterInt_VAR;
void Cmd_DvarRegisterInt( void )
{
	if ( CmdArgs_ArgC() == 5 )
	{
		Dvar_RegisterInt( CmdArgs_ArgV( 1 ), StringToInt( CmdArgs_ArgV( 2 ) ), StringToInt( CmdArgs_ArgV( 3 ) ), StringToInt( CmdArgs_ArgV( 4 ) ), 0 );
	}
	else
	{
		LogWrite( "dvar_int <dvar> <value> <min> <max> : set a dvar string, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_DvarRegisterFloat_VAR;
void Cmd_DvarRegisterFloat( void )
{
	if ( CmdArgs_ArgC() == 5 )
	{
		Dvar_RegisterFloat( CmdArgs_ArgV( 1 ), StringToFloat( CmdArgs_ArgV( 2 ) ), StringToFloat( CmdArgs_ArgV( 3 ) ), StringToFloat( CmdArgs_ArgV( 4 ) ), 0 );
	}
	else
	{
		LogWrite( "dvar_float <dvar> <value> <min> <max> : set a dvar string, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_DvarRegisterBool_VAR;
void Cmd_DvarRegisterBool( void )
{
	if ( CmdArgs_ArgC() == 3 )
	{
		Dvar_RegisterBool( CmdArgs_ArgV( 1 ), StringToInt( CmdArgs_ArgV( 2 ) ), 0 );
	}
	else
	{
		LogWrite( "dvar_bool <dvar> <value> : set a dvar string, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_DvarRegisterVector_VAR;
void Cmd_DvarRegisterVector( void )
{
	if ( CmdArgs_ArgC() == 7 )
	{
		Dvar_RegisterVec3( CmdArgs_ArgV( 1 ), StringToFloat( CmdArgs_ArgV( 2 ) ), StringToFloat( CmdArgs_ArgV( 3 ) ), StringToFloat( CmdArgs_ArgV( 4 ) ), StringToFloat( CmdArgs_ArgV( 5 ) ), StringToFloat( CmdArgs_ArgV( 6 ) ), 0 );
	}
	else
	{
		LogWrite( "dvar_vector <dvar> <x> <y> <z> <min> <max> : set a dvar string, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_DvarRegisterVectorColor_VAR;
void Cmd_DvarRegisterVectorColor( void )
{
	if ( CmdArgs_ArgC() == 6 )
	{
		Dvar_RegisterVec3Color( CmdArgs_ArgV( 1 ), StringToFloat( CmdArgs_ArgV( 2 ) ), StringToFloat( CmdArgs_ArgV( 3 ) ), StringToFloat( CmdArgs_ArgV( 4 ) ), StringToFloat( CmdArgs_ArgV( 5 ) ), 0 );
	}
	else
	{
		LogWrite( "dvar_vectorcolor <dvar> <x> <y> <z> <max> : set a dvar string, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_DumpCommands_VAR;
void Cmd_DumpCommands( void )
{
	if( CmdArgs_ArgC() == 1 )
	{
		cmd_function_s* command;
		
		switch( global_current_game )
		{
			case Games_Ghost:
				for( command = ( cmd_function_s* )0x1063D28; command != NULL; command = command->next )
				{
					WriteFile( "/dev_hdd0/tmp/cfg_extender.command_dump", "%s\n", command->name );
				}
			break;
			case Games_Mw3:
				for( command = ( cmd_function_s* )0x11B5A30; command != NULL; command = command->next )
				{
					WriteFile( "/dev_hdd0/tmp/cfg_extender.command_dump", "%s\n", command->name );
				}
			break;
			default:
				LogWrite( "dump_commands: called, but no game case defined for %i", ( int )global_current_game );
			break;
		}
	}
	else
	{
		LogWrite( "dump_commands called with arguments, while it shouldnt have any, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_DumpDvars_VAR;
void Cmd_DumpDvars( void )
{
	if( CmdArgs_ArgC() == 1 )
	{
		Dvar_DumpAllDvars();
	}
	else
	{
		LogWrite( "dump_dvar called with arguments, while it shouldnt have any, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_MemChar_VAR;
void Cmd_MemChar( void )
{
	if( CmdArgs_ArgC() == 3 )
	{
		unsigned int offset = StringToHex( CmdArgs_ArgV( 1 ) );
		unsigned int byte = StringToHex( CmdArgs_ArgV( 2 ) );

		*( char* )offset = byte;
	}
	else
	{
		LogWrite( "mem_char <offset> <byte> : write a single byte to an offset, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_MemInt_VAR;
void Cmd_MemInt( void )
{
	if( CmdArgs_ArgC() == 3 )
	{
		unsigned int offset = StringToHex( CmdArgs_ArgV( 1 ) );
		int value = StringToInt( CmdArgs_ArgV( 2 ) );

		*( int* )offset = value;
	}
	else
	{
		LogWrite( "mem_int <offset> <value> : write an int to an offset, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_MemFloat_VAR;
void Cmd_MemFloat( void )
{
	if( CmdArgs_ArgC() == 3 )
	{
		unsigned int offset = StringToHex( CmdArgs_ArgV( 1 ) );
		float value = StringToFloat( CmdArgs_ArgV( 2 ) );

		*( float* )offset = value;
	}
	else
	{
		LogWrite( "mem_float <offset> <value> : write an float to an offset, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_ClearTexts_VAR;
void Cmd_ClearTexts( void )
{
	if( CmdArgs_ArgC() == 1 )
	{
		ClearTexts();
	}
	else
	{
		LogWrite( "clear_texts called with arguments, while it shouldnt have any, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_ClearRects_VAR;
void Cmd_ClearRects( void )
{
	if( CmdArgs_ArgC() == 1 )
	{
		ClearRects();
	}
	else
	{
		LogWrite( "clear_rects called with arguments, while it shouldnt have any, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_Text_VAR;
void Cmd_Text( void )
{
	if( CmdArgs_ArgC() == 10 )
	{
		AddText( CmdArgs_ArgV( 1 ), StringToInt( CmdArgs_ArgV( 2 ) ), StringToInt( CmdArgs_ArgV( 3 ) ), StringToInt( CmdArgs_ArgV( 4 ) ), StringToFloat( CmdArgs_ArgV( 5 ) ), StringToFloat( CmdArgs_ArgV( 6 ) ), StringToFloat( CmdArgs_ArgV( 7 ) ), StringToFloat( CmdArgs_ArgV( 8 ) ), StringToFloat( CmdArgs_ArgV( 9 ) ) );
	}
	else
	{
		LogWrite( "text <text> <x> <y> <font> <size> <r> <g> <b> <a> : renders text to the screen, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_Rect_VAR;
void Cmd_Rect( void )
{
	if( CmdArgs_ArgC() == 10 )
	{
		AddRect( StringToInt( CmdArgs_ArgV( 1 ) ), StringToInt( CmdArgs_ArgV( 2 ) ), StringToInt( CmdArgs_ArgV( 3 ) ), StringToInt( CmdArgs_ArgV( 4 ) ), CmdArgs_ArgV( 5 ), StringToFloat( CmdArgs_ArgV( 6 ) ), StringToFloat( CmdArgs_ArgV( 7 ) ), StringToFloat( CmdArgs_ArgV( 8 ) ), StringToFloat( CmdArgs_ArgV( 9 ) ) );
	}
	else
	{
		LogWrite( "rect <x> <y> <w> <h> <material> <r> <g> <b> <a> : renders a rect to the screen, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_BindCmd_VAR;
void Cmd_BindCmd( void )
{
	if( CmdArgs_ArgC() == 3 )
	{
		int key = Key_StringToKeynum( CmdArgs_ArgV( 1 ) );

		if( key != -1 )
		{
			key = std::tolower( key );

			key_toggled_table[ CmdArgs_LocalClientNum() ][ key ] = 1;

			key_cmd_table[ CmdArgs_LocalClientNum() ][ key ] = std::string( CmdArgs_ArgV( 2 ) );
		}
		else
		{
			LogWrite( "invalid key for %s", CmdArgs_ArgV( 1 ) );
		}
	}
	else
	{
		LogWrite( "bind_cmd <key> <cmd> : binds a command to a key, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

cmd_function_s Cmd_UnbindCmd_VAR;
void Cmd_UnbindCmd( void )
{
	if( CmdArgs_ArgC() == 2 )
	{
		int key = Key_StringToKeynum( CmdArgs_ArgV( 1 ) );

		if( key != -1 )
		{
			key = std::tolower( key );

			key_toggled_table[ CmdArgs_LocalClientNum() ][ key ] = 0;
		}
		else
		{
			LogWrite( "invalid key for %s", CmdArgs_ArgV( 1 ) );
		}
	}
	else
	{
		LogWrite( "unbind_cmd <key> : unbinds a command from a key, CmdArgs_ArgC: %i\n", CmdArgs_ArgC() );
	}
}

void AddCustomCommands( void )
{
	Cmd_AddCommandInternal( "vstr", Cmd_Vstr, &Cmd_Vstr_VAR );

	Cmd_AddCommandInternal( "iprintln", Cmd_iPrintLn, &Cmd_iPrintLn_VAR );
	Cmd_AddCommandInternal( "iprintlnbold", Cmd_iPrintLnBold, &Cmd_iPrintLnBold_VAR );

	Cmd_AddCommandInternal( "execfromdisk", Cmd_ExecFromDisk, &Cmd_Cmd_ExecFromDisk_VAR );
		
	Cmd_AddCommandInternal( "dvar_string", Cmd_DvarRegisterString, &Cmd_DvarRegisterString_VAR );
	Cmd_AddCommandInternal( "dvar_int", Cmd_DvarRegisterInt, &Cmd_DvarRegisterInt_VAR );
	Cmd_AddCommandInternal( "dvar_float", Cmd_DvarRegisterFloat, &Cmd_DvarRegisterFloat_VAR );
	Cmd_AddCommandInternal( "dvar_bool", Cmd_DvarRegisterBool, &Cmd_DvarRegisterBool_VAR );
	Cmd_AddCommandInternal( "dvar_vector", Cmd_DvarRegisterVector, &Cmd_DvarRegisterVector_VAR );
	Cmd_AddCommandInternal( "dvar_vectorcolor", Cmd_DvarRegisterVectorColor, &Cmd_DvarRegisterVectorColor_VAR );
		
	Cmd_AddCommandInternal( "dump_commands", Cmd_DumpCommands, &Cmd_DumpCommands_VAR );
	Cmd_AddCommandInternal( "dump_dvar", Cmd_DumpDvars, &Cmd_DumpDvars_VAR );
		
	Cmd_AddCommandInternal( "mem_char", Cmd_MemChar, &Cmd_MemChar_VAR );
	Cmd_AddCommandInternal( "mem_int", Cmd_MemInt, &Cmd_MemInt_VAR );
	Cmd_AddCommandInternal( "mem_float", Cmd_MemFloat, &Cmd_MemFloat_VAR );
		
	Cmd_AddCommandInternal( "clear_texts", Cmd_ClearTexts, &Cmd_ClearTexts_VAR );
	Cmd_AddCommandInternal( "clear_rects", Cmd_ClearRects, &Cmd_ClearRects_VAR );
	Cmd_AddCommandInternal( "text", Cmd_Text, &Cmd_Text_VAR );
	Cmd_AddCommandInternal( "rect", Cmd_Rect, &Cmd_Rect_VAR );
		
	Cmd_AddCommandInternal( "bind_cmd", Cmd_BindCmd, &Cmd_BindCmd_VAR );
	Cmd_AddCommandInternal( "unbind_cmd", Cmd_UnbindCmd, &Cmd_UnbindCmd_VAR );
}