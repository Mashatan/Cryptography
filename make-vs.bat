@echo off

rem compile 64-bit  
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" 
set PATH="c:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\x86_amd64\";%PATH% 

rem Visual Studio 2013
set QMAKESPEC=win32-msvc2013

rem Calling QMake for making Visual Studio files.
qmake -r -Wparser  -Wlogic -tp vc

