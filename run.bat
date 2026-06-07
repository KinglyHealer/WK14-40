@echo off
chcp 65001 >nul
@echo off
chcp 65001 >nul
:: Student Grade Management - One-Click Build & Run V2.0

:: Create output directory if not exists
if not exist "output" mkdir "output"

:: Compile with strict warnings
echo ========== Compiling ==========
gcc -Wall -Wextra src\main.c src\student.c -I.\include -o app.exe

:: Check compilation result
if %errorlevel% equ 0 (
    echo Compilation successful! Starting program...
    echo Program output will be saved to output\run_result.txt
    echo ==============================
    echo.
    .\app.exe
    echo.
    echo ==============================
    echo Output saved to output\run_result.txt
) else (
    echo Compilation failed! Please check your code.
    echo Make sure GCC is installed and added to PATH.
)

echo.
echo ========== Done ==========
pause
