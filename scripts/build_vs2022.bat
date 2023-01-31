@echo off

set CMAKE_GENERATOR="Visual Studio 17 2022"
set ROOT_DIR=..

mkdir %ROOT_DIR%\build
cd %ROOT_DIR%\build
cmake -G %CMAKE_GENERATOR% %ROOT_DIR%

echo Solution file generated in the %ROOT_DIR%\build directory.

pause
