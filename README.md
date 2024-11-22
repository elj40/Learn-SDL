# Learn-SDL
Learn SDL by making some simple examples from scratch

## Important things to note
* SDL was downloaded and stored in ` C:\Users\elaij\Software\SDL2\i686-w64-mingw32 ` so if you were to set this up on a new computer make sure of the path
* The `SDL2.dll` file had to included in the same directory as the project
* Program must take arguments:
```C
int main(int argc, char * argv[]) {...
```
* When using a library like SDL_ttf, its kind of easier to copy paste the header file into the same dir as SDL2.h. There probably is some magic with flags, still not sure what standard practice is for this stuff on windows

## Examples

1. 01_Hello_SDL.c: Simply compiling with SDL
2. 02_SDL_Window.c: Make and display an empty window with custom colors
3. 03_SDL_Event.c: Close a window using enter, otherwise output the key that was pressed 
4. 04_SDL_Text.c: Display text using SDL_ttf and surfaces
5. 05_SDL_Text_Renderer.c: Same as 04_SDL_Text.c, but this time using the renderer so we can use the gpu
6. 06_SDL_Shapes.c: Using SDL to draw shapes that bounce on the screen
7. 07_SDL_Button.c: Make a slow moving button that closes the application

## References
* [SDL2 for MinGW zip download](https://github.com/libsdl-org/SDL/releases/download/release-2.30.9/SDL2-devel-2.30.9-mingw.zip)
* [Opening a window tutorial](https://dev.to/noah11012/using-sdl2-opening-a-window-79c)
* [Limiting frame rate](https://thenumb.at/cpp-course/sdl2/08/08.html)
