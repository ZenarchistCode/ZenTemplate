@echo off
setlocal EnableExtensions EnableDelayedExpansion

rem ---- WAVE 2: replace GAMEDIRECTORY and override P:\ in all .bat/.cmd ----
set "PLACE=GAMEDIRECTORY"
set "DEFAULT=C:\Program Files (x86)\Steam\steamapps\common\"
set /p "VAL=COMMON directory (Enter = %DEFAULT%): "
if not defined VAL set "VAL=%DEFAULT%"
if not "%VAL:~-1%"=="\" set "VAL=%VAL%\"

set "WORKDEF=P:\"
set /p "WORK=Work drive root for P:\ override (Enter = %WORKDEF%): "
if not defined WORK set "WORK=%WORKDEF%"
if not "%WORK:~-1%"=="\" set "WORK=%WORK%\"

rem --- normalize WORK to X:\ form ---
rem if user typed just X -> X:\
if "%WORK:~1,1%"=="" (
  set "WORK=%WORK%:\"
) else if "%WORK:~1,1%"==":" (
  rem X:    -> X:\    |   X:\Something -> keep, we’ll just ensure trailing backslash later
  if not "%WORK:~2,1%"=="\" set "WORK=%WORK%\"
) else if "%WORK:~1,1%"=="\" (
  rem X\    -> X:\    (insert missing colon)
  set "WORK=%WORK:~0,1%:%WORK:~1%"
)

rem always ensure trailing backslash
if not "%WORK:~-1%"=="\" set "WORK=%WORK%\"

set "RUNNING_BAT=%~f0"
set "PS2=%temp%\_replace_in_bats.ps1"

> "%PS2%" echo $Root    = '%cd%'
>>"%PS2%" echo $Token   = '%PLACE%'
>>"%PS2%" echo $Value   = '%VAL%'
>>"%PS2%" echo $Work    = '%WORK%'
>>"%PS2%" echo $SelfBat = '%RUNNING_BAT%'
>>"%PS2%" echo $ErrorActionPreference = 'Stop'
>>"%PS2%" echo Get-ChildItem -LiteralPath $Root -Recurse -Include *.bat,*.cmd -File ^| `
>>"%PS2%" echo   Where-Object { $_.FullName -ne $SelfBat } ^| ForEach-Object {
>>"%PS2%" echo     try { $t = [IO.File]::ReadAllText($_.FullName) } catch { continue }
>>"%PS2%" echo     if ($null -eq $t) { continue }
>>"%PS2%" echo     $nt = $t.Replace($Token, $Value)
>>"%PS2%" echo     $nt = $nt.Replace('P:\', $Work).Replace('p:\', $Work)
>>"%PS2%" echo     if ($nt -ne $t) { [IO.File]::WriteAllText($_.FullName, $nt, [Text.UTF8Encoding]::new($false)) }
>>"%PS2%" echo }

powershell -NoProfile -ExecutionPolicy Bypass -File "%PS2%"

echo Done editing batch files. You can copy them into their respective folders now.
echo.
echo Subscribe to youtube.com/@Zenarchist
echo.
pause