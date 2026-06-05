#pragma once

#include <libpsutil.h>

#define WEAK __declspec( selectany )

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

WEAK libpsutil::symbol<const char*( const char *dvarName )> Dvar_GetVariantString{ 0x51FDEC };
WEAK libpsutil::symbol<dvar_t*( const char *dvarName )> Dvar_FindVar{ 0x50A63C };
WEAK libpsutil::symbol<dvar_t*( const char *dvarName, const char *value, unsigned int flags )> Dvar_RegisterString{ 0x4EAFF4 };