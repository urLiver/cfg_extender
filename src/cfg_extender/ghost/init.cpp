#include "init.hpp"

bool init = false;

libpsutil::memory::detour* detour_Menu_PaintAll_Internal;
void hook_Menu_PaintAll_Internal( int a1, int a2 )
{
	detour_Menu_PaintAll_Internal->invoke( a1, a2 );
	
	if( ! init )
	{
		init = true;
		
		Cmd_AddCommandInternal( "vstr", Cmd_Vstr, &Cmd_Vstr_VAR );
		Cmd_AddCommandInternal( "dvar_string", Cmd_DvarRegisterString, &Cmd_DvarRegisterString_VAR );
		Cmd_AddCommandInternal( "iprintln", Cmd_iPrintLn, &Cmd_iPrintLn_VAR );
		Cmd_AddCommandInternal( "iprintlnbold", Cmd_iPrintLnBold, &Cmd_iPrintLnBold_VAR );
		Cmd_AddCommandInternal( "execfromdisk", Cmd_ExecFromDisk, &Cmd_Cmd_ExecFromDisk_VAR );
		
		WebmanNotify( "Loaded Commands" );
	}
}

void OnStart( void )
{
	detour_Menu_PaintAll_Internal = new libpsutil::memory::detour( static_cast<int>( 0x36D5D0 ), hook_Menu_PaintAll_Internal );
}

void OnStop( void )
{
	detour_Menu_PaintAll_Internal->~detour();
}