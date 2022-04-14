@ECHO OFF
ECHO Building Visual Studio project files to /build directory...

cd ..
mkdir build

cd build

ECHO FOUND CMake at:
WHERE cmake
IF %ERRORLEVEL% NEQ 0 (ECHO cmake wasn't found) ELSE (cmake ..)
PAUSE



