#include "dvars.hpp"s

struct DvarLimits_unnamed_type_vector
{
    float min;
    float max;
};

struct DvarLimits_unnamed_type_integer
{
    int min;
    int max;
};

struct DvarLimits_unnamed_type_enumeration
{
    int stringCount;
    const char *const *strings;
};

struct DvarLimits_unnamed_type_value
{
    float min;
    float max;
};

union DvarLimits
{
    DvarLimits_unnamed_type_enumeration enumeration;
    DvarLimits_unnamed_type_integer integer;
    DvarLimits_unnamed_type_value value;
    DvarLimits_unnamed_type_vector vector;
};

struct dvar_t_ghost
{
    const char *name;
    unsigned int flags;
    uint8_t type;
    bool modified;
    DvarValue current;
    DvarValue latched;
    DvarValue reset;
    DvarLimits domain;
    bool (__fastcall *domainFunc)(dvar_t_ghost *, DvarValue);
    dvar_t_ghost *hashNext;
};

struct dvar_t_mw3
{
    const char *name;
    const char *description;
    uint16_t flags;
    uint8_t type;
    bool modified;
    DvarValue current;
    DvarValue latched;
    DvarValue reset;
    DvarLimits domain;
    dvar_t_mw3 *hashNext;
};

void* Dvar_FindVar( const char *dvarName )
{
    static libpsutil::symbol<void*( const char *dvarName )> Dvar_FindVar_Ghost{ 0x50A63C };
    static libpsutil::symbol<void*( const char *dvarName )> Dvar_FindVar_Mw3{ 0x2904C4 };

    switch( global_current_game )
    {
        case Games_Ghost:
            return Dvar_FindVar_Ghost( dvarName );
        break;
        case Games_Mw3:
            return Dvar_FindVar_Mw3( dvarName );
        break;
        default:
            LogWrite( "Dvar_FindVar: called, but no game case defined for %i", ( int )global_current_game );
            return nullptr;
        break;
    }
}

void* Dvar_RegisterBool( const char *dvarName, bool value, unsigned int flags )
{
    static libpsutil::symbol<void*( const char *dvarName, bool value, unsigned int flags )> Dvar_RegisterBool_Ghost{ 0x6BDAB8 };
    static libpsutil::symbol<void*( const char *dvarName, bool value, unsigned int flags, const char* description )> Dvar_RegisterBool_Mw3{ 0x2933F0 };

    switch( global_current_game )
    {
        case Games_Ghost:
            return Dvar_RegisterBool_Ghost( dvarName, value, flags );
        break;
        case Games_Mw3:
            return Dvar_RegisterBool_Mw3( dvarName, value, flags, "none" );
        break;
        default:
            LogWrite( "Dvar_RegisterBool: called, but no game case defined for %i", ( int )global_current_game );
            return nullptr;
        break;
    }
}

void* Dvar_RegisterString( const char *dvarName, const char *value, unsigned int flags )
{
    static libpsutil::symbol<void*( const char *dvarName, const char *value, unsigned int flags )> Dvar_RegisterString_Ghost{ 0x4EAFF4 };
    static libpsutil::symbol<void*( const char *dvarName, const char *value, unsigned int flags, const char* description )> Dvar_RegisterString_Mw3{ 0x2936A0 };

    switch( global_current_game )
    {
        case Games_Ghost:
            return Dvar_RegisterString_Ghost( dvarName, value, flags );
        break;
        case Games_Mw3:
            return Dvar_RegisterString_Mw3( dvarName, value, flags, "none" );
        break;
        default:
            LogWrite( "Dvar_RegisterString: called, but no game case defined for %i", ( int )global_current_game );
            return nullptr;
        break;
    }
}

void* Dvar_RegisterInt( const char *dvarName, int value, int min, int max, unsigned int flags )
{
    static libpsutil::symbol<void*( const char *dvarName, int value, int min, int max, unsigned int flags )> Dvar_RegisterInt_Ghost{ 0x54601C };
    static libpsutil::symbol<void*( const char *dvarName, int value, int min, int max, unsigned int flags, const char* description )> Dvar_RegisterInt_Mw3{ 0x293454 };

    switch( global_current_game )
    {
        case Games_Ghost:
            return Dvar_RegisterInt_Ghost( dvarName, value, min, max, flags );
        break;
        case Games_Mw3:
            return Dvar_RegisterInt_Mw3( dvarName, value, min, max, flags, "none" );
        break;
        default:
            LogWrite( "Dvar_RegisterInt: called, but no game case defined for %i", ( int )global_current_game );
            return nullptr;
        break;
    }
}

void* Dvar_RegisterFloat( const char *dvarName, float value, float min, float max, unsigned int flags )
{
    static libpsutil::symbol<void*( const char *dvarName, float value, float min, float max, unsigned int flags )> Dvar_RegisterFloat_Ghost{ 0x50C2A0 };
    static libpsutil::symbol<void*( const char *dvarName, float value, float min, float max, unsigned int flags, const char* description )> Dvar_RegisterFloat_Mw3{ 0x2934B4 };

    switch( global_current_game )
    {
        case Games_Ghost:
            return Dvar_RegisterFloat_Ghost( dvarName, value, min, max, flags );
        break;
        case Games_Mw3:
            return Dvar_RegisterFloat_Mw3( dvarName, value, min, max, flags, "none" );
        break;
        default:
            LogWrite( "Dvar_RegisterFloat: called, but no game case defined for %i", ( int )global_current_game );
            return nullptr;
        break;
    }
}

void* Dvar_RegisterVec3( const char *dvarName, float x, float y, float z, float min, float max, unsigned int flags )
{
    static libpsutil::symbol<void*( const char *dvarName, float x, float y, float z, float min, float max, unsigned int flags )> Dvar_RegisterVec3_Ghost{ 0x6C8A98 };
    static libpsutil::symbol<void*( const char *dvarName, float x, float y, float z, float min, float max, unsigned int flags, const char* description )> Dvar_RegisterVec3_Mw3{ 0x293578 };

    switch( global_current_game )
    {
        case Games_Ghost:
            return Dvar_RegisterVec3_Ghost( dvarName, x, y, z, min, max, flags );
        break;
        case Games_Mw3:
            return Dvar_RegisterVec3_Mw3( dvarName, x, y, z, min, max, flags, "none" );
        break;
        default:
            LogWrite( "Dvar_RegisterVec3: called, but no game case defined for %i", ( int )global_current_game );
            return nullptr;
        break;
    }
}

void* Dvar_RegisterVec3Color( const char *dvarName, float x, float y, float z, float max, unsigned int flags )
{
    static libpsutil::symbol<void*( const char *dvarName, float x, float y, float z, float max, unsigned int flags )> Dvar_RegisterVec3Color_Ghost{ 0x5E23CC };
    static libpsutil::symbol<void*( const char *dvarName, float x, float y, float z, float max, unsigned int flags, const char* description )> Dvar_RegisterVec3Color_Mw3{ 0x2935DC };

    switch( global_current_game )
    {
        case Games_Ghost:
            return Dvar_RegisterVec3Color_Ghost( dvarName, x, y, z, max, flags );
        break;
        case Games_Mw3:
            return Dvar_RegisterVec3Color_Mw3( dvarName, x, y, z, max, flags, "none" );
        break;
        default:
            LogWrite( "Dvar_RegisterVec3Color: called, but no game case defined for %i", ( int )global_current_game );
            return nullptr;
        break;
    }
}

void Dvar_ForEach( void (*callback)(const void *, void *), void *userData )
{
    static libpsutil::symbol<void( void (*callback)(const void *, void *), void *userData )> Dvar_ForEach_Ghost{ 0x57B198 };
    static libpsutil::symbol<void( void (*callback)(const void *, void *), void *userData )> Dvar_ForEach_Mw3{ 0x28FFF4 };

    switch( global_current_game )
    {
        case Games_Ghost:
            Dvar_ForEach_Ghost( callback, userData );
        break;
        case Games_Mw3:
            Dvar_ForEach_Mw3( callback, userData );
        break;
        default:
            LogWrite( "Dvar_ForEach: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}

int Dvar_GetInt( const char* dvarName )
{
    static libpsutil::symbol<int( const char* dvarName )> Dvar_GetInt_Ghost{ 0x5749A8 };
    static libpsutil::symbol<int( const char* dvarName )> Dvar_GetInt_Mw3{ 0x2910DC };

    switch( global_current_game )
    {
        case Games_Ghost:
            return Dvar_GetInt_Ghost( dvarName );
        break;
        case Games_Mw3:
            return Dvar_GetInt_Mw3( dvarName );
        break;
        default:
            LogWrite( "Dvar_GetInt: called, but no game case defined for %i", ( int )global_current_game );
            return 0;
        break;
    }
}

float Dvar_GetFloat( const char* dvarName )
{
    static libpsutil::symbol<float( const char* dvarName )> Dvar_GetFloat_Ghost{ 0x6AA6C8 };
    static libpsutil::symbol<float( const char* dvarName )> Dvar_GetFloat_Mw3{ 0x291148 };

    switch( global_current_game )
    {
        case Games_Ghost:
            return Dvar_GetFloat_Ghost( dvarName );
        break;
        case Games_Mw3:
            return Dvar_GetFloat_Mw3( dvarName );
        break;
        default:
            LogWrite( "Dvar_GetFloat: called, but no game case defined for %i", ( int )global_current_game );
            return 0.0f;
        break;
    }
}

void Dvar_SetIntByName( const char* dvarName, int value )
{
    static libpsutil::symbol<void( const char* dvarName, int value )> Dvar_SetIntByName_Ghost{ 0x6C19C8 };
    static libpsutil::symbol<void( const char* dvarName, int value )> Dvar_SetIntByName_Mw3{ 0x294238 };

    switch( global_current_game )
    {
        case Games_Ghost:
            Dvar_SetIntByName_Ghost( dvarName, value );
        break;
        case Games_Mw3:
            Dvar_SetIntByName_Mw3( dvarName, value );
        break;
        default:
            LogWrite( "Dvar_SetIntByName: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}

int Dvar_GetType( const void* dvar )
{
    switch( global_current_game )
    {
        case Games_Ghost:
            return ( ( dvar_t_ghost* )dvar )->type;
        break;
        case Games_Mw3:
            return ( ( dvar_t_mw3* )dvar )->type;
        break;
        default:
            LogWrite( "Dvar_GetType: called, but no game case defined for %i", ( int )global_current_game );

            return 0;
        break;
    }
}

const char* Dvar_GetTypeString( const void* dvar )
{
    int type = Dvar_GetType( dvar );

    const char* result = "unknow";

    switch ( type )
    {
        case 0:
            result = "DVAR_TYPE_BOOL";
            break;
        case 1:
            result = "DVAR_TYPE_FLOAT";
            break;
        case 2:
            result = "DVAR_TYPE_FLOAT_2";
            break;
        case 3:
            result = "DVAR_TYPE_FLOAT_3";
            break;
        case 4:
            result = "DVAR_TYPE_FLOAT_4";
            break;
        case 5:
            result = "DVAR_TYPE_INT";
            break;
        case 6:
            result = "DVAR_TYPE_ENUM";
            break;
        case 7:
            result = "DVAR_TYPE_STRING";
            break;
        case 8:
            result = "DVAR_TYPE_COLOR";
            break;
        case 9:
            result = "DVAR_TYPE_FLOAT_3_COLOR";
            break;
    }

    return result;
}

const char* Dvar_GetEnumValue( const void* dvar, const DvarValue* value )
{
    switch( global_current_game )
    {
        case Games_Ghost: 
            if ( ( ( dvar_t_ghost* )dvar )->domain.enumeration.stringCount )
            {
                return ( ( dvar_t_ghost* )dvar )->domain.enumeration.strings[ value->integer ];
            }
        break;
        case Games_Mw3:
            if ( ( ( dvar_t_mw3* )dvar )->domain.enumeration.stringCount )
            {
                return ( ( dvar_t_mw3* )dvar )->domain.enumeration.strings[ value->integer ];
            }
        break;
        default:
            LogWrite( "Dvar_GetEnumValue: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
    
    return "";
}

const char* Dvar_ValueToString( const void* dvar, const DvarValue* value )
{
    int type = Dvar_GetType( dvar );

    const char* result = "";

    switch ( type )
    {
        case 0:
            result = value->enabled ? "true" : "false";
            break;
        case 1:
            result = va( "%g", value->value );
            break;
        case 2:
            result = va( "%g %g", value->vector[ 0 ], value->vector[ 1 ] );
            break;
        case 3:
        case 9:
            result = va( "%g %g %g", value->vector[ 0 ], value->vector[ 1 ], value->vector[ 2 ] );
            break;
        case 4:
            result = va("%g %g %g %g", value->vector[ 0 ], value->vector[ 1 ], value->vector[ 2 ], value->vector[ 3 ] );
            break;
        case 5:
            result = va( "%i", value->unsignedInt );
            break;
        case 6:
            result = Dvar_GetEnumValue( dvar, value );
            break;
        case 7:
            result = va( "%s", value->string );
            break;
        case 8:
            result = va( "%g %g %g %g", ( float )( ( float )value->color[ 0 ] * 0.0039215689 ), ( float )( ( float )value->color[ 1 ] * 0.0039215689 ), ( float )( ( float )value->color[ 2 ] * 0.0039215689 ), ( float )( ( float )value->color[ 3 ] * 0.0039215689 ) );
            break;
    }

    return result;
}

const char* Dvar_GetName( const void* dvar )
{
    switch( global_current_game )
    {
        case Games_Ghost: 
            return ( ( dvar_t_ghost* )dvar )->name;
        break;
        case Games_Mw3:
            return ( ( dvar_t_mw3* )dvar )->name;
        break;
        default:
            LogWrite( "Dvar_GetName: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
    
    return "";
}

DvarValue Dvar_GetCurrentValue( const void* dvar )
{
    switch( global_current_game )
    {
        case Games_Ghost: 
            return ( ( dvar_t_ghost* )dvar )->current;
        break;
        case Games_Mw3:
            return ( ( dvar_t_mw3* )dvar )->current;
        break;
        default:
            LogWrite( "Dvar_GetCurrentValue: called, but no game case defined for %i", ( int )global_current_game );
        break;
    }
}

void Dvar_DumpDvar( const void* dvar, void* data )
{
    if( dvar == NULL )
    {
        return;
    }

    DvarValue value = Dvar_GetCurrentValue( dvar );

    WriteFile( "/dev_hdd0/tmp/cfg_extender.dvar_dump", "%s; %s; %s\n", Dvar_GetName( dvar ), Dvar_GetTypeString( dvar ), Dvar_ValueToString( dvar, &value ) );
}

void Dvar_DumpAllDvars( void )
{
    Dvar_ForEach( Dvar_DumpDvar, NULL );
}
