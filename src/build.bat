@echo off
cls
echo ================================
echo Building Static Security Scanner...
echo ================================

:: Move to the script directory
cd /d "%~dp0"

:: Compile using relative paths
gcc main.c scanner.c patterns.c export.c -o analyze.exe
if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b %errorlevel%
)

echo Build succeeded!
echo.

echo ================================
echo Running Static Analyzer on ../test/
echo ================================

:: Run it with correct relative path to test/
analyze.exe ../test --summary --output json

echo.
pause
