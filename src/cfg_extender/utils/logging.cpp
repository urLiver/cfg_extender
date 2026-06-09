#include "logging.hpp"

#define LOGPATH "/dev_hdd0/tmp/cfg_extender.log"

static void Com_vsnprintf( char *dest, int size, const char *fmt, char *vargs )
{
    static libpsutil::symbol<void( char *dest, int size, const char *fmt, char *vargs )> Com_vsnprintf_Ghost{ 0x38CF48 };
    static libpsutil::symbol<void( char *dest, int size, const char *fmt, char *vargs )> Com_vsnprintf_Mw3{ 0x49286C };

    switch( global_current_game )
    {
        case Games_Ghost:
            Com_vsnprintf_Ghost( dest, size, fmt, vargs );
        break;
        case Games_Mw3:
            Com_vsnprintf_Mw3( dest, size, fmt, vargs );
        break;
        default:
            LogWrite( "Com_vsnprintf: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}

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
    
    size_t len = strlen(dest);
    if( len > 0 && dest[ len - 1 ] != '\n' )
    {
        if( len < sizeof( dest ) - 1 )
        {
            dest[ len ] = '\n';
            dest[ len + 1 ] = '\0';
        }
        else
        {
            dest[ sizeof( dest ) - 2 ] = '\n';
            dest[ sizeof( dest ) - 1 ] = '\0';
        }
    }

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
