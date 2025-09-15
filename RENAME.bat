@echo off
setlocal EnableExtensions EnableDelayedExpansion

rem Run this .bat from the mod root folder (where Scripts lives)
for %%f in ("%cd%") do set "CURFOLDER=%%~nxf"

rem Strip trailing " - Copy", optional " (n)", and "-main"/"-master" from folder name
for /f "usebackq delims=" %%S in (`
  powershell -NoProfile -Command ^
    "$n=[IO.Path]::GetFileName((Resolve-Path .));" ^
    "$n=[regex]::Replace($n,' - Copy( \(\d+\))?$','', 'IgnoreCase');" ^
    "$n=[regex]::Replace($n,'-main( \(\d+\))?$','', 'IgnoreCase');" ^
    "$n=[regex]::Replace($n,'-master( \(\d+\))?$','', 'IgnoreCase');" ^
    "[Console]::Write($n)"
`) do set "CURFOLDER=%%S"

set "OLD=ZenTemplate"
set /p "NEW=New mod name: "
if not defined NEW (
  echo New name is required.
  exit /b 1
)

set "PS=%temp%\_rename_mod.ps1"
> "%PS%" echo param([string]$Root,[string]$Old,[string]$New)
>>"%PS%" echo $ErrorActionPreference = 'Stop'
>>"%PS%" echo $esc = [regex]::Escape($Old)
>>"%PS%" echo Write-Host "Root: $Root`nOld: $Old`nNew: $New`n"
rem Replace text inside common text files (add/remove extensions as you like)
>>"%PS%" echo $exts = @('*.c','*.cpp','*.h','*.hpp','*.txt','*.cfg','*.json','*.xml','*.mod.cpp','*.rvmat','*.md','*.imageset','*.meta')
>>"%PS%" echo foreach($pat in $exts){
>>"%PS%" echo   foreach($f in Get-ChildItem -Path $Root -Recurse -File -Filter $pat){
>>"%PS%" echo     try{ $t = Get-Content -LiteralPath $f.FullName -Raw -ErrorAction Stop }catch{ continue }
>>"%PS%" echo     $nt = $t -replace $esc, $New
>>"%PS%" echo     if($nt -ne $t){ [IO.File]::WriteAllText($f.FullName, $nt, [Text.UTF8Encoding]::new($false)) }
>>"%PS%" echo   }
>>"%PS%" echo }
rem Rename files that contain OLD in the name
>>"%PS%" echo Get-ChildItem -Path $Root -Recurse -File ^| Where-Object { $_.Name -match $esc } ^| ForEach-Object {
>>"%PS%" echo   Rename-Item -LiteralPath $_.FullName -NewName ($_.Name -replace $esc, $New)
>>"%PS%" echo }
rem Rename folders deepest-first
>>"%PS%" echo Get-ChildItem -Path $Root -Recurse -Directory ^| Sort-Object FullName -Descending ^| Where-Object { $_.Name -match $esc } ^| ForEach-Object {
>>"%PS%" echo   Rename-Item -LiteralPath $_.FullName -NewName ($_.Name -replace $esc, $New)
>>"%PS%" echo }

powershell -NoProfile -ExecutionPolicy Bypass -File "%PS%" "%cd%" "%OLD%" "%NEW%"

echo Done renaming files and folders.
echo.
rem Only remind if the root folder name still differs
if /I not "%CURFOLDER%"=="%NEW%" (
  echo Don't forget to rename the ROOT mod folder "%CURFOLDER%" to "%NEW%",
  echo as this .bat script cannot rename the folder it runs in.
  echo.
)
echo Subscribe to youtube.com/@Zenarchist
echo.
pause