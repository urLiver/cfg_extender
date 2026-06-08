#pragma once

#include "utils.hpp"

#include <cell/cell_fs.h>

namespace CodModernWarfare3
{
	void WriteFile( const char* path, const char* fmt, ... );

	void LogWrite( const char* fmt, ... );
}