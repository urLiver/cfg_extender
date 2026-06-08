

#include <cellstatus.h>
#include <sys/prx.h>
#include <sys\ppu_thread.h>
#include <sys\Timer.h>
#include <cstddef>

#include "utils/webman.hpp"
#include "utils/game_finder.hpp"

#include "game/init.hpp"
#include "game/global.hpp"

SYS_MODULE_INFO( cfg, 0, 1, 1);
SYS_MODULE_START( Entry );
SYS_MODULE_STOP( End );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );	
SYS_LIB_EXPORT( Export, LIBNAME );

extern "C" int Export( void )
{
    return CELL_OK;
}

extern "C" int Entry( void )
{
	sys_ppu_thread_t id;
	
	sys_ppu_thread_create( &id, []( uint64_t ) 
	{
		sys_timer_usleep( 20000000 );
	
		if( IsCodGhost() )
		{
			global_current_game = Games_Ghost;

			WebmanNotify( "Game: CoD Ghost ( Multiplayer )" );
		}
		else if( IsCodMw3() )
		{
			global_current_game = Games_Mw3;

			WebmanNotify( "Game: CoD Modern Warfare 3 ( Multiplayer )" );
		}

		OnStart();

		sys_ppu_thread_exit( 0 );
	}, NULL, 0x7FC, 0x100, 0, "Entry" );

    return SYS_PRX_RESIDENT;
}

extern "C" int End( void ) 
{
	sys_ppu_thread_t id;
	
	sys_ppu_thread_create( &id, []( uint64_t ) 
	{
		WebmanNotify( "Stopping sprx" );
	
		OnStop();
		
		sys_ppu_thread_exit( 0 );
	}, NULL, 0x7FC, 0x100, 0, "End" );

	return SYS_PRX_RESIDENT;
}
