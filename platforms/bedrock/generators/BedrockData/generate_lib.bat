@echo off
if [%1]==[] (
	set /P server_path=Enter server directory:
) else (
	set server_path=%1
)
echo %server_path%
if not exist Lib mkdir Lib
LiteLoaderSDK\Tools\LibraryBuilder.exe -o "..\..\Lib" %server_path%
