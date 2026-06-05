#pragma once

#include "cmd_args.hpp"
#include "dvars.hpp"
#include "utils.hpp"

#include "../utils/webman.hpp"

#include <cell/cell_fs.h>

extern cmd_function_s Cmd_Vstr_VAR;
void Cmd_Vstr( void );

extern cmd_function_s Cmd_DvarRegisterString_VAR;
void Cmd_DvarRegisterString( void );

extern cmd_function_s Cmd_iPrintLn_VAR;
void Cmd_iPrintLn( void );

extern cmd_function_s Cmd_iPrintLnBold_VAR;
void Cmd_iPrintLnBold( void );

extern cmd_function_s Cmd_Cmd_ExecFromDisk_VAR;
void Cmd_ExecFromDisk( void );