@echo off

cd ..\..\Math
call all-gen.bat
xcopy /c /f /y /d reels.txt "%~dp0"
cd "%~dp0"
start Teutoburg.exe -n 10000000 -start

