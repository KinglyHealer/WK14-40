@echo off
chcp 65001 >nul
<<<<<<< HEAD
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
=======
mkdir output 2>nul

:: 编译程序
gcc -Wall -Wextra src/main.c src/student.c -I./include -o student.exe

:: 如果编译成功就运行
if %errorlevel% equ 0 (
    echo 编译成功，正在运行...
    student.exe > output/run_result.txt
    echo 运行完成！结果已保存到 output\run_result.txt
) else (
    echo 编译失败！
)

pause
>>>>>>> cfda5089502290bde8632f9bc179c3dc54091687
