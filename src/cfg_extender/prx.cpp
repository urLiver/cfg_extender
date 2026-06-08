

#include <cellstatus.h>
#include <sys/prx.h>
#include <sys\ppu_thread.h>
#include <sys\Timer.h>
#include <cstddef>

#include "utils/webman.hpp"
#include "utils/game_finder.hpp"

#include "ghost/init.hpp"

#include "mw3/init.hpp"

SYS_MODULE_INFO( cfg, 0, 1, 1);
SYS_MODULE_START( Entry );
SYS_MODULE_STOP( End );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );	
SYS_LIB_EXPORT( Export, LIBNAME );

extern "C" int Export( void )
{
    return CELL_OK;
}

void (*OnStop)( void ) = NULL;

extern "C" int Entry( void )
{
	sys_ppu_thread_t id;
	
	sys_ppu_thread_create( &id, []( uint64_t ) 
	{
		sys_timer_usleep( 20000000 );
	
		if( IsCodGhost() )
		{
			CodGhost::OnStart();
			
			OnStop = CodGhost::OnStop;

			WebmanNotify( "Game: CoD Ghost ( Multiplayer )" );
		}
		else if( IsCodMw3() )
		{
			CodModernWarfare3::OnStart();
			
			OnStop = CodModernWarfare3::OnStop;

			WebmanNotify( "Game: CoD Modern Warfare 3 ( Multiplayer )" );
		}
		else
		{
			WebmanNotify( "Game Not Found!" );
		}

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
	
		if( OnStop != NULL )
		{
			OnStop();
		}
		
		sys_ppu_thread_exit( 0 );
	}, NULL, 0x7FC, 0x100, 0, "End" );

	return SYS_PRX_RESIDENT;
}
