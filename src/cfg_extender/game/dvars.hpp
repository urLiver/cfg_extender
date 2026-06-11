#pragma once

#include "utils.hpp"

#include "../utils/logging.hpp"

#include "global.hpp"

#include <libpsutil.h>

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

void* Dvar_FindVar( const char *dvarName );

void* Dvar_RegisterBool( const char *dvarName, bool value, unsigned int flags );

void* Dvar_RegisterString( const char *dvarName, const char *value, unsigned int flags );

void* Dvar_RegisterInt( const char *dvarName, int value, int min, int max, unsigned int flags );

void* Dvar_RegisterFloat( const char *dvarName, float value, float min, float max, unsigned int flags );

void* Dvar_RegisterVec3( const char *dvarName, float x, float y, float z, float min, float max, unsigned int flags );

void* Dvar_RegisterVec3Color( const char *dvarName, float x, float y, float z, float max, unsigned int flags );

void Dvar_ForEach( void (*callback)(const void *, void *), void *userData );

int Dvar_GetInt( const char* dvarName );

float Dvar_GetFloat( const char* dvarName );

bool Dvar_GetBool( const char* dvarName );

void Dvar_SetIntByName( const char* dvarName, int value );

int Dvar_GetType( const void* dvar );

const char* Dvar_GetTypeString( const void* dvar );

const char* Dvar_GetEnumValue( const void* dvar, const DvarValue* value );

const char* Dvar_ValueToString( const void* dvar, const DvarValue* value );

const char* Dvar_GetName( const void* dvar );

DvarValue Dvar_GetCurrentValue( const void* dvar );

void Dvar_DumpAllDvars( void );