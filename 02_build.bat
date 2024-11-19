@echo off
gcc -g -Wall -o SDL_Window "02_SDL_Window.c" -IC:\Users\elaij\Software\SDL2\i686-w64-mingw32\include -LC:\Users\elaij\Software\SDL2\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2  

if %errorlevel% neq 0 exit /b %errorlevel%

SDL_Window.exe
