#include "init.hpp"

bool init = false;

libpsutil::memory::detour* detour_Menu_PaintFullscreen;
void hook_Menu_PaintFullscreen( int a1 )
{
	Render();
	
	detour_Menu_PaintFullscreen->invoke( a1 );
	
	if( ! init )
	{
		init = true;
		
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
		
		WebmanNotify( "Loaded Commands" );
	}
}

libpsutil::memory::detour* detour_CG_TranslateGamepadButton;
bool hook_CG_TranslateGamepadButton( int localClientNum, int button, int cmd )
{
	if( key_toggled_table[ localClientNum ][ button ] )
	{
		const char* str = key_cmd_table[ localClientNum ][ button ].c_str();

		Cbuf_AddText( localClientNum, str );
		Cbuf_AddText( localClientNum, "\n" );

		return true;
	}

	return detour_CG_TranslateGamepadButton->invoke<bool>( localClientNum, button, cmd );
}

libpsutil::memory::detour* detour_Entitlements_IsIDUnlocked;
bool hook_Entitlements_IsIDUnlocked( int controllerindex, int a2 )
{
	return true;
}

libpsutil::memory::detour* detour_Content_DoWeHaveDLCPackByName;
bool hook_Content_DoWeHaveDLCPackByName( int controllerindex, unsigned int a2 )
{
	return true;
}

void OnStart( void )
{
	detour_Menu_PaintFullscreen = new libpsutil::memory::detour( static_cast<int>( 0x36DBC4 ), hook_Menu_PaintFullscreen );
	detour_CG_TranslateGamepadButton = new libpsutil::memory::detour( static_cast<int>( 0x15925C ), hook_CG_TranslateGamepadButton );

	detour_Entitlements_IsIDUnlocked = new libpsutil::memory::detour( static_cast<int>( 0x42EA98 ), hook_Entitlements_IsIDUnlocked );
	detour_Content_DoWeHaveDLCPackByName = new libpsutil::memory::detour( static_cast<int>( 0x5EF42C ), hook_Content_DoWeHaveDLCPackByName );
	
	Dvar_RegisterInt( "extinction_map_selection_enabled", 1, 0, 1, 0 );
	Dvar_RegisterInt( "extendedLoadoutsEnable", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_announcer", 3, 3, 3, 0 );
	Dvar_RegisterInt( "igs_swp", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_shp", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_svp", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_sve", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_svs", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_svr", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_swap", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_fo", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_td", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_sripper", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_smappacks", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_sosp", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_s1", 1, 0, 1, 0 );
	Dvar_RegisterInt( "igs_crossgame", 1, 0, 1, 0 );
}

void OnStop( void )
{
	detour_Menu_PaintFullscreen->~detour();
	detour_CG_TranslateGamepadButton->~detour();

	detour_Entitlements_IsIDUnlocked->~detour();
	detour_Content_DoWeHaveDLCPackByName->~detour();
}