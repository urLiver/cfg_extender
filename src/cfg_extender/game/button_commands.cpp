#include "button_commands.hpp"

cmd_function_s cmd_functions[ 45 ];

struct __declspec(align(4)) kbutton_t
{
  int down[2];
  unsigned int downtime;
  unsigned int msec;
  bool active;
  bool wasPressed;
};

int KeyToCmd( const char* key )
{
    const char** commands;
    
    switch( global_current_game )
    {
        case Games_Ghost:
            commands = ( const char** )0xA85E38;
        break;
        case Games_Mw3:
            commands = ( const char** )0x728ADC;
        break;
        default:
            LogWrite( "KeyToCmd: called, but no game case defined for %i", ( int )global_current_game );
            return 0;
        break;
    }

    int binding = 0;

    while( 1 )
    {
        const char* command = commands[ binding ];

        if( ! strcmp( command, key ) )
        {            
            break;
        }

        if( ++binding >= 0x2B )
        {
            LogWrite( "KeyToCmd: no binding found for key %s", key );
            break;
        }
    }

    return binding;
}

void ExecBinding( void )
{
    static libpsutil::symbol<void( int localClientNum, int button, int cmd, int idk )> ExecBinding_Ghost{ 0x5E600C };

    if( CmdArgs_ArgC() == 1 )
    {
        switch( global_current_game )
        {
            case Games_Ghost:
                ExecBinding_Ghost( CmdArgs_LocalClientNum(), KeyToCmd( CmdArgs_ArgV( 0 ) ), KeyToCmd( CmdArgs_ArgV( 0 ) ), 0 );
            break;
            case Games_Mw3:
                LogWrite( "ExecBinding: currently is unsupported in mw3 as of function inlining" );
            break;
            default:
                LogWrite( "ExecBinding: called, but no game case defined for %i", ( int )global_current_game );
                return;
            break;
        }
    }
    else
    {
        LogWrite( "%s : called with arguments while it shouldn't have any, argc: %i", CmdArgs_ArgV( 0 ), CmdArgs_ArgC() );
    }
}

void AddBindingCommands( void )
{
    const char** commands;
    
    switch( global_current_game )
    {
        case Games_Ghost:
            commands = ( const char** )0xA85E38;
        break;
        case Games_Mw3:
            commands = ( const char** )0x728ADC;
        break;
        default:
            LogWrite( "AddBindingCommands: called, but no game case defined for %i", ( int )global_current_game );
            return;
        break;
    }

    int binding = 0;

    while( 1 )
    {
        const char* command = commands[ binding ];

        Cmd_AddCommandInternal( command, ExecBinding, &cmd_functions[ binding ] );

        if( ++binding >= 0x2B )
        {
            break;
        }
    }
}