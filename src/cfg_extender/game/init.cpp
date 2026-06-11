#include "init.hpp"

#include "cmd_args.hpp"
#include "commands.hpp"
#include "rendering.hpp"
#include "button_commands.hpp"

#include "../utils/webman.hpp"

namespace Cod_Ghost
{	
	libpsutil::memory::detour* detour_Menu_PaintFullscreen;
	void hook_Menu_PaintFullscreen( int a1 )
	{
		Render();

		detour_Menu_PaintFullscreen->invoke( a1 );
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
		return Dvar_GetBool( "unlock_dlc_content" ) ? true : detour_Entitlements_IsIDUnlocked->invoke<bool>( controllerindex, a2 );
	}

	libpsutil::memory::detour* detour_Content_DoWeHaveDLCPackByName;
	bool hook_Content_DoWeHaveDLCPackByName( int controllerindex, unsigned int a2 )
	{
		return Dvar_GetBool( "unlock_dlc_content" ) ? true : detour_Content_DoWeHaveDLCPackByName->invoke<bool>( controllerindex, a2 );
	}

	struct __declspec(align(8)) StringTableCell
	{
		const char *string;
		int hash;
	};

	struct StringTable
	{
		const char *name;
		int columnCount;
		int rowCount;
		StringTableCell *values;
	};
	
	libpsutil::memory::detour* detour_StringTable_GetAsset;
	void hook_StringTable_GetAsset( const char *filename, StringTable **tablePtr )
	{
		detour_StringTable_GetAsset->invoke( filename, tablePtr );
	
		StringTable* table = *tablePtr;

		if( Dvar_GetBool( "unlock_any_attachment_combo" ) && ! strcmp( "mp/attachmentCombos.csv", filename ) )
		{
			for( int row = 0; row < table->rowCount; row++ )
			{
				for ( int col = 0; col < table->columnCount; col++ )
				{
					if( ! strcmp( table->values[ row * table->columnCount + col ].string, "no" ) )
					{
						table->values[ row * table->columnCount + col ].string = "";
						table->values[ row * table->columnCount + col ].hash = 0;
					}
				}
			}
		}
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
		
		detour_StringTable_GetAsset = new libpsutil::memory::detour( static_cast<int>( 0x382888 ), hook_StringTable_GetAsset );

		detour_Menu_PaintFullscreen = new libpsutil::memory::detour( static_cast<int>( 0x36DBC4 ), hook_Menu_PaintFullscreen );
		detour_CG_TranslateGamepadButton = new libpsutil::memory::detour( static_cast<int>( 0x15925C ), hook_CG_TranslateGamepadButton );

		detour_Entitlements_IsIDUnlocked = new libpsutil::memory::detour( static_cast<int>( 0x42EA98 ), hook_Entitlements_IsIDUnlocked );
		detour_Content_DoWeHaveDLCPackByName = new libpsutil::memory::detour( static_cast<int>( 0x5EF42C ), hook_Content_DoWeHaveDLCPackByName );
	}

	void OnStop( void )
	{
		detour_StringTable_GetAsset->~detour();

		detour_Menu_PaintFullscreen->~detour();
		detour_CG_TranslateGamepadButton->~detour();

		detour_Entitlements_IsIDUnlocked->~detour();
		detour_Content_DoWeHaveDLCPackByName->~detour();
	}
}

namespace Cod_Mw3
{
	libpsutil::memory::detour* detour_Menu_PaintFullscreen;
	void hook_Menu_PaintFullscreen( int a1 )
	{
		Render();

		detour_Menu_PaintFullscreen->invoke( a1 );
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

void AddCommands( void )
{
	AddCustomCommands();

	AddBindingCommands();

	Dvar_RegisterBool( "unlock_dlc_content", 1, 0 );
	Dvar_RegisterBool( "unlock_any_attachment_combo", 1, 0 );
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

			return;
        break;
    }
	
	AddCommands();

	if( libpsutil::filesystem::file_exists( "/dev_hdd0/tmp/on_start.cfg" ) )
	{
		Cbuf_AddText( 0, ";execfromdisk \"/dev_hdd0/tmp/on_start.cfg\";" );
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