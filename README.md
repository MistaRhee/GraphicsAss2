GraphicsAss2
=============

Shit you'll need:
- SDL2
- SDL2 ttf
- glew
- rapidJSON

They should all be correctly placed in the libs/ folder etc. Shouldn't need to manually install, but if everything crashes and burns, instructions can be found below.

(ENSURE THAT SHIT WORKS BY RUNNING THE TEST SETUP.)

Installation for glew can be found [here](https://www.badprog.com/c-opengl-setting-up-visual-studio)
Installation for SDL2/SDL2 ttf are [here](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvsnet2010u/index.php) and [here](http://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php) respectively. (TTF requires you to read the steps to install Image, then just reapply. Nothing too difficult)

We'll be using the 32 bit (x86) libraries for maximum compatability.

[rapidJSON](http://rapidjson.org/) is just a bunch of header files (found in include/). Link for reference to documentation. Erm, you might want to set up your own project files as required (so have include directories in all their respective locations), but try to keep the existing file structure (i.e. header files in include/ source files in src/ data in system/)