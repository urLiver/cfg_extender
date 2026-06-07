The Code for the .sprx in this repo aims to enhance the functionality of .cfg on old cods on the ps3

### Supported Games And There Commands:
Call of Duty - Ghost
- vstr &lt;variablename&gt;
- iprintln &lt;message&gt;
- iprintlnbold &lt;message&gt;
- execfromdisk &lt;filepath&gt;
- dvar_string &lt;dvar&gt; &lt;value&gt;
- dvar_int &lt;dvar&gt; &lt;value&gt; &lt;min&gt; &lt;max&gt;
- dvar_float &lt;dvar&gt; &lt;value&gt; &lt;min&gt; &lt;max&gt;
- dvar_bool &lt;dvar&gt; &lt;value&gt;
- dvar_vector &lt;dvar&gt; &lt;x&gt; &lt;y&gt; &lt;z&gt; &lt;min&gt; &lt;max&gt;
- dvar_vectorcolor &lt;dvar&gt; &lt;x&gt; &lt;y&gt; &lt;z&gt; &lt;max&gt;
- dump_commands
- dump_dvar
- mem_char &lt;offset&gt; &lt;byte&gt;
- mem_int &lt;offset&gt; &lt;value&gt;
- mem_float &lt;offset&gt; &lt;value&gt;
- clear_texts
- clear_rects
- text &lt;text&gt; &lt;x&gt; &lt;y&gt; &lt;font&gt; &lt;size&gt; &lt;r&gt; &lt;g&gt; &lt;b&gt; &lt;a&gt;
- rect &lt;x&gt; &lt;y&gt; &lt;w&gt; &lt;h&gt; &lt;material&gt; &lt;r&gt; &lt;g&gt; &lt;b&gt; &lt;a&gt;
- bind_cmd &lt;key&gt &lt;command&gt
- unbind_cmd &lt;key&gt

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