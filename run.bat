@echo off
chcp 65001 >nul
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