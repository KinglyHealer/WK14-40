#!/bin/bash
# student成绩管理项目一键编译运行脚本V2.0
mkdir -p output
# 带警告编译 -Wall -Wextra
gcc -Wall -Wextra src/main.c src/student.c -I./include -o app.out
if [ $? -eq 0 ];then
    echo "编译成功，开始运行程序，输出存入output/run_result.txt"
    ./app.out > output/run_result.txt
else
    echo "编译失败，请检查代码！"
fi