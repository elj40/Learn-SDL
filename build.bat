@echo off

set SDL_INCLUDE=C:\Users\elaij\Software\SDL2\i686-w64-mingw32\include
set SDL_LIBS=C:\Users\elaij\Software\SDL2\i686-w64-mingw32\lib

set SDL_TTF_PATH=C:\Users\elaij\Software\SDL2\SDL2_ttf-devel-2.22.0-mingw\SDL2_ttf-2.22.0\i686-w64-mingw32

REM gcc -g -Wall -o SDL_Window.exe "02_SDL_Window.c" -I%SDL_INCLUDE% -L%SDL_LIBS% -lmingw32 -lSDL2main -lSDL2
REM gcc -g -Wall -o "SDL_Event.exe" "03_SDL_Event.c" -I%SDL_INCLUDE% -L%SDL_LIBS% -lmingw32 -lSDL2main -lSDL2  
gcc -g -Wall -o "SDL_Text.exe" "04_SDL_Text.c" -I%SDL_INCLUDE% -L%SDL_LIBS%  -L%SDL_TTF_PATH%\lib -lmingw32 -lSDL2_ttf -lSDL2main -lSDL2  

if %errorlevel% neq 0 exit /b %errorlevel%

REM SDL_Window.exe
SDL_Text.exe
