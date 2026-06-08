#pragma once

#include "utils.hpp"

#include "logging.hpp"

#include <libpsutil.h>

#define WEAK __declspec( selectany )

namespace CodGhost
{
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

    union DvarValue
    {
        bool enabled;
        int integer;
        unsigned int unsignedInt;
        float value;
        float vector[4];
        const char *string;
        uint8_t color[4];
    };

    union DvarLimits
    {
      DvarLimits_unnamed_type_enumeration enumeration;
      DvarLimits_unnamed_type_integer integer;
      DvarLimits_unnamed_type_value value;
      DvarLimits_unnamed_type_vector vector;
    };

    struct dvar_t
    {
        const char *name;
        unsigned int flags;
        uint8_t type;
        bool modified;
        DvarValue current;
        DvarValue latched;
        DvarValue reset;
        DvarLimits domain;
        bool (__fastcall *domainFunc)(dvar_t *, DvarValue);
        dvar_t *hashNext;
    };

    WEAK libpsutil::symbol<dvar_t*( const char *dvarName )> Dvar_FindVar{ 0x50A63C };
    WEAK libpsutil::symbol<dvar_t*( const char *dvarName, bool value, unsigned int flags )> Dvar_RegisterBool{ 0x6BDAB8 };
    WEAK libpsutil::symbol<dvar_t*( const char *dvarName, const char *value, unsigned int flags )> Dvar_RegisterString{ 0x4EAFF4 };
    WEAK libpsutil::symbol<dvar_t*( const char *dvarName, int value, int min, int max, unsigned int flags )> Dvar_RegisterInt{ 0x54601C };
    WEAK libpsutil::symbol<dvar_t*( const char *dvarName, float value, float min, float max, unsigned int flags )> Dvar_RegisterFloat{ 0x50C2A0 };
    WEAK libpsutil::symbol<dvar_t*( const char *dvarName, float x, float y, float z, float min, float max, unsigned int flags )> Dvar_RegisterVec3{ 0x6C8A98 };
    WEAK libpsutil::symbol<dvar_t*( const char *dvarName, float x, float y, float z, float max, unsigned int flags )> Dvar_RegisterVec3Color{ 0x5E23CC };
    WEAK libpsutil::symbol<void( void (*callback)(const dvar_t *, void *), void *userData )> Dvar_ForEach{ 0x57B198 };
    WEAK libpsutil::symbol<int( const char* dvarName )> Dvar_GetInt{ 0x5749A8 };
    WEAK libpsutil::symbol<float( const char* dvarName )> Dvar_GetFloat{ 0x6AA6C8 };
    WEAK libpsutil::symbol<void( const char* dvarName, int value )> Dvar_SetIntByName{ 0x6C19C8 };
    
    static const char* DvarToType( const dvar_t* dvar )
    {
        const char* result = "unknow";
        switch ( dvar->type )
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

    static const char* DvarToValue( const dvar_t* dvar, const DvarValue* value )
    {
        const char* result = "";
        switch ( dvar->type )
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
                if ( dvar->domain.enumeration.stringCount )
                {
                    result = dvar->domain.enumeration.strings[ value->integer ];
                }
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

    static void DumpDvar( const dvar_t* dvar, void* data )
    {
        if( dvar == NULL )
        {
            return;
        }

        WriteFile( "/dev_hdd0/tmp/cfg_extender.dvar_dump", "%s; %s; %s\n", dvar->name, DvarToType( dvar ), DvarToValue( dvar, &dvar->current ) );
    }

    static void DumpDvars( void )
    {
        Dvar_ForEach( DumpDvar, NULL );
    }
}