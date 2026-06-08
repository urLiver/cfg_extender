#include "init.hpp"

#include "cmd_args.hpp"
#include "commands.hpp"
#include "rendering.hpp"

#include "../utils/webman.hpp"

namespace Cod_Ghost
{
	bool init = false;
	
	libpsutil::memory::detour* detour_Menu_PaintFullscreen;
	void hook_Menu_PaintFullscreen( int a1 )
	{
		Render();
	
		detour_Menu_PaintFullscreen->invoke( a1 );
	
		if( ! init )
		{
			init = true;
		
			Cmd_AddCommandInternal( "cfge_vstr", Cmd_Vstr, &Cmd_Vstr_VAR );

			Cmd_AddCommandInternal( "cfge_iprintln", Cmd_iPrintLn, &Cmd_iPrintLn_VAR );
			Cmd_AddCommandInternal( "cfge_iprintlnbold", Cmd_iPrintLnBold, &Cmd_iPrintLnBold_VAR );
			Cmd_AddCommandInternal( "cfge_execfromdisk", Cmd_ExecFromDisk, &Cmd_Cmd_ExecFromDisk_VAR );
		
			Cmd_AddCommandInternal( "cfge_dvar_string", Cmd_DvarRegisterString, &Cmd_DvarRegisterString_VAR );
			Cmd_AddCommandInternal( "cfge_dvar_int", Cmd_DvarRegisterInt, &Cmd_DvarRegisterInt_VAR );
			Cmd_AddCommandInternal( "cfge_dvar_float", Cmd_DvarRegisterFloat, &Cmd_DvarRegisterFloat_VAR );
			Cmd_AddCommandInternal( "cfge_dvar_bool", Cmd_DvarRegisterBool, &Cmd_DvarRegisterBool_VAR );
			Cmd_AddCommandInternal( "cfge_dvar_vector", Cmd_DvarRegisterVector, &Cmd_DvarRegisterVector_VAR );
			Cmd_AddCommandInternal( "cfge_dvar_vectorcolor", Cmd_DvarRegisterVectorColor, &Cmd_DvarRegisterVectorColor_VAR );
		
			Cmd_AddCommandInternal( "cfge_dump_commands", Cmd_DumpCommands, &Cmd_DumpCommands_VAR );
			Cmd_AddCommandInternal( "cfge_dump_dvar", Cmd_DumpDvars, &Cmd_DumpDvars_VAR );
		
			Cmd_AddCommandInternal( "cfge_mem_char", Cmd_MemChar, &Cmd_MemChar_VAR );
			Cmd_AddCommandInternal( "cfge_mem_int", Cmd_MemInt, &Cmd_MemInt_VAR );
			Cmd_AddCommandInternal( "cfge_mem_float", Cmd_MemFloat, &Cmd_MemFloat_VAR );
		
			Cmd_AddCommandInternal( "cfge_clear_texts", Cmd_ClearTexts, &Cmd_ClearTexts_VAR );
			Cmd_AddCommandInternal( "cfge_clear_rects", Cmd_ClearRects, &Cmd_ClearRects_VAR );
			Cmd_AddCommandInternal( "cfge_text", Cmd_Text, &Cmd_Text_VAR );
			Cmd_AddCommandInternal( "cfge_rect", Cmd_Rect, &Cmd_Rect_VAR );
		
			Cmd_AddCommandInternal( "cfge_bind_cmd", Cmd_BindCmd, &Cmd_BindCmd_VAR );
			Cmd_AddCommandInternal( "cfge_unbind_cmd", Cmd_UnbindCmd, &Cmd_UnbindCmd_VAR );
			
			Cmd_AddCommandInternal( "cfge_print", Cmd_Print, &Cmd_Print_VAR );
			Cmd_AddCommandInternal( "cfge_clear_prints", Cmd_ClearPrints, &Cmd_ClearPrints_VAR );
		
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
		Dvar_SetIntByName( "extinction_map_selection_enabled", 1 );
		Dvar_SetIntByName( "extendedLoadoutsEnable", 1 );
		Dvar_SetIntByName( "igs_announcer", 3 );
		Dvar_SetIntByName( "igs_swp", 1 );
		Dvar_SetIntByName( "igs_shp", 1 );
		Dvar_SetIntByName( "igs_svp", 1 );
		Dvar_SetIntByName( "igs_sve", 1 );
		Dvar_SetIntByName( "igs_svs", 1 );
		Dvar_SetIntByName( "igs_svr", 1 );
		Dvar_SetIntByName( "igs_swap", 1 );
		Dvar_SetIntByName( "igs_fo", 1 );
		Dvar_SetIntByName( "igs_td", 1 );
		Dvar_SetIntByName( "igs_sripper", 1 );
		Dvar_SetIntByName( "igs_smappacks", 1 );
		Dvar_SetIntByName( "igs_sosp", 1 );
		Dvar_SetIntByName( "igs_s1", 1 );
		Dvar_SetIntByName( "igs_crossgame", 1 );
		
		Dvar_RegisterInt( "cfge_print_font", 2, 2, 10, 0 );
		Dvar_RegisterFloat( "cfge_print_size", 0.5f, 0.1f, 10.0f, 0 );
		Dvar_RegisterInt( "cfge_print_x", 150, 0, 640, 0 );
		Dvar_RegisterInt( "cfge_print_y", 100, 0, 640, 0 );
		Dvar_RegisterInt( "cfge_print_padding", 20, 0, 200, 0 );

		detour_Menu_PaintFullscreen = new libpsutil::memory::detour( static_cast<int>( 0x36DBC4 ), hook_Menu_PaintFullscreen );
		detour_CG_TranslateGamepadButton = new libpsutil::memory::detour( static_cast<int>( 0x15925C ), hook_CG_TranslateGamepadButton );

		detour_Entitlements_IsIDUnlocked = new libpsutil::memory::detour( static_cast<int>( 0x42EA98 ), hook_Entitlements_IsIDUnlocked );
		detour_Content_DoWeHaveDLCPackByName = new libpsutil::memory::detour( static_cast<int>( 0x5EF42C ), hook_Content_DoWeHaveDLCPackByName );
	}

	void OnStop( void )
	{
		detour_Menu_PaintFullscreen->~detour();
		detour_CG_TranslateGamepadButton->~detour();

		detour_Entitlements_IsIDUnlocked->~detour();
		detour_Content_DoWeHaveDLCPackByName->~detour();
	}
}

namespace Cod_Mw3
{
	bool init = false;

	libpsutil::memory::detour* detour_Menu_PaintFullscreen;
	void hook_Menu_PaintFullscreen( int a1 )
	{
		Render();
	
		detour_Menu_PaintFullscreen->invoke( a1 );
	
		if( ! init )
		{
			init = true;
		
			Cmd_AddCommandInternal( "cfge_vstr", Cmd_Vstr, &Cmd_Vstr_VAR );

			Cmd_AddCommandInternal( "cfge_iprintln", Cmd_iPrintLn, &Cmd_iPrintLn_VAR );
			Cmd_AddCommandInternal( "cfge_iprintlnbold", Cmd_iPrintLnBold, &Cmd_iPrintLnBold_VAR );
			Cmd_AddCommandInternal( "cfge_execfromdisk", Cmd_ExecFromDisk, &Cmd_Cmd_ExecFromDisk_VAR );
		
			Cmd_AddCommandInternal( "cfge_dvar_string", Cmd_DvarRegisterString, &Cmd_DvarRegisterString_VAR );
			Cmd_AddCommandInternal( "cfge_dvar_int", Cmd_DvarRegisterInt, &Cmd_DvarRegisterInt_VAR );
			Cmd_AddCommandInternal( "cfge_dvar_float", Cmd_DvarRegisterFloat, &Cmd_DvarRegisterFloat_VAR );
			Cmd_AddCommandInternal( "cfge_dvar_bool", Cmd_DvarRegisterBool, &Cmd_DvarRegisterBool_VAR );
			Cmd_AddCommandInternal( "cfge_dvar_vector", Cmd_DvarRegisterVector, &Cmd_DvarRegisterVector_VAR );
			Cmd_AddCommandInternal( "cfge_dvar_vectorcolor", Cmd_DvarRegisterVectorColor, &Cmd_DvarRegisterVectorColor_VAR );
		
			Cmd_AddCommandInternal( "cfge_dump_commands", Cmd_DumpCommands, &Cmd_DumpCommands_VAR );
			Cmd_AddCommandInternal( "cfge_dump_dvar", Cmd_DumpDvars, &Cmd_DumpDvars_VAR );
		
			Cmd_AddCommandInternal( "cfge_mem_char", Cmd_MemChar, &Cmd_MemChar_VAR );
			Cmd_AddCommandInternal( "cfge_mem_int", Cmd_MemInt, &Cmd_MemInt_VAR );
			Cmd_AddCommandInternal( "cfge_mem_float", Cmd_MemFloat, &Cmd_MemFloat_VAR );
		
			Cmd_AddCommandInternal( "cfge_clear_texts", Cmd_ClearTexts, &Cmd_ClearTexts_VAR );
			Cmd_AddCommandInternal( "cfge_clear_rects", Cmd_ClearRects, &Cmd_ClearRects_VAR );
			Cmd_AddCommandInternal( "cfge_text", Cmd_Text, &Cmd_Text_VAR );
			Cmd_AddCommandInternal( "cfge_rect", Cmd_Rect, &Cmd_Rect_VAR );
		
			Cmd_AddCommandInternal( "cfge_bind_cmd", Cmd_BindCmd, &Cmd_BindCmd_VAR );
			Cmd_AddCommandInternal( "cfge_unbind_cmd", Cmd_UnbindCmd, &Cmd_UnbindCmd_VAR );
		
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

	void OnStart( void )
	{
		detour_Menu_PaintFullscreen = new libpsutil::memory::detour( static_cast<int>( 0x2772BC ), hook_Menu_PaintFullscreen );
		detour_CG_TranslateGamepadButton = new libpsutil::memory::detour( static_cast<int>( 0x72664 ), hook_CG_TranslateGamepadButton );
	}

	void OnStop( void )
	{
		detour_Menu_PaintFullscreen->~detour();
		detour_CG_TranslateGamepadButton->~detour();
	}
}

void OnStart( void )
{
    switch( global_current_game )
    {
        case Games_Ghost:
			Cod_Ghost::OnStart();
        break;
        case Games_Mw3:
			Cod_Mw3::OnStart();	
		break;
        default:
            LogWrite( "OnStart: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}

void OnStop( void )
{
    switch( global_current_game )
    {
        case Games_Ghost:
			Cod_Ghost::OnStop();
        break;
        case Games_Mw3:
			Cod_Mw3::OnStop();	
		break;
        default:
            LogWrite( "OnStop: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}