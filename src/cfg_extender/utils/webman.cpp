#include "webman.hpp"

void SendWebManRequest( const char* command ) {
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0x7F000001; //127.0.0.1 (localhost)
    sin.sin_port = htons( 80 );

    int socket_connection = socket( AF_INET, SOCK_STREAM, 0 );
    if ( socket_connection < 0 || connect( socket_connection, ( struct sockaddr* )&sin, sizeof( sin )) < 0)
    {
        socket_connection = -1;
    }

    struct timeval time_val;
    time_val.tv_usec = 0;
    time_val.tv_sec = 3;

    setsockopt( socket_connection, SOL_SOCKET, SO_SNDTIMEO, &time_val, sizeof( time_val ) );
    setsockopt( socket_connection, SOL_SOCKET, SO_RCVTIMEO, &time_val, sizeof( time_val ) );

    if ( socket_connection < 0 )
    {
        return;
    }

    char webman_command[ 1048 ];
    int length = _sys_sprintf( webman_command, "GET %s HTTP/1.0\r\n", command );
    send( socket_connection, webman_command, length, 0 );

    if ( socket_connection == -1 )
    {
        return;
    }

    shutdown( socket_connection, SHUT_RDWR );
    socketclose( socket_connection );
    socket_connection = -1;
}
       
void FixSpaces( char** string_input ) 
{
    char* string = *string_input;

    char string_output[ 512 ];
    string_output[ 0 ] = '\0';

    int index = 0;
    for ( int i = 0; i < strlen( string ) + 1; i++ ) 
    {
        if( string[ i ] != 0x20 ) 
        {
	        string_output[ index ] = string[ i ];
	        index++;
        }
        else{
	        string_output[ index ] = '%';
	        string_output[ index + 1 ] = '2';
	        string_output[ index + 2 ] = '0';
	        index += 3;
        }

        string_output[ index ] = '\0';
    }

    *string_input = string_output;
}

void WebmanNotify( char* msg )
{
    FixSpaces( &msg );

    char buffer[ 512 ];
    sprintf( buffer, "/notify.ps3mapi?msg=%s", msg );

    SendWebManRequest( buffer );
}