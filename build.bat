@echo off
cls
echo Building Static Security Scanner...

:: Compiler and output config
set COMPILER=gcc
set OUTPUT=analyze.exe

:: Source files
set SOURCES=main.c scanner.c patterns.c export.c

:: Include folders (optional, if you use headers in subdirs)
:: set INCLUDES=-Iinclude

:: Build command
%COMPILER% %SOURCES% -o %OUTPUT%

:: Check if compilation was successful
if %errorlevel% neq 0 (
    echo.
    echo Build failed!
    pause
    exit /b %errorlevel%
)

echo Build succeeded!
echo Running analyzer...
echo.

:: Run analyzer on test folder (you can edit this)
.\%OUTPUT% test/ --summary --output json

echo.
pause
