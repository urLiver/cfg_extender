#pragma once

#include "../game/global.hpp"

#include <libpsutil.h>
#include <cell/cell_fs.h>

void WriteFile( const char* path, const char* fmt, ... );

void LogWrite( const char* fmt, ... );
