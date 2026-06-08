#include "logging.hpp"

#define LOGPATH "/dev_hdd0/tmp/cfg_extender.log"

namespace CodModernWarfare3
{
    void WriteFile( const char* path, const char* fmt, ... )
    {
        char dest[ 512 ] = { 0 };

        va_list vargs;

        va_start( vargs, fmt );

        Com_vsnprintf( dest, sizeof( dest ), fmt, vargs );

        int file_descriptor = 0;

	    CellFsErrno error = cellFsOpen( path, CELL_FS_O_RDWR | CELL_FS_O_CREAT | CELL_FS_O_APPEND, &file_descriptor, NULL, 0 );

	    if ( error != CELL_FS_SUCCEEDED)
	    {
            goto end;
	    }

	    cellFsWrite( file_descriptor, dest, strlen( dest ), NULL );

    end:
	    cellFsClose( file_descriptor );

        va_end( vargs );
    }

    void LogWrite( const char* fmt, ... )
    {
        char dest[ 512 ] = { 0 };

        va_list vargs;

        va_start( vargs, fmt );

        Com_vsnprintf( dest, sizeof( dest ), fmt, vargs );

        int file_descriptor = 0;

	    CellFsErrno error = cellFsOpen( LOGPATH, CELL_FS_O_RDWR | CELL_FS_O_CREAT | CELL_FS_O_APPEND, &file_descriptor, NULL, 0 );

	    if( error != CELL_FS_SUCCEEDED )
	    {
            va_end( vargs );
    
            return;
	    }

	    cellFsWrite( file_descriptor, dest, strlen( dest ), NULL );

    end:
	    cellFsClose( file_descriptor );

        va_end( vargs );
    }
}