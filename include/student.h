#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdarg.h>

/* 宏定义：消除代码硬编码，统一配置参数 */
#define MAX_STU_NUM    100    // 最大学生数量
#define NAME_LEN       20     // 姓名字符串长度
#define SCORE_MIN      0      // 成绩下限
#define SCORE_MAX      100    // 成绩上限

// 函数声明
int  input_student_count(void);
void input_student_info(char names[][NAME_LEN], int scores[], int n);
void calculate_stats(int scores[], int n, int *sum, float *avg, int *max, int *min);
void sort_students(char names[][NAME_LEN], int scores[], int n);
void print_results(char names[][NAME_LEN], int scores[], int n, float avg, int max, int min);

// 日志系统：同时输出到控制台和日志文件
void log_init(void);
void log_close(void);
void tee_printf(const char *fmt, ...);

#endif