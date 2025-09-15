@echo off
setlocal EnableExtensions EnableDelayedExpansion

rem Where to remember the last value (next to this .bat)
set "STORE=%~dp0last_modname.txt"

rem Load previous value if it exists
if exist "%STORE%" (
    set /p LAST=<"%STORE%"
)

rem Prompt with a default if we have one
set "MODNAME="
if defined LAST (
    <nul set /p "=Enter your mod folder name [%LAST%]: "
) else (
    <nul set /p "=Enter your mod folder name: "
)
set /p MODNAME=

rem If user hit Enter, fall back to LAST
if not defined MODNAME set "MODNAME=%LAST%"

rem Abort if still empty
if not defined MODNAME (
    echo.
    echo No value provided and no previous value stored. Aborting.
    exit /b 1
)

rem Persist for next run
> "%STORE%" echo %MODNAME%

echo Using mod: "%MODNAME%"
start /D "GAMEDIRECTORYDayZ" DayZDiag_x64.exe "-mod=P:\@PackedMods\@%modname%;P:\@Dependencies\@CF;P:\@Dependencies\@VPPAdminTools;" -filePatching -server -config=serverDZ.cfg -profiles=profiles