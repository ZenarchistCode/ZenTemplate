@echo off
set /p modname=Enter your mod source folder name: 

mklink /J "GAMEDIRECTORYDayZ\%modname%" "P:\%modname%"
pause