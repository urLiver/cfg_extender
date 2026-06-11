The Code for the .sprx in this repo aims to enhance the functionality of .cfg on old cods on the ps3

### Supported Games:
- Ghost
- Modern Warfare 3

#### Supported Commands:
- vstr <variable: <span style="color:#4295f5">string</span>>
- iprintln <message: <span style="color:#4295f5">string</span>>
- iprintlnbold <message: <span style="color:#4295f5">string</span>
- execfromdisk <filepath: <span style="color:#4295f5">string</span>> 
- dvar_string <dvar: <span style="color:#4295f5">string</span>> <value: <span style="color:#4295f5">string</span>>
- dvar_int <dvar: <span style="color:#4295f5">string</span>> <value: <span style="color:#4295f5">int</span>> <min: <span style="color:#4295f5">int</span>> <max: <span style="color:#4295f5">int</span>>
- dvar_float <dvar: <span style="color:#4295f5">string</span>> <value: <span style="color:#4295f5">float</span>> <min: <span style="color:#4295f5">float</span>> <max: <span style="color:#4295f5">float</span>>
- dvar_bool <dvar: <span style="color:#4295f5">string</span>> <value: <span style="color:#4295f5">int</span>>
- dvar_vector <dvar: <span style="color:#4295f5">string</span>> <x: <span style="color:#4295f5">float</span>> <y: <span style="color:#4295f5">float</span>> <z: <span style="color:#4295f5">float</span>> <min: <span style="color:#4295f5">float</span>> <max: <span style="color:#4295f5">float</span>>
- dvar_vectorcolor <dvar: <span style="color:#4295f5">string</span>> <r: <span style="color:#4295f5">float</span>> <g: <span style="color:#4295f5">float</span>> <b: <span style="color:#4295f5">float</span>> <max: <span style="color:#4295f5">float</span>>
- dump_commands
- dump_dvar
- mem_char <offset: <span style="color:#4295f5">hex</span>> <value: <span style="color:#4295f5">byte</span>>
- mem_int <offset: <span style="color:#4295f5">hex</span>> <value: <span style="color:#4295f5">int</span>>
- mem_float <offset: <span style="color:#4295f5">hex</span>> <value: <span style="color:#4295f5">float</span>>
- clear_texts
- clear_rects
- text <text: <span style="color:#4295f5">string</span>> <x: <span style="color:#4295f5">int</span>> <y: <span style="color:#4295f5">int</span>> <font: <span style="color:#4295f5">int</span>> <size: <span style="color:#4295f5">float</span>> <r: <span style="color:#4295f5">float</span>> <g: <span style="color:#4295f5">float</span>> <b: <span style="color:#4295f5">float</span>> <a: <span style="color:#4295f5">float</span>>
- rect <x: <span style="color:#4295f5">int</span>> <y: <span style="color:#4295f5">int</span>> <w: <span style="color:#4295f5">int</span>> <h: <span style="color:#4295f5">int</span>> <material: <span style="color:#4295f5">string</span>> <r: <span style="color:#4295f5">float</span>> <g: <span style="color:#4295f5">float</span>> <b: <span style="color:#4295f5">float</span>> <a: <span style="color:#4295f5">float</span>>
- bind_cmd <key: <span style="color:#4295f5">string</span>> <command: <span style="color:#4295f5">string</span>>
- unbind_cmd <key: <span style="color:#4295f5">string</span>>
- old binding commands such as +melee if the game loads them

#### Supported Dvars:
- unlock_dlc_content: allows on cod ghost the usage of any skin, camo ( by default on )
- unlock_any_attachment_combo: allows on cod ghost to use multpile sights and so on ( by default on )

#### File Explanations ( if exist in tmp ):
- on_start.cfg: will be auto loaded by the sprx if it exist in tmp
- cfg_extender.log: contains any error message that happend within the sprx, such as wrong calls to custom commands
- cfg_extender.command_dump: includes the commands dumped with dump_commands
- cfg_extender.dvar_dump: includes the dvars dumped with dump_dvar

### How to build
1. Take all Files for the Game you want to build the .sprx.
2. Make a new Ps3 prx Project in Visual Studio
3. #define ISGHOST or whatever game you build it for
4. Replace prx.cpp and put the folder into the Project, hit Build in Release and you good to go.

### Important
These steps only account for Windows as Linux and Mac dont got Visual Studio.

### What you need for the Build:
- PS3 SDK 4.75
- [libpsutil ( use Version 1.0.5 )](https://github.com/skiff/libpsutil)

## Credits
- anonymous, you know who you are
- me or so

Enjoy :D