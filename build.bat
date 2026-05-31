@echo off
echo Creating necessary folders...
if not exist bin mkdir bin
if not exist obj mkdir obj

echo.
echo Compiling C Project...
gcc src\*.c -I include -o bin\missile_guidance.exe

if %errorlevel% neq 0 (
    echo.
    echo COMPILATION FAILED.
    echo.
    pause
    exit /b
)

echo.
echo Compilation Successful!
echo.
echo Running Simulation...
echo ----------------------------------------
bin\missile_guidance.exe

echo.
echo ----------------------------------------
pause