The Code for the .sprx in this repo aims to enhance the functionality of .cfg on old on the ps3

### Supported Games:
1. Call of Duty - Ghost

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