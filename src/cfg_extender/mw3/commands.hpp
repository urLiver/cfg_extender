#pragma once

#include "cmd_args.hpp"
#include "dvars.hpp"
#include "utils.hpp"
#include "rendering.hpp"

#include "../utils/webman.hpp"
#include "../utils/globals.hpp"

#include "logging.hpp"

#include <cell/cell_fs.h>

namespace CodModernWarfare3
{
	extern cmd_function_s Cmd_Vstr_VAR;
	void Cmd_Vstr( void );

	extern cmd_function_s Cmd_iPrintLn_VAR;
	void Cmd_iPrintLn( void );

	extern cmd_function_s Cmd_iPrintLnBold_VAR;
	void Cmd_iPrintLnBold( void );

	extern cmd_function_s Cmd_Cmd_ExecFromDisk_VAR;
	void Cmd_ExecFromDisk( void );

	extern cmd_function_s Cmd_DvarRegisterString_VAR;
	void Cmd_DvarRegisterString( void );

	extern cmd_function_s Cmd_DvarRegisterInt_VAR;
	void Cmd_DvarRegisterInt( void );

	extern cmd_function_s Cmd_DvarRegisterFloat_VAR;
	void Cmd_DvarRegisterFloat( void );

	extern cmd_function_s Cmd_DvarRegisterBool_VAR;
	void Cmd_DvarRegisterBool( void );

	extern cmd_function_s Cmd_DvarRegisterVector_VAR;
	void Cmd_DvarRegisterVector( void );

	extern cmd_function_s Cmd_DvarRegisterVectorColor_VAR;
	void Cmd_DvarRegisterVectorColor( void );

	extern cmd_function_s Cmd_DumpCommands_VAR;
	void Cmd_DumpCommands( void );

	extern cmd_function_s Cmd_DumpDvars_VAR;
	void Cmd_DumpDvars( void );

	extern cmd_function_s Cmd_MemChar_VAR;
	void Cmd_MemChar( void );

	extern cmd_function_s Cmd_MemInt_VAR;
	void Cmd_MemInt( void );

	extern cmd_function_s Cmd_MemFloat_VAR;
	void Cmd_MemFloat( void );

	extern cmd_function_s Cmd_ClearTexts_VAR;
	void Cmd_ClearTexts( void );

	extern cmd_function_s Cmd_ClearRects_VAR;
	void Cmd_ClearRects( void );

	extern cmd_function_s Cmd_Text_VAR;
	void Cmd_Text( void );

	extern cmd_function_s Cmd_Rect_VAR;
	void Cmd_Rect( void );

	extern cmd_function_s Cmd_BindCmd_VAR;
	void Cmd_BindCmd( void );

	extern cmd_function_s Cmd_UnbindCmd_VAR;
	void Cmd_UnbindCmd( void );
}