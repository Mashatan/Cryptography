@echo off

if exist ipch rmdir /S /Q ipch
if exist build rmdir /S /Q build
if exist bin rmdir /S /Q bin
if exist .moc rmdir /S /Q .moc

if exist debug rmdir /S /Q debug
if exist release rmdir /S /Q release

if exist *.sln del /Q *.sln
if exist *.ncb del /Q *.ncb
if exist *.suo del /Q /F /A *.suo
if exist ui_*.h del /Q ui_*.h
if exist *.vcproj* del /Q *.vcproj*
if exist *.vcxproj* del /Q *.vcxproj*
if exist *.idb del /Q *.idb
if exist *.pdb del /Q *.pdb
if exist *.sdf del /Q *.sdf
if exist *.idc del /Q *.idc
if exist *.aps del /Q *.aps
