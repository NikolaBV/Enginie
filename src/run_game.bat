@echo off
echo Setting up 2D Engine...

REM Copy resources to debug directory if they don't exist
if not exist "x64\Debug\resources" (
    echo Copying resources...
    xcopy resources x64\Debug\resources /E /I /Y >nul
)

REM Copy DLLs to debug directory if they don't exist
if not exist "x64\Debug\SDL2.dll" (
    echo Copying DLLs...
    xcopy dlls\*.dll x64\Debug\ /Y >nul
)

REM Copy missing zlib1.dll if it doesn't exist
if not exist "x64\Debug\zlib1.dll" (
    echo Copying zlib1.dll...
    copy "..\..\lib\SDL2_image-2.0.5\lib\x64\zlib1.dll" "x64\Debug\" /Y >nul
)

REM Change to debug directory and run the game
cd x64\Debug
echo Starting 2D Engine...
"2D Engine.exe"
pause
