The Code for the .sprx in this repo aims to enhance the functionality of .cfg on old cods on the ps3

### Supported Games And There Commands:
#### Call of Duty - Ghost
- cfge_vstr &lt;variablename&gt;
- cfge_iprintln &lt;message&gt;
- cfge_iprintlnbold &lt;message&gt;
- cfge_execfromdisk &lt;filepath&gt;
- cfge_dvar_string &lt;dvar&gt; &lt;value&gt;
- cfge_dvar_int &lt;dvar&gt; &lt;value&gt; &lt;min&gt; &lt;max&gt;
- cfge_dvar_float &lt;dvar&gt; &lt;value&gt; &lt;min&gt; &lt;max&gt;
- cfge_dvar_bool &lt;dvar&gt; &lt;value&gt;
- cfge_dvar_vector &lt;dvar&gt; &lt;x&gt; &lt;y&gt; &lt;z&gt; &lt;min&gt; &lt;max&gt;
- cfge_dvar_vectorcolor &lt;dvar&gt; &lt;x&gt; &lt;y&gt; &lt;z&gt; &lt;max&gt;
- cfge_dump_commands
- cfge_dump_dvar
- cfge_mem_char &lt;offset&gt; &lt;byte&gt;
- cfge_mem_int &lt;offset&gt; &lt;value&gt;
- cfge_mem_float &lt;offset&gt; &lt;value&gt;
- cfge_text &lt;text&gt; &lt;x&gt; &lt;y&gt; &lt;font&gt; &lt;size&gt; &lt;r&gt; &lt;g&gt; &lt;b&gt; &lt;a&gt;
- cfge_clear_texts
- cfge_rect &lt;x&gt; &lt;y&gt; &lt;w&gt; &lt;h&gt; &lt;material&gt; &lt;r&gt; &lt;g&gt; &lt;b&gt; &lt;a&gt;
- cfge_clear_rects
- cfge_print &lt;text&gt;
- cfge_clear_prints
- cfge_bind_cmd &lt;key&gt; &lt;command&gt;
- cfge_unbind_cmd &lt;key&gt;

##### Added Dvars
- cfge_print_font: int 2 - 10, default 2
- cfge_print_x: int 0 - 640, default 150
- cfge_print_y: int 0 - 640, default 100
- cfge_print_padding: int 0 - 200, default 20
- cfge_print_size: float 0.1 - 10, default 0.5

#### Call of Duty - Modern Warfare 3 ( Untested )
- cfge_vstr &lt;variablename&gt;
- cfge_iprintln &lt;message&gt;
- cfge_iprintlnbold &lt;message&gt;
- cfge_execfromdisk &lt;filepath&gt;
- cfge_dvar_string &lt;dvar&gt; &lt;value&gt;
- cfge_dvar_int &lt;dvar&gt; &lt;value&gt; &lt;min&gt; &lt;max&gt;
- cfge_dvar_float &lt;dvar&gt; &lt;value&gt; &lt;min&gt; &lt;max&gt;
- cfge_dvar_bool &lt;dvar&gt; &lt;value&gt;
- cfge_dvar_vector &lt;dvar&gt; &lt;x&gt; &lt;y&gt; &lt;z&gt; &lt;min&gt; &lt;max&gt;
- cfge_dvar_vectorcolor &lt;dvar&gt; &lt;x&gt; &lt;y&gt; &lt;z&gt; &lt;max&gt;
- cfge_dump_commands
- cfge_dump_dvar
- cfge_mem_char &lt;offset&gt; &lt;byte&gt;
- cfge_mem_int &lt;offset&gt; &lt;value&gt;
- cfge_mem_float &lt;offset&gt; &lt;value&gt;
- cfge_text &lt;text&gt; &lt;x&gt; &lt;y&gt; &lt;font&gt; &lt;size&gt; &lt;r&gt; &lt;g&gt; &lt;b&gt; &lt;a&gt;
- cfge_clear_texts
- cfge_rect &lt;x&gt; &lt;y&gt; &lt;w&gt; &lt;h&gt; &lt;material&gt; &lt;r&gt; &lt;g&gt; &lt;b&gt; &lt;a&gt;
- cfge_clear_rects
- cfge_bind_cmd &lt;key&gt; &lt;command&gt;
- cfge_unbind_cmd &lt;key&gt;

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