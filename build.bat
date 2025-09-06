@Rem cmake -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Debug 
@echo off
cmake --build build
if %errorlevel% neq 0 exit /b %errorlevel%
echo Running
build\bin\CPlusPlusGame.exe
